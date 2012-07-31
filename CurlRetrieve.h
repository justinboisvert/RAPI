#ifndef RedditPortable_CurlRetrieve_h
#define RedditPortable_CurlRetrieve_h
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <sstream>
#include <vector>

class CurlRetrieve {
private:
    static size_t writer(char *data, size_t size, size_t nmb, void *func);
    CURL *handle;
    std::string buffer;
public:
    CurlRetrieve();
    void setCookie(std::string cookie);
    void targetURL(std::string path);
    const char* grabData();
    void setToPOST();
    void setToGET();
    void setFieldData(void* defs);
    void clearBuffer();
    void setAgent(std::string ag);
    void appendHeaders(const std::vector<std::string>& list);
    void appendSingleHeader(std::string headr);
    virtual size_t writeOut(char *stream, size_t size, size_t nmb);
    ~CurlRetrieve();
    
};

#endif
