

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
    string header = "";
    int plength = 0;
    int elength = 0;
    int dlength = 0;
    bool safe = false;
    string uniq;
    int cypher = 0;
    string headerType = "";
  };

basicInfo* handleArgs(char** argv, int argc);

#endif