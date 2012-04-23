/*
 * contentHandler.h
 *
 *  Created on: 3 apr. 2012
 *      Author: Jan
 */

#ifndef CONTENTHANDLER_H_
#define CONTENTHANDLER_H_

#include <Wormhole/WebAppMoblet.h>
#include <Wormhole/MessageProtocol.h>
#include <Wormhole/MessageStream.h>
#include <Wormhole/Libs/JSONMessage.h>
#include <Wormhole/Libs/PhoneGap/PhoneGapMessageHandler.h>
#include <Wormhole/Libs/JSNativeUI/NativeUIMessageHandler.h>
#include <Wormhole/Libs/JSNativeUI/ResourceMessageHandler.h>

#include "sourceCodeLoader.h"
#include "lolSourceParser.h"
#include "DatabaseHandler.h"
#include "lolapp.h"

using namespace MAUtil; // Class Moblet
using namespace NativeUI; // WebView widget.

class ContentHandler : public IdleListener{
private:
	SourceCodeLoader *sourceCodeLoader;
	LolSourceParser* lolSourceParser;
	DatabaseHandler* database;

	WebView* main;

	bool dataReady;
	bool newsReady;
	bool competitiveready;

	bool thereIsNeedToParse;

	void idle();
public:
	/**
	 * constructor
	 * @param main
	 */
	ContentHandler(WebView* main);
};


#endif /* CONTENTHANDLER_H_ */
