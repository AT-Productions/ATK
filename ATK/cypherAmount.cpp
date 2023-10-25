#include <string>

#include "argHeader.h"
#include "cryption.h"

int cypherAmount(basicInfo* result) {
	int finalInt;

	int length = result->password.length() + 3;
	int sugar = 5;


	if (length <= 5) {
		sugar *= 4;
	}
	else if (length <= 7) {
		sugar *= 3;
	}
	else {
		sugar *= 2;
	}

	finalInt = 10 + sugar + length;
	return finalInt;
}