import device_model
import multiprocessing
import time
from datetime import datetime
import serial
from serial import SerialException
import statistics
import json
import os
import threading
import queue

from Subsoiler import SubsoilerCalculator
from RotaryTiller import RotaryTillerCalculator
from Plough import PloughCalculator
from HeightModel import MultiToolHeightModel

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
PDA_CMD_REQ_DEPTH_ONCE = 0x10  # 请求单次耕深数据（响应一次耕深+稳定性+高度）
PDA_CMD_START_STREAM = 0x11  # 开始连续上报，未带数据则使用默认间隔1秒
PDA_CMD_STOP_STREAM = 0x12  # 停止连续上报

PDA_CMD_TOOL_TYPE = 0x21  # 机具类别
PDA_CMD_SENSOR_STATUS = 0x22  # 传感器状态
PDA_CMD_DEPTH = 0x23  # 耕深
PDA_CMD_DEPTH_STABILITY = 0x24  # 当前耕深和深度稳定性
PDA_CMD_SUSPENSION_HEIGHT = 0x25  # 三点悬挂高度

PDA_CMD_SET_TARGET_DEPTH = 0x30  # 设置目标耕深（2字节，mm）
PDA_CMD_SET_ACTUAL_HEIGHT = 0x31  # 下发实际三点悬挂高度（2字节，mm）
PDA_CMD_SET_SPEED = 0x32  # 下发车辆作业速度（2字节，0.01 km/h，即放大100倍）

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

        self.rx_queue = queue.Queue()
        self.rx_thread = None
        self.rx_stop_event = threading.Event()

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
            if self.is_open:
                self.rx_stop_event.clear()
                self.rx_thread = threading.Thread(target=self._rx_loop, daemon=True)
                self.rx_thread.start()
            return self.is_open
        except SerialException as e:
            print(f"打开RS485 PDA串口 {self.port_name} 失败: {e}")
            return False

    def close_connection(self):
        """关闭PDA串口连接"""
        self.rx_stop_event.set()
        if self.rx_thread and self.rx_thread.is_alive():
            self.rx_thread.join(timeout=1)
        if self.serial_port and self.is_open:
            self.serial_port.close()
            self.is_open = False
            print("RS485 PDA串口已关闭")

    # PDA接收线程，持续监听RS485总线上的数据并解析完整协议数据包
    def _rx_loop(self):
        buffer = bytearray()
        while not self.rx_stop_event.is_set():
            if self.serial_port and self.serial_port.in_waiting:
                data = self.serial_port.read(self.serial_port.in_waiting or 1)
                buffer.extend(data)
                # 尝试解析完整数据包（最少12字节）
                while len(buffer) >= 12:
                    # 查找设备地址和功能码
                    if buffer[0] != DEVICE_ADDR or buffer[1] != FUNC_CODE:
                        buffer.pop(0)
                        continue
                    if len(buffer) < 3:
                        break
                    data_len = buffer[3] if len(buffer) > 3 else 0
                    total_len = 2 + data_len + 2  # addr+func + data_section + crc
                    if len(buffer) < total_len:
                        break
                    packet = buffer[:total_len]
                    buffer = buffer[total_len:]
                    self._parse_packet(packet)
            else:
                time.sleep(0.01)

    def _parse_packet(self, packet):
        # 整体CRC校验
        calc_crc = get_crc(packet[:-2], len(packet) - 2)
        recv_crc = (packet[-2] << 8) | packet[-1]

        if calc_crc != recv_crc:
            return
        # 提取数据区 [Start][Len][Cmd][Data...][PDACRC][End]
        data_section = packet[2:-2]
        if data_section[0] != PDA_START_BYTE or data_section[-1] != PDA_END_BYTE:
            return
        # PDA CRC校验
        pda_crc_pos = len(data_section) - 3
        pda_calc = get_crc(data_section[:pda_crc_pos], pda_crc_pos)
        pda_recv = (data_section[pda_crc_pos] << 8) | data_section[pda_crc_pos + 1]
        if pda_calc != pda_recv:
            return
        cmd = data_section[2]
        real_data = data_section[3:pda_crc_pos]

        print(
            f"[RX] 收到指令 0x{cmd:02X}, 数据长度={len(real_data)}, 内容={real_data.hex().upper() if real_data else '无'}"
        )
        # 根据指令类型放入队列
        if cmd == PDA_CMD_REQ_DEPTH_ONCE:
            self.rx_queue.put(("req_once", None))
        elif cmd == PDA_CMD_START_STREAM:
            interval = 1.0
            if len(real_data) >= 1:
                interval = real_data[0] / 10.0
                interval = max(0.1, min(10.0, interval))
            self.rx_queue.put(("start_stream", interval))
        elif cmd == PDA_CMD_STOP_STREAM:
            self.rx_queue.put(("stop_stream", None))
        elif cmd == PDA_CMD_SET_TARGET_DEPTH:
            if len(real_data) >= 2:
                depth = (real_data[0] << 8) | real_data[1]
                # 扩展：第3字节为控制使能（0=停止，非0=启动）
                if len(real_data) >= 3:
                    enable = real_data[2] != 0
                else:
                    enable = True  # 兼容旧指令，默认启用
                self.rx_queue.put(("target_depth", (depth, enable)))
        elif cmd == PDA_CMD_SET_ACTUAL_HEIGHT:
            if len(real_data) >= 2:
                height = (real_data[0] << 8) | real_data[1]
                self.rx_queue.put(("actual_height", height))
        elif cmd == PDA_CMD_SET_SPEED:
            if len(real_data) >= 2:
                speed_raw = (real_data[0] << 8) | real_data[1]
                speed = speed_raw / 100.0
                self.rx_queue.put(("speed", speed))

    def get_command(self, block=False, timeout=None):
        try:
            return self.rx_queue.get(block=block, timeout=timeout)
        except queue.Empty:
            return None

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

        # print(f"计算耕深: {depth_value:.3f}m -> {depth_mm}mm")

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

    def send_height_data(self, height_mm):
        """
        发送三点悬挂高度数据（指令 0x25）
        :param height_mm: 高度（毫米），整数 0~65535
        """
        # 限制范围
        if height_mm < 0:
            height_mm = 0
        elif height_mm > 65535:
            height_mm = 65535
        # 转换为2字节大端序
        height_bytes = [(height_mm >> 8) & 0xFF, height_mm & 0xFF]
        pda_data = [PDA_CMD_SUSPENSION_HEIGHT] + height_bytes  # 指令 0x25
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
            log_file.write(
                "Beta(deg) | Alpha(deg) | Depth(mm) | Height(mm) | Hardness(MPa) | Speed(km/h) | SlopeX(deg) | SlopeY(deg) | Timestamp\n"
            )
        print(f"日志文件 '{log_filename}' 已创建。")
        return log_file, log_filename
    except Exception as e:
        print(f"创建日志文件失败: {e}")
        return None, None


def write_log_entry(log_file, beta, alpha, depth_mm, height_mm):
    """写入一条日志记录到已打开的日志文件对象中。"""
    if log_file is None:
        return
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
    log_file.write(
        f"{beta:.3f} | {alpha:.3f} | {depth_mm:.2f} | {height_mm:.2f} | {timestamp}\n"
    )
    log_file.flush()


def monitor_data(shared_data, pda_config, tool_config, monitor_config, device_names):
    """
    监控主函数：读取角度传感器数据，计算耕深，响应PDA指令，
    支持训练模式（模型更新）和控制模式（目标深度闭环）。
    """
    # 在子进程中创建 PDA 发送器（包含接收线程）
    pda_sender = PDASender(pda_config["port"], pda_config["baudrate"])
    if not pda_sender.open_connection():
        print("错误: 无法打开 PDA 串口，监控进程退出")
        return

    # 获取设备名称
    impl_name = device_names["implement"]
    veh_name = device_names["vehicle"]

    # 创建机具计算器
    calculator = create_calculator(tool_config["type"], tool_config["params"])

    # 创建高度自适应模型
    rls_forget = monitor_config.get("rls_forget_factor", 0.98)
    rls_delta = monitor_config.get("rls_delta", 100.0)
    rls_ridge = monitor_config.get("rls_ridge_penalty", 1e-4)
    height_model = MultiToolHeightModel(rls_forget, rls_delta, rls_ridge)

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
    sleep_interval = monitor_config.get("sleep_interval", 0.25)
    log_enabled = monitor_config.get("log_enabled", True)
    soil_hardness = monitor_config.get("soil_hardness_mpa", 2.0)
    default_speed = monitor_config.get("default_speed_kph", 5.0)

    # PI 控制参数（控制模式）
    kp = monitor_config.get("control_kp", 0.5)
    ki = monitor_config.get("control_ki", 0.05)

    # 状态变量
    initial_alpha = None
    initial_beta = None
    sensor_status_check_count = 0
    initial_status_sent = False

    # 上报控制
    streaming = False
    stream_interval = 1.0
    last_stream_time = 0

    # 控制模式相关
    target_depth_mm = None

    # 动态速度（可被PDA下发覆盖）
    current_speed_kph = default_speed

    # 日志
    log_file, _ = init_logging(log_enabled)

    # 深度历史（用于稳定性）
    depth_history = []

    # 辅助函数：发送完整上报数据（耕深+稳定性+预测高度）
    def send_full_report(depth_mm, stability, height_mm):
        pda_sender.send_depth_data(depth_mm)
        pda_sender.send_depth_stability(depth_mm, stability)
        pda_sender.send_height_data(int(height_mm))

    # 主循环
    try:
        while True:
            # print("\n" + "=" * 50)
            # print("当前所有设备的角度信息:")

            current_alpha = None
            current_beta = None
            sensor_data_available = True

            # 读取共享数据中的角度信息
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
                        # print(
                        #    f"{device_name}: AngX={ang_x:.2f}° AngY={ang_y:.2f}° AngZ={ang_z:.2f}°"
                        # )
                    elif device_name == veh_name:  # 车身角度传感器
                        current_beta = ang_y
                        if initial_beta is None:
                            initial_beta = current_beta
                            print(f"初始化 BETA_0 = {initial_beta:.2f}°")
                        # print(
                        #    f"{device_name}: AngX={ang_x:.2f}° AngY={ang_y:.2f}° AngZ={ang_z:.2f}°"
                        # )
                else:
                    print(f"{device_name}: 暂无角度数据")
                    sensor_data_available = False

            # 发送初始状态（机具类型 + 传感器状态）
            """ if not initial_status_sent and sensor_data_available:
                print("\n发送初始状态信息...")
                pda_sender.send_tool_type(pda_sender.current_tool_type)
                time.sleep(0.1)
                pda_sender.send_sensor_status(pda_sender.current_sensor_status)
                initial_status_sent = True """

            # 定期检查传感器状态
            """ sensor_status_check_count += 1
            if sensor_status_check_count >= 10:
                pda_sender.current_sensor_status = (
                    SENSOR_STATUS_NORMAL
                    if sensor_data_available
                    else SENSOR_STATUS_ERROR
                )
                pda_sender.send_sensor_status(pda_sender.current_sensor_status)
                sensor_status_check_count = 0 """

            # 计算耕深（需要初始角度和当前角度）
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
                # print(f"\n计算深度: {depth_cm:.1f} cm ({depth_mm} mm)")

                # 坡度（使用车身角度）
                slope_x = current_beta  # 横向坡度
                slope_y = current_alpha  # 纵向坡度

                # 预测悬挂高度
                predicted_height = height_model.predict(
                    tool_config["type"],
                    depth_mm,
                    soil_hardness,
                    current_speed_kph,
                    slope_x,
                    slope_y,
                )
                # print(f"预测悬挂高度: {predicted_height:.1f} mm")

                # 更新深度历史，计算稳定性
                current_time = time.time()
                depth_history.append((current_time, depth_mm))
                cutoff = current_time - window_seconds
                depth_history = [(t, d) for t, d in depth_history if t >= cutoff]
                stability = compute_stability(depth_history, min_samples)

                # ---------- 处理来自 PDA 的指令（非阻塞） ----------
                while True:
                    cmd = pda_sender.get_command(block=False)
                    if cmd is None:
                        break
                    typ, val = cmd
                    if typ == "req_once":
                        send_full_report(depth_mm, stability, predicted_height)
                        print("响应单次耕深请求")
                    elif typ == "start_stream":
                        streaming = True
                        stream_interval = val
                        last_stream_time = time.time()  # 立即发送第一包
                        print(f"开始连续上报，间隔 {stream_interval} 秒")
                    elif typ == "stop_stream":
                        streaming = False
                        print("停止连续上报")
                    elif typ == "target_depth":
                        depth, enable = val
                        if enable:
                            target_depth_mm = depth
                            print(f"控制模式启用，设置目标耕深: {target_depth_mm} mm")
                        else:
                            target_depth_mm = None
                            print("控制模式已禁用（停止控制）")
                    elif typ == "actual_height":
                        # 训练模式：用实际高度更新模型
                        height_model.update(
                            tool_config["type"],
                            depth_mm,
                            soil_hardness,
                            current_speed_kph,
                            slope_x,
                            slope_y,
                            val,
                        )
                        print(f"模型更新: 实际高度 = {val} mm")
                    elif typ == "speed":
                        current_speed_kph = val
                        print(f"作业速度更新: {current_speed_kph:.2f} km/h")

                # ---------- 控制模式：根据目标深度输出悬挂高度指令 ----------
                if target_depth_mm is not None:
                    # 输入目标耕深，模型输出所需悬挂高度
                    cmd_height = height_model.predict(
                        tool_config["type"],
                        target_depth_mm,  # 注意：这里传入目标耕深，而非当前耕深
                        soil_hardness,
                        current_speed_kph,
                        slope_x,
                        slope_y,
                    )
                    cmd_height = max(0, min(600, int(cmd_height)))
                    pda_sender.send_height_data(cmd_height)
                    print(
                        f"[控制] 目标深度={target_depth_mm}mm, 模型预测高度={cmd_height}mm"
                    )

                # ---------- 连续上报（若已开启） ----------
                if streaming and (time.time() - last_stream_time >= stream_interval):
                    send_full_report(depth_mm, stability, predicted_height)
                    last_stream_time = time.time()

                # 写入日志
                write_log_entry(
                    log_file, current_beta, current_alpha, depth_mm, predicted_height
                )

            else:
                if initial_alpha is None or initial_beta is None:
                    print("\n等待初始角度数据...")
                else:
                    print("\n无法计算深度，缺少当前角度数据")

            time.sleep(sleep_interval)

    finally:
        if log_file:
            log_file.close()
        pda_sender.close_connection()


if __name__ == "__main__":
    # 加载配置
    config = load_config(".\DepthControlProgram\config.json")

    manager = multiprocessing.Manager()
    shared_data = manager.dict()
    addr_list = [config["devices"]["implement"]["address"]]

    # 创建 PDA 发送器
    pda_config = config["devices"]["pda"]

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
        args=(shared_data, pda_config, config["tool"], config["monitor"], device_names),
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
