#ifndef FINDFROMARRAY_H
#define FINDFROMARRAY_H

#include <string>
#include <vector>
using namespace std;

/**
 * Finds items from an array, if it finds
 * the same item, it returns true
 *
 * @param arr Array where to find from
 * @param arrSize arrays size
 * @param toFind string to find
*/
bool findFromArray(const string arr[],int arrSize,  const string& toFind);

#endif