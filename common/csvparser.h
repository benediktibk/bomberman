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
	CSVParser();
	void parseFile(std::string filename);
	unsigned int getHeightOfFile() const;
	unsigned int getWidthOfFile() const;
	std::string getTextInField(unsigned int x, unsigned int y) const;
	bool isFileCorrect();

private:
	std::vector<std::string> m_textInFile;
	unsigned int m_height;
	unsigned int m_width;
	bool m_isFileCorrect;
};
}
#endif // CSVPARSER_H
