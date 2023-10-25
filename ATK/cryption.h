#ifndef CRYPTION_H
#define CRYPTION_H

#include <string>
#include <vector>
#include "cryption.h"
#include "argHeader.h"

/**
 * Crypts given content.
 * Turns characters to UTF8 Decimals and
 * changes some values
 *
 * @param content String to be crypted
*/
std::vector<char16_t> crypt(std::string content, basicInfo* result);


/**
 * Decrypts given content.
 * Turns characters to UTF8 Decimals and
 * changes some values
 *
 * @param content String to be decrypted
*/
std::vector<char16_t> deCrypt(std::string content, basicInfo* result);

int cypherAmount(basicInfo* result);

string passwordHash(basicInfo* result);

#endif