#include <string>
#include <vector>

#include "cryption.h"
#include "argHeader.h"


#include <iostream>
std::vector<char16_t> deCrypt(std::string content, basicInfo* result) {
    // Holds the final string full of unicode characters
    // Vector to store Unicode characters
    std::vector<char16_t> results;
    int cypher = cypherAmount(result);
    // Loops through the content string
    std::cout << content << endl;
    for (char16_t c : content) {
        // If c is under 0
        if (c - cypher < 0) {
        } 
        else {
            // Pushes to the back of the vector
            // And takes off cypher amount
            results.push_back(c - cypher);
        }
    }
    return results;
}