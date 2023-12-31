#include "csvparser.h"

using namespace Common;
using namespace std;

CSVParser::CSVParser(std::string filename) :
	m_filename(filename),
	m_height(0),
	m_width(0),
	m_isFileCorrect(true),
	m_couldOpenFile(true)
{
	parseFile();
}

void CSVParser::parseFile()
{
	string opneninngFile = "resources/" + m_filename + ".csv";
	ifstream csvRead(opneninngFile.c_str());
	string textInLine;
	string textInField;
	unsigned int width = 0;
	bool firstLine = false;

	if(csvRead.is_open())
	{
		while(!csvRead.eof() && csvRead.good())
		{
			while (getline(csvRead, textInLine))
			{
				istringstream record(textInLine);
				m_height += 1;
				width = 0;
				while (getline(record, textInField, ';'))
				{
					m_textInFile.push_back(textInField);
					width +=1;
				}
				if(!firstLine)
				{
					m_width = width;
					firstLine = true;
				}
				if(m_width != width)
				{
					m_isFileCorrect = false;
					break;
				}
			}
		}
	}
	else
		m_couldOpenFile = false;

	csvRead.close();
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

bool CSVParser::isFileCorrect() const
{
	return m_isFileCorrect;
}

bool CSVParser::couldOpenFile() const
{
	return m_couldOpenFile;
}

string CSVParser::getTextInFile() const
{
	string textInFile;
	for (size_t i = 0; i < m_textInFile.size(); ++i)
		textInFile += m_textInFile[i] + "\n";
	return textInFile;
}
