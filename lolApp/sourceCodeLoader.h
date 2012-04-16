/*
 * sourceCodeLoader.h
 *
 * Singleton class used for getting the sourcecode of a website.
 *
 *  Link http://en.wikipedia.org/wiki/Singleton_pattern
 *  Created on: 3 apr. 2012
 *  Author: Jan
 */

#ifndef SOURCECODELOADER_H_
#define SOURCECODELOADER_H_

#include <ma.h>
#include <mastdlib.h>
#include <MAUtil/Connection.h>
#include <conprint.h>

#define BUFFSIZE 100000

using namespace MAUtil;


/**
 * Singleton class handling downloading sourcecode from a website
 *
 * Use sourceCodeLoader = sourceCodeLoader->getInstance() to create
 * an instance of this Class instead of the usual sourceCodeLoader = new SourceCodeLoader()
 *
 */
class SourceCodeLoader : public ConnectionListener {
private:
	/*
	 * Constructor
	 */
	SourceCodeLoader();

	/*
	 * Singleton Pattern variables
	 */
	static bool instanceFlag;
	static SourceCodeLoader *sourceCodeLoader;

	/*
	 * Private Class Variables
	 */

	/**
	 * Databuffer
	 *
	 * Maximum (default) size is 100000
	 */
	char dataBuffer[BUFFSIZE];

	/**
	 * Status of the download and read process false if not done
	 */
	bool dataStatus;

	/**
	 * Int holding the length of the last received data
	 */
	int dataLen;

	/**
	 * Variable holding the connection in SourceCodeLoader
	 */
	Connection connection;

	/*
	 * ConnectionListner event functions
	 */
	void connectFinished(Connection *conn, int result);
	void connRecvFinished(Connection *conn, int result);
	void connWriteFinished(Connection *conn, int result);
	void connReadFinished(Connection *conn, int result);
public:

	/**
	 * Returns true when data is ready, false if it is not
	 * @return true or false
	 */
	bool dataReady();

	/**
	 * Returns what is currently in the buffer
	 * @return data
	 */
	char* getData();

	/**
	 * Setups a connection with an url and gets the data from it
	 * @param url of a website
	 */
	void getDataFromUrl(char* url);

	/**
	 * Get a SourceLoaderInstance, following the Singleton Pattern
	 * @return SourceCodeLoader instance
	 */
	static SourceCodeLoader* getInstance();
};


#endif /* SOURCECODELOADER_H_ */
