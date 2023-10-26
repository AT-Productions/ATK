#include <string>
#include "help.h"
#include "getVersion.h"

string longHelp(){
    string result = getVersion() + "Usage: atk [TYPE] [PATH] [KEY]\n\n---------------------------\n\nEXAMPLES:\n\natk -t dir -p \"./dir/name/\" -k 1234\natk -t file -p \"C:\\path\\to\\file.ext\" -k 4321\n\n---------------------------\n\nARGUMENTS:\n\n-t, --type      FILE TYPE: Choose \'dir\' for directories or \'file\' for files.\n-p, --path      PATH: Specify the target path, either relative like \"./filename.ext\" or an absolute path.\n-k, --key       KEY: Set the key for encryption. It can be any string, enclosed in double quotes if needed.\n\n---------------------------\n\nOPTIONS:\n\n--help          Display this help message.\n-v, --version   Show the current version of atk.\n-l, --location  Return the location of the atk.exe executable.\n\n---------------------------\n";
    return result;
}