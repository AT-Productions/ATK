#ifndef WRITEFILE_H
#define WRITEFILE_H
#include <string>
/**
 * Write to given file
 * @param pathToFile Path to the file
 * @param result Pointer to result struct
 * @param action Parameter that checks actions
 * @param decrypt true = File is going to be decrypted
 * @param newPathToFile Contains the new path.
*/
void writeFile(std::string content, basicInfo* result, 
				int action, bool decrypt);

#endif