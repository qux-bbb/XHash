# XHash

The project is archived. PeaZip's hash function is excellent: https://github.com/peazip/PeaZip

A simple tool for calculating hash, and this is for practicing QT.  


# Usage
You can download it from release, or build it yourself.  

After starting the program, just open the file or drag the file to the program window.  
Hash type is optional, you can choose crc32, md5, sha1, sha256, sha512 or all of them.  


## Build
### Windows Portable
1. Open QT Creator，build release version，find XHash.exe
2. Copy XHash.exe to a new folder
3. Open QT command window  
   If you choose 32-bit release, open `Qt 5.15.2 (MSVC 2019 32-bit)`  
   If you choose 64-bit release, open `Qt 5.15.2 (MSVC 2019 64-bit)`  
4. Go to XHash.exe folder
5. Execute the command: `windeployqt XHash.exe`  

### Windows Installer
Download qt-installer-framework and install:  
https://download.qt.io/official_releases/qt-installer-framework/  

Base on Windows Portable, we can build a Windows Installer.  
1. Copy all file in XHash.exe folder to win_installer_build/packages/Xhash/data/
2. go to win_installer_build folder
3. Execute the command: `<binarycreator.exe path> -c config\config.xml -p packages XHashInstaller.exe`  
   For me, command is `D:\Qt\QtIFW-4.1.1\bin\binarycreator.exe -c config\config.xml -p packages XHashInstaller.exe`

### Linux AppImage
Download linuxdeploy and linuxdeploy-plugin-qt(I choose x86_64), put them in the same folder:  
https://github.com/linuxdeploy/linuxdeploy/releases  
https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases  

Modify linuxdeploy path in build_appimage.sh  

Run build_appimage.sh in the same directory, then an AppImage file will be generated in linux_build folder  
