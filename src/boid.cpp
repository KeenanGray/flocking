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
    // position.set(ofGetWidth() / 2, ofGetHeight() / 2, 0); // create our boid in the center of the window
    position.set(rand() % ofGetWidth(), rand() % ofGetHeight(), 0); // create our boid at a random position within the window
    velocity.set(ofRandom(-1, 1), ofRandom(-1, 1), 0);
    velocity.set(velocity.getScaled(this->maxSpeed));
    this->color.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255), 255);
}

void boid::flock(const vector<boid> &boids)
{
    ofVec3f alignment = boid::alignment(boids);
    ofVec3f cohesion = boid::cohesion(boids);
    ofVec3f seperation = boid::seperation(boids);
    // assign the acceleration to the sum of the steering vectors
    acceleration += alignment;
    acceleration += cohesion;
    acceleration += seperation;
}

void boid::update()
{
    // position is velocity over time
    // so each update we change our position according to the velocity
    this->position += this->velocity;

    // velocity is acceleration over time.
    // so each update we change our velocity according to the acceleration
    this->velocity += this->acceleration;

    // acceleration will be changed by the steering behavior
    // at the end of our update we want to reset this 0 to avoid accumulation of acceleration
    // this makes it easy for the flock to change direction, or alter it's behavior on the fly.
    this->acceleration *= 0;
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
    float desired_distance = 2500;
    int neighbors = 0;

    // loop through all the boids
    // find the ones that are within the desired distance
    for (boid b : boids)
    {
        float d = this->position.squareDistance(b.position);

        if (b != *this && d < desired_distance)
        {
            neighbors += 1;
            steering += b.velocity; // sum the VELOCITY of all nearby neighbors
        }
    }

    if (neighbors > 0)
    {
        // get the average from our steering vector
        // by dividing the total number of boids
        steering /= neighbors;

        // set the magnitude of the avg steering vector to our max speed
        //||v|| is sqrt(v^2 + y^2)
        // getScaled returns a new vector with the requested length.
        steering.set(steering.getScaled(maxSpeed));

        // then subtract our velocity
        steering -= this->velocity;

        // that gives the middle ground between our velocity
        // and the average.
        // finally limit our steering to the maxForce.
        steering.set(steering.getLimited(maxForce));
    }
    return steering;
}

// return a vector that moves the boid in a
// direction according to the average position
// of nearby boids.
ofVec3f boid::cohesion(const vector<boid> &boids)
{
    // we will return a "steering" vector
    // to update our acceleration
    ofVec3f steering = ofVec3f(0, 0, 0);
    float desired_distance = 2500;
    int neighbors = 0;

    // loop through all the boids
    // find the ones that are within the desired distance
    for (boid b : boids)
    {
        float d = this->position.squareDistance(b.position);

        if (b != *this && d < desired_distance)
        {
            neighbors += 1;
            steering += b.position; // sum the POSITION of all nearby neighbors
        }
    }

    if (neighbors > 0)
    {
        // as in alignment(): we first get the average
        steering /= neighbors;

        // to get the vector towards the avg position we take the difference
        // between the avg location and the boids location
        steering -= this->position;

        // as in alignment(): set the magnitude of the avg steering vector to our max speed
        steering.set(steering.getScaled(maxSpeed));

        // as in alignment(): then subtract our velocity
        steering -= this->velocity;

        // as in alignment(): limit the steering to our maximum force
        steering.set(steering.getLimited(maxForce));
    }
    return steering;
}

// return a vector that moves the boid
// in the average direction AWAY from
// nearby boids
ofVec3f boid::seperation(const vector<boid> &boids)
{
    // we will return a "steering" vector
    // to update our acceleration
    ofVec3f steering = ofVec3f(0, 0, 0);
    float desired_distance = 2500;
    int neighbors = 0;

    // loop through all the boids
    // find the ones that are within the desired distance
    for (boid b : boids)
    {
        float d = this->position.squareDistance(b.position);

        if (b != *this && d < desired_distance)
        {
            neighbors += 1;
            // from the distance of each neighbor
            // add the inverse vector to the steering total
            ofVec3f opp = ofVec3f(0, 0, 0);
            if (d != 0) // just in case
            {
                opp = (this->position - b.position) / d * d;
            }
            steering += opp; // sum the velocity of all nearby neighbors
        }
    }

    if (neighbors > 0)
    {
        // get the average from our steering vector
        // by dividing the total number of boids
        steering /= neighbors;

        // set the magnitude of the avg steering vector to our max speed
        //||v|| is sqrt(v^2 + y^2)
        // getScaled returns a new vector with the requested length.
        steering.set(steering.getScaled(maxSpeed));

        // then subtract our velocity
        steering -= this->velocity;

        // that gives the middle ground between our velocity
        // and the average.
        // finally limit our steering to the maxForce.
        steering.set(steering.getLimited(maxForce));
    }
    return steering;
}
