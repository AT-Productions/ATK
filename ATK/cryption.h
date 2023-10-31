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
 * @param content String to be crypted
 * @param result Pointer to result struct
 * @returns vector containing crypted data
*/
std::vector<unsigned char> crypt(std::vector<unsigned char> content, basicInfo* result);


/**
 * Decrypts given content.
 * Turns characters to UTF8 Decimals and
 * changes some values
 *
 * @param content String to be decrypted
 * @param result Pointer to result struct
 * @param what What to be decrypted
 * @returns vector containing crypted data
*/
std::vector<unsigned char> deCrypt(std::vector<unsigned char> content, basicInfo* result);

void cypherAmount(basicInfo* result);

#endif // CRYPTION_H