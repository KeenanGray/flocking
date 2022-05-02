#ifndef _quadTree // if this class hasn't been defined, the program can define it
#define _quadTree // by using this if statement you prevent the class to be called more than once which would confuse the compiler

#include "ofMain.h" // include this to have a reference to the openFrameworks framework
#include "boid.h"

class quadTree
{
public:
    ofPoint top_left;
    ofPoint bottom_right;
    int capacity;
    quadTree();                       // defualt constructor
    quadTree(ofPoint tl, ofPoint br); // constructor

    boid *b;
    std::vector<boid *> nodes;

    // children of the tree
    quadTree *topLeftTree;
    quadTree *topRightTree;
    quadTree *botLeftTree;
    quadTree *botRightTree;

    void insert(boid *);
    boid *search(ofPoint);
    std::vector<boid *> &getNearby(quadTree quad, ofPoint tl, ofPoint br);
    bool inBoundary(ofPoint);
};

#endif