# File encryptor

Advanced file encryptor with sophisticated encryption algorithm.
Encrypts files of all kind fast and reliably without data loss.
Has build in password feature to lock files after encryption

  # Installation
 -  Visit the  [ATK Releases](https://github.com/Antonako1/ATK/releases)  page on GitHub.
 -  Download the appropriate binary for your operating system and architecture.

---

# Manually setting up on Windows

Setup environmental variables and RegEd by running the following script: ```run_setup.bat```

---

# Building standalone executable

### Windows build

* Run ```0_windows_build.bat```
- Requires cygwin, msys2 or alternatives with g++ installed.
- Build will be generated to ATK\build\ directory.
* Building with Visual Studio 2022
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