#include <string>
#include "argHeader.h"
#include "cryption.h"

int cypherAmount(basicInfo* result) {
	int finalInt;

	int length = result->password.length() + 17;
	int sugar = 80;

	if (length <= 5) {
		sugar *= 11.5;
	}
	else if (length <= 7) {
		sugar *= 7.2;
	}
	else {
		sugar *= 5.4;
	}

	finalInt = 10 + sugar + length;
	
	// If finalInt is over 15. 15 is max length for some reason.
	while (finalInt > 15) {
		finalInt -= 5;
	}
	return finalInt;
}