import device_model
import multiprocessing
import time
from datetime import datetime
import serial
from serial import SerialException
import statistics
import json
import os

from Subsoiler import SubsoilerCalculator
from RotaryTiller import RotaryTillerCalculator
from Plough import PloughCalculator

# 机具计算器注册表
CALCULATOR_REGISTRY = {
    "subsoiler": SubsoilerCalculator,
    "rotary_tiller": RotaryTillerCalculator,
    "plough": PloughCalculator,
}

# 完整协议相关常量
DEVICE_ADDR = 0x50  # 设备地址
FUNC_CODE = 0x06  # 功能码
PDA_START_BYTE = 0xA5  # PDA起始标 志
PDA_END_BYTE = 0xAA  # PDA结束标志

# PDA指令定义
PDA_CMD_TOOL_TYPE = 0x21  # 机具类别
PDA_CMD_SENSOR_STATUS = 0x22  # 传感器状态
PDA_CMD_DEPTH = 0x23  # 耕深
PDA_CMD_DEPTH_STABILITY = 0x24  # 当前耕深和深度稳定性

# 机具类型定义
TOOL_TYPE_ROTARY_TILLER = 0x01  # 旋耕机
TOOL_TYPE_SUBSOILER = 0x02  # 深松机
TOOL_TYPE_PLOUGH = 0x03  # 翻转犁

INIT_ANGLE = 82.2

# 传感器状态定义
SENSOR_STATUS_NORMAL = 0x01  # 正常工作
SENSOR_STATUS_ERROR = 0x02  # 工作异常


# CRC16表格（与device_model中相同）
auchCRCHi = [
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x01,
    0xC0,
    0x80,
    0x41,
    0x00,
    0xC1,
    0x81,
    0x40,
]

auchCRCLo = [
    0x00,
    0xC0,
    0xC1,
    0x01,
    0xC3,
    0x03,
    0x02,
    0xC2,
    0xC6,
    0x06,
    0x07,
    0xC7,
    0x05,
    0xC5,
    0xC4,
    0x04,
    0xCC,
    0x0C,
    0x0D,
    0xCD,
    0x0F,
    0xCF,
    0xCE,
    0x0E,
    0x0A,
    0xCA,
    0xCB,
    0x0B,
    0xC9,
    0x09,
    0x08,
    0xC8,
    0xD8,
    0x18,
    0x19,
    0xD9,
    0x1B,
    0xDB,
    0xDA,
    0x1A,
    0x1E,
    0xDE,
    0xDF,
    0x1F,
    0xDD,
    0x1D,
    0x1C,
    0xDC,
    0x14,
    0xD4,
    0xD5,
    0x15,
    0xD7,
    0x17,
    0x16,
    0xD6,
    0xD2,
    0x12,
    0x13,
    0xD3,
    0x11,
    0xD1,
    0xD0,
    0x10,
    0xF0,
    0x30,
    0x31,
    0xF1,
    0x33,
    0xF3,
    0xF2,
    0x32,
    0x36,
    0xF6,
    0xF7,
    0x37,
    0xF5,
    0x35,
    0x34,
    0xF4,
    0x3C,
    0xFC,
    0xFD,
    0x3D,
    0xFF,
    0x3F,
    0x3E,
    0xFE,
    0xFA,
    0x3A,
    0x3B,
    0xFB,
    0x39,
    0xF9,
    0xF8,
    0x38,
    0x28,
    0xE8,
    0xE9,
    0x29,
    0xEB,
    0x2B,
    0x2A,
    0xEA,
    0xEE,
    0x2E,
    0x2F,
    0xEF,
    0x2D,
    0xED,
    0xEC,
    0x2C,
    0xE4,
    0x24,
    0x25,
    0xE5,
    0x27,
    0xE7,
    0xE6,
    0x26,
    0x22,
    0xE2,
    0xE3,
    0x23,
    0xE1,
    0x21,
    0x20,
    0xE0,
    0xA0,
    0x60,
    0x61,
    0xA1,
    0x63,
    0xA3,
    0xA2,
    0x62,
    0x66,
    0xA6,
    0xA7,
    0x67,
    0xA5,
    0x65,
    0x64,
    0xA4,
    0x6C,
    0xAC,
    0xAD,
    0x6D,
    0xAF,
    0x6F,
    0x6E,
    0xAE,
    0xAA,
    0x6A,
    0x6B,
    0xAB,
    0x69,
    0xA9,
    0xA8,
    0x68,
    0x78,
    0xB8,
    0xB9,
    0x79,
    0xBB,
    0x7B,
    0x7A,
    0xBA,
    0xBE,
    0x7E,
    0x7F,
    0xBF,
    0x7D,
    0xBD,
    0xBC,
    0x7C,
    0xB4,
    0x74,
    0x75,
    0xB5,
    0x77,
    0xB7,
    0xB6,
    0x76,
    0x72,
    0xB2,
    0xB3,
    0x73,
    0xB1,
    0x71,
    0x70,
    0xB0,
    0x50,
    0x90,
    0x91,
    0x51,
    0x93,
    0x53,
    0x52,
    0x92,
    0x96,
    0x56,
    0x57,
    0x97,
    0x55,
    0x95,
    0x94,
    0x54,
    0x9C,
    0x5C,
    0x5D,
    0x9D,
    0x5F,
    0x9F,
    0x9E,
    0x5E,
    0x5A,
    0x9A,
    0x9B,
    0x5B,
    0x99,
    0x59,
    0x58,
    0x98,
    0x88,
    0x48,
    0x49,
    0x89,
    0x4B,
    0x8B,
    0x8A,
    0x4A,
    0x4E,
    0x8E,
    0x8F,
    0x4F,
    0x8D,
    0x4D,
    0x4C,
    0x8C,
    0x44,
    0x84,
    0x85,
    0x45,
    0x87,
    0x47,
    0x46,
    0x86,
    0x82,
    0x42,
    0x43,
    0x83,
    0x41,
    0x81,
    0x80,
    0x40,
]


