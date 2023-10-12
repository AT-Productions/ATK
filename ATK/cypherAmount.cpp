#include <iostream>
#include <string>

#include "argHeader.h"
#include "cryption.h"

int cypherAmount(basicInfo* result) {
	int finalInt;



	// Takes passwords length and adds three to it
	int length = result->password.length() + 3;

	if (length <= 5) {
		std::cout << "ASADSDSA";
	}
	else if (length <= 7) {
		std::cout << "dsadsadsa";
	}
	else {
		std::cout << "fdsfds";
	}

	finalInt = 10;
	return finalInt;
}