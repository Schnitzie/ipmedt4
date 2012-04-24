/*
 * contentHandler.cpp
 *
 *  Created on: 3 apr. 2012
 *      Author: Jan
 */

#include "contentHandler.h"

/**
 * constructor
 * @param main
 */
ContentHandler::ContentHandler(WebView* main) {
	this->main = main;

	//sourceCodeLoader = new SourceCodeLoader();
	lolSourceParser = new LolSourceParser();
}

/**
 * Function that executes when there is nothing else to do
 */
void ContentHandler::idle() {

}


