#pragma once

/************************************************************************/
/* @function ��libCurl�İ�װ������ģʽ                                  */
/* @author	zhangzhongqing												*/
/************************************************************************/
#include <string>
#include <map>
#include "curl/curl.h"

#ifdef UTIL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
using namespace std;

#define CURL_STR_COPY(x, y, x_size) \
	do \
	{ \
		if (x_size > strlen(y)) \
			strcpy(x, y); \
		else \
			strncpy(x, y, (x_size - 1)); \
	} \
	while (0)

class DLL_EXPORT CurlHttp
{
public:
	CurlHttp();
	virtual ~CurlHttp();

	/**
	* @function ����http��������ΪGet
	* @param	strUrl	http������ʵ�URL
	* @return	������Ӧ����
	*/
	int  HttpGet(const string strUrl,string& strResponse);

	/**
	* @function ����http��������ΪPost
	* @param	strUrl	http������ʵ�URL
	* @return	������Ӧ����
	*/
	int  HttpPost(const char* lpUrl,const char* lpData,string& strResponse);
private:
	CURL*	m_pCurl;
};
