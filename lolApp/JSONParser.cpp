/*
 * JSONParser.cpp
 *
 *  Created on: 21 Feb 2010
 *      Author: sjp
 *   Source: http://www.mosync.com/content/parsing-json
 */
#include "JSONParser.h"
#define LOG lprintfln

JSONParser::JSONParser()
{
}

JSONParser::~JSONParser()
{
}

void JSONParser::reset()
{
  _start = 0;
  data.clear();
  temp.clear();
  gotHeader = false;
}

void JSONParser::parseString(String& jsondata)
{
  data = jsondata;
  _start = 0;
  parse();
}
void JSONParser::parse()
{
  while(_start < data.length())
  {
    //Move through white space
    char firstChar = data.c_str()[_start];

    while(firstChar < 33)
      firstChar = data.c_str()[++_start];

    //Check the first character, if it is an [,],{ or } raise the approriate event
    if(firstChar == '[')
    {
      Vector_each(JSONListener*, itr, _listeners)
        (*itr)->arrayStart();
      _start++;
      gotHeader = false;
    }
    else if(firstChar == ']')
    {
      Vector_each(JSONListener*, itr, _listeners)
        (*itr)->arrayEnd();
      _start++;
      gotHeader = false;
    }
    else if(firstChar == '{')
    {
      Vector_each(JSONListener*, itr, _listeners)
        (*itr)->objectStart();
      _start++;
      gotHeader = false;
    }
    else if(firstChar == '}')
    {
      Vector_each(JSONListener*, itr, _listeners)
        (*itr)->objectEnd();
      _start++;
      gotHeader = false;
    }
    else if(firstChar == ',')
    {
      _start++;
      gotHeader = false;
    }
    else if(firstChar == ':')
    {
      _start++;
      gotHeader = true;
    }

    else if(!gotHeader)
    {
      //read the header
      //LOG("Reading header");
      temp.clear();
      _end = data.findFirstOf(':', _start);

      _end -= _start; //get the length
      if(_end > 0)
      {
        temp = data.substr(_start, _end);
        //LOG("Header: '%s'", temp.c_str());
        _start += _end;
        Vector_each(JSONListener*, itr, _listeners)
          (*itr)->header(temp);
      }
    }
    else
    {
      //Processing data
      if(firstChar == '\"')
      {
        //LOG("Reading string");
        //Processing a string
        _end = findNextQuote(_start + 1) + 1;
        //LOG("Next quote at %d", _end);
        _end -= _start;
        //LOG("Giving a length of %d", _end);
        if(_end > 150)
          temp = data.substr(_start + 1, 150); //don't take the leading quote, it won't have a pair
        else
        {
          //LOG("Taking substring %d to %d", _start, _end);
          temp = data.substr(_start, _end);
        }
        //LOG("Got string");
        _start += _end;
        Vector_each(JSONListener*, itr, _listeners)
          (*itr)->data(temp);
      }
      else
      {
        //LOG("Reading value");
        _end = nextDelimiter(_start);
        _end -= _start;
        temp = data.substr(_start, _end);
        //LOG("Value '%s'", temp.c_str());
        _start += _end;
        Vector_each(JSONListener*, itr, _listeners)
          (*itr)->data(temp);
      }
    }
  }
}

int JSONParser::findNextQuote(int startPos)
{
  startPos = data.findFirstOf('\"', startPos);
  if(data.c_str()[startPos-1] == '\\')
    startPos = findNextQuote(startPos + 1); //Ignore any \" pairs in the string data
  return startPos;
}


void JSONParser::addListener(JSONListener* listener)
{
  _listeners.add(listener);
}

int JSONParser::nextDelimiter(int startPos)
{
  int nextComma = findPosition(',', startPos);
  int nextSquareBrace = findPosition(']', startPos);
  int nextCurlyBrace = findPosition('}', startPos);

  int lowest = nextComma < nextSquareBrace ? nextComma : nextSquareBrace;
  if(nextCurlyBrace < lowest)
    lowest = nextCurlyBrace;

  return lowest;
}

int JSONParser::findPosition(char c, int startPos)
{
  int cpos = data.findFirstOf(c, startPos);
  if(cpos == -1)
    cpos = data.length();

  return cpos;
}
