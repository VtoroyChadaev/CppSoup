# CppSoup
Xml <-----> Vector

## Introduction

Implement a set of functions for converting an array of integers to an xml format string and back.

An array of integers, the name of the array and the tag of the array element are passed to the input of the function. 

The vector to string conversion function should return a string in xml format.

The string to vector conversion function must receive a string representation of the array as input and
return the original array.

For example, an array of numbers 1,2,3 with the array name "array" and the element tag "value" must
be converted to the string `<array><value>1</value><value>2</value><value>3</value></array>`.

Implemented 3 overloads of the described functions:
1. Works with a null-terminated string (const char*).
2. Works with an array of characters and their number (const char* + size_t).
3. Works with an instance of the std::string class

## How to compile

Clone project repository
`git clone https://github.com/VtoroyChadaev/CppSoup.git`

Go to project root directory
`cd your/abs/path/CppSoup`

Create build directory
`mkdir build`

Then run cmake
`cmake -B ./build/`

Go to build directory
`cd ./build/`

Finally, run make
`make`

Main program called "program" will appear in `build` directory.
Tests program will appear in `build/tests/` directory.

## How to test
### 1. Compile executables 
(w. How to compile)
### 2. Run tests
`./build/tests/tests_program`
### 3. Create coverage report
Create directory for report files
`mkdir tests/report`

Run gcovr
`gcovr -e build/CMakeFiles/ --html-details -o tests/report/coverage.html`

report files wil be in `./tests/report` directory
