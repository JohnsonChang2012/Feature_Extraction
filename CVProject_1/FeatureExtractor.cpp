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
 * Class: FeatureExtractor
 *   provide several methods to calculate the features of area, centroid, perimeter, and axis of least inertia
 *
 */
class FeatureExtractor {
private:
    double imgArea, imgCentroidR,imgCentroidC, imgPerimeter, imgAxisInertia;

    /*
     * Method Member: getNeighborCoordinate(int, coordinate)
     *     get the coordinate of the next 8-connected neighbor
     *
     * Parameters:
     *     int n         - a request of which coordinate of 8-connected neighbor will be returned
     *     coordinate sp - a struct storing one pair of x- and y-value in the x-y coordinate system
     *
     * Return:
     *     coordinate neighbor - the coordinate of the next 8-connected neighbor
     *
     */
    coordinate getNeighborCoordinate(int n, coordinate &sp) {
        coordinate neighbor;
            
        if (n == 0) neighbor.x = sp.x - 1;
        if (n == 0) neighbor.y = sp.y - 1;
            
        if (n == 1) neighbor.x = sp.x;
        if (n == 1) neighbor.y = sp.y - 1;
            
        if (n == 2) neighbor.x = sp.x + 1;
        if (n == 2) neighbor.y = sp.y - 1;
            
        if (n == 3) neighbor.x = sp.x - 1;
        if (n == 3) neighbor.y = sp.y;
            
        if (n == 4) neighbor.x = sp.x + 1;
        if (n == 4) neighbor.y = sp.y;
            
        if (n == 5) neighbor.x = sp.x - 1;
        if (n == 5) neighbor.y = sp.y + 1;
            
        if (n == 6) neighbor.x = sp.x;
        if (n == 6) neighbor.y = sp.y + 1;
            
        if (n == 7) neighbor.x = sp.x + 1;
        if (n == 7) neighbor.y = sp.y + 1;
        
        return neighbor;
    }
    
    /*
     * Method Member: getBoundaryNeighborCoordinate(int, int, coordinate)
     *     get the coordinate of the next 8-connected neighbor
     *
     * Parameters:
     *     int b_position - there are four possible value for this.
     *                      0: a background pixel is located on the top of current pixel
     *                      1: a background pixel is located on the right side of current pixel
     *                      2: a background pixel is located on the bottom of current pixel
     *                      3: a background pixel is located on the left side of current pixel
     *     int n         - a request of which coordinate of 8-connected neighbor will be returned
     *     coordinate sp - a struct storing one pair of x- and y-value in the x-y coordinate system
     *
     * Return:
     *     coordinate neighbor - the coordinate of the next 8-connected neighbor in the boundary 
     *
     */
    coordinate getBoundaryNeighborCoordinate(int b_position, int n, coordinate &sp) {
        coordinate neighbor;
        // when b is located on the top of current pixel
        if (b_position == 0) {
            
            if (n == 0) neighbor.x = sp.x + 1;
            if (n == 0) neighbor.y = sp.y - 1;
            
            if (n == 1) neighbor.x = sp.x + 1;
            if (n == 1) neighbor.y = sp.y;
            
            if (n == 2) neighbor.x = sp.x + 1;
            if (n == 2) neighbor.y = sp.y + 1;
            
            if (n == 3) neighbor.x = sp.x;
            if (n == 3) neighbor.y = sp.y + 1;
            
            if (n == 4) neighbor.x = sp.x - 1;
            if (n == 4) neighbor.y = sp.y + 1;
            
            if (n == 5) neighbor.x = sp.x - 1;
            if (n == 5) neighbor.y = sp.y;
            
            if (n == 6) neighbor.x = sp.x - 1;
            if (n == 6) neighbor.y = sp.y - 1;
        }
        
        // when b is located on the right side of current pixel
        if (b_position == 1) {
            
            if (n == 0) neighbor.x = sp.x + 1;
            if (n == 0) neighbor.y = sp.y + 1;
                    
            if (n == 1) neighbor.x = sp.x;
            if (n == 1) neighbor.y = sp.y + 1;
                    
            if (n == 2) neighbor.x = sp.x - 1;
            if (n == 2) neighbor.y = sp.y + 1;
                    
            if (n == 3) neighbor.x = sp.x - 1;
            if (n == 3) neighbor.y = sp.y;
                    
            if (n == 4) neighbor.x = sp.x - 1;
            if (n == 4) neighbor.y = sp.y - 1;
                    
            if (n == 5) neighbor.x = sp.x;
            if (n == 5) neighbor.y = sp.y - 1;
                    
            if (n == 6) neighbor.x = sp.x + 1;
            if (n == 6) neighbor.y = sp.y - 1;
        }
        
        // when b is located on the bottom of current pixel
        if (b_position == 2) {
            if (n == 0) neighbor.x = sp.x - 1 ;
            if (n == 0) neighbor.y = sp.y + 1;
            
            if (n == 1) neighbor.x = sp.x - 1;
            if (n == 1) neighbor.y = sp.y;
            
            if (n == 2) neighbor.x = sp.x - 1;
            if (n == 2) neighbor.y = sp.y - 1;
            
            if (n == 3) neighbor.x = sp.x;
            if (n == 3) neighbor.y = sp.y - 1;
            
            if (n == 4) neighbor.x = sp.x + 1;
            if (n == 4) neighbor.y = sp.y - 1;
            
            if (n == 5) neighbor.x = sp.x + 1;
            if (n == 5) neighbor.y = sp.y;
            
            if (n == 6) neighbor.x = sp.x + 1;
            if (n == 6) neighbor.y = sp.y + 1;
        }
        
        // when b is located on the left side of current pixel
        if (b_position == 3) {
            if (n == 0) neighbor.x = sp.x - 1 ;
            if (n == 0) neighbor.y = sp.y - 1;
            
            if (n == 1) neighbor.x = sp.x;
            if (n == 1) neighbor.y = sp.y - 1;
            
            if (n == 2) neighbor.x = sp.x + 1;
            if (n == 2) neighbor.y = sp.y - 1;
            
            if (n == 3) neighbor.x = sp.x + 1;
            if (n == 3) neighbor.y = sp.y;
            
            if (n == 4) neighbor.x = sp.x + 1;
            if (n == 4) neighbor.y = sp.y + 1;
            
            if (n == 5) neighbor.x = sp.x;
            if (n == 5) neighbor.y = sp.y + 1;
            
            if (n == 6) neighbor.x = sp.x - 1;
            if (n == 6) neighbor.y = sp.y + 1;
        }
        return neighbor;
    }
        
