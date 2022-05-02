#include "boid.h"
boid::boid()
{
    id = count;
    count++;
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
    position.set(rand() % ofGetWidth(), rand() % ofGetHeight(), 0); // create our boid at a random position within the window

    velocity.set(ofRandom(-1, 1), ofRandom(-1, 1), 0);
    velocity.set(velocity.getScaled(this->maxSpeed));
    this->color.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255), 255);
}

void boid::update()
{
    // position is velocity over time
    // so each update we change our position according to the velocity
    position += velocity;

    // velocity is acceleration over time.
    // so each update we change our velocity according to the acceleration
    velocity += acceleration;

    // acceleration will be changed by the steering behavior
    // at the end of our update we want to reset this 0 to avoid accumulation of acceleration
    // this makes it easy for the flock to change direction, or alter it's behavior on the fly.
    acceleration *= 0;
}

void boid::draw()
{
    // draw triangles (made up of lines + points) to visualize the boids
    ofPushMatrix();
    ofTranslate(position.x, position.y, position.z);
    line.clear();
    line.addVertex(ofPoint(-10, 10));
    line.addVertex(ofPoint(0, 0));
    line.addVertex(ofPoint(10, 10));

    float angle = atan2(velocity.y, velocity.x) + PI / 2;
    ofRotateRad(angle);
    line.draw();
    ofPopMatrix();

    // edge handling
    // wrap when x or y is offscreen
    if (this->position.x > ofGetWidth())
        this->position.x = 0;
    if (position.x < 0)
        this->position.x = ofGetWidth();

    if (this->position.y > ofGetHeight())
        this->position.y = 0;
    if (this->position.y < 0)
        this->position.y = ofGetHeight();
}

// return a vector that moves the boid in the
// avg direction of nearby boids
ofVec3f boid::alignment(const vector<boid> &boids)
{
    // we will return a "steering" vector
    // to update our acceleration
    ofVec3f steering = ofVec3f(0, 0, 0);
    return steering;
}

// return a vector that moves the boid in a
// direction according to the average position
// of nearby boids.
ofVec3f boid::cohesion(const vector<boid> &boids)
{
    ofVec3f steering = ofVec3f(0, 0, 0);
    return steering;
}

// return a vector that moves the boid
// in the average direction AWAY from
// nearby boids
ofVec3f boid::seperation(const vector<boid> &boids)
{
    ofVec3f steering = ofVec3f(0, 0, 0);
    return steering;
}

void boid::flock(const vector<boid> &boids)
{
    ofVec3f alignment = boid::alignment(boids);
    ofVec3f cohesion = boid::cohesion(boids);
    ofVec3f seperation = boid::seperation(boids);
    // assign the acceleration to the sum of the steering vectors
    acceleration = alignment + cohesion + seperation;
}