#include <string>
#include "help.h"
#include "getVersion.h"

string longHelp(){
    string result = getVersion() + "atk [TYPE] [PATH] [PASSWORD] \n-----------------------------\nEXAMPLES \natk -t dir -p \"./dir/name/\" -s 1234 \natk -t file -p \"C:\\path\\to\\file.ext\\\" -s 4321 \n\nARG TYPES : \n -t = FILE TYPE | dir | file \n -p = PATH | .\\filename.ext | absolutepath \n -s = PASSWORD | anything | \"you want\"\n--help = Returns this message \n -v / --version = Returns current version \n -l / --location = Returns the location of atk.exe\n-----------------------------\n";
        return result;
}