    /*
     * Method Member: isBoundaryElements(vector<<vector<int> >, coordinate)
     *     check if it is an element of boundary based on 8-connected strategy
     *
     * Parameters:
     *     vector imageVec - a 2-D vector storing the values of pixels
     *     coordinate sp   - a struct storing one pair of x- and y-value in the x-y coordinate system
     *
     * Return:
     *     true  - the pixel is the boundary element
     *     false - the pixel is not the boundary element
     *
     */
    bool isBoundaryElements(vector<vector<int> > &imageVecClone, coordinate &sp) {
        coordinate neighbor;
        
        int four_sum  = 0;
        int eight_sum = 0;
        int max_y    = (int) imageVecClone.size();
        int max_x    = (int) imageVecClone[0].size();
        
        for (int n = 0; n < 8; n++) {
            // get the next 8-connected neighbor
            neighbor = this->getNeighborCoordinate(n, sp);
            // ignore the neighbor out of dimension
            if (neighbor.x == -1 || neighbor.y == -1 || neighbor.x == max_x || neighbor.y == max_y) continue;
            // 0, 2, 5, 6 mean the neighbors in the diagonal direction
            if (n == 0 || n == 2 || n == 5 || n == 7) eight_sum += imageVecClone[neighbor.y][neighbor.x];
            // 1, 3, 4, 6 mean the neighbors in the vertical or horizonal direction
            if (n == 1 || n == 3 || n == 4 || n == 6) four_sum += imageVecClone[neighbor.y][neighbor.x];
        }
        // if the cases is that the sum of all four connected neighbors is 4 and the sum of all eight connected neighbors is less than and equal to 4
        // then it is not a boundary element. Otherwise, it will be a boundary element.
        if (four_sum == 4 && eight_sum <= 4) return false;
        return true;
    }
    
