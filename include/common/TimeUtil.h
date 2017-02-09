#ifndef _UTIL_DATETIME_H_
#define _UTIL_DATETIME_H_

#include    <cstdio>                   //  sscanf(), sprintf()    
#include    <ctime>                    //  time(), localtime(), mktime()    
#include    <string>                   //  strchr()  
#include	"string.h"

#ifdef UTIL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

using namespace std;

#define DATE_TIME_LENGTH 20


class  DLL_EXPORT TimeUtil
{
public:
	TimeUtil(){memset(m_szTime,0,sizeof(m_szTime));}
	TimeUtil(const char* st)
	{
		time_t t=ToTime_t(st);
		memset(m_szTime,0,sizeof(m_szTime));
		strcpy(m_szTime,ToDateTime(t).c_str());
	}
	TimeUtil(TimeUtil& st)
	{
		memset(m_szTime,0,sizeof(m_szTime));
		strcpy(m_szTime,st.m_szTime);
	}
	TimeUtil(time_t t);

	TimeUtil& operator =(const TimeUtil& t)
	{
		memset(m_szTime,0,sizeof(m_szTime));
		strcpy(m_szTime,t.m_szTime);
		return *this;
	}

	~TimeUtil(){}

public:
	time_t GetTime();

	const char* GetTimeString()
	{
		return (const char*)m_szTime;
	}

public:
	/**********************************************************************
	* Description  : Change standard time string(yyyy-mm-dd hh:mm:ss) to time_t
	* Return type  : time_t
	* Argument(s)  : time(YYYY-MM-DD hh:mm:ss)
	* Return Value : the seconds from 1970-00-00 00:00:00 to cpDatetime
	**********************************************************************/
	static	time_t		ToTime_t(string time);

	/* Return Value : current datetime(YYYY-MM-DD hh:mm:ss) */
	static	string		Now();

	/* Return Value :  date(YYYY-MM-DD ) */
	static	string		ToDate(time_t tSecond);

	/* Return Value :  datetime(YYYY-MM-DD hh:mm:ss) */
	static	string		ToDateTime(time_t tSecond=-1);

	/*
	 * ����format ����ʾt ��ʱ���ַ���. 
	 * ���յ�format���ͣ�
	 * "%Y-%m-%d %H:%M:%S"  ��׼��ʱ���ʱ�䴮   Y-M-D hh:mm:ss
	 * "%Y-%m-%d"	��-��-�� : Y-M-D
	 * "%H:%M:%S"	ʱ:��:�� --- hh:mm:ss
	 * "%H:%M"		Сʱ:���� --- hh:mm
	 * "%Y-%m"		��-�� : Y-M
	 * "%H:%M:00"
	 * "%H:%M:59"
	 * "%Y-%m-%d %H:%M:00"
	 * "%Y-%m-%d %H:%M:59"
	 */
	static  string      ToFormatTimeStr(string format, time_t t =0);

	/* Return Value :  �������� */
	static	int			GetDayAmount(int year, int month);

	/* Argument(s)  : t is the seconds from 1970-00-00 00:00:00 */
	static	string		GetLastDayOfMonth(time_t t = 0);
	static	string		GetLastDayOfPrevMonth(time_t t = 0);
	static	string		GetFirstDayOfMonth(time_t t = 0);
	static	string		GetLastMonthOfYear(time_t t = 0);
	static	string		GetFirstMonthOfYear(time_t t = 0);
	static	string		GetPrevDay(time_t t = 0);
	static	string		GetPrevMinute(time_t t = 0);
	static	string		GetPrevMonth(time_t t = 0);
	static	string		GetMonth(time_t t = 0);

	/*���ص�ǰʱ�����ṩ��ʱ����������*/
	static	time_t		GetTickCountBySubSeconds(time_t sub);
	
private:
	char				m_szTime[DATE_TIME_LENGTH];
};

#endif	
