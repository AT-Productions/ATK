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


    // Size of results
    const int length = results.size();

    // Spacing for randomness
    int spacing = length <= 10 ? length / 2 : length / 10;
    int amount = spacing;

    int ogSpacing = 0;
    int ogAmount = 0;
        std::cout << length << " A "<< amount << std::endl;

    for (int y = 0; y <= length; y++) {
        int x = amount * y;
        if (x + y == length) {
            std::cout << "HAHAHA " << x << " + " << y << " = " << length << std::endl;
            break;
        }
    }

    std::vector<unsigned char> newResults;
    if (result->safe) {
        // Safe decrypt
    }

   

    int i = 0;
    for (unsigned char c : results) {
        std::cout << c << " - ";
        if (i == spacing) {
            spacing += amount;
            std::cout << "NEXTSPACE " << spacing << endl;
        }
        else {
            newResults.push_back(c);
        }

        i++;
    }
    std::cout << std::endl;
    for (unsigned char c : newResults) {
        std::cout << (int)c << ", ";
    }
    std::cout << "Length of newResults: " << newResults.size() << " From: " << length << endl;
    std::cout << std::endl;

    return newResults;
}