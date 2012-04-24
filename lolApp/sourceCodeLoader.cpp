/*
 * sourceCodeLoader.cpp
 *
 *  Created on: 3 apr. 2012
 *      Author: Jan
 *
 */


#include "sourceCodeLoader.h"
#include <conprint.h>
#include <MAUtil/Connection.h>

/**
 * Boolean representing if this class is representing an instance
 */
bool SourceCodeLoader::instanceFlag = false;

/**
 * Container for the instance of this class
 */
SourceCodeLoader* SourceCodeLoader::sourceCodeLoader = NULL;

/**
 * Constructor of the class
 * Get an instance of this class by calling the static getInstance function
 */
SourceCodeLoader::SourceCodeLoader() : connection(this) {

}


/**
 * Function returning what is currently in the databuffer
 *
 * The databuffer is filled after calling the getDataFromUrl function in this class
 *
 * @return char
 */
char* SourceCodeLoader::getData() {
	return dataBuffer;
}


/**
 * Returns true if the data is ready, false if its not
 *
 * When a Call for the source of a site is made, the status boolean is set false.
 * When the reading of the data to the buffer is finished the status boolean is set true.
 *
 * @return true or false
 */
bool SourceCodeLoader::dataReady() {
	return dataStatus;
}

/**
 * Returns an instance of the SourcodeLoader,
 * if no instance exists, one is made.
 *
 * @return Instance of SourceCodeLoader
 */
SourceCodeLoader* SourceCodeLoader::getInstance() {
	if(!instanceFlag) {
		sourceCodeLoader = new SourceCodeLoader();
		instanceFlag = true;

		return sourceCodeLoader;
	}
	else {
		return sourceCodeLoader;
	}
}


/**
 * Sets up a connection with the url provided.
 * If there is already a connection open we don't try to connect.
 *
 * @param url of website that we are trying to get data from
 */
void SourceCodeLoader::getDataFromUrl(char* url) {
	dataStatus = false;
	if(!connection.isOpen()) {
		connection.connect(url) ;
	}
}

/*
 * ConnectionListener event functions
 */

/**
 * Function that is called when a connection is finished.
 *
 * When the connection is finished we start receiving the data.
 *
 * @param conn Connection that handled the request
 * @param result Returns HTTP status code
 */
void SourceCodeLoader::connectFinished(Connection *conn, int result) {
	connection.read(dataBuffer, BUFFSIZE);
}

/**
 * Function that is called when receiving the data has finished
 *
 * @param conn Connection that handled the request
 * @param result Length of data received
 */
void SourceCodeLoader::connRecvFinished(Connection *conn, int result) {
	dataLen = result;
	dataStatus = true;
}

void SourceCodeLoader::connWriteFinished(Connection *conn, int result) {

}

void SourceCodeLoader::connReadFinished(Connection *conn, int result) {
	dataLen = result;
	dataStatus = true;
}