    /*
     * Method Member: findNextBoundaryNeighbor(vector<<vector<int> >, int, coordinate, vector<pixel_count>)
     *     find out the next element of boundary based on the least number of visiting
     *
     * Parameters:
     *     vector imageVec - a 2-D vector storing the values of pixels
     *     int b_position  - there are four possible value for this.
     *                       0: a background pixel is located on the top of current pixel
     *                       1: a background pixel is located on the right side of current pixel
     *                       2: a background pixel is located on the bottom of current pixel
     *                       3: a background pixel is located on the left side of current pixel
     *
     *     coordinate sp   - a struct storing one pair of x- and y-value in the x-y coordinate system
     *
     * Return:
     *     coordinate - the coordinate of the next boundary neighbor
     *
     */
    coordinate findNextBoundaryNeighbor(vector<vector<int> > &imageVecClone, int b_position, coordinate &sp) {
        coordinate candidate_neighbor;
        
        for (int n = 0; n < 7; n++) {
            // get the next 8-connected neighbor
            candidate_neighbor = this->getBoundaryNeighborCoordinate(b_position, n, sp);
            
            // ignore background pixels
            if (imageVecClone[candidate_neighbor.y][candidate_neighbor.x] == 0) continue;
            
            // find out all possible next boundary neighbor in the clockwise order.
            if (imageVecClone[candidate_neighbor.y][candidate_neighbor.x] == 1 && isBoundaryElements(imageVecClone, candidate_neighbor)) return candidate_neighbor;
        }
        
        candidate_neighbor.x = -1;
        candidate_neighbor.y = -1;
        return candidate_neighbor; // no neighbor;
    }
    
    /*
     * Method Member: isLinearMove(coordinate, coordinate)
     *     find out which kind of moving from a coordinate to another
     *
     * Parameters:
     *     coordinate cp - a struct storing current pair of x- and y-value in the x-y coordinate system
     *     coordinate np - a struct storing the next pair of x- and y-value in the x-y coordinate system
     *
     * Return:
     *     true  - it is a linear moving
     *     false - it is a diagonal moving
     *
     */
    bool isLinearMove(coordinate &cp, coordinate &np) {
        int diff_x = abs(cp.x - np.x);
        int diff_y = abs(cp.y - np.y);
        if (diff_x == 0 || diff_y == 0) return true;
        return false;
    }
    
    /*
     * Method Member: determineBPosition(coordinate, coordinate)
     *     find out the position of background pixel in 8-connected neighbors according to 8 moving directions 
     *
     * Parameters:
     *     coordinate sp - a struct storing one starting pair of x- and y-value in the x-y coordinate system
     *     coordinate np - a struct storing the next pair of x- and y-value in the x-y coordinate system
     *
     * Return:
     *     0 - b will be located on the top of the next current pixel (default)
     *     1 - b will be located on the right side of the next current pixel
     *     2 - b will be located on the bottom of the next current pixel
     *     3 - b will be located on the left of the next current pixel
     *
     */
    int determineBPosition(coordinate cp, coordinate np) {
        int x_direction = np.x - cp.x;
        int y_direction = np.y - cp.y;
        
        if (x_direction == 1 && y_direction == 0) return 0;     // b will be located on the top of the next current pixel
        if (x_direction == 0 && y_direction == 1) return 1;     // b will be located on the right side of the next current pixel
        if (x_direction == -1 && y_direction == 0) return 2;    // b will be located on the bottom of the next current pixel
        if (x_direction == 0 && y_direction == -1) return 3;    // b will be located on the left side of the next current pixel
        
        if (x_direction == 1 && y_direction == 1) return 0;     // b will be located on the top of the next current pixel
        if (x_direction == -1 && y_direction == 1) return 1;    // b will be located on the right side of the next current pixel
        if (x_direction == -1 && y_direction == -1) return 2;   // b will be located on the bottom of the next current pixel
        if (x_direction == 1 && y_direction == -1) return 3;    // b will be located on the left side of the next current pixel
        return 0;
    }
    
    /*
     * Method Member: isExistBoundaryPairs(string, vector)
     *     compute the number of visiting of a 8-connected neighbor pixel adjacent to current pixel
     *
     * Parameters:
     *     string                - a string of one pair of coordinates of two pixels
     *     vector boundary_pairs - a vector storing all pairs of coordinates of two pixels in the boundary
     *
     * Return:
     *     true                  - it is a duplicate pair
     *     false                 - it is not
     *
     */
    bool isExistBoundaryPairs(string new_pair, vector<string> &boundary_pairs) {
        bool isExist = false;
        int size = (int) boundary_pairs.size();
        // check if the new_pair exist in the set of boundary_pair already
        for (int n = 0; n < size; n++) {
            if (boundary_pairs.at(n) == new_pair) {
                isExist = true;
                break;
            }
        }
        return isExist;
    }
    
