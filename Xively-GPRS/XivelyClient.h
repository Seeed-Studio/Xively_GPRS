
#ifndef XIVELYCLIENT_H
#define XIVELYCLIENT_H

#include <Client.h>
#include <GPRSClient.h>
#include <XivelyFeed.h>

#define BUFF_LEN    400
#define CHUNK_SIZE  400

class XivelyClient
{
public:
  XivelyClient(GPRSClient& aClient);

  int get(XivelyFeed& aFeed, const char* aApiKey);
  int put(XivelyFeed& aFeed, const char* aApiKey);

protected:
    void buildPath(char* aDest, unsigned long aFeedId, const char* aFormat);
    int getDataStream(char* buf, XivelyFeed& aFeed);
    char* currPo(char* buf){return (buf+strlen(buf));}
    int leftLen(char* buf){return (BUFF_LEN-strlen(buf));}
    GPRSClient& _client;
};

#endif
