# Finding PI (π)

One method to estimate the value of π (3.141592...) is by using a Monte Carlo method. This methods consists of drawing on a canvas a square with an inner circle. We then generate a large number of random points within the square and count how many fall in the enclosed circle.

## Code
Code witten in C++ for testing purposes only. 
Open `main.cpp` to check the code. 

## Build
Compile code with: G++. E.g.:
`[PATH]\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe` 

## Result
Example results on i7 processor, single thread

`Samples: 1000000000,
Result PI: ~3.14161,
Duration: 77.894 seconds`
