#include <string>
#include "argHeader.h"
#include "cryption.h"

int cypherAmount(basicInfo* result) {
	int finalInt;

	int length = result->password.length() + 17;
	int sugar = 80;

	if (length <= 5) {
		sugar *= 1445;
	}
	else if (length <= 7) {
		sugar *= 722;
	}
	else {
		sugar *= 354;
	}

	finalInt = 10 + sugar + length;
	
	// If finalInt is over 15. 15 is max length for some reason.
	while (finalInt > 255) {
		finalInt -= 145;
	}
	return finalInt;
}