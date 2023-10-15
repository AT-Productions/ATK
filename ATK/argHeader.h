

#ifndef HANDLEARGS_H
#define HANDLEARGS_H

#include <string>
using namespace std;

struct basicInfo
  {
    string type;
    string path;
    string password;
    string newPath;
  };

basicInfo* handleArgs(char** argv, int argc);

#endif