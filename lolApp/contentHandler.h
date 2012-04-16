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

class ContentHandler : public IdleListener{
private:
	SourceCodeLoader *sourcodeLoader;
	LolSourceParser lolSourceParser;

	void idle();
public:
	ContentHandler();
};


#endif /* CONTENTHANDLER_H_ */
