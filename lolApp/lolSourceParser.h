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
#include "competitiveModel.h"

using namespace std;
using namespace MAUtil;

class LolSourceParser {
private:
	BasicString<char> string_content;
	BasicString<char> string_title;
	BasicString<char> string_author;
	BasicString<char> string_date;
	BasicString<char> string_full_html;
	BasicString<char> string_team_name;
	BasicString<char> string_points;
	int calc_plus;
	int calc_min;
	int news_left;
	int comp_count;
	char* data_c;
	bool is_more_news;
public:
	LolSourceParser();
	NewsModel* Data();
	CompetitiveModel* Data_comp();
	char* html;
	NewsModel* parseNews(char* html);
	BasicString<char> parseNewsFindStringBasic(BasicString<char> first_search_string, BasicString<char> second_search_string, BasicString<char> string_to_search);
	BasicString<char> parseNewsFindStringAdvanced(BasicString<char> first_search_string, BasicString<char> second_search_string, int calc_min, int calc_plus, BasicString<char> string_to_search);
	NewsModel* parseNewsLoop(BasicString<char> temp_data);
	CompetitiveModel* parseCompLoop(BasicString<char> temp_data, int comp_count);
	bool parseMoreNews();
	bool parseMoreCompetitive();
	CompetitiveModel* parseCompetitive(char* html);
	char* parseMedia(char* html);
};


#endif /* LOLSOURCEPARSER_H_ */
