#include <string>
#include <vector>
#include <iomanip> 
#include "cryption.h"
#include "argHeader.h"
#include "exitFailure.h"
#include <iostream>
std::vector<unsigned char> deCrypt(std::vector<unsigned char> content, basicInfo* result) {
    // Holds the final string full of unicode characters
    // Vector to store Unicode characters
    std::vector<unsigned char> results;
    int cypher = result->cypher;
    // Loops through the content string
    int finalValue;
    for (char16_t c : content) {
        // If c is under 0
        if (static_cast<int>(c) - cypher < 0) {
            // Calculates underflow 0
            finalValue = 255 - cypher + static_cast<int>(c) + 1;
            //std::cout << static_cast<int>(c) << "+" << cypher << "=" << finalValue << std::endl;
            results.push_back(static_cast<unsigned char>(finalValue));
        } 
        else {
            // Pushes to the back of the vector
            // And takes off cypher amount
            results.push_back(c - cypher);
        }
    }

    /*
    // Size of results
    const int length = results.size();

    // Spacing for randomness
    int spacing = length <= 10 ? length / 2 : length / 10;
    int amount = length / spacing;
    int test = amount;

    int x, y, z;

    std::vector<unsigned char> newResults;

    // ! HUOM I = 1; ~~ I = 0;
    int i = 1;
    std::cout << " | " << spacing << " | " << length << " | " << amount << " | " << test << " | " << std::endl;
    for (unsigned char c : results) {
        if (i == amount) {
            amount += test;
            //std::cout << "NEXTSPACE " << amount << ". RANDOM " << random << std::endl;
        }
        else {
            newResults.push_back(c);
        }
        i++;
    }

    std::cout << "Length of newResults: " << newResults.size() << " From: " << length << " AND I: " << i << std::endl;
    std::cout << std::endl;
    return newResults;
    */
    return results;
}