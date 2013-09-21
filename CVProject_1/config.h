/*
 *  CS 6643   Fall  2012
 *  Project 1:  Geometric Features
 *  Programmer: Ching-Che Chang
 *  Description:
 *      This program is designed for feature extraction of a binary image and built on the environment
 *      of Mac OS X Mountain Lion with the tool of Xcode. Since Mac OS X is an Unix-like OS, the program
 *      is compatible with the OS like Unix and Linux if using the same compilers. This program is
 *      compiled by GNU compiler collection (GCC) of the latest version 4.7.2, which is suitable for
 *      operating systems, such as Unix, Linux, and Mac OS X. Once you install the compiler, you will be
 *      able to compile and run this program on your computer with those operating systems listed above.
 *
 */

#ifndef CVProject_1_config_h
#define CVProject_1_config_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define PI 3.14159265

using namespace std;

struct coordinate {
    int x;
    int y;
};

struct pixel_tag {
    bool external;
    bool internal;
};

struct pair_type {
    int line;
    int diagonal;
};

struct Result {
    double area;
    double centroidR;
    double centroidC;
    double perimeter;
    double axis;
};

#endif