def get_crc(datas, dlen):
    """计算CRC16校验值"""
    tempH = 0xFF  # 高 CRC 字节初始化
    tempL = 0xFF  # 低 CRC 字节初始化
    for i in range(0, dlen):
        tempIndex = (tempH ^ datas[i]) & 0xFF
        tempH = (tempL ^ auchCRCHi[tempIndex]) & 0xFF
        tempL = auchCRCLo[tempIndex]
    return (tempH << 8) | tempL


def load_config(config_path="config.json"):
    """加载配置文件"""
    if not os.path.exists(config_path):
        raise FileNotFoundError(f"配置文件 {config_path} 不存在")
    with open(config_path, "r", encoding="utf-8") as f:
        return json.load(f)


def create_calculator(tool_type, tool_params):
    """工厂方法：根据机具类型创建对应的计算器实例"""
    if tool_type not in CALCULATOR_REGISTRY:
        raise ValueError(f"不支持的机具类型: {tool_type}")
    calculator_class = CALCULATOR_REGISTRY[tool_type]
    return calculator_class(**tool_params)


class PDASender:
    """PDA数据发送器（完整协议）"""

    def __init__(self, port_name, baud_rate=9600):
        self.port_name = port_name
        self.baud_rate = baud_rate
        self.serial_port = None
        self.is_open = False

        # 当前状态
        self.current_tool_type = TOOL_TYPE_ROTARY_TILLER  # 默认旋耕机
        self.current_sensor_status = SENSOR_STATUS_NORMAL  # 默认正常工作

    def open_connection(self):
        """打开PDA串口连接（RS485）"""
        try:
            self.serial_port = serial.Serial(
                port=self.port_name,
                baudrate=self.baud_rate,
                bytesize=serial.EIGHTBITS,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                timeout=1,
                write_timeout=1,
            )

            self.is_open = True
            print(f"RS485 PDA串口 {self.port_name} 已打开，波特率: {self.baud_rate}")
            return True
        except SerialException as e:
            print(f"打开RS485 PDA串口 {self.port_name} 失败: {e}")
            return False

    def close_connection(self):
        """关闭PDA串口连接"""
        if self.serial_port and self.is_open:
            self.serial_port.close()
            self.is_open = False
            print("RS485 PDA串口已关闭")

    def build_complete_packet(self, pda_data_bytes):
        """
        构建完整协议数据包
        格式: [设备地址(1)] + [功能码(1)] + [数据区(N)] + [CRC校验(2)]
        其中数据区 = [起始标志(1)] + [数据区长度(1)] + [指令(1)] + [真实数据(n)] + [CRC校验位(2)] + [结束标志(1)]
        """
        # 构建数据区部分（不包括CRC和End）
        data_section = [
            PDA_START_BYTE,  # 起始标志 (0xA5)
            0x00,  # 数据区长度 (先填0，后面计算)
        ] + pda_data_bytes  # PDA数据部分

        # 计算数据区长度（从起始标志到结束标志的所有字节数）
        # 数据区长度 = 起始标志 + 数据区长度字节 + PDA数据 + PDA CRC + 结束标志
        data_section_length = (
            len(data_section) + 3
        )  # +3 是因为要加上PDA CRC(2)和结束标志(1)
        data_section[1] = data_section_length

        # 计算PDA CRC（对数据区从起始标志到真实数据结束的部分进行计算）
        pda_crc = get_crc(data_section, len(data_section))
        pda_crc_high = (pda_crc >> 8) & 0xFF
        pda_crc_low = pda_crc & 0xFF

        # 完整数据区
        complete_data_section = data_section + [pda_crc_high, pda_crc_low, PDA_END_BYTE]

        # 构建完整协议（设备地址 + 功能码 + 数据区）
        complete_packet = [
            DEVICE_ADDR,  # 设备地址 (0x50)
            FUNC_CODE,  # 功能码 (0x06)
        ] + complete_data_section

        # 计算完整协议的CRC（对设备地址到数据区结束的部分进行计算）
        complete_crc = get_crc(complete_packet, len(complete_packet))
        complete_crc_high = (complete_crc >> 8) & 0xFF
        complete_crc_low = complete_crc & 0xFF

        # 完整协议数据包
        full_packet = complete_packet + [complete_crc_high, complete_crc_low]

        return bytes(full_packet)

    def send_complete_packet(self, packet):
        """发送完整协议数据包到RS485总线"""
        if not self.is_open or not self.serial_port:
            print("RS485 PDA串口未打开，无法发送数据")
            return False

        try:
            # 发送数据
            bytes_written = self.serial_port.write(packet)

            # 强制刷新输出缓冲区，确保数据立即发送
            self.serial_port.flush()

            print(
                f"已通过RS485发送完整协议数据包 ({bytes_written} 字节): {packet.hex().upper()}"
            )
            return True

        except Exception as e:
            print(f"通过RS485发送完整协议数据失败: {e}")
            return False

    def send_tool_type(self, tool_type):
        """发送机具类别（完整协议）"""
        # PDA数据部分 = [指令(1)] + [真实数据(1)]
        pda_data = [PDA_CMD_TOOL_TYPE, tool_type]
        packet = self.build_complete_packet(pda_data)
        return self.send_complete_packet(packet)

    def send_sensor_status(self, status):
        """发送传感器状态（完整协议）"""
        # PDA数据部分 = [指令(1)] + [真实数据(1)]
        pda_data = [PDA_CMD_SENSOR_STATUS, status]
        packet = self.build_complete_packet(pda_data)
        return self.send_complete_packet(packet)

    def send_depth_data(self, depth_value):
        """
        发送耕深数据（完整协议）
        depth_value: 原始深度值（厘米）
        """
        # 将深度值扩大1000倍并取整数部分（转换为毫米的整数）
        depth_mm = int(depth_value * 10)

        # 确保深度值在合理范围内（0-65535毫米）
        if depth_mm < 0:
            depth_mm = 0
        elif depth_mm > 65535:
            depth_mm = 65535

        print(f"计算耕深: {depth_value:.3f}m -> {depth_mm}mm")

        # 将深度值转换为2字节（大端序）
        depth_bytes = [(depth_mm >> 8) & 0xFF, depth_mm & 0xFF]

        # PDA数据部分 = [指令(1)] + [真实数据(2)]
        pda_data = [PDA_CMD_DEPTH] + depth_bytes

        # 构建完整协议数据包并发送
        packet = self.build_complete_packet(pda_data)
        return self.send_complete_packet(packet)

    def send_depth_stability(self, depth_mm, stability_percent):
        """
        发送当前耕深和深度稳定性（指令 0x24）
        :param depth_mm: 耕深（毫米），整数 0~65535
        :param stability_percent: 稳定性百分比，整数 0~100
        """
        # 耕深转2字节大端序
        depth_bytes = [(depth_mm >> 8) & 0xFF, depth_mm & 0xFF]
        # 稳定性单字节
        stability_byte = stability_percent & 0xFF
        # PDA数据部分：指令 + 耕深(2) + 稳定性(1)
        pda_data = [PDA_CMD_DEPTH_STABILITY] + depth_bytes + [stability_byte]
        packet = self.build_complete_packet(pda_data)
        return self.send_complete_packet(packet)

    def print_packet_details(self, packet, command, data_bytes):
        """打印完整协议数据包详细信息"""
        print("\n完整协议数据包详细解析:")
        print("=" * 60)

        # 解析完整协议
        print("完整协议结构:")
        print(f"  设备地址: 0x{packet[0]:02X} (50)")
        print(f"  功能码: 0x{packet[1]:02X} (06)")

        # 解析数据区
        print("  数据区:")
        print(f"    起始标志: 0x{packet[2]:02X} (A5)")
        print(f"    数据区长度: 0x{packet[3]:02X} ({packet[3]} 字节)")
        print(f"    指令: 0x{packet[4]:02X}", end="")

        # 指令说明
        if command == PDA_CMD_TOOL_TYPE:
            print(" (21 - 机具类别)")
            tool_type = data_bytes[0]
            if tool_type == TOOL_TYPE_ROTARY_TILLER:
                print(f"      机具类型: 0x{tool_type:02X} (旋耕机)")
            elif tool_type == TOOL_TYPE_SUBSOILER:
                print(f"      机具类型: 0x{tool_type:02X} (深松机)")
            print(f"    PDA CRC: 0x{packet[6]:02X} 0x{packet[7]:02X}")
            print(f"    结束标志: 0x{packet[8]:02X} (AA)")
            print(f"  完整协议 CRC: 0x{packet[9]:02X} 0x{packet[10]:02X}")

        elif command == PDA_CMD_SENSOR_STATUS:
            print(" (22 - 传感器状态)")
            status = data_bytes[0]
            if status == SENSOR_STATUS_NORMAL:
                print(f"      传感器状态: 0x{status:02X} (正常工作)")
            elif status == SENSOR_STATUS_ERROR:
                print(f"      传感器状态: 0x{status:02X} (工作异常)")
            print(f"    PDA CRC: 0x{packet[6]:02X} 0x{packet[7]:02X}")
            print(f"    结束标志: 0x{packet[8]:02X} (AA)")
            print(f"  完整协议 CRC: 0x{packet[9]:02X} 0x{packet[10]:02X}")

        elif command == PDA_CMD_DEPTH:
            print(" (23 - 耕深)")
            depth_mm = (data_bytes[0] << 8) | data_bytes[1]
            print(
                f"      耕深值: {depth_mm}mm (0x{data_bytes[0]:02X} 0x{data_bytes[1]:02X})"
            )
            print(f"    PDA CRC: 0x{packet[7]:02X} 0x{packet[8]:02X}")
            print(f"    结束标志: 0x{packet[9]:02X} (AA)")
            print(f"  完整协议 CRC: 0x{packet[10]:02X} 0x{packet[11]:02X}")

        print(f"完整数据包: {packet.hex().upper()}")
        print("=" * 60)


def updateData(DeviceModel, shared_data):
    # 将设备数据更新到共享字典中
    shared_data[DeviceModel.deviceName] = DeviceModel.deviceData


def run_device(device_name, port, baud_rate, addr_list, shared_data):
    def device_callback(device):
        updateData(device, shared_data)

    device = device_model.DeviceModel(
        device_name, port, baud_rate, addr_list, device_callback
    )
    device.openDevice()
    device.startLoopRead()


def compute_stability(depth_history, min_samples=3):
    """
    根据深度历史列表计算稳定性百分比。
    depth_history: list of (timestamp, depth_mm)
    min_samples: 最少样本数
    返回: stability (int, 0~100)
    """
    if len(depth_history) < min_samples:
        return 100

    depths = [d for _, d in depth_history]

    # IQR 异常剔除
    sorted_depths = sorted(depths)
    n = len(sorted_depths)
    q1 = sorted_depths[int(0.25 * n)]
    q3 = sorted_depths[int(0.75 * n)]
    iqr = q3 - q1
    lower = q1 - 1.5 * iqr
    upper = q3 + 1.5 * iqr
    filtered = [d for d in depths if lower <= d <= upper]

    # 若剔除后样本太少，回退至原始数据
    if len(filtered) < min_samples:
        filtered = depths

    # 稳健统计：中位数和 MAD
    median = statistics.median(filtered)
    deviations = [abs(d - median) for d in filtered]
    mad = statistics.median(deviations)
    std_robust = 1.4826 * mad if mad > 0 else 0.0

    if median > 0:
        cv_robust = std_robust / median
        stability = max(0, min(100, 100 - cv_robust * 100))
    else:
        stability = 100.0

    return int(stability)


