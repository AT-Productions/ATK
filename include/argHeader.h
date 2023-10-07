

#ifndef handleArgs_h
#define handleArgs_h

#include <string>
using namespace std;

struct basicInfo
  {
    string type;
    string path;
    string password;
  };

basicInfo* handleArgs(char** argv, int argc);

#endif