Setup environmental variables by running:
 * run_setup.bat

---

Build this program with by running either:
 * .windows_build.bat
 * .linux_build.sh

Make msi with WiX:
```
wix build -o atkInstaller.msi .\installation\Project.wxs .\installation\components.wxs .\installation\folder.wxs
```