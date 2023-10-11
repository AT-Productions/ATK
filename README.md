
Setup environmental variables for windows by running:

* **run_setup.bat**

---

**Build**:
*  **0_windows_build.bat**
	- Requires cygwin, msys2 or alternatives with g++ installed.
	- Builds to ATK/build/
* **0_linux_build.sh**
	- Requires g++ or alternatives
	- ATK/build/
*  **Building with Visual Studio 2022**
	- Open project by opening ATK.sln
	- Choose the correct platform
    - Choose C++17 by going to Properties -> C/C++ -> Language -> C++ Language Standard -> ISO C++ 17
    - Choose C++17 by going to Properties -> Configuration Properties -> General -> C++ Language Standard -> ISO C++ 17
	- Change from Debug to Release
	- Build -> Build ATK
	- Build will appear in ATK\Release\ATK.exe

Make msi with WiX:
```
wix build -o atkInstaller.msi .\installation\Project.wxs 
.\installation\components.wxs .\installation\folder.wxs
```
