/*
 * JSONParser.h
 *
 *  Created on: 21 Feb 2010
 *      Author: sjp
 *   Source: http://www.mosync.com/content/parsing-json
 */

#ifndef JSONCONNECTION_H_
#define JSONCONNECTION_H_

#include <MAUtil/String.h>

using namespace MAUtil;

class JSONListener
{
  public:
    virtual void header(String& header) = 0;
    virtual void data(String& value) = 0;
    virtual void arrayStart() = 0;
    virtual void arrayEnd() = 0;
    virtual void objectStart() = 0;
    virtual void objectEnd() = 0;

};

class JSONParser
{
  public:
    JSONParser();
    ~JSONParser();

    void parseString(String& jsondata);

    void addListener(JSONListener* listener);

    void reset();
  private:
    String data;
    String temp;
    int _start;
    int _end;

    Vector<JSONListener*> _listeners;
    void parse();
    int findNextQuote(int startPos);
    int nextDelimiter(int startPos);
    int findPosition(char c, int startPos);
    bool gotHeader;
};
#endif /* JSONCONNECTION_H_ */
