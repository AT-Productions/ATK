# File and directory encryptor

Advanced file and directory encryptor with sophisticated encryption algorithm.

Encrypts files and directories of all kind fast and reliably without data loss.

Has build in password feature to lock files after encryption

---

 # Installation
 -  Visit the  [ATK Releases](https://github.com/Antonako1/ATK/releases/latest)  page on GitHub.

---

# Usage

```
Usage: ATK -t {dir | file} -p {absolute | relative} -k (keystring) [-s]
        
--------------------------- 
ARGUMENTS: 
        
-t, --type      FILE TYPE : Choose 'dir' for directories or 'file' for files.
-p, --path      PATH : Specify the target path, either relative like "./filename.ext" or an absolute path.
-k, --key       KEY : Set the key for encryption. It can be any string, enclosed in double quotes if needed.
-s, --safe      SAFE : Changes the key so that only the same computer with same user can unlock it.
        
---------------------------
        
OPTIONS:
        
--help          Display this help message.
-v, --version   Show the current version of ATK.
-l, --location  Return the location of the ATK.exe file.

---------------------------
```

---

# Manually setting up on Windows

Setup environmental variables and RegEd by running the following script: ```run_setup.bat```

---

# Building standalone executable

### Windows build

*  Run ```0_windows_build.bat```
	- Requires cygwin, msys2 or alternatives with g++ installed.
	- Build will be generated to ATK\build\ directory.

*  Building with Visual Studio 2022
	- Open project by opening ATK.sln
	- Choose C++17 by going to Properties -> C/C++ -> Language -> C++ Language Standard -> ISO C++ 17
	- Choose C++17 by going to Properties -> Configuration Properties -> General -> C++ Language Standard -> ISO C++ 17
	- Change from Debug to Release
	- Choose target platform
	- Build -> Build ATK
	- Build will appear in ATK\Release\ATK.exe

### Linux build

* Run ```0_linux_build.sh```
	- Requires g++
	- Build will be generated to ATK/build/ directory.

### Making installer executable for Windows

Look at ATK/installation/ directory, it will contain all the steps