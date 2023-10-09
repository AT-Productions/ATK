#include <string>
#include "../../include/help.h"
/**
 * RETURNS --HELP MESSAGE
 * 
 * MESSAGE CAN IS IN help.txt
*/
string longHelp(){
    string result = "Usage atk.exe [TYPE] [PATH] [PASSWORD] \n atk -t type -p path -s password \n\nEXAMPLES \natk -t dir -p \"cwd/filename.atk\" -s 1234 \ncwd points to current directory \n\natk -t file -p \"C:/path/to/file\" -s 4321 \n\nARG TYPES: \n-t = FILE TYPE \n-p = PATH \n-s = PASSWORD \nNOTE if you want to use spaces in  \nyour passwords use ""-characters \natk -t dir -p \"cwd/filename.atk\" -s \"Just A Test\"----------------------------- \n-l = LOCK THE FILE \n-u = UNLOCK THE FILE \n----------------------------- \nTHESE CAN\'T BE USED WITH THE \nCOMMAND LINE ARGUMENTS IN DEFINITIONS: \natk -t dir -p \"cwd/filename.atk\" -l \natk -t file -p \"cwd/filename.atk\" -u \nTHIS WOULD WORK! IT WOULD \nPROMPT FOR THE PASSWORD! \n\natk -t dir -p cwd -s 1234 -l \nTHIS WOULD NOT WORK! \n----------------------------- \n --help = RETURNS HELP MESSAGE \n-v / --version = RETURNS CURRENT VERSION \n-l / --location = RETURNS .EXE LOCATION OF THE atk.exe";
    
        return result;
}