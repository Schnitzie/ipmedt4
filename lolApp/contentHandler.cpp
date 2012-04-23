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
	this->newsReady = false;
	this->competitiveready = false;
	this->dataReady = false;
	this->thereIsNeedToParse = true;

	sourceCodeLoader = sourceCodeLoader->getInstance();
	lolSourceParser = new LolSourceParser();
	database = new DatabaseHandler();

	if(thereIsNeedToParse) {
		sourceCodeLoader->getDataFromUrl("http://euw.leagueoflegends.com/news");
	}
	else {
		database->getNewsData();
	}
}

/**
 * Function that executes when there is nothing else to do
 */
void ContentHandler::idle() {
	if(thereIsNeedToParse) {
		//If all the data is not ready yet, go check what is not ready
		if(!this->dataReady) {
			//If news ain't ready yet, go make it ready :o)
			if(!this->newsReady) {
				if(sourceCodeLoader->dataReady()) {
					char* data = sourceCodeLoader->getData();
					if(lolSourceParser->parseMoreNews()) { // we parse once every cycle
						NewsModel* news = lolSourceParser->parseNews(data);
						database->addNews(news);

						//TODO callJS function on the webview where we set the data to the handler

					}
					else { //means there is no more news to be parsed
						this->newsReady = true;
					}

				}
			}//if news is ready we will check if the competitive is ready
			else if(!this->competitiveready) {
				this->competitiveready = true;
			}

			//If all the data is ready, we set all data ready to true
			if(this->competitiveready && this->newsReady) {
				this->dataReady = true;
			}
		}
	}
	else {
		if(!this->dataReady) {
			if(database->newsReady()) {
				char* news = database->getNewsData();
			}
		}
	}
}


