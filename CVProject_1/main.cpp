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

#include "config.h"
#include "FeatureExtractor.cpp"
#include "FileController.cpp"

int main() {
    vector<string> inputdata;
    FileController myFileController;
    FeatureExtractor myExtractor;
    
    inputdata   = myFileController.requestInputs();
    int n_input = (int) inputdata.size();
    vector<Result> myAllResult;
    
    // read input data
    int n;
    for (n = 0; n < n_input; n++) {
        // read input data
        vector<vector<int> > imageVec = myFileController.readFile(inputdata.at(n));
    
        // compute all the process of feature extraction
        myExtractor.extractAreaAndCentroid(imageVec);
        myExtractor.extractPerimeter(imageVec);
        myExtractor.extractAxisInertia(imageVec);
    
        // get all results of feature extraction   
        Result myResult;
        myResult.area      = myExtractor.getImgArea();
        myResult.centroidR = myExtractor.getImgCentroidR();
        myResult.centroidC = myExtractor.getImgCentroidC();
        myResult.perimeter = myExtractor.getImgPerimeter();
        myResult.axis      = myExtractor.getImgAxisInertia();
        myAllResult.push_back(myResult);
        
    }
    cout << n << "," << (n_input - 1) << endl;
    if (n == n_input) {
        // output all results into a file.
        myFileController.outputResult(inputdata, myAllResult);
    }
    
}