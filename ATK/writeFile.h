#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <string>
/**
 * Write to given file
 * @param content Content that will be written
 * @param result Pointer to result struct
 * @param action Parameter contains the action
 * @param decrypt if true, file is going to be decrypted
*/
void writeFile(std::string content, basicInfo* result, 
				int action, bool decrypt);

#endif