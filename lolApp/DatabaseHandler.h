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
	/**
	 * Constructor
	 */
	DatabaseHandler();

	/**
	 * Get the data stored in the buffer
	 * @return json string with data
	 */
	char* getNewsData();

	/**
	 * Add News to the database
	 * @return true if succesfull
	 */
	bool addNews();

	/**
	 * Check if getting data is ready
	 * @return true if its ready
	 */
	bool newsReady();

	/**
	 * Start getting news from the database
	 * @return true if connecting to the database is succesfull
	 */
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
	void connWriteFinished(MAUtil::Connection *conn, int result);
};

#endif /* DATABASEHANDLER_H_ */
