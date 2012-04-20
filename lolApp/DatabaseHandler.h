/*
 * DatabaseHandler.h
 *
 *  Created on: 20 apr. 2012
 *      Author: Jan
 */

#ifndef DATABASEHANDLER_H_
#define DATABASEHANDLER_H_

#include <mautil/connection.h>
#include <mastdlib.h>

#define DATATYPE_NEWS 1

#define CONNECTION_BUFFER_SIZE 1024

class DatabaseHandler : public MAUtil::HttpConnectionListener
{
public:
	DatabaseHandler();

	char* getNewsData();

	bool newsReady();
	bool getNews();
private:
	char mBuffer[CONNECTION_BUFFER_SIZE];
	MAUtil::HttpConnection mHttp;
	bool mIsConnected;
	bool isDataReady;
	int dataType;

	void httpFinished(MAUtil::HttpConnection *conn, int result);
	void connRecvFinished(MAUtil::Connection *conn, int result);
	void connReadFinished(MAUtil::Connection *conn, int result);
};

#endif /* DATABASEHANDLER_H_ */
