#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <string>

void writeFile(std::string content, basicInfo* result, 
				int action, bool decrypt, string newPathToFile);

#endif