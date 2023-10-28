#include <string>
#include <vector>

//#include <iostream>
//#include "exitFailure.h"

#include "argHeader.h"
#include "cryption.h"

int cypherAmount(basicInfo* result) {
	int finalInt;

	int length = result->password.length() + 17;
	int sugar = 80;

	std:vector<unsigned char>data;

	for (char c : result->password) {
		data.push_back(static_cast<unsigned char>(c));
	}
	

	if (length <= 5) {
		sugar *= 1444;
	}
	else if (length <= 7) {
		sugar *= 7223;
	}
	else {
		sugar *= 3523;
	}
	for (unsigned char c : data) {
		length += static_cast<int>(c);
		sugar -= static_cast<int>(c);
	}

	finalInt = 10 + sugar + length;
	
	while (finalInt > 255) {
		for (unsigned char c : data) {

			if (finalInt - static_cast<int>(c) < 0) {
				finalInt += static_cast<int>(c);
			}
			else {
				finalInt -= static_cast<int>(c);
			}

		}
	}
	if (finalInt <= 5) {
		finalInt += 6;
	}

	return finalInt;
}