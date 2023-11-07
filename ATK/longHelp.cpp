#include <string>
#include "help.h"
#include "getVersion.h"

string longHelp(){
    string result = getVersion() +
R"(Usage: ATK -t {dir | file} -p {absolute | relative} -k (keystring) [-s]
        
--------------------------- 
ARGUMENTS: 
        
-t, --type      FILE TYPE : Choose 'dir' for directories or 'file' for files.
-p, --path      PATH : Specify the target path, either relative like "./filename.ext" or an absolute path.
-k, --key       KEY : Set the key for encryption. It can be any string, enclosed in double quotes if needed.
-s, --safe      SAFE : Changes the key so that only the same computer with same user can unlock it.
        
---------------------------
        
OPTIONS:
        
-h, --help      Display this help message.
-v, --version   Show the current version of ATK.
-l, --location  Return the location of the ATK.exe file.

---------------------------
)";
    return result;
}