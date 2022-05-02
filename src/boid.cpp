#include "boid.h"
boid::boid()
{
}

bool operator==(const boid &b1, const boid &b2)
{
    return (b1.id == b2.id);
}

bool operator!=(const boid &b1, const boid &b2)
{
    return (b1.id != b2.id);
}

void boid::setup()
{
   //position.set(ofGetWidth() / 2, ofGetHeight() / 2, 0);  //create our boid in the center of the window
    position.set(rand() % ofGetWidth(), rand() % ofGetHeight(),0); //create our boid at a random position within the window 

    //setup for the cone
    cone.set(coneRadius, coneHeight, coneRadiusSegments, coneHeightSegments);
    cone.setPosition(position.x, position.y, 0);

    //normalized our initial velocity
    //which is initialized randomly in boid.h
    velocity = velocity.getNormalized();
}

void boid::update()
{
    //position is velocity over time
    //so each update we change our position according to the velocity
    position += velocity;

    //velocity is acceleration over time.
    //so each update we change our velocity according to the acceleration
    velocity += acceleration;

    //acceleration will be changed by the steering behavior
    //at the end of our update we want to reset this 0 to avoid accumulation of acceleration
    //this makes it easy for the flock to change direction, or alter it's behavior on the fly.
    acceleration *= 0;
}

void boid::draw()
{
    // get all the faces from the cpme, handy when you want to copy
    // individual vertices or tweak them a little ;)
   // vector<ofMeshFace> triangles = cone.getMesh().getUniqueFaces();

    cone.setPosition(position.x, position.y, position.z);

    // now draw
    cone.draw();
    line.draw();

    // edge handling
    // wrap when x or y is offscreen
    if (position.x > ofGetWidth())
        position.x = 0;
    if (position.x < 0)
        position.x = ofGetWidth();

    if (position.y > ofGetHeight())
        position.y = 0;
    if (position.y < 0)
        position.y = ofGetHeight();
}


//return a vector that moves the boid in the 
//avg direction of nearby boids
ofVec3f boid::alignment(const vector<boid>& boids)
{
    //we will return a "steering" vector 
    //to update our acceleration
    ofVec3f steering = ofVec3f(0, 0, 0);
    return steering;
}

//return a vector that moves the boid in a
//direction according to the average position
//of nearby boids.
ofVec3f boid::cohesion(const vector<boid>& boids)
{
    ofVec3f steering = ofVec3f(0, 0, 0);
    return steering;
}

//return a vector that moves the boid
//in the average direction AWAY from
//nearby boids
ofVec3f boid::seperation(const vector<boid>& boids)
{
    ofVec3f steering = ofVec3f(0, 0, 0);
    return steering;
}

void boid::flock(const vector<boid>& boids)
{
    ofVec3f alignment = boid::alignment(boids);
    ofVec3f cohesion = boid::cohesion(boids);
    ofVec3f seperation = boid::seperation(boids);
    //assign the acceleration to the sum of the steering vectors
    acceleration = alignment + cohesion + seperation;
}