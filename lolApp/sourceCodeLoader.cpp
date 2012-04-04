/*
 * sourceCodeLoader.cpp
 *
 *  Created on: 3 apr. 2012
 *      Author: Jan
 *
 */


#include "sourceCodeLoader.h"
#include <conprint.h>

/*
 * See header file for documentation on vars
 */
bool SourceCodeLoader::instanceFlag = false;
SourceCodeLoader* SourceCodeLoader::sourceCodeLoader = NULL;

/**
 * PRIVATE Constructor of the class
 * Get an instance of this class by calling the static getInstance function
 */
SourceCodeLoader::SourceCodeLoader() {

}


/**
 * PUBLIC function returning what is currently in the databuffer
 *
 * the dataBuffer is filled by the connreadfinished event function
 *
 * @return char
 */
char* SourceCodeLoader::getData() {
	return dataBuffer;
}


/**
 * PUBLIC Returns true if the data is ready, false if its not
 *
 * When a Call for the source of a site is made, the status boolean is set false.
 * When the reading of the data to the buffer is finished the status boolean is set true.
 *
 * @return true or false
 */
bool SourceCodeLoader::dataReady() {

}

/**
 * PUBLIC Returns the Singleton instance of the SourcodeLoader,
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


/*
 * ConnectionListener event functions
 */
void SourceCodeLoader::connectFinished(Connection *conn, int result) {}
void SourceCodeLoader::connRecvFinished(Connection *conn, int result) {}
void SourceCodeLoader::connWriteFinished(Connection *conn, int result) {}
void SourceCodeLoader::connReadFinished(Connection *conn, int result) {}

