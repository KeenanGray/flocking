#include "quadTree.h"

quadTree::quadTree()
{
    this->nodes = vector<boid *>(this->capacity);
    this->top_left = ofPoint(0, 0);
    this->bottom_right = ofPoint(ofGetWidth(), ofGetHeight());
    this->capacity = 10;

    b = NULL;
    this->topLeftTree = NULL;
    this->topRightTree = NULL;
    this->botLeftTree = NULL;
    this->botRightTree = NULL;
}
quadTree::quadTree(ofPoint tl, ofPoint br)
{
    this->nodes = vector<boid *>(this->capacity);
    this->top_left = tl;
    this->bottom_right = br;
    this->capacity = 50;

    b = NULL;
    this->topLeftTree = NULL;
    this->topRightTree = NULL;
    this->botLeftTree = NULL;
    this->botRightTree = NULL;
}

void quadTree::insert(boid *boid)
{
    if (boid == NULL)
    {
        return;
    }

    // make sure that the boid is within the bounds
    if (!inBoundary(boid->position))
        return;

    // if we are less than capacity, insert to our list.
    if (this->nodes.size() < this->capacity)
    {
        this->nodes.push_back(b);
    }
    else
    {
        // if we can subdivide
        if (abs(this->top_left.x - this->bottom_right.x) <= 1 &&
            abs(this->top_left.y - this->bottom_right.y) <= 1)
        {
            if (this->b == NULL)
                this->b = boid;
            return;
        }

        // subdivide function
        if ((this->top_left.x + this->bottom_right.x) / 2 >= boid->position.x)
        {
            // Indicates topLeftTree
            if ((this->top_left.y + this->bottom_right.y) / 2 >= boid->position.y)
            {
                if (this->topLeftTree == NULL)
                    this->topLeftTree = new quadTree(
                        ofPoint(this->top_left.x, this->top_left.y),
                        ofPoint((this->top_left.x + this->bottom_right.x) / 2,
                                (this->top_left.y + this->bottom_right.y) / 2));
                topLeftTree->insert(boid);
            }

            // Indicates botLeftTree
            else
            {
                if (this->botLeftTree == NULL)
                    this->botLeftTree = new quadTree(
                        ofPoint(this->top_left.x,
                                (this->top_left.y + this->bottom_right.y) / 2),
                        ofPoint((this->top_left.x + this->bottom_right.x) / 2,
                                this->bottom_right.y));
                this->botLeftTree->insert(boid);
            }
        }
        else
        {
            // Indicates topRightTree
            if ((this->top_left.y + this->bottom_right.y) / 2 >= boid->position.y)
            {
                if (this->topRightTree == NULL)
                    this->topRightTree = new quadTree(
                        ofPoint((this->top_left.x + this->bottom_right.x) / 2,
                                this->top_left.y),
                        ofPoint(this->bottom_right.x,
                                (this->top_left.y + this->bottom_right.y) / 2));
                this->topRightTree->insert(boid);
            }

            // Indicates botRightTree
            else
            {
                if (this->botRightTree == NULL)
                    this->botRightTree = new quadTree(
                        ofPoint((this->top_left.x + this->bottom_right.x) / 2,
                                (this->top_left.y + this->bottom_right.y) / 2),
                        ofPoint(this->bottom_right.x, this->bottom_right.y));
                botRightTree->insert(boid);
            }
        }
    }
}

// Find a node in a quadtree
boid *quadTree::search(ofPoint p)
{
    // Current quad cannot contain it
    if (!inBoundary(p))
        return NULL;

    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (this->b != NULL)
        return this->b;

    if ((this->top_left.x + this->bottom_right.x) / 2 >= p.x)
    {
        // Indicates topLeftTree
        if ((this->top_left.y + this->bottom_right.y) / 2 >= p.y)
        {
            if (this->topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }

        // Indicates botLeftTree
        else
        {
            if (this->botLeftTree == NULL)
                return NULL;
            return this->botLeftTree->search(p);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((this->top_left.y + this->bottom_right.y) / 2 >= p.y)
        {
            if (this->topRightTree == NULL)
                return NULL;
            return this->topRightTree->search(p);
        }

        // Indicates botRightTree
        else
        {
            if (this->botRightTree == NULL)
                return NULL;
            return this->botRightTree->search(p);
        }
    }
};

std::vector<boid *> &quadTree::getNearby(quadTree quad, ofPoint tl, ofPoint br)
{
    // Prepare an array of results

    /*
        // Check objects at this quad level
        for (int p = 0; p < quad.nodes.size(); p++)
        {
            if (quad.nodes[p]->position.x > tl.x &&
                quad.nodes[p]->position.x < br.x &&
                quad.nodes[p]->position.y<br.y &&this->nodes[p]->position.y> tl.y)
            {
                if (quad.nodes[p] != NULL)
                {
                    // cout << quad.nodes[0]->id << endl;
                    //results.push_back(this->nodes[p]);
                }
            }
        }

        // Terminate here, if there are no children
        if (this->topLeftTree == NULL)
            return results;

        // Otherwise, add the points from the children
        std::vector<boid *> b = this->topLeftTree->getNearby(*this->topLeftTree, tl, br);
        results.insert(results.end(), b.begin(), b.end());

        b = this->topRightTree->getNearby(*this->topRightTree, tl, br);
        results.insert(results.end(), b.begin(), b.end());

        b = this->botLeftTree->getNearby(*this->botLeftTree, tl, br);
        results.insert(results.end(), b.begin(), b.end());

        b = this->botRightTree->getNearby(*this->botRightTree, tl, br);
        results.insert(results.end(), b.begin(), b.end());

        return results;
        */
}

bool quadTree::inBoundary(ofPoint p)
{
    return (p.x >= this->top_left.x &&
            p.x <= this->bottom_right.x &&
            p.y >= this->top_left.y &&
            p.y <= this->bottom_right.y);
}