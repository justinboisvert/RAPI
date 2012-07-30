#include "CurlRetrieve.h"

CurlRetrieve::CurlRetrieve(){
    handle = curl_easy_init();
    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION, &CurlRetrieve::writer);
    curl_easy_setopt(handle,CURLOPT_WRITEDATA,this);
    clearBuffer();
}

void CurlRetrieve::setToPOST(){
    curl_easy_setopt(handle,CURLOPT_POST,1);
}


void CurlRetrieve::setToGET(){
    curl_easy_setopt(handle,CURLOPT_HTTPGET,1);
}

void CurlRetrieve::targetURL(std::string path){
    curl_easy_setopt(handle,CURLOPT_URL,path.c_str());
}
CurlRetrieve::~CurlRetrieve(){
    curl_easy_cleanup(handle);
}

size_t CurlRetrieve::writer(char *stream, size_t size, size_t nmb, void *f){
    return static_cast<CurlRetrieve*>(f)->writeOut(stream,size,nmb);
}

size_t CurlRetrieve::writeOut(char *stream, size_t size, size_t nmb){
    for(int i = 0 ; i < nmb; i++){
        buffer.push_back(stream[i]);
    }
    return size*nmb;
}

void CurlRetrieve::setAgent(std::string ag){
    curl_easy_setopt(handle, CURLOPT_USERAGENT,ag.c_str());
}

void CurlRetrieve::setCookie(std::string cookie){
    std::stringstream s;
    s << "reddit_session=" << cookie;
    curl_easy_setopt(handle,CURLOPT_COOKIE,s.str().c_str());
}

void CurlRetrieve::appendSingleHeader(std::string headr){
    struct curl_slist *headers = NULL;
    curl_slist_append(headers, headr.c_str());
    curl_easy_setopt(handle,CURLOPT_HTTPHEADER,headers);
}

void CurlRetrieve::appendHeaders(const std::vector<std::string>& list){
    struct curl_slist *headers = NULL;
    for(int i = 0; i < (int)list.size(); i++){
        curl_slist_append(headers, list[i].c_str());
    }
    curl_easy_setopt(handle,CURLOPT_HTTPHEADER,headers);
}

void CurlRetrieve::clearBuffer(){
    buffer = "";
}

void CurlRetrieve::setFieldData(void *defs){
     curl_easy_setopt(handle,CURLOPT_POSTFIELDS, defs);
}
const char* CurlRetrieve::grabData(){
    const char *err = "ERROR";
    CURLcode s = curl_easy_perform(handle);
    if(s == CURLE_OK){
        return buffer.c_str();
    }
    else {
        return err;
    }
}

