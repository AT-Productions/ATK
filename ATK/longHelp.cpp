#include <string>
#include "help.h"
#include "getVersion.h"

string longHelp()
{
    string result = getVersion() + R"(
        Usage: atk [TYPE] [PATH] [KEY]
        ---------------------------
        EXAMPLES:
        atk -t dir -p \"./dir/name/\" -k 1234\n
        atk -t file -p \file.ext/" -k "pass 123"\n
        ---------------------------
        ARGUMENTS:
        -t, --type      FILE TYPE: Choose \'dir\' for directories or \'file\' for files.
        -p, --path      PATH: Specify the target path, either relative like \"./filename.ext\" or an absolute path.
        -k, --key       KEY: Set the key for encryption. It can be any string, enclosed in quotes if needed.
        ---------------------------
        OPTIONS:
        --help          Display this help message.
        -v, --version   Show the current version of atk.
        -l, --location  Return the location of the atk.exe executable.
        ---------------------------
        )";
    return result;
}