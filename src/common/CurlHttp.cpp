#include "common/CurlHttp.h"
#include "curl/curl.h"

CurlHttp::CurlHttp()
{
	long	timeout = 3L;
	m_pCurl = curl_easy_init();
	curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(m_pCurl, CURLOPT_NOSIGNAL, 1L);
}

CurlHttp::~CurlHttp()
{
	curl_easy_cleanup(m_pCurl);
}

static size_t OnGetWriteData(void* buffer,size_t size,size_t nmemb,void* lpVoid)
{
	string * str=dynamic_cast<string*>((string*)lpVoid);
	if( !str )
		return -1;

	//*str+=(char*)buffer;
	size_t realsize = nmemb*size;
	str->append((char*)buffer, realsize);
	return realsize;
}

static size_t OnWriteData(void* buffer,size_t size,size_t nmemb,void* lpVoid)
{
	string * str=dynamic_cast<string*>((string*)lpVoid);
	if( !str )
		return -1;

	//*str+=(char*)buffer;
	size_t realsize = nmemb*size;
	str->append((char*)buffer, realsize);
	return realsize;
}

int  CurlHttp::HttpPost(const char* lpUrl,const char* lpData,string& strResponse)
{
	CURLcode res;
	CURL* curl=curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, lpUrl);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, lpData);
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA,(unsigned long)&strResponse);
	curl_easy_setopt(curl,CURLOPT_NOSIGNAL,1);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return res;
}

int  CurlHttp::HttpGet(const string strUrl,string& strResponse)
{
	CURLcode res;
	CURL* curl=curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,OnGetWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA,(unsigned long)&strResponse);
	curl_easy_setopt(curl,CURLOPT_NOSIGNAL,1);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return res;
}
