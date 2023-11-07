#ifndef CRYPTION_H

#define CRYPTION_H
#include <vector>
#include "cryption.h"
#include "argHeader.h"

/**
 * Crypts given content.
 * Turns characters to UTF8 Decimals and
 * changes some values
 *
 * @param content Vector to be crypted
 * @param result Pointer to result struct
 * @returns vector containing crypted data
*/
std::vector<unsigned char> crypt(std::vector<unsigned char> content, basicInfo* result, int what);


/**
 * Decrypts given content.
 * Turns characters to UTF8 Decimals and
 * changes some values
 *
 * @param content Vector to be decrypted
 * @param result Pointer to result struct
 * @returns vector containing crypted data
*/
std::vector<unsigned char> deCrypt(std::vector<unsigned char> content, basicInfo* result, int what);

/*
* @param Result Pointer to result struct
*/
void cypherAmount(basicInfo* result);

#endif // CRYPTION_H