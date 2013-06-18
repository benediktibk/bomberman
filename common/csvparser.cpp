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
	string textInField;

	if(csvRead.is_open())
	{
		while(!csvRead.eof() && csvRead.good())
		{
			while (getline(csvRead, textInLine))
			{
				istringstream record(textInLine);
				m_height += 1;
				while (getline(record, textInField, ';'))
				{
					m_textInFile.push_back(textInField);
				}
			}
		}
	}
	else
		cerr << "ERROR could not open file" << endl;

	csvRead.close();
}

unsigned int CSVParser::getWidthFromFile() const
{
	return m_width;
}

unsigned int CSVParser::getHeightFromFile() const
{
	return m_height;
}

string CSVParser::getTextInField(unsigned int x, unsigned int y) const
{
	return m_textInFile[y * m_width + x];
}
