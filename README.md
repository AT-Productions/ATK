# Characters
Supports crypting of all characters found in Unicode 15.1.0 version

# Setting up
Setup environmental variables and RegEd by running:
```bash
run_setup.bat
```
This will add the folder to the system pa

---

# Build

*  ```0_windows_build.bat```bash
	- Requires cygwin, msys2 or alternatives with g++ installed.
	- Builds to ATK/build/

---

* ```0_linux_build.sh```bash
	- Requires g++
	- ATK/build/

---

*  **Building with Visual Studio 2022**
	- Open project by opening ATK.sln
	- Choose C++17 by going to Properties -> C/C++ -> Language -> C++ Language Standard -> ISO C++ 17
	- Choose C++17 by going to Properties -> Configuration Properties -> General -> C++ Language Standard -> ISO C++ 17
	- Change from Debug to Release
	- Choose target platform
	- Build -> Build ATK
	- Build will appear in ATK\Release\ATK.exe

---
 
Make msi with WiX:

```bash
wix build -o atkInstaller.msi .\installation\Project.wxs .\installation\components.wxs .\installation\folder.wxs
```