def init_logging(log_enabled):
    """
    初始化日志文件。
    返回: (log_file, log_filename) 或 (None, None) 当禁用或失败时。
    """
    if not log_enabled:
        return None, None
    log_filename = f"data-{datetime.now().strftime('%Y-%m-%d_%H-%M-%S')}.txt"
    try:
        log_file = open(log_filename, "a", encoding="utf-8")
        if os.path.getsize(log_filename) == 0:
            log_file.write("Beta_车身(deg) | Alpha_机具(deg) | Depth(mm) | Timestamp\n")
        print(f"日志文件 '{log_filename}' 已创建。")
        return log_file, log_filename
    except Exception as e:
        print(f"创建日志文件失败: {e}")
        return None, None


def write_log_entry(log_file, beta, alpha, depth_mm):
    """写入一条日志记录到已打开的日志文件对象中。"""
    if log_file is None:
        return
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
    log_file.write(f"{beta:.3f} | {alpha:.3f} | {depth_mm:.2f} | {timestamp}\n")
    log_file.flush()


def monitor_data(shared_data, pda_sender, tool_config, monitor_config, device_names):
    """
    tool_config: 包含 "type" 和 "params" 的字典
    monitor_config: 监控参数，如 window_seconds, min_samples, send_interval 等
    device_names: 包含 'implement' 和 'vehicle' 设备名称的字典
    """
    # 获取设备名称
    impl_name = device_names["implement"]
    veh_name = device_names["vehicle"]

    # 创建机具计算器
    calculator = create_calculator(tool_config["type"], tool_config["params"])

    # 设置 PDA 发送器的机具类型
    tool_type_map = {
        "subsoiler": TOOL_TYPE_SUBSOILER,
        "rotary_tiller": TOOL_TYPE_ROTARY_TILLER,
        "plough": TOOL_TYPE_PLOUGH,
    }
    pda_sender.current_tool_type = tool_type_map.get(
        tool_config["type"], TOOL_TYPE_SUBSOILER
    )

    # 从配置中读取监控参数
    window_seconds = monitor_config.get("window_seconds", 10.0)
    min_samples = monitor_config.get("min_samples", 3)
    send_interval = monitor_config.get("send_interval", 5)
    sleep_interval = monitor_config.get("sleep_interval", 0.25)
    log_enabled = monitor_config.get("log_enabled", True)

    # 参考角度初始值
    initial_alpha = None
    initial_beta = None
    sensor_status_check_count = 0
    initial_status_sent = False

    # 日志文件（保持句柄）
    # log_file, _ = init_logging(log_enabled)

    depth_history = []
    send_counter = 0

    try:
        while True:
            print("\n" + "=" * 50)
            print("当前所有设备的角度信息:")

            current_alpha = None
            current_beta = None
            sensor_data_available = True

            for device_name, data in shared_data.items():
                if (
                    data
                    and 0x50 in data
                    and "AngX" in data[0x50]
                    and "AngY" in data[0x50]
                    and "AngZ" in data[0x50]
                ):
                    ang_x = data[0x50]["AngX"]
                    ang_y = data[0x50]["AngY"]
                    ang_z = data[0x50]["AngZ"]
                    if device_name == impl_name:  # 机具角度传感器
                        current_alpha = ang_y
                        if initial_alpha is None:
                            initial_alpha = current_alpha
                            print(f"初始化 ALPHA_0 = {initial_alpha:.2f}°")
                        print(
                            f"{device_name}: AngX={ang_x:.2f}° AngY={ang_y:.2f}° AngZ={ang_z:.2f}° "
                            # f"{device_name}: AngY={ang_x:.2f}° (相对初始: {ang_x - initial_alpha:.2f}°)"
                        )
                    elif device_name == veh_name:  # 车身角度传感器
                        current_beta = ang_y
                        if initial_beta is None:
                            initial_beta = current_beta
                            print(f"初始化 BETA_0 = {initial_beta:.2f}°")
                        print(
                            f"{device_name}: AngX={ang_x:.2f}° AngY={ang_y:.2f}° AngZ={ang_z:.2f}° "
                            # f"{device_name}: AngY={ang_x:.2f}° (相对初始: {ang_x - initial_beta:.2f}°)"
                        )
                else:
                    print(f"{device_name}: 暂无角度数据")
                    sensor_data_available = False

            # 发送初始状态
            if not initial_status_sent and sensor_data_available:
                print("\n发送初始状态信息...")
                pda_sender.send_tool_type(pda_sender.current_tool_type)
                time.sleep(0.1)
                pda_sender.send_sensor_status(pda_sender.current_sensor_status)
                initial_status_sent = True

            # 定期检查传感器状态
            sensor_status_check_count += 1
            if sensor_status_check_count >= 10:
                pda_sender.current_sensor_status = (
                    SENSOR_STATUS_NORMAL
                    if sensor_data_available
                    else SENSOR_STATUS_ERROR
                )
                pda_sender.send_sensor_status(pda_sender.current_sensor_status)
                sensor_status_check_count = 0

            # 计算耕深
            can_calculate = (
                current_alpha is not None
                and current_beta is not None
                and initial_alpha is not None
                and initial_beta is not None
            )
            if can_calculate:
                depth_mm = calculator.calculate(
                    alpha=current_alpha,
                    beta=current_beta,
                    alpha0=initial_alpha,
                    beta0=initial_beta,
                )
                depth_cm = depth_mm / 10.0
                print(f"\n计算深度: {depth_cm:.1f} cm ({depth_mm} mm)")

                # 更新深度历史
                current_time = time.time()
                depth_history.append((current_time, depth_mm))
                cutoff = current_time - window_seconds
                depth_history = [(t, d) for t, d in depth_history if t >= cutoff]

                # 稳定性计算
                stability = compute_stability(depth_history, min_samples)

                # 发送数据
                send_counter += 1
                if send_counter % send_interval == 0:
                    pda_sender.send_depth_data(depth_mm)
                    pda_sender.send_depth_stability(depth_mm, stability)

                # 写入日志（使用保持的文件句柄）
                # write_log_entry(log_file, current_beta, current_alpha, depth_mm)
            else:
                if initial_alpha is None or initial_beta is None:
                    print("\n等待初始角度数据...")
                else:
                    print("\n无法计算深度，缺少当前角度数据")

            time.sleep(sleep_interval)
    finally:
        if log_file:
            log_file.close()


