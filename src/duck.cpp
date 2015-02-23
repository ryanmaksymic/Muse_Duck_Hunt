//
//  duck.cpp
//  museTest1
//
//  Created by Ryan Maksymic on 2015-02-18.
//
//

#include "duck.h"

// Constructor:
duck::duck()
{
    // Random position:
    x = ofRandom(10, 400);
    y = ofRandom(10, 330);
    
    // Random non-zero speeds:
    do
    {
        speedX = ofRandomf()*3;
        speedY = ofRandomf()*2;
    }
    while (speedX == 0 || speedY == 0);
    
    cout << "speedX = " << speedX << ", speedY = " << speedY << endl;
    
    // Initial state:
    flying = true;
    falling = false;
    dead = false;
}

void duck::update(ofSoundPlayer quack_)
{
    // Flying state:
    if (flying)
    {
        // Update X position:
        x += speedX;
        
        // If X boundary is hit:
        if (x < (0 - duckR.width) || x > ofGetWidth())
        {
            // Reverse X direction:
            speedX *= -1;
        }
        
        // Update Y position:
        y += speedY;
        
        // If Y boundary is hit:
        if (y < 0 || y > ofGetHeight()/2)
        {
            // Reverse Y direction:
            speedY *= -1;
        }
    }
    // Falling state:
    else if (falling)
    {
        // Update Y position:
        y += speedY;
        
        // When duck hits the ground
        if (y > ofGetHeight()*0.8)
        {
            // Update duck state:
            falling = false;
            dead = true;
            
            // Play quack sound:
            quack_.play();
        }
    }
    else if (dead)
    {
    }
}

void duck::draw()
{
    if (flying)
    {
        // If traveling right:
        if (speedX > 0)
        {
            // Draw right-facing duck:
            duckR.draw(x, y);
        }
        // If traveling left:
        else if (speedX < 0)
        {
            // Draw left-facing duck:
            duckL.draw(x, y);
        }
    }
    else if (falling)
    {
        // Draw falling duck:
        duckF.draw(x, y);
    }
    else if (dead)
    {
    }
}
