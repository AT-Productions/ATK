#include <string>
#include <vector>
#include <iomanip> 
#include "cryption.h"
#include "argHeader.h"
#include "exitFailure.h"
#include <iostream>


int calculation1(int* x);

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


    // Calculate originals
    int originalLength = 0;


    //int calc1 = result->dlength >= 100 ? calculation1(&result->dlength) : calculation1(&result->dlength) - 1;
    int calc1 = calculation1(&result->dlength) - 1;

    // TODO FIX MAX FILE LENGTH > 10 BEFORE DATA LOSS !!!!!
    int calc2 = result->elength > 9 ? calculation1(&result->elength) : calculation1(&result->elength) - 1;
    int calc3 = result->plength >= 100 ? calculation1(&result->plength)  : calculation1(&result->plength) - 1;
    
   /* calc1 = calc1 <= 0 ? calc1 = 1 : calc1;
    calc2 = calc2 <= 0 ? calc2 = 1 : calc2;
    calc3 = calc3 <= 0 ? calc3 = 1 : calc3;*/

    std::cout << result->dlength << " || " << calc1 << " || " << result->dlength + calc1 << " || " << length << std::endl;
    std::cout << result->elength << " || " << calc2 << " || " << result->elength + calc2 << " || " << length << std::endl;
    std::cout << result->plength << " || " << calc3 << " || " << result->plength + calc3 << " || " << length << std::endl;

    if (result->dlength + calc1 == length) {
        originalLength = result->dlength;
    }
    else if (result->elength + calc2 == length) {
        originalLength = result->elength;
    }
    else if (result->plength + calc3 == length) {
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

    int amount = spacing == 0 ? 0 : originalLength / spacing;
    int test = amount + 1;

    std::vector<unsigned char> newResults;

    int i = -1;
    for (unsigned char c : results) {
        newResults.push_back(c);

        if (i == amount) {
            amount += test;
            newResults.pop_back();
            cout << c << " " << amount << " - ";
        }

        i++;
    }
    return newResults;
}


int calculation1(int* x) {
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

    if (integer <= 0) {
        integer = 1;
    }

    return integer;
}