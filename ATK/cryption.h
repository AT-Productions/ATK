#ifndef CRYPTION_H
#define CRYPTION_H

#include <string>
#include <vector>
#include "cryption.h"
#include "argHeader.h"

std::vector<char32_t> crypt(std::string content, basicInfo* result);

std::vector<char32_t> deCrypt(std::string content, basicInfo* result);

int cypherAmount(basicInfo* result);

string passwordHash(basicInfo* result);

string passwordHash(basicInfo* result);

#endif