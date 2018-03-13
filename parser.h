/// \file parser.h
/// \brief markdown parser
/// \author suntangji, suntangj2016@gmail.com
/// \version 1.0
/// \date 2018-03-02

#ifndef __PARSER_H
#define __PARSER_H

#include<string>
#include<vector>

class Markdown {
 public:
	Markdown();
	void Translate(std::vector<std::string>& md);
	std::vector<std::string>& GetContent();

 private:
  void SetFrontTags();
	void SetBackTags();
  int IsTitle(std::string & s);
  void SetTitle(int level,std::string& s);
	int IsBlockquotes(std::string & s);
	void SetBlockquotes(int level,std::string& s);
	int IsUnOrderList(std::string& s);
	void SetUnOrderList(int pos,std::string& s);
	int IsOrderList(std::string& s );
	void SetOrderList(int pos,std::string& s);
	bool Run(std::string& s);
	int OnlyText(std::string& s);
	void SetToken(std::string& s);
	bool IsCode(std::string& s);
	void SetCode(std::string& s);
	bool IsTable(std::string& s);
	void SetTable();
	void GetTableContext(std::vector<std::string>& table_context,std::string& s);

  std::vector<std::string> v;
	static int pre_block ;
	static int count_of_block;

	enum STATUS{
		NORMAL,
		LIST,
		UNLIST,
		CODE,
		BLOCK,
		TABLE,
		TABLE_START
	}status;
};

#endif //__PARSER_H
