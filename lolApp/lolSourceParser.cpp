 /*
 * lolSourceParser.cpp
 *
 *  Created on: 18 apr. 2012
 *      Author: Douwe
 */

#include "lolSourceParser.h"
#include <conprint.h>

//Constructor
LolSourceParser::LolSourceParser() {
	this->news_left = 5;
	this->comp_count = 0;
}

NewsModel* LolSourceParser::Data() {
		NewsModel* parsed_news = this->parseNews(html);
		this->parseMoreNews();
		return parsed_news;
}

/**
 * Used for getting a string piece of an other string
 * @param first_search_string
 * @param second_search_string
 * @param string_to_search
 * @return string found between the two positions
 */
BasicString<char> LolSourceParser::parseNewsFindStringBasic(BasicString<char> first_search_string, BasicString<char> second_search_string, BasicString<char> string_to_search) {

	size_t position1 = string_to_search.find(first_search_string);
	size_t position2 = string_to_search.find(second_search_string);
	BasicString<char> new_string = string_to_search.substr (position1, position2);

	return new_string;

}

/**
 * @Description Also used for getting a string piece out of an other string, but with advanced parameters for specific finding
 * @param first_search_string
 * @param second_search_string
 * @param calc_min
 * @param calc_plus
 * @param string_to_search
 * @return string found between the two positions
 */
BasicString<char> LolSourceParser::parseNewsFindStringAdvanced(BasicString<char> first_search_string, BasicString<char> second_search_string, int calc_min, int calc_plus, BasicString<char> string_to_search) {

	size_t position1 = string_to_search.find(first_search_string);
	size_t position2 = string_to_search.find(second_search_string);
	position1=position1+calc_min;
	position2 = position2-position1;
	position2 = position2+calc_plus;
	BasicString<char> new_string = string_to_search.substr (position1, position2);

	return new_string;

}

/**
 * @Description Function used for extracing/parsing the desired data out of the html source code
 * @param temp_data
 * @return parse_news object. Contains the attributes title, author, content and date
 */
NewsModel* LolSourceParser::parseNewsLoop(BasicString<char> temp_data) {

	BasicString<char> split_string;
	string_full_html = this->parseNewsFindStringAdvanced("<h3 class=\"article_title\">", "</html>", 0, 7, temp_data);
	split_string = this->parseNewsFindStringBasic("<h3 class=\"article_title\">", "</html>", string_full_html);
	split_string = this->parseNewsFindStringAdvanced("<a href=\"", "</a>", 0, 4, split_string);
	string_title = this->parseNewsFindStringAdvanced("\">", "</a>", 2, 0, split_string);
	split_string = this->parseNewsFindStringAdvanced("<span class=\"posted_by\">", "class=\"article_body\"", 0, 0, string_full_html);
	split_string = this->parseNewsFindStringAdvanced("<span class=\"posted_by\">", "</span>", 25, 0, split_string);
	string_author = split_string;
	split_string = this->parseNewsFindStringAdvanced("<span class=\"date\">", "</span>", 0, 15, string_full_html);
	string_date = this->parseNewsFindStringAdvanced("<span class=\"date\">", "</span>", 25, 0, split_string);
	string_content = this->parseNewsFindStringAdvanced("<p>", "class=\"article_controls\"", 0, 0, string_full_html);

	size_t position1 = string_full_html.find("Français");
	size_t position2 = string_full_html.find("</html");
	position2 = position2-position1;
	position2 = position2+7;
	BasicString<char> new_string = string_full_html.substr (position1, position2);

	char * title_c;
	title_c = new char[string_title.length() + 1];
	strcpy(title_c, string_title.c_str());

	char * author_c;
	author_c = new char[string_author.length() + 1];
	strcpy(author_c, string_author.c_str());

	char * content_c;
	content_c = new char[string_content.length() + 1];
	strcpy(content_c, string_content.c_str());

	char * date_c;
	date_c = new char[string_date.length() + 1];
	strcpy(date_c, string_date.c_str());

	NewsModel* parse_news;
	parse_news = new NewsModel();
	parse_news->title = title_c;
	parse_news->author = author_c;
	parse_news->content = content_c;
	parse_news->date = date_c;

	data_c = new char[new_string.length() + 1];
	strcpy(data_c, new_string.c_str());

	return parse_news;

}

/**
 * @description Creates new newmodel instance, calls the parsing function
 * @param temp_data
 * @return the parsed newsmodel object
 */
NewsModel* LolSourceParser::parseNews(char* temp_data) {

	NewsModel* parse_news;
	parse_news = new NewsModel();
	if ( news_left > 4 )
	{
	  temp_data = temp_data;
	}
	else
	{
	  temp_data = data_c;
	}

	parse_news = this->parseNewsLoop(temp_data);
	news_left = news_left-1;
	return parse_news;
}

/**
 * @description Returns true or false depending if there's more news to display
 * @return true or false
 */
bool LolSourceParser::parseMoreNews() {

  if ( news_left > 0 )
  {
	  return true;
  }
  else {
	  return false;
  }

}

CompetitiveModel* LolSourceParser::parseCompetitive(char* temp_data) {
	temp_data = temp_data;
	CompetitiveModel* parse_comp;
	parse_comp = new CompetitiveModel();
	parse_comp = this->parseCompLoop(temp_data, comp_count); comp_count++;
	return parse_comp;
}


CompetitiveModel* LolSourceParser::parseCompLoop(BasicString<char> temp_data, int comp_count) {

	string_full_html = this->parseNewsFindStringAdvanced("<!", "-->", 0, 0, temp_data);

	size_t position1 = string_full_html.find("class");
	size_t position2 = string_full_html.find("dir=");
	position2 = position2-position1;
	position2 = position2+7;
	BasicString<char> new_string = string_full_html.substr (position1, position2);

	  if ( comp_count == 0 )
	  {
		  string_team_name = "Team SoloMid";
		  string_points = "1075+400";

	  }
	  else if ( comp_count == 1 )
	  {
		  string_team_name = "Counter Logic Gaming";
		  string_points = "950+200";
	  }
	  else if ( comp_count == 2 )
	  {
		  string_team_name = "Dignitas";
		  string_points = "735+125";
	  }
	  else if ( comp_count == 3 )
	  {
		  string_team_name = "Moscow Five";
		  string_points = "800";
	  }
	  else if ( comp_count == 4 )
	  {
		  string_team_name = "SK Gaming";
		  string_points = "310";
	  }
	  else if ( comp_count == 5 )
	  {
		  string_team_name = "FnaticRC";
		  string_points = "260";
	  }

	  	char * team_name_c;
	  	team_name_c = new char[string_team_name.length() + 1];
	  	strcpy(team_name_c, string_team_name.c_str());

	  	char * points_c;
	  	points_c = new char[string_points.length() + 1];
	  	strcpy(points_c, string_points.c_str());

	  	CompetitiveModel* parse_comp;
		parse_comp = new CompetitiveModel();
		parse_comp->team_name = team_name_c;
		parse_comp->points = points_c;
		printf("true: %s", "x");
	  return parse_comp;
}

bool LolSourceParser::parseMoreCompetitive() {

  if ( comp_count < 6 )
  {
	  return true;
  }
  else
  {
	  return false;
  }

}
