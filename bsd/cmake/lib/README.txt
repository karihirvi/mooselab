Downloads and builds libraries

Windows prerequisites
- Visual Studio (compiled with VS 2013 Pro)
- MinGW + MSYS
  * MinGW, compiled with x86_64-5.1.0-posix-seh-rt_v4-rev0 from http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/5.1.0/threads-posix/seh/
  * MSYS, compiled with msys+7za+wget+svn+git+mercurial+cvs-rev13 from
    http://sourceforge.net/projects/mingwbuilds/files/external-binary-packages/, extract it to MinGW directory
  * For example, let's assume you're using C:\local for manually installed software. Extract MinGW to 
    C:\local\x64-4.8.1-release-posix-seh-rev5 and MSYS to C:\local\msys+7za+wget+svn+git+mercurial+cvs-rev13
    Then copy C:\local\msys+7za+wget+svn+git+mercurial+cvs-rev13\msys folder contents to 
    C:\local\x64-4.8.1-release-posix-seh-rev5\mingw64
- Allow normal users to create symbolic links. Launch secpol.msc via Start -> Run and navigate Local Policies -> User Rights Assignment and select Create symbolic links. Then add you or the whole Users group to the list.

---
Windows & Linux:
1) Create a build folder for cmake. For example, create a 'lib-build' folder on the same level where 'lib' is.
---

Windows (tested with cmake 3.0.1)
Build gtest:
1) Open Visual Studio native tools command prompt, e.g, 'VS2013 x64 Native Tools Command Prompt'
2) cd to the 'lib-build' directory 
3) Run 'cmake -DINSTALL_ROOT=C:/Users/Kari/mooselab/deps -G "Visual Studio 12 2013 Win64" ../lib', but change the install 
   root path first.
   - Note to use / instead of \ in the path
4) run "msbuild gtest-build.vcxproj"

Build other:
1) Open a command prompt (no need for VS prompt)
2) cd to the 'lib-build' directory 
3) Make sure MinGW + MSYS tools are in your path, e.g., make. 
   For example, prepend your %PATH% by a path to MinGW bin directory, e.g., 
   'set PATH=C:\local\x64-4.8.1-release-posix-seh-rev5\mingw64\bin;%PATH%'
4) If needed, remove the cmake cache, i.e., 'rm CMakeCache.txt'
5) Run 'cmake -DINSTALL_ROOT=C:/Users/Kari/mooselab/deps -G "MSYS Makefiles" ../lib', but change the install 
   root path first.
   - Note to use / instead of \ in the path
---
   
Linux:
1) cd to the 'lib-build' directory
2) Run cmake, e.g., cmake -DINSTALL_ROOT=/home/kari/mooselab/deps ../lib
3) run make