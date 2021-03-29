#### Structure
A solution contains multiple projects. Each project contains code.

#### Dependencies

lua - pull down the git submodule
sqlite - requires tcl installation

must wrap include in `extern c`
sqlite requires

SQLITE_OS_WINRT=1

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

#### Frustrations

* The Microsoft CppUnitTest is, in practice, worthless because you're limited to one assert per test. In other words, someone's ego prescribes how I should write my tests. Don't use it. 
#### Links
https://github.com/google/googletest/blob/master/docs/primer.md
https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html