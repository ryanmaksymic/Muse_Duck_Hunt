//
//  duck.h
//  museTest1
//
//  Created by Ryan Maksymic on 2015-02-18.
//
//

#ifndef __museTest1__duck__
#define __museTest1__duck__

#include <stdio.h>
#include "ofMain.h"

class duck
{
public:
    // Constructor:
    duck();
    
    // Properties:
    ofImage duckR1, duckR2, duckR3;
    ofImage duckL1, duckL2, duckL3;
    ofImage duckF;
    int x, y;
    int speedX, speedY;
    bool flying, falling, dead;
    
    // Methods:
    void update(ofSoundPlayer quack_);
    void draw();
};

#endif /* defined(__museTest1__duck__) */
