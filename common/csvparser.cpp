#include "csvparser.h"

using namespace Common;
using namespace std;

CSVParser::CSVParser() :
	m_height(0),
	m_width(0)
{ }

void CSVParser::parseFile(std::string filename)
{
	string opneninngFile = "resources/levels/" + filename + ".csv";
	ifstream csvRead(opneninngFile.c_str());
	string textInLine;
	string textInField;
	unsigned int height = 0;
	unsigned int width;

	if(csvRead.is_open())
	{
		while(!csvRead.eof() && csvRead.good())
		{
			while (getline(csvRead, textInLine))
			{
				istringstream record(textInLine);
				height += 1;
				width = 0;
				while (getline(record, textInField, ';'))
				{
					m_textInFile.push_back(textInField);
					width +=1;
				}
			}
		}
	}
	else
		cerr << "ERROR could not open file" << endl;

	csvRead.close();
	m_height = height;
	m_width = width;
}

unsigned int CSVParser::getWidthOfFile() const
{
	return m_width;
}

unsigned int CSVParser::getHeightOfFile() const
{
	return m_height;
}

string CSVParser::getTextInField(unsigned int x, unsigned int y) const
{
	return m_textInFile[(m_height * m_width - 1) - (y * m_width) - (m_width - 1 - x)];
}