    /*
     * Method Member: toString(int)
     *     convert an integer into a string
     *
     * Parameters:
     *     int i  - an integer to be converted
     *
     * Return:
     *     string - a string from an integer
     *
     */
    string toString(int i) {
        std::string s;
        std::stringstream out;
        out << i;
        s = out.str();
        return s;
    }
    
    /*
     * Method Member: runBoundaryFollowingAlgorithm(coordinate, vector<<vector<int> >, coordinate)
     *     check if it is an element of boundary based on 8-connected strategy
     *
     * Parameters:
     *     coordinate sp         - a struct storing one starting pair of x- and y-value in the x-y coordinate system
     *     vector imageVecClone  - a 2-D vector storing the values of pixels
     *     vector boundary_pixel - a vector storing every pair of x- and y-value in the x-y coordinate system of a boundary element
     *     pair_type b_pars      - a struct storing the numbers of linear moves and diagonal ones
     *
     * Return:
     *     pair_type - a struct storing the numbers of linear moves and diagonal ones
     *
     */
    pair_type runBoundaryFollowingAlgorithm(coordinate sp, vector<vector<int> > &imageVecClone, vector<coordinate> &boundary_pixel, pair_type &b_pairs) {
        coordinate cp, np;             // current and the next pixels
        int b_position = 0;            // b is located on the top of start pixel as default
        boundary_pixel.push_back(sp);  // put starting pixel into the set of boundary pixel
        
        // initialize several data for further process
        cp.x = sp.x;
        cp.y = sp.y;
        b_pairs.line     = 0;
        b_pairs.diagonal = 0;
        
        do {
            // find out the next boundary neighbor
            np = this->findNextBoundaryNeighbor(imageVecClone, b_position, cp);
            
            // if no neighbor exist, the algorithm stop
            if (np.x == -1 || np.y == -1) break;
            
            // store it into sets and decide its moving direction
            boundary_pixel.push_back(np);         // put the neighbor into the set of boundary pixel
                
            // determine if the pairs is a linear move or diagonal one.
            if (this->isLinearMove(cp, np)) b_pairs.line++;
            else b_pairs.diagonal++;
            
            // find out the position of background pixel in 8-connected neighbors according to 8 moving directions
            b_position = this->determineBPosition(cp, np);
            
            // assign the coordinate of np to current pixel
            cp.x = np.x;
            cp.y = np.y;
            
        } while (!(sp.y == cp.y && sp.x == cp.x)); // if cp is not the starting pixel, continue
        
        return b_pairs;
    }
    
    /*
     * Method Member: rndup(double, int)
     *     round up a double type and show it into some decimal place
     *
     * Parameters:
     *     double n - a doulbe value you would like to round up
     *     int prec - how many specific decimal places you need
     *
     * Return:
     *     double
     *
     */
    double rndup(double n, int prec) {
        if (n == 0.0) return n;
        double ex = floor(log10(abs(n))) - (prec + 1) + 1;
        double div = pow(10, ex);
        return floor(n / div + 0.5) * div;
    }
    
public:
    double getImgArea() {
        return this->imgArea;
    }
    double getImgCentroidR() {
        return this->imgCentroidR;
    }
    double getImgCentroidC() {
        return this->imgCentroidC;
    }
    double getImgPerimeter() {
        return this->imgPerimeter;
    }
    double getImgAxisInertia() {
        return this->imgAxisInertia;
    }

    /*
     * Method Member: extractAreaAndCentroid(vector<<vector<int> >)
     *     calculate the two features of Area and Centroid at the same time
     *
     * Parameters:
     *     vector imageVec - a 2-D vector storing the values of pixels
     *
     * Return:
     *     true  - the process is executed successfully
     *     false - the process failed
     */
    bool extractAreaAndCentroid(vector<vector<int> > &imageVec) {
        int pixel      = 0;
        int max_y      = (int) imageVec.size();
        int max_x      = (int) imageVec[0].size();
        double row_sum = 0;
        double col_sum = 0;
        
        // do nothing because there is no pixel information to calculate
        if (imageVec.size() == 0) return false;
        
        // calculate features based on x-y coordinate system
        for(size_t y = 0; y != max_y; ++y) {
            for(size_t x = 0; x != max_x; ++x) {
                if (imageVec[y][x] == 1) {
                    pixel++;                 // calculate the feature Area
                    row_sum += max_y - y;    // calculate the sum of the values of y in x-y coordinate system
                    col_sum += x;            // calculate the sum of the values of x in x-y coordinate system
                }
            }
        }
        this->imgArea = pixel;
        if (pixel == 0) {
            this->imgCentroidR = 0.0;
            this->imgCentroidC = 0.0;
        } else {
            this->imgCentroidR = this->rndup((row_sum / pixel), 2); // calculate the feature Centroid R
            this->imgCentroidC = this->rndup((col_sum / pixel), 2); // calculate the feature Centroid C
        }
        return true;
    }
    
