/*
 * contentHandler.h
 *
 *  Created on: 3 apr. 2012
 *      Author: Jan
 */

#ifndef CONTENTHANDLER_H_
#define CONTENTHANDLER_H_

#include "sourceCodeLoader.h"
#include "lolSourceParser.h"

class ContentHandler {
private:
	SourceCodeLoader *sourceCodeLoader;
	LolSourceParser lolSourceParser;
public:
	ContentHandler();
};


#endif /* CONTENTHANDLER_H_ */
