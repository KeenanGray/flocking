#ifndef _boid // if this class hasn't been defined, the program can define it
#define _boid // by using this if statement you prevent the class to be called more than once which would confuse the compiler

#include "ofMain.h" // include this to have a reference to the openFrameworks framework

class boid
{
public: 
    //open frameworks methods. 
    // methods, equivalent to specific functions of your class objects
    void setup();  // setup method, use this to setup your object's initial state
    void update(); // update method, used to refresh your objects properties
    void draw();   // draw method, this where you'll do the object's drawing

    //steering methods
    ofVec3f alignment(const vector<boid>& boids);  // returns a steering vector resulting from the average direction of nearby boids
    ofVec3f cohesion(const vector<boid>& boids);   // returns a steering vector resulting from the average position of nearby boids
    ofVec3f seperation(const vector<boid>& boids); // returns a steering vector computed by a desire to move away from nearby boids

    void flock(const vector<boid>& boids); //change the boids acceleration by accumulating the 3 steering vectors.

    boid(); // constructor

private:
    //our boids will be represented by open frameworks cones
    //here are the cone properties.
    ofConePrimitive cone;
    float coneRadius = 10;
    float coneHeight = 50;
    float coneRadiusSegments = 12;
    float coneHeightSegments = 12;

    //steering properties
    ofVec3f position = ofVec3f(0, 0, 0);
    ofVec3f velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0);
    ofVec3f acceleration = ofVec3f(0, 0, 0);

    //we can also use a open frameworks line to draw the direction of our vectors.
    ofPolyline line;

};
#endif