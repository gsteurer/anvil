# Anvil

Anvil is a library of selected algorithms, data structures, and utilities existing for the sole purpose of discovering implementation details of staples commonly found in standard libraries. 

Anvil aims, first and foremost, to provide easier-to-grok-and-test implementations of support commonly provided by standard libraries. While Anvil tries to provide the "best" implementation possible though sacrifices are made to preserve readability. No guarantee is made, however, that this has actually been accomplished. Anvil is written to be read by people before computers. 

Anvil is not reccomended for use outside of hobby projects as superior, optimized, idiomatic implementations exist elsewhere. 

Implementations of the algorithims, data structures, and functions within are derived from commonly used sources and texts and the terms and conditions of the original authors naturally supplant the license placed on top of this library. 

Review and feedback is affably welcome though feedback shrouded in ego or tainted by smug condescension is cordially invited to seek audience elsewhere.  

## Header Only
Anvil currently requires static linking for some functionality. This is considered tech debt and anvil should eventually migrate to a header only implementation. 

## Overview
### Utilities
- Smart Pointer
- Optional/Nullable
### Containers
- Hash Map
- Linked List
- Dynamic Array
- Graph
### Math
- Vectors
- Matricies
### Strings
- Object Oriented C String Wrapper

## Notes

### Visual Studio 2019 Project Structure
A `solution` contains multiple `project`s. Each `project` contains code.

### These notes belong elsewhere:
lua - pull down the git submodule
sqlite - requires tcl installation

must wrap include in `extern c`
sqlite requires

cd sqlite\sqlite
mkdir bld
nmake /f ..\Makefile.msc TOP=..\ FOR_WINRT=1

```

C:\Users\jsteurer\Code\cpp_workbench\tcl\__INSTALL\bin

cd C:\Users\jsteurer\Code\cpp_workbench\anvil\sqlite\sqlite
mkdir bld
cd bld
set PATH=%PATH%;C:\Users\jsteurer\Code\cpp_workbench\tcl\__INSTALL\bin
nmake /f ..\Makefile.msc sqlite3.c TOP=..\..\sqlite
```

* add project to solution - static lib, UWP
* remove pch, targetver, generated file and disable pch in properties
* add git sumodule to new project via CLI
  * ```git submodule add https://github.com/sqlite/sqlite.git .\sqlite\sqlite```
* fetch the submodule and perform any necessary build steps
* in vs2019, in the static lib project for the dependency, add all relevant code and header files
* add any requisite preprocessor definitions; right click > properties > preprocessor 
* right click to build the new static lib
* right click target project > add > references 
* build 

WINRT requires c++ 17
Right click Project > C++ > Language
https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/troubleshooting

#### Frustrations

* The Microsoft CppUnitTest is, in practice, worthless because you're limited to one assert per test. It seems like some sneering time wasting pedantic dipshit at microsoft thinks tests should be written this way.  
#### Links
https://docs.microsoft.com/en-us/windows/uwp/files/file-access-permissions
https://github.com/google/googletest/blob/master/docs/primer.md
https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
https://stackoverflow.com/questions/275004/timer-function-to-provide-time-in-nano-seconds-using-c high resolution timestamps
#### SDK Includes
C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0

#### Leak Finding
`leaks -atExit -- bin/tests --gtest_filter=SliceTests.InsertPrimitive`

