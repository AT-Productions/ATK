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
    int spacing = length <= 10 ? length / 2 : length / 10;
    int amount = spacing;

    std::vector<unsigned char> newResults;
    int i = 0;

    for (unsigned char c : results) {
        if (i == spacing) {
            int random = rand() % (255 - 1) + 1; // Random value between 1 and 255
            newResults.push_back(random);
            spacing += amount;
            std::cout << "NEXTSPACE " << spacing << ". RANDOM " << random << std::endl;
        }
        newResults.push_back(c);
        i++;
    }

    // Calculate the remaining random values needed to reach 110 total elements
    int remainingRandomValues = (amount + length) - newResults.size();
    for (int j = 0; j < remainingRandomValues; j++) {
        int random = rand() % (255 - 1) + 1;
        newResults.push_back(random);
    }

    std::cout << "Length of newResults: " << newResults.size() << " From: " << length << std::endl;
    std::cout << std::endl;
    return newResults;

}