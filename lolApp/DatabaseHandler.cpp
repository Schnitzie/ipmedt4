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


char* DatabaseHandler::getNewsData() {
	if(dataType == DATATYPE_NEWS) {
		return mBuffer;
	}
}

bool DatabaseHandler::newsReady() {
	if(dataType == DATATYPE_NEWS) {
		return isDataReady;
	}
	else {
		return false;
	}
}


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
void DatabaseHandler::connRecvFinished(MAUtil::Connection *conn, int result) {
	if(result >= 0) {
		mHttp.recv(mBuffer, CONNECTION_BUFFER_SIZE);
		return;
	}

	mHttp.close();
	mIsConnected = false;
	isDataReady = true;
}
void DatabaseHandler::connReadFinished(MAUtil::Connection *conn, int result) {
	mHttp.close();
	mIsConnected = false;
	isDataReady = true;
}
