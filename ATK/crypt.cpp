#include <string>
#include <vector>
#include <iomanip> 
#include <cstdlib>
#include "cryption.h"
#include "argHeader.h"
#include "exitFailure.h"
//#include <iostream>
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

    int amount = spacing;
    int test = amount;

    std::vector<unsigned char> newResults;

    //std::cout << newResults.size() << " | " << length << " | " << amount << " | " << test << " | " << spacing << " | " << length / 2 << " | " << std::endl;

    for (int i = 0; i < results.size(); i++) {
        if (i == amount) {
			int random = rand() % (255 - 1) + 1; // Random value between 1 and 255
            while (true) {
				random = rand() % (255 - 1) + 1;
				if (random <= 20) { // NO \r\n
                	break;
                }
			}
			newResults.push_back(random);
			amount += test;
		}
		newResults.push_back(results[i]);
	}

    //std::cout << newResults.size() << " | " << length << " | " << /*i <<*/ " | " << amount << " | " << test << " | " << spacing << " | " << std::endl;
    return newResults;
}