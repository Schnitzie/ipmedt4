/*
 * DatabaseHandler.cpp
 *
 *  Created on: 20 apr. 2012
 *      Author: Jan
 */

#include "DatabaseHandler.h"
#include <conprint.h>

DatabaseHandler::DatabaseHandler() : mHttp(this) {
	InitConsole();
	gConsoleLogging = 1;
	isDataReady = false;
}

/**
 * Function that adds news to the database
 * @return true on succes
 */
bool DatabaseHandler::addNews(NewsModel* news) {

	MAUtil::String data = "?&key=aa&token=13453";

	MAUtil::String title = "&title=";
	MAUtil::String content = "&content=";
	MAUtil::String author = "&author=";
	MAUtil::String date = "&date=";

	title.append(news->title, strlen(news->title));
	content.append(news->content, strlen(news->content));
	author.append(news->author, strlen(news->author));
	date.append(news->date, strlen(news->date));

	data = data+title+content+author+date;

	if(!mIsConnected) {
		dataType = DATATYPE_NEWS;
		isDataReady = false;
		int res = mHttp.create("http://ehs-webdesign.nl/lolapp/addNews.php", HTTP_POST);
		char buffer[10];
		sprintf(buffer, "%d", data.length());
		mHttp.setRequestHeader("Content-Length", buffer);


		if(res < 0) {
			return false;
		} else {
			mIsConnected = true;
			mHttp.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
			mHttp.setRequestHeader("User-Agent","Profile/MIDP-2.0 Configuration/CLDC-1.0");
			mHttp.write(data.c_str(), data.length());
			return true;
		}
	}
	else {
		return false;
	}

}

/**
 * Function that starts getting the news from the database
 * @return true if succes
 */
bool DatabaseHandler::getNews() {
	if(!mIsConnected) {
		dataType = DATATYPE_NEWS;
		isDataReady = false;
		int res = mHttp.create("http://ehs-webdesign.nl/lolapp/getdata.php", HTTP_POST);
		if(res < 0) {
			return false;
		} else {
			mHttp.finish();
			mIsConnected = true;
			return true;
		}
	}
	else {
		return false;
	}
}

/**
 * get the data stored in the buffer
 * @return data
 */
char* DatabaseHandler::getNewsData() {
	if(dataType == DATATYPE_NEWS) {
		return mBuffer;
	}
}

/**
 * Check if storing the news to the buffer is ready
 * @return true if ready
 */
bool DatabaseHandler::newsReady() {
	if(dataType == DATATYPE_NEWS) {
		return isDataReady;
	}
	else {
		return false;
	}
}

/**
 * Function that executes when a connection is finished
 * @param conn
 * @param result
 */
void DatabaseHandler::httpFinished(MAUtil::HttpConnection *conn, int result) {
	MAUtil::String contentLengthStr;
	int responseBytes = mHttp.getResponseHeader("content-length", &contentLengthStr);
	int contentLength = 0;

	if(responseBytes != CONNERR_NOHEADER) {
		contentLength = atoi(contentLengthStr.c_str());
	}

	if(contentLength >= CONNECTION_BUFFER_SIZE || contentLength == 0) {
		mHttp.recv(mBuffer, CONNECTION_BUFFER_SIZE);
	}
	else {
		mBuffer[contentLength] = 0;
		mHttp.read(mBuffer, contentLength);
	}
}

/**
 * Function that executes when recieving data is finished
 * @param conn
 * @param result
 */
void DatabaseHandler::connRecvFinished(MAUtil::Connection *conn, int result) {
	if(result >= 0) {
		mHttp.recv(mBuffer, CONNECTION_BUFFER_SIZE);
		return;
	}

	mHttp.close();
	mIsConnected = false;
	isDataReady = true;
}

/**
 * Function that executes when reading data is finished
 * @param conn
 * @param result
 */
void DatabaseHandler::connReadFinished(MAUtil::Connection *conn, int result) {
	mHttp.close();
	mIsConnected = false;
	isDataReady = true;
}

/**
 * Function that executes when writing data has finished
 * @param conn
 * @param result
 */
void DatabaseHandler::connWriteFinished(MAUtil::Connection *conn, int result){
	mHttp.finish();
	printf("result write: %i", result);
}
