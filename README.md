# Anvil

Anvil is a collection of algorithms, data structures, and utilities commonly found in standard libraries. Anvil is written with human readability in mind. 

Anvil is not reccomended for use outside of hobby projects because better implementations exist elsewhere.
## Header Only
Anvil currently requires static linking for some functionality. I'm on the fence about making it a header only implementation.

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

#### SDK Includes
C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0

#### Debugging
`lldb -- bin/tests  --gtest_filter=RedBlackTreeTests.InsertDuplicatesKey`

#### Leak Finding
`leaks -atExit -- bin/tests --gtest_filter=SliceTests.InsertPrimitive`