    /*
     * Method Member: extractPerimeter(vector<<vector<int> >)
     *     calculate the feature of perimeter for a connected component
     *
     * Parameters:
     *     vector imageVec - a 2-D vector storing the values of pixels
     *
     * Return:
     *     true  - the process is executed succesfully
     *     false - the process failed
     */
    bool extractPerimeter(vector<vector<int> > &imageVec) {
        int max_y    = (int) imageVec.size();
        int max_x    = (int) imageVec[0].size();
        
        coordinate sp;                     // starting point
        vector<coordinate> rp;             // 8-connected neighbors
        vector<coordinate> boundary_pixel; // store all pixels in the boundary of a connected component
        pair_type b_pairs;                 // store the numbers of linear moves and diagonal ones
        bool isStartingPixel = false;
        
        // initialize imageTagVec and imageVecClone
        int maxc_y    = (int) max_y + 2;
        int maxc_x    = (int) max_x + 2;
        vector<vector<int> > imageVecClone(maxc_y, vector<int>(maxc_x) );
        vector<vector<pixel_tag> > imageTagVec(maxc_y, vector<pixel_tag>(maxc_x) ) ;
        
        // extend one column and one row for imageVecClone and set them 0 as default
        for(int y = 0; y < maxc_y; ++y) {
            for(int x = 0; x < maxc_x; ++x) imageVecClone[y][x] = 0;
        }
        
        for(int y = 0; y < max_y; ++y) {
            for(int x = 0; x < max_x; ++x) imageVecClone[y + 1][x + 1] = imageVec[y][x];
        }
        
        // find starting pixel by checking 8-connected neighbors
        for(int y = 1; y <= max_y; ++y) {
            for(int x = 1; x <= max_x; ++x) {
                //cout << x << ", " << y << endl;
                if (imageVecClone[y][x] == 0) continue;
                sp.x = x;
                sp.y = y;
                isStartingPixel = this->isBoundaryElements(imageVecClone, sp);
                if (isStartingPixel) break;
            }
            if (isStartingPixel) break;
        }
        
        // run algorithm to find out all of pixels in the boundary.
        this->runBoundaryFollowingAlgorithm(sp, imageVecClone, boundary_pixel, b_pairs);
        
        // calculate the feature of perimeter
        this->imgPerimeter = rndup((b_pairs.line + b_pairs.diagonal * sqrt(2)), 2);
        return true;
    }
    
    /*
     * Method Member: extractAxisInertia(vector<<vector<int> >)
     *     calculate the feature of axis of least inertia for a connected component
     *
     * Parameters:
     *     vector imageVec - a 2-D vector storing the values of pixels
     *
     * Return:
     *     true  - the process is executed successfully
     *     false - the process failed
     */
    bool extractAxisInertia(vector<vector<int> > &imageVec) {
        // if the feature of area is still unknown, calculate this feature first
        if (this->imgArea == -1) this->extractAreaAndCentroid(imageVec);
        
        int max_y               = (int) imageVec.size();
        int max_x               = (int) imageVec[0].size();
        double rc, cc, rr       = 0.0;
        double p_rc, p_cc, p_rr = 0.0;
        double result           = 0.0;
        
        // compute the sums of rr, cc, and rc separately
        for(int r = 0; r != max_y; ++r) {
            for(int c = 0; c != max_x; ++c) {
                if ( imageVec[r][c] == 1) {
                    p_rr = (max_y - r) - this->imgCentroidR;  // transfer r into y value of x-y coordinate system
                    p_cc = c - this->imgCentroidC;
                    p_rc = p_rr * p_cc;
                    rr += pow(p_rr, 2);
                    cc += pow(p_cc, 2);
                    rc += p_rc;
                }
            }
        }
        
        // normalize those three values
        rr = rr / this->imgArea;
        cc = cc / this->imgArea;
        rc = rc / this->imgArea;
        
        // compute the final value of alpha
        result = (2 * rc) / (rr - cc);
        result = atan(result) / 2;

        this->imgAxisInertia = this->rndup(result, 2);
        
        return true;
    }
};