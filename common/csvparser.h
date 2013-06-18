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
	unsigned int getHeightFromFile() const;
	unsigned int getWidthFromFile() const;
	std::string getTextInField(unsigned int x, unsigned int y) const;

private:
	std::vector<std::string> m_textInFile;
	unsigned int m_height;
	unsigned int m_width;
};
}
#endif // CSVPARSER_H
