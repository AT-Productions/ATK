#include <string>
#include <vector>
#include <iomanip> 
#include "cryption.h"
#include "argHeader.h"

//#include <iostream>
std::vector<unsigned char> crypt(std::vector<unsigned char> content, basicInfo* result){
    // Holds the final string full of unicode characters

    // Vector to store Unicode characters
    std::vector<unsigned char> results;
    int cypher = cypherAmount(result);

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
    return results;
}