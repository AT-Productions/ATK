#include <string>
#include <vector>

#include "cryption.h"
#include "argHeader.h"

/**
 * Decrypts given content.
 * Turns characters to UTF8 Decimals and
 * changes some values
 *
 * @param content String to be decrypted
*/

std::vector<char32_t> deCrypt(std::string content, basicInfo* result) {
    // Holds the final string full of unicode characters
    // Vector to store Unicode characters
    std::vector<char32_t> results;
    int cypher = cypherAmount(result);
    // Loops through the content string
    for (char32_t c : content) {
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