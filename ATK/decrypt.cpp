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


    int calc1 = calculation1(&result->dlength);
    int calc2 = calculation1(&result->elength);
    int calc3 = calculation1(&result->plength);


    int ans1 = result->dlength / calc1;
    int ans2 = result->elength / calc2;
    int ans3 = result->plength / calc3;

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
    int amount = originalLength / spacing;
    int test = amount;

    std::vector<unsigned char> newResults;

    int i = 0;
    std::cout << "| " << spacing << " | " << length << " | " << originalLength << " | " << amount << " | " << test << " | " << std::endl;
    for (unsigned char c : results) {
        if (i == amount) {
            amount += test;
            cout << c << " && " << amount << " - ";
        }
        else {
            newResults.push_back(c);
        }
        i++;
    }
    std::cout << std::endl;
    for (char c : newResults) {
        std::cout << c << ", ";
    }
    std::cout << std::endl;
    std::cout << "Length of newResults: " << newResults.size() << " From: " << length << " AND I: " << i << std::endl;


    return newResults;
    /*
    return results;
    */
}


int calculation1(int* x) {
    if (*x <= 10) {
        return *x / 2;
    }
    else if (*x <= 1000) {
        return *x / 10;
    }
    else if (*x <= 10000) {
        return *x / 100;
    }
    else if (*x <= 1000000) {
        return *x / 1000;
    }
    else if (*x <= 1000000000) {
        return *x / 100000;
    }
    else {
        return *x / 1000000;
    }
}