#include <string>
#include <vector>
#include <iomanip> 

#include "cryption.h"
#include "argHeader.h"
#include "exitFailure.h"


int calculation1(int* x);

//#include <iostream>
std::vector<unsigned char> deCrypt(std::vector<unsigned char> content, basicInfo* result, int what) {
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


    // Calculate originals
    int originalLength = 0;

    int calc1 = calculation1(&result->dlength);
    int calc2 = calculation1(&result->elength);
    int calc3 = calculation1(&result->plength);
    //std::cout << result->dlength << " |+| " << calc1 << " |=| " << result->dlength + calc1 << " |==| " << length << " | " << what << " |" << std::endl;
    //std::cout << result->elength << " |+| " << calc2 << " |=| " << result->elength + calc2 << " |==| " << length << " | " << what << " |" << std::endl;
    //std::cout << result->plength << " |+| " << calc3 << " |=| " << result->plength + calc3 << " |==| " << length << " | " << what << " |" << std::endl;
    //std::cout << "--------------------------" << std::endl;

    if (what == 2) {
        originalLength = result->dlength;
    }
    else if (what == 1) {
        originalLength = result->elength;
    }
    else if (what == 0) {
        originalLength = result->plength;
    }
    else {
        std::cerr << "Error decrypting." << std::endl;
        exitfailure();
    }


    // Spacing for randomness
    int spacing = 0;

    if (originalLength <= 10) {
        spacing = originalLength / 2;
    }
    else if (originalLength <= 1000) {
        spacing = originalLength / 10;
    }
    else if (originalLength <= 10000) {
        spacing = originalLength / 100;
    }
    else if (originalLength <= 1000000) {
        spacing = originalLength / 1000;
    }
    else if (originalLength <= 1000000000) {
        spacing = originalLength / 100000;
    }
    else {
        spacing = originalLength / 1000000;
    }

    int amount = spacing;
    int test = amount;

    std::vector<unsigned char> newResults;

    //std::cout << newResults.size() << " | " << originalLength << " | " << amount << " | " << test << " | " << spacing << " | " << originalLength << " | " << std::endl;

    // TODO: Fix this. Not optimal.
    if (originalLength == 1) {
        newResults.push_back(results[1]);
    }
    else {
        // ! Trial and error success???
        for (int i = 0; i < results.size(); i++) {
            newResults.push_back(results[i]);
            if (i == amount) {
                amount += test + 1;
                //cout << " C " << results[i] << endl;
                newResults.pop_back();
            }
            //else {
            //    cout << " A " << results[i] << endl;
            //}
        }
    }

    /*for (unsigned char c : newResults) {
		cout << c << endl;
	}*/

    //std::cout << newResults.size() << " | " << originalLength << " | " << /*i <<*/ " | " << amount << " | " << test << " | " << spacing << " | " << std::endl;
    return newResults;
}

// @param x: int pointer, same as length
int calculation1(int* x) {

    // integer same as spacing
    int integer = 0;

    if (*x <= 10) {
        integer = *x / 2;
    }
    else if (*x <= 1000) {
        integer = *x / 10;
    }
    else if (*x <= 10000) {
        integer = *x / 100;
    }
    else if (*x <= 1000000) {
        integer = *x / 1000;
    }
    else if (*x <= 1000000000) {
        integer = *x / 100000;
    }
    else {
        integer = *x / 1000000;
    }

    /// EN MUISTA MITÄ TEKEE
    int og = integer;
    for (int i = 0; i < og; i++) {
        integer++;
    }

    return integer;
}