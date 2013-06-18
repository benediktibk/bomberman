#include "csvparser.h"

using namespace Common;
using namespace std;

CSVParser::CSVParser()
{ }

void CSVParser::parseFile(std::string filename)
{
	string opneninngFile = "resources/levels/" + filename + ".csv";
	ifstream csvRead(opneninngFile.c_str());
	string textInLine;

	if(csvRead.is_open())
	{
		while(!csvRead.eof() && csvRead.good())
		{
			getline(csvRead, textInLine, ';');
			m_textInFile.push_back(textInLine);
		}
	}
	else
		cerr << "ERROR could not open file" << endl;

	csvRead.close();
}

unsigned int CSVParser::getColumsFromFile() const
{
	return m_colums;
}

unsigned int CSVParser::getRowsFromFile() const
{
	return m_rows;
}
