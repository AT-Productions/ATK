#include <string>
#include "../../include/findFromArray.h"
#include <vector>

using namespace std;
/**
 * Finds items from an array, if it finds 
 * the same item, it returns true
*/
bool findFromArray(const string arr[], int arrSize, const string& toFind) {
    for (int i = 0; i < arrSize; ++i) {
        if (arr[i] == toFind) {
            return true;
        }
    }
    return false;
}
