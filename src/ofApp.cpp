#include "ofApp.h"

#include "boid.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0, 0, 0); // set the background color of the open frameworks window

    boids = vector<boid>(numberOfBoids, boid());

    // setup the boids array.
    for (int i = 0; i < numberOfBoids; i++)
    {
        boids[i].setup();
    }
    ofSetLineWidth(4);
}

//--------------------------------------------------------------

void ofApp::update()
{
    for (int i = 0; i < numberOfBoids; i++)
    {
        boids[i].flock(boids); // add the results of the steering functions for each boid
    }

    // boids should update once all flocking calculations are done.
    for (int i = 0; i < numberOfBoids; i++)
    {
        boids[i].update(); // update the boid positions.
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    for (int i = 0; i < numberOfBoids; i++)
    {
        ofSetColor(boids[i].color[0], boids[i].color[1], boids[i].color[2], 255);
        boids[i].draw();
    }
}
