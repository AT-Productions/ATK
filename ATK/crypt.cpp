#include <string>
#include <vector>
#include <iomanip> 
#include "cryption.h"
#include "argHeader.h"

#include <iostream>
std::vector<unsigned char> crypt(std::vector<unsigned char> content, basicInfo* result){
    // Holds the final string full of unicode characters

    // Vector to store Unicode characters
    std::vector<unsigned char> results;
    int cypher = result->cypher;

    int finalValue;
    // Loops through the content string
    for (char16_t c : content) {
        // If c is over 255 decimals
        if (static_cast<int>(c) + cypher > 255) {
            // Calculates overflow 255
            finalValue = static_cast<int>(c) + cypher - 255 - 1;
            //std::cout << static_cast<int>(c) << "+" << cypher << "=" << finalValue << std::endl;
            results.push_back(static_cast<unsigned char>(finalValue));
        }
        else {
            // Pushes to the back of the vector
            // And adds cypher amount
            results.push_back(c + cypher);

        }
    }

    // Size of results
    const int length = results.size();

    // Spacing for randomness
    int spacing = 0;

    if (length <= 10) {
        spacing = length / 2;
    }
    else if (length <= 1000) {
        spacing = length / 10;
    }
    else if (length <= 10000) {
        spacing = length / 100;
    }
    else if (length <= 1000000) {
        spacing = length / 1000;
    }
    else if (length <= 1000000000) {
        spacing = length / 100000;
    }
    else {
        spacing = length / 1000000;
    }

    int amount = spacing == 0 ? 0 : length / spacing;
    int test = amount;

    std::vector<unsigned char> newResults;

    int i = 0;
    for (unsigned char c : results) {
        newResults.push_back(c);
        if (i == amount) {

            int random = rand() % (255 - 1) + 1; // Random value between 1 and 255
            newResults.push_back(random);
            amount += test;
        }
        i++;
    }
    std::cout << newResults.size() << " | " << length << " | " << i << " | " << amount << std::endl;
    return newResults;
}