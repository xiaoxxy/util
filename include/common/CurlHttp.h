#pragma once

/************************************************************************/
/* @function 对libCurl的包装，单例模式                                  */
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
	* @function 发送http请求，请求为Get
	* @param	strUrl	http请求访问的URL
	* @return	返回响应报文
	*/
	int  HttpGet(const string strUrl,string& strResponse);

	/**
	* @function 发送http请求，请求为Post
	* @param	strUrl	http请求访问的URL
	* @return	返回响应报文
	*/
	int  HttpPost(const char* lpUrl,const char* lpData,string& strResponse);
private:
	CURL*	m_pCurl;
};
