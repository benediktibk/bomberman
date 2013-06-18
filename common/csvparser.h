#ifndef COMMON_CSVPARSER_H
#define COMMON_CSVPARSER_H

#include <stddef.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Common
{
class CSVParser
{
public:
	CSVParser();
	void parseFile(std::string filename);
	unsigned int getRowsFromFile() const;
	unsigned int getColumsFromFile() const;

private:
	std::vector<std::string> m_textInFile;
	unsigned int m_rows;
	unsigned int m_colums;
};
}
#endif // CSVPARSER_H