if __name__ == "__main__":
    # 加载配置
    config = load_config("config.json")

    manager = multiprocessing.Manager()
    shared_data = manager.dict()
    addr_list = [config["devices"]["implement"]["address"]]

    # 创建 PDA 发送器
    pda_config = config["devices"]["pda"]
    pda_sender = PDASender(pda_config["port"], pda_config["baudrate"])
    if not pda_sender.open_connection():
        print("警告: 无法打开 PDA RS485 连接")

    # 启动机具角度设备进程
    impl_config = config["devices"]["implement"]
    process_impl = multiprocessing.Process(
        target=run_device,
        args=(
            impl_config["name"],
            impl_config["port"],
            impl_config["baudrate"],
            addr_list,
            shared_data,
        ),
    )

    # 启动车身角度设备进程
    veh_config = config["devices"]["vehicle"]
    process_veh = multiprocessing.Process(
        target=run_device,
        args=(
            veh_config["name"],
            veh_config["port"],
            veh_config["baudrate"],
            addr_list,
            shared_data,
        ),
    )

    # 构造设备名称映射
    device_names = {"implement": impl_config["name"], "vehicle": veh_config["name"]}

    # 创建监控进程，传入 device_names
    monitor_process = multiprocessing.Process(
        target=monitor_data,
        args=(shared_data, pda_sender, config["tool"], config["monitor"], device_names),
    )

    process_impl.start()
    process_veh.start()
    monitor_process.start()

    try:
        process_impl.join()
        process_veh.join()
        monitor_process.join()
    except KeyboardInterrupt:
        print("\n程序被用户中断")
    finally:
        pda_sender.close_connection()
