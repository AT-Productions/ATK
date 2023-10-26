#include <string>
#include "findFromArray.h"
#include <vector>

using namespace std;

bool findFromArray(const string arr[], int arrSize, const string& toFind) {
    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] == toFind) {
            return true;
        }
    }
    return false;
}
