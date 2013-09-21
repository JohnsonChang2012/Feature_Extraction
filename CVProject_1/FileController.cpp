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

/*
 * Class: FileController
 *        handle the process of input and output data
 */
class FileController {
private:
    ofstream myfile;
    string outputfile, inputfile;
    
    /*
     * Method Member: getCurrentPath()
     *     find out current path of this program.
     *
     * Return:
     *     string value - a current path.
     */
    string getCurrentPath() {
        stringstream ss;
        string path;
        char cCurrentPath[FILENAME_MAX];
        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) return "./";
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
        for (int i=0;i<FILENAME_MAX;i++) ss << cCurrentPath[i];
        ss >> path;
        return path;
    }
    
    /*
     * Method Member: getFileNameFromPath(string, bool)
     *     get a filename from the string of path
     *
     * Parameters:
     *     string filename     - a file path including path and the name of a file
     *     bool isNonExtension - remove extension of a file or not (default is false)
     *
     * Return:
     *     string - a filename.
     */
    string getFileNameFromPath(string filename, bool isNonExtension=false) {
        // Remove directory if present.
        // Do this before extension removal incase directory has a period character.
        const size_t last_slash_idx = filename.find_last_of("\\/");
        if (std::string::npos != last_slash_idx) {
            filename.erase(0, last_slash_idx + 1);
        }
    
        // Remove extension if present.
        if (isNonExtension) {
            const size_t period_idx = filename.rfind('.');
            if (std::string::npos != period_idx) {
                filename.erase(period_idx);
            }
        }
        return filename;
    }
    
    /*
     * Method Member: splitString(string, char, int)
     *     receives a char delimiter; returns a vector of strings
     *
     * Parameters:
     *     string data - a string to be split
     *     char delim  - a delimiter helping split a string into several parts
     *     int rep     - by default ignores repeated delimiters, unless argument rep == 1
     *
     * Return:
     *     string - a filename.
     */
    vector<string> splitString(string data, char delim, int rep=0) {
        vector<string> flds;
        if (!flds.empty()) flds.clear();  // empty vector if necessary
        
        string buf = "";
        int i = 0;
        while (i < data.length()) {
            if (data[i] != delim) buf += data[i];
            else if (rep == 1) {
                flds.push_back(buf);
                buf = "";
            } else if (buf.length() > 0) {
                flds.push_back(buf);
                buf = "";
            }
            i++;
        }
        if (!buf.empty()) flds.push_back(buf);
        return flds;
    }
    
public:
    
    FileController() {
        this->outputfile = "./result.txt";
    }
    
    FileController(string path) {
        this->outputfile = path + "result.txt";
    }
    /*
     * Method Member: requestInputs()
     *     show info on console and request user to enter data.
     *
     * Return:
     *     vector<vector<int> > - a vector including more than one paths of files
     */
    vector<string> requestInputs() {
        string input_string;
        vector<string> inputdata;
        cout << "This program is designed to extract features from images." << endl;
        cout << "You can enter more than one image as the inputs with delimiting character 'comma'. " << endl;
        cout << "ex:" << endl;
        cout << "    /test/0.raw,1.raw,/test/test2/2.raw" << endl << endl;
        cout << "Now enter your inputs: ";
        getline(cin, input_string);
        
        char delim = ',';
        return this->splitString(input_string, delim);
    }
    
    /*
     * Method Member: readFile(string)
     *     handle reading input data and store all data into a vector.
     *
     * Parameters:
     *     string fileName - a file path including path and the name of an input file.
     *
     * Return:
     *     vector<vector<int> > - a vector stores the values of pixels.
     */
    vector<vector<int> > readFile(string fileName, int row=64, int col=64) {
        int tmp_value, n_bytes;
        unsigned char pixel;
        ifstream inFile;
        
        this->inputfile = fileName;
        
        inFile.open(fileName.c_str(), ios::in | ios::binary);
        if (!inFile) {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        
        vector<vector<int> > tmpVec(row, vector<int> (col));
        n_bytes = 0;
        
        // start to read raw image
        for (int n=0; n< row; n++) {
            for (int m=0; m< col; m++) {
                //getline(inFile, pixel, ',');  // read a value of a pixel with a delimiting character ','

                pixel = inFile.get();
                tmp_value = pixel;                    // casting unsigned char into integer
                // To further calculation, here will transfer the values of pixels into zero or one. 
                if (tmp_value == 255) tmp_value = 0;  // convert 255 into 0 as background
                else tmp_value = 1;                   // convert 0 into 1 as foreground
                tmpVec[n][m] = tmp_value;
                n_bytes++;
            }
        }
        
        inFile.close();
        return tmpVec;
    }
    
    /*
     * Method Member: outputResult(vector, vector)
     *     handle how to print out the result into a text file.
     *
     * Parameters:
     *     vector inputdata   - a vector including more than one paths of files
     *     vector myAllResult - a vector including features of area, centroid, perimeter, and Axis of 
     *                          Least Inertia for each input data
     */
    bool outputResult(vector<string> &inputdata, vector<Result> &myAllResult) {
        
        this->myfile.open (this->outputfile.c_str(), ios::out);
        if (this->myfile.is_open()) {
            int n_result = (int) myAllResult.size();
            for (int n = 0; n < n_result; n++) {
                // show in outputfile
                this->myfile << "                             Feature Extraction\n\n";
                this->myfile << "Filename : " << this->getFileNameFromPath(inputdata.at(n)) << "\n";
                this->myfile << "-----------------------------------------------------------------------------\n";
                this->myfile << "                 Area = " << myAllResult.at(n).area << "\n";
                this->myfile << "             Centroid = (" << myAllResult.at(n).centroidC << ", " << myAllResult.at(n).centroidR << ") based on x-y coordinate system" << "\n";
                this->myfile << "            Perimeter = " << myAllResult.at(n).perimeter << "\n";
                this->myfile << "Axis of Least Inertia = " << myAllResult.at(n).axis << " in degree based on x-y coordinate system\n";
                this->myfile << "-----------------------------------------------------------------------------\n\n\n\n";
                
                // show in console
                cout << "                             Feature Extraction\n\n";
                cout << "Filename : " << this->getFileNameFromPath(inputdata.at(n)) << "\n";
                cout << "------------------------------------------------------------------------------\n";
                cout << "                 Area = " << myAllResult.at(n).area << "\n";
                cout << "             Centroid = (" << myAllResult.at(n).centroidC << ", " << myAllResult.at(n).centroidR << ") based on x-y coordinate system" << "\n";
                cout << "            Perimeter = " << myAllResult.at(n).perimeter << "\n";
                cout << "Axis of Least Inertia = " << myAllResult.at(n).axis << " in degree based on x-y coordinate system\n";
                cout << "------------------------------------------------------------------------------\n";
                cout << endl;
            }
            this->myfile.close();
        } else {
            cout << "Unable to open file" << endl;
        }
        cout << "Your result file is put in the path of " + this->outputfile << endl;
        return true;
    }
};