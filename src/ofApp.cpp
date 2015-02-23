#include "ofApp.h"
#include "duck.h"

// Font:
ofTrueTypeFont font;

// Audio:
ofSoundPlayer start;
ofSoundPlayer gun;
ofSoundPlayer quack;

// Sky colour:
ofColor sky;

// Images:
ofImage grass;
ofImage crosshairs;

// Ducks:
#define NUM_DUCKS 8
duck ducks[NUM_DUCKS];
int killCount = 0;

// Crosshairs variables:
int crosshairsX, crosshairsY;

// Blinking:
int blinkState;
bool blinked;

// Game over state:
bool gameOver = false;


//--------------------------------------------------------------
void ofApp::setup()
{
    // Hide mouse cursor:
    ofHideCursor();
    
    // Set up OSC communication
    receiver.setup(PORT);
    
    // Load font:
    font.loadFont("fonts/slkscr.ttf", 30);
    
    // Load audio files:
    start.loadSound("audio/start.mp3");
    gun.loadSound("audio/gun.mp3");
    quack.loadSound("audio/quack.mp3");
    
    // Set sky colour:
    sky = ofColor(150, 200, 255);
    
    // Load images:
    //grass.loadImage("images/grass.gif");
    grass.loadImage("images/grass.png");
    crosshairs.loadImage("images/crosshairs.png");
    
    for (int i = 0; i < NUM_DUCKS; i++)
    {
        ducks[i].duckR1.loadImage("images/duckR1.gif");
        ducks[i].duckR2.loadImage("images/duckR2.gif");
        ducks[i].duckR3.loadImage("images/duckR3.gif");
        ducks[i].duckL1.loadImage("images/duckL1.gif");
        ducks[i].duckL2.loadImage("images/duckL2.gif");
        ducks[i].duckL3.loadImage("images/duckL3.gif");
        ducks[i].duckF.loadImage("images/duck_3.gif");
    }
    
    // Play opening music:
    //start.play();
}


//--------------------------------------------------------------
void ofApp::update()
{
    // While there are new OSC messages:
    while(receiver.hasWaitingMessages())
    {
        // Retrieve the next message:
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        // If it is a Blink message:
        if(m.getAddress() == "/muse/elements/blink")
        {
            // Grab state as int:
            blinkState = m.getArgAsInt32(0);
            
            // Test message:
            //cout << "blinkState = " << blinkState << endl;
            
            // Check blink state:
            blinked = blinkState ? true : false;
        }
        
        // If it is an Accelerometer message:
        if(m.getAddress() == "/muse/acc")
        {
            // Grab X value as int:
            //int accelX = m.getArgAsInt32(2);
            int accelX = m.getArgAsFloat(2);
            
            // Grab Y value as int:
            //int accelY = m.getArgAsInt32(0);
            int accelY = m.getArgAsFloat(0);
            
            //cout << "X: " << accelX << ", Y: " << accelY << endl;
            
            // Map accelerometer values to crosshairs:
            //crosshairsX = ofMap(accelX, -280, 520, 0, ofGetWidth(), true);
            //crosshairsY = ofMap(accelY, -40, 420, 0, ofGetHeight(), true);
        }
    }
    
    // Update duck locations:
    for (int i = 0; i < NUM_DUCKS; i++)
    {
        ducks[i].update(quack);
    }
}


//--------------------------------------------------------------
void ofApp::draw()
{
    // Draw sky:
    ofBackground(sky);
    
    // Draw ducks:
    for (int i = 0; i < NUM_DUCKS; i++)
    {
        ducks[i].draw();
    }
    
    // Draw grass:
    //ofSetColor(255);
    grass.draw(0, ofGetHeight()/2);
    
    // Draw crosshairs:
    crosshairs.draw(crosshairsX - crosshairs.width/2, crosshairsY - crosshairs.height/2);
    
    // If user blinks:
    if (blinked)
    {
        // Pull trigger:
        gunshot();
    }
    else
    {
        // Sky returns to blue:
        sky = ofColor(150, 200, 255);
    }
    
    // If GAME OVER:
    if (gameOver)
    {
        // Display "YOU WIN!":
        font.drawString("YOU WIN!", 610, 70);
        
        // Display "NEW GAME" button:
        ofSetColor(255, 0, 0);
        font.drawString("NEW GAME", 600, 830);
        ofSetColor(255);
    }
}


//--------------------------------------------------------------
void ofApp::gunshot()
{
    // Play gun sound:
    gun.play();
    
    // Sky flashes white:
    sky = ofColor(255, 255, 255);
    
    // Check if ducks have been shot:
    for (int i = 0; i < NUM_DUCKS; i++)
    {
        // If duck has been hit:
        if ((crosshairsX > ducks[i].x && crosshairsX < ducks[i].x + ducks[i].duckR1.width) && (crosshairsY > ducks[i].y && crosshairsY < ducks[i].y + ducks[i].duckR1.height) && ducks[i].flying)
        {
            // Update duck state:
            ducks[i].flying = false;
            ducks[i].falling = true;
            
            // Update duck speeds:
            ducks[i].speedX = 0;
            ducks[i].speedY = 5;
            
            // Update kill count:
            killCount++;
        }
    }
    
    // If all ducks killed:
    if (killCount == NUM_DUCKS)
    {
        // Update state:
        gameOver = true;
    }
    
    // If game is over:
    if (gameOver)
    {
        // If "NEW GAME" button clicked:
        if ((crosshairsX > 120 && crosshairsX < 360) && (crosshairsY > 660 && crosshairsY < 700))
        {
            // Update state:
            gameOver = false;
            
            // Reset kill count:
            killCount = 0;
            
            // Reset ducks:
            for (int i = 0; i < NUM_DUCKS; i++)
            {
                ducks[i].flying = true;
                ducks[i].falling = false;
                ducks[i].dead = false;
                
                ducks[i].x = ofRandom(10, 400);
                ducks[i].y = ofRandom(10, 330);
                
                do
                {
                    ducks[i].speedX = ofRandomf()*3;
                    ducks[i].speedY = ofRandomf()*2;
                }
                while (ducks[i].speedX == 0 || ducks[i].speedY == 0);
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    // Update crosshairs position:
    crosshairsX = x;
    crosshairsY = y;
    
    cout << "X: " << x << ", Y: " << y << endl;
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)      // Trigger pulled
{
    // Play gun sound:
    gun.play();
    
    // Sky flashes white:
    sky = ofColor(255, 255, 255);
    
    // Check if ducks have been shot:
    for (int i = 0; i < NUM_DUCKS; i++)
    {
        // If duck has been hit:
        if ((x > ducks[i].x && x < ducks[i].x + ducks[i].duckR1.width) && (y > ducks[i].y && y < ducks[i].y + ducks[i].duckR1.height) && ducks[i].flying)
        {
            // Update duck state:
            ducks[i].flying = false;
            ducks[i].falling = true;
            ducks[i].dead = false;
            
            // Update duck speeds:
            ducks[i].speedX = 0;
            ducks[i].speedY = 5;
            
            // Update kill count:
            killCount++;
        }
    }
    
    // If all ducks killed:
    if (killCount == NUM_DUCKS)
    {
        // Update state:
        gameOver = true;
    }
    
    if (gameOver)
    {
        // If "NEW GAME" button clicked:
        if ((x > 590 && x < 840) && (y > 790 && y < 840))
        {
            // Update state:
            gameOver = false;
            
            // Reset kill count:
            killCount = 0;
            
            // Reset ducks:
            for (int i = 0; i < NUM_DUCKS; i++)
            {
                ducks[i].flying = true;
                ducks[i].falling = false;
                ducks[i].dead = false;
                
                ducks[i].x = ofRandom(10, 1430);
                ducks[i].y = ofRandom(10, 330);
                
                do
                {
                    ducks[i].speedX = ofRandomf()*3;
                    ducks[i].speedY = ofRandomf()*2;
                }
                while (ducks[i].speedX == 0 || ducks[i].speedY == 0);
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)     // Trigger released
{
    // Sky returns to blue:
    sky = ofColor(150, 200, 255);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
