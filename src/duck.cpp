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
    x = ofRandom(10, 1430);
    y = ofRandom(10, 330);
    
    // Random non-zero speeds:
    do
    {
        speedX = ofRandomf()*3;
        speedY = ofRandomf()*2;
    }
    while (speedX == 0 || speedY == 0);
    
    // Initial state:
    flying = true;
    falling = false;
    dead = false;
}


// Update:
void duck::update(ofSoundPlayer quack_)
{
    // Flying state:
    if (flying)
    {
        // Update X position:
        x += speedX;
        
        // If X boundary is hit:
        if (x < 0 || x > (ofGetWidth() - duckR1.width))
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
        // Increment Y position:
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


// Draw:
void duck::draw()
{
    // Flying state:
    if (flying)
    {
        // If traveling right:
        if (speedX > 0)
        {
            // Draw one of three right-facing ducks:
            switch ((x/20)%3)
            {
                case 0:
                    duckR1.draw(x, y);
                    break;
                case 1:
                    duckR2.draw(x, y);
                    break;
                case 2:
                    duckR3.draw(x, y);
                    break;
            }
        }
        // If traveling left:
        else if (speedX < 0)
        {
            // Draw one of three left-facing ducks
            switch ((x/20)%3)
            {
                case 0:
                    duckL1.draw(x,y);
                    break;
                case 1:
                    duckL2.draw(x,y);
                    break;
                case 2:
                    duckL3.draw(x,y);
                    break;
            }
        }
    }
    // Falling state:
    else if (falling)
    {
        // Draw falling duck:
        duckF.draw(x, y);
    }
    else if (dead)
    {
    }
}
