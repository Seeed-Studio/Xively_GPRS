#include <Xively.h>
#include <GPRSClient.h>
#include <CountingStream.h>

XivelyClient::XivelyClient(GPRSClient& aClient)
  : _client(aClient)
{
}

int XivelyClient::put(XivelyFeed& aFeed, const char* aApiKey)
{
    char defaultHost[] = "api.xively.com";
    uint8_t count = 0;
    while(1){
        int ret = _client.connect(defaultHost,80);
        count++;
        if (ret < 1) {
            _client.stop();
            delay(500);
        }else{ break; }
        if(count > 2){
            return false;
        }
    }

    char request[BUFF_LEN];
    char* data = request+BUFF_LEN/2;
    memset(request,'\0',sizeof(request));
    const char* method = "PUT";
    char path[30];
    
    buildPath(path, aFeed.id(), "json");
    snprintf(request, sizeof(request), "%s %s HTTP/1.1\r\nHost: %s\r\n", method, path, defaultHost); //Write request

    snprintf(currPo(request),leftLen(request),"X-ApiKey: %s\r\n", aApiKey);
    snprintf(currPo(request),leftLen(request),"User-Agent: %s\r\n", "Xively-Arduino-Lib/1.0");

    int dataLen = getDataStream(data,aFeed);
    snprintf(currPo(request),leftLen(request),"Content-Length: %d\r\n", dataLen);
    strcpy(currPo(request),"\r\n");
    snprintf(currPo(request),leftLen(request),"%s\r\n", data);
        
    _client.write(request,strlen(request));
    memset(request,'\0',sizeof(request));
    int trfLen = _client.read(request, 32); //32 bytes is enough
    request[trfLen] = '\0';

    _client.stop();
    int m_httpResponseCode = 0;
    //Parse HTTP response
    if(1 != sscanf(request, "\nHTTP/%*d.%*d %d %*[^\r\n]", &m_httpResponseCode)) {
        return false;//Cannot match string, error
    }
    if((m_httpResponseCode < 200) || (m_httpResponseCode >= 300)) {
        return false;
    } 
    return true;
}


int XivelyClient::getDataStream(char* buf, XivelyFeed& aFeed)
{
    strcpy(buf+strlen(buf),"{");
    strcpy(buf+strlen(buf),"\"version\":\"1.0.0\",");
    strcpy(buf+strlen(buf),"\"datastreams\" : [");
    for(int i = 0; i < aFeed._datastreamsCount;i++){
        aFeed._datastreams[i].printToBuff(buf+strlen(buf));
        if (i == aFeed._datastreamsCount-1){
            //to do something?
        }else{
          strcpy(buf+strlen(buf),",");
        }    
    }
    strcpy(buf+strlen(buf),"]}");
    return (strlen(buf));
}


void XivelyClient::buildPath(char* aDest, unsigned long aFeedId, const char* aFormat)
{
    char idstr[12]; 
    strcpy(aDest, "/v2/feeds/");
    char* p = &idstr[10];
    idstr[11] = 0;
    for(*p--=aFeedId%10+0x30;aFeedId/=10;*p--=aFeedId%10+0x30);
    strcat(aDest, p+1);
    strcat(aDest, ".");
    strcat(aDest, aFormat);
}

int XivelyClient::get(XivelyFeed& aFeed, const char* aApiKey)
{
    char defaultHost[] = "api.xively.com";   
    uint8_t count = 0;
    while(1){
        int ret = _client.connect(defaultHost,80);
        count++;
        if (ret < 1) {
            _client.stop();
            delay(500);
            Serial.print("E\n");
        }else{ break; }
        if(count > 2){
            return -1;
        }
    }

    char request[BUFF_LEN];
    memset(request,'\0',sizeof(request));
    const char* method = "GET";
    char path[30];
    
    buildPath(path, aFeed.id(), "csv");
    snprintf(request, sizeof(request), "%s %s HTTP/1.1\r\nHost: %s\r\n", method, path, defaultHost); //Write request
    snprintf(currPo(request),leftLen(request),"X-ApiKey: %s\r\n", aApiKey);
    snprintf(currPo(request),leftLen(request),"User-Agent: %s\r\n", "Xively-Arduino-Lib/1.0");
    snprintf(currPo(request),leftLen(request),"\r\n");

    _client.write(request,strlen(request));
    memset(request,'\0',sizeof(request));
    int trfLen = _client.read(request, sizeof(request));
    request[trfLen] = '\0';    
    _client.stop();
    
    int m_httpResponseCode = 0;
    //Parse HTTP response
    if(1 != sscanf(request, "\nHTTP/%*d.%*d %d %*[^\r\n]", &m_httpResponseCode)) {
        return false;//Cannot match string, error
    }
    if((m_httpResponseCode < 200) || (m_httpResponseCode >= 300)) {
        return false;
    } 

    int commaCount = 0;
    char* crlfPtr = strstr(request,"\r\n\r\n");
    if(crlfPtr == NULL){
        return false;
    }    
    crlfPtr += 4;   
    for(int i = 0; i < aFeed.size(); i++){
        while(*(crlfPtr++) != '\0'){
            if(*crlfPtr == ','){
                commaCount++;
                if((commaCount > 0) && (commaCount%2 == 0)){
                    aFeed[i].updateValue(crlfPtr+1);
                }
            }
        }
    }
    return true;
}





