#include <string>
#include "../../include/help.h"
/**
 * RETURNS --HELP MESSAGE
 * 
 * MESSAGE CAN IS IN help.txt
*/
string longHelp(){
    string result = "() means it is not obligatory \nkml TYPE type PATH path (PASS password) \n\nEXAMPLES \nkml -t dir -p \"cwd/filename.atk\" -s 1234 \ncwd points to current directory \n\nkml -t file -p \"C:/path/to/file\" \n\nARG TYPES: \n-t = FILE TYPE \n-p = PATH \n-s = PASSWORD \n----------------------------- \n-l = LOCK THE FILE \n-u = UNLOCK THE FILE \n----------------------------- \nTHESE CAN\'T BE USED WITH THE \nCOMMAND LINE ARGUMENTS IN DEFINITIONS: \nkml -t dir -p \"cwd/filename.atk\" -l \nkml -t file -p \"cwd/filename.atk\" -u \nTHIS WOULD WORK! IT WOULD \nPROMPT FOR THE PASSWORD! \n\nkml -t dir -p cwd -s 1234 -l \nTHIS WOULD NOT WORK! \n----------------------------- \n -help = RETURNS HELP MESSAGE \n-v / --version = RETURNS CURRENT VERSION \n-location = RETURNS .EXE LOCATION OF THE kml.exe";
    return result;
}