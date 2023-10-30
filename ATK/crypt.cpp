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

    /*
    // Size of results
    const int length = results.size();

    // Spacing for randomness
    int spacing = length <= 10 ? length / 2 : length / 10;
    int amount = spacing == 0 || spacing == 0? 0 : length / spacing;
    int test = amount;

    std::vector<unsigned char> newResults;

    // ! HUOM I = 1; ~~ I = 0;
    int i = 1;
    std::cout << " | " << spacing << " | " << length << " | " << amount << " | " << test << " | " << std::endl;
    for (unsigned char c : results) {
        if (i == amount) {
            int random = rand() % (255 - 1) + 1; // Random value between 1 and 255
            newResults.push_back(random);
            amount += test;
            //std::cout << "NEXTSPACE " << amount << ". RANDOM " << random << std::endl;
        }
        newResults.push_back(c);
        i++;
    }

    std::cout << "Length of newResults: " << newResults.size() << " From: " << length << " AND I: " << i << std::endl;
    std::cout << std::endl;
    return newResults;
    */
    return results;
}