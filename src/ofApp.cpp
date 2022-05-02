#include "ofApp.h"

#include "boid.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(255, 255, 255); // set the background color of the open frameworks window
    ofSetFrameRate(30);

    boids = vector<boid>(numberOfBoids);

    // setup the boids array.
    for (int i = 0; i < numberOfBoids; i++)
    {
        boids[i] = boid();
        boids[i].setup();
    }

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
        ofSetLineWidth(4);
        ofSetColor(boids[i].color[0], boids[i].color[1], boids[i].color[2], 255);
        boids[i].draw();
    }
}
