# CppSoup
Xml <-----> Vector

# Introduction to c++

## Option no.3

Implement a set of functions for converting an array of integers to an xml format string and back.

An array of integers, the name of the array and the tag of the array element are passed to the input of the function. 

The vector to string conversion function should return a string in xml format.

The string to vector conversion function must receive a string representation of the array as input and
return the original array.

For example, an array of numbers 1,2,3 with the array name "array" and the element tag "value" must
be converted to the string "<array><value>1</value><value>2</value><value>3</value></array>".

Implement 3 overloads of the described functions:
1. Works with a null-terminated string (const char*).
2. Works with an array of characters and their number (const char* + size_t).
3. Works with an instance of the std::string class

## How to compile

Go to project root directory
`cd your/abs/path/CppSoup`

Then run cmake
`cmake -B ./build/`

Go to build directory
'cd ./build/'

Finally, run make
`make`

main program called "program" will appear in build directory.
tests program will appear in build/tests/ directory.

