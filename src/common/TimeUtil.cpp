#include "common/TimeUtil.h"
#include "string.h"

using namespace std;


TimeUtil::TimeUtil(time_t t)
{
	memset(m_szTime,0,sizeof(m_szTime));
	strcpy(m_szTime,ToDateTime(t).c_str());
}

time_t TimeUtil::GetTime()
{
	return ToTime_t((const char*)m_szTime);
}


time_t TimeUtil::ToTime_t(string time)   
{   
	if(time.empty())
		return -1;

	struct tm tmVar;
	memset(&tmVar,0,sizeof(tm));

	const char *strVar = time.c_str();
	time_t timeVar;

	if(sscanf(strVar,"%d-%d-%d %d:%d:%d", &tmVar.tm_year, &tmVar.tm_mon, &tmVar.tm_mday, &tmVar.tm_hour, &tmVar.tm_min, &tmVar.tm_sec) == 6)
	{
		tmVar.tm_year -= 1900;
		tmVar.tm_mon -= 1;
		timeVar = mktime(&tmVar);
	}
	else // bad format
		return -1;

	return timeVar;
}


string TimeUtil::Now()
{
	return ToDateTime(time(NULL));
}

string TimeUtil::ToDateTime(time_t tSecond)   
{
	if( tSecond == -1 )
		return "1900-01-01 00:00:00";

	char szDateTime[DATE_TIME_LENGTH]={0};
	struct tm* ptmTime = localtime(&tSecond);

	sprintf(szDateTime, "%04d-%02d-%02d %02d:%02d:%02d",
		ptmTime->tm_year + 1900,
		ptmTime->tm_mon + 1,
		ptmTime->tm_mday,
		ptmTime->tm_hour,
		ptmTime->tm_min,
		ptmTime->tm_sec);

	return szDateTime;
}

string TimeUtil::ToDate(time_t tSecond)   
{
	if( tSecond==-1 )
		return "1900-01-01";

	char szDate[64]={0};
	struct tm* ptmTime = localtime(&tSecond);

	sprintf(szDate, "%04d-%02d-%02d",
		ptmTime->tm_year + 1900,
		ptmTime->tm_mon + 1,
		ptmTime->tm_mday);

	return szDate;
}

int TimeUtil::GetDayAmount(int year,int month)
{
	if(month==2)
	{
		if((year%4==0 && year%100!=0) || (year%400==0))
			return 29;
		else
			return 28;
	}
	else if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
		return 31;

	return 30;
}

/*
 * 依据format 来显示t 的时间字符串. 
 * 接收的format类型：
 * "%Y-%m-%d %H:%M:%S"  标准的时间的时间串   Y-M-D hh:mm:ss
 * "%Y-%m-%d" 年-月-日 : Y-M-D
 * "%H:%M:%S" 时:分:秒 --- hh:mm:ss
 * "%H:%M" 小时:分钟 --- hh:mm
 * "%Y-%m" 年-月 : Y-M
 * "%H:%M:00"
 * "%H:%M:59"
 * "%Y-%m-%d %H:%M:00"
 * "%Y-%m-%d %H:%M:59"
 */
string  TimeUtil::ToFormatTimeStr(string format, time_t t)
{
	if( t==0 )t = time(NULL);
	struct tm* t_tm = localtime(&t);
	char sysTime[ DATE_TIME_LENGTH ] = { 0, };
	strftime(sysTime, sizeof(sysTime), format.c_str(), t_tm);
	return sysTime;
}


string TimeUtil::GetFirstDayOfMonth(time_t t)
{
	if (t == 0)t = time(NULL);
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };
	sprintf(sysTime, "%04d-%02d-%02d", t_tm->tm_year + 1900, t_tm->tm_mon + 1, 1);
	return sysTime;
}

string TimeUtil::GetLastDayOfMonth(time_t t)
{
	if (t == 0)t = time(NULL);
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };

	sprintf(sysTime, "%04d-%02d-%02d", t_tm->tm_year + 1900, t_tm->tm_mon + 1, GetDayAmount(t_tm->tm_year + 1900, t_tm->tm_mon + 1));
	return sysTime;
}

string TimeUtil::GetLastDayOfPrevMonth(time_t t)
{
	if (t == 0)t = time(NULL);
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };

	if (t_tm->tm_mon != 0)
		sprintf(sysTime, "%04d-%02d-%02d", t_tm->tm_year + 1900, t_tm->tm_mon, GetDayAmount(t_tm->tm_year + 1900, t_tm->tm_mon));
	else
		sprintf(sysTime, "%04d-%02d-%02d", t_tm->tm_year + 1899, 12, 31);

	return sysTime;
}

string	TimeUtil::GetPrevDay(time_t t)
{
	if (t == 0) t = time(NULL);
	t -= 86400;
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };
	sprintf(sysTime, "%04d-%02d-%02d", t_tm->tm_year + 1900, t_tm->tm_mon + 1, t_tm->tm_mday);
	return sysTime;
}

string	TimeUtil::GetPrevMinute(time_t t)
{
	if (t == 0) t = time(NULL);
	t -= 60;
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };
	sprintf(sysTime, "%04d-%02d-%02d %02d:%02d:%02d", t_tm->tm_year + 1900, t_tm->tm_mon + 1, t_tm->tm_mday, t_tm->tm_hour, t_tm->tm_min, t_tm->tm_sec);
	return sysTime;
}

string	TimeUtil::GetLastMonthOfYear(time_t t)
{
	if (t == 0)t = time(NULL);
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };
	sprintf(sysTime, "%04d-%02d-31", t_tm->tm_year + 1900, 12);
	return sysTime;
}

string	TimeUtil::GetFirstMonthOfYear(time_t t)
{
	if (t == 0) t = time(NULL);
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };
	sprintf(sysTime, "%04d-%02d-01", t_tm->tm_year + 1900, 1);
	return sysTime;
}

string  TimeUtil::GetPrevMonth(time_t t)
{
	if (t == 0) t = time(NULL);
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };
	if (t_tm->tm_mon != 0)
		sprintf(sysTime, "%04d-%02d", t_tm->tm_year + 1900, t_tm->tm_mon);
	else
		sprintf(sysTime, "%04d-%02d", t_tm->tm_year + 1899, 12);
	return sysTime;
}

string	TimeUtil::GetMonth(time_t t)
{
	if (t == 0) t = time(NULL);
	struct tm* t_tm;
	t_tm = localtime(&t);
	char sysTime[20] = { 0, };

	sprintf(sysTime, "%04d-%02d", t_tm->tm_year + 1900, t_tm->tm_mon + 1);
	return sysTime;
}

time_t TimeUtil::GetTickCountBySubSeconds(time_t sub)
{
	time_t now_time = time(NULL);
	return now_time - sub;
}

