/**
 * 输入一个日期 startdate和天数 days， 输出自该输入日期days天后的日期enddate(即 enddate = startdate + days)。
 * 要求输入和输出的年份为四位整数, 输入时要对输入数据的有效性进行检查，并确保得到有效的输入数据。同时需要考虑
 * 跨月，跨年和闰年等情况，闰年用自定义函数计算，日期用自定义结构体描述
 */

#include <iostream>
using namespace std;
typedef struct date
{
    int year;
    int month;
    int day;
} Date;

int leapMonth[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int formatMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return true;
    }
    return false;
}

Date addDays(Date startDate, int days, int *month)
{
    if (days <= 0)
    {
        return startDate;
    }

    if (days > month[startDate.month])
    {
        days = days - month[startDate.month];
        startDate.month++;
    }
    else
    {
        startDate.day += days;
        days = 0;
    }
    if (startDate.month > 12)
    {
        startDate.month = startDate.month - 12;
        startDate.year++;
    }
    return addDays(startDate, days, month);
}

Date calcEndDate(Date startDate, int days)
{
    if (days <= 0)
    {
        return startDate;
    }
    if (isLeapYear(startDate.year))
    {
        return addDays(startDate, days, leapMonth);
    }
    else
    {
        return addDays(startDate, days, formatMonth);
    }
}

int main()
{
    Date startDate;
    int days;
    printf("please input year month day\n");
    scanf("%d%d%d", &startDate.year, &startDate.month, &startDate.day);
    printf("please input last days\n");
    scanf("%d", &days);
    Date endDate = calcEndDate(startDate, days);
    printf("%d-%d-%d", endDate.year, endDate.month, endDate.day);
    return 0;
}