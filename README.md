Build this program with:
```
g++ -Iinclude/*.h -o atk.exe src/args/*.cpp src/global/*.cpp main.cpp
```

Make msi with WiX:
```
wix build -o atkInstaller.msi .\installation\Project.wxs .\installation\components.wxs .\installation\folder.wxs
```