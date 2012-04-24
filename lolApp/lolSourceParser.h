/*
 * lolSourceParser.h
 *
 *  Created on: 18 apr. 2012
 *      Author: Douwe
 */

#ifndef LOLSOURCEPARSER_H_
#define LOLSOURCEPARSER_H_

#include <MAUtil/String.h>
#include "newsModel.h"

using namespace std;
using namespace MAUtil;

class LolSourceParser {
private:
	BasicString<char> string_content;
	BasicString<char> string_title;
	BasicString<char> string_author;
	BasicString<char> string_date;
	BasicString<char> string_full_html;
	int calc_plus;
	int calc_min;
	int news_left;
	char* data_c;
	bool is_more_news;
public:
	LolSourceParser();
	NewsModel* Data();
	char* html;
	NewsModel* parseNews(char* html);
	BasicString<char> parseNewsFindStringBasic(BasicString<char> first_search_string, BasicString<char> second_search_string, BasicString<char> string_to_search);
	BasicString<char> parseNewsFindStringAdvanced(BasicString<char> first_search_string, BasicString<char> second_search_string, int calc_min, int calc_plus, BasicString<char> string_to_search);
	NewsModel* parseNewsLoop(BasicString<char> temp_data);
	bool parseMoreNews();
	char* parseCompetitive(char* html);
	char* parseMedia(char* html);
};


#endif /* LOLSOURCEPARSER_H_ */
