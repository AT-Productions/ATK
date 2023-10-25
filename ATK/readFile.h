#ifndef READFILE_H
#define READFILE_H

#include <string>
using namespace std;
/**
 * Reads given file
 * @param filepath Path to the given file which will be read by this function
 * @param result Pointer to the result struct
*/
void readFile(string filePath, basicInfo* result);

#endif