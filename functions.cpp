#include <curl/curl.h>
#include "functions.h"
#include "json/json.h"
#include <string>

std::string result;
CURL* curl;
std::string userid;
std::string user;


size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* output) {
	size_t totalSize = size * nmemb;
	output->append(contents, totalSize);
	return totalSize;
}

LPCWSTR CharToLPCWSTR(const char* input) {
	int wideCharLength = MultiByteToWideChar(CP_UTF8, 0, input, -1, NULL, 0); // »ñÈ¡×ª»»ºóµÄ¿í×Ö·û×Ö·û´®µÄ³¤¶È
	wchar_t* wideCharString = new wchar_t[wideCharLength]; // ¸ù¾Ý³¤¶È´´½¨¿í×Ö·û×Ö·û´®µÄ»º³åÇø
	MultiByteToWideChar(CP_UTF8, 0, input, -1, wideCharString, wideCharLength); // ½«char×Ö·û´®×ª»»Îª¿í×Ö·û×Ö·û´®
	return wideCharString; // ·µ»Ø¿í×Ö·û×Ö·û´®Ö¸Õë
}

int GetID() {
	//MessageBox(NULL, (LPCWSTR)L"test", (LPCWSTR)L"test", MB_OK);
	//initcurl();
	result = "";

	short err = curl_easy_perform(curl);

	if (err == CURLE_OK) {
		//MessageBox(NULL, CharToLPCWSTR(result.c_str()), (LPCWSTR)L"result", MB_OK);
	} else {
		MessageBox(NULL, (LPCWSTR)L"Fail to excute ID", (LPCWSTR)L"ERROR", MB_OK);
	}

	Json::Value root;
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	std::string Serr;
	bool success = reader->parse(result.c_str(), result.c_str() + result.size(), &root, &Serr);

	user = root["user"].asString();
	userid = root["userid"].asString();

	//MessageBox(NULL, CharToLPCWSTR(user.c_str()), (LPCWSTR)L"res", MB_OK);
	//MessageBox(NULL, CharToLPCWSTR(userid.c_str()), (LPCWSTR)L"res", MB_OK);

	return 0;
}

void initcurl() {
	curl = curl_easy_init();

	if (!curl)
		MessageBox(NULL, (LPCWSTR)L"ERROR on function curl_easy_init()", (LPCWSTR)L"error", MB_OK);
	else
		//no need
		//MessageBox(NULL, (LPCWSTR)L"curl_easy_init()", (LPCWSTR)L"success", MB_OK);

	curl_easy_setopt(curl, CURLOPT_URL, "https://api.aagtool.top/api/sjsfz?country=cn");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
	headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, br");
	headers = curl_slist_append(headers, "Accept-Language: zh-CN,zh;q=0.9");
	headers = curl_slist_append(headers, "Cache-Control: max-age=0");
	headers = curl_slist_append(headers, "Sec-Fetch-Dest: document");
	headers = curl_slist_append(headers, "Sec-Fetch-Mode: navigate");
	headers = curl_slist_append(headers, "Sec-Fetch-Site: none");
	headers = curl_slist_append(headers, "Sec-Fetch-User: ?1");
	headers = curl_slist_append(headers, "Upgrade-Insecure-Requests: 1");
	headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}

void oninit() {
	initcurl();
}