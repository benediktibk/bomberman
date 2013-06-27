#ifndef COMMON_CSVPARSER_H
#define COMMON_CSVPARSER_H

#include <stddef.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace Common
{
class CSVParser
{
public:
	CSVParser(std::string filename);
	unsigned int getHeightOfFile() const;
	unsigned int getWidthOfFile() const;
	std::string getTextInField(unsigned int x, unsigned int y) const;
	bool isFileCorrect() const;
	bool couldOpenFile() const;
	std::string getTextInFile() const;

private:
	void parseFile();

private:
	std::vector<std::string> m_textInFile;
	std::string m_filename;
	unsigned int m_height;
	unsigned int m_width;
	bool m_isFileCorrect;
	bool m_couldOpenFile;
};
}
#endif // CSVPARSER_H
