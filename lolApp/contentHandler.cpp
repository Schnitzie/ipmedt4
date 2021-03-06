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
	this->cyclecounter = 0;
	this->newscounter = 1;
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
	//The cyclecounter prevents the idle function to do too much checks every cycle and runs once a hundred cycles now.
	if(cyclecounter > 200) {
		if(thereIsNeedToParse) {
			//If all the data is not ready yet, go check what is not ready
			if(!this->dataReady) {
				//If news ain't ready yet, go make it ready :o)
				if(!this->newsReady) {
					if(sourceCodeLoader->dataReady()) {
						char* data = sourceCodeLoader->getData();

						if(lolSourceParser->parseMoreNews()) { // we parse once every cycle
							NewsModel* news = lolSourceParser->parseNews(data);


							WebViewMessage* messageescape;

							char buf[2048];
									sprintf(
										buf,
										"{title1=%s; content1 = %s; date1 = %s}",
										news->title,
										news->content,
										news->date
									);

							main->callJS(buf);
							newscounter++;
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
		else {//If therse no need to parse the lol website we will get the data from the databse
			if(!this->dataReady) {
				if(database->newsReady()) {
					char* news = database->getNewsData();
				}
			}
		}
		cyclecounter = 0;
	}
	cyclecounter++;
}


