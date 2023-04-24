#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sound.load("trouble.mp3"); //loads audio file
    sound.play(); //plays audio file
    sound.setLoop(true); // loops audio file
    
    gui.setup();
    gui.add(volume.set("Volume",0.8,0.1,1.0)); //name, starting val, min, max
    gui.add(decay.set("Decay",0.5,0.0,0.99));
    gui.add(audioReactive.set("Audio Reactive",false,false,true));
    gui.add(gravity.set("Gravity",false,false,true));
    gui.add(gravityStrength.set("Gravity Force",4,1,20));
    gui.add(systemSize.set("System size",120,5,240));
    gui.add(spreadSpeed.set("Particle Weight", 10, 1, 15));
    
    hide = false; //hides gui
    
    fft = new float[128];
    for(int i = 0; i < 128; i++)
    {
        fft[i] = 0; //fills array with 0's
    }
    bands = 128; //frequency bands
    
    
    ofSetBackgroundColor(0, 0, 0); //black background
    
    gravityForce = 0; //gravity variable
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSoundUpdate(); //updates sound engine(IMPORTANT)
    
    sound.setVolume(volume); //makes changes based on GUI changes
    
    cutoffAmount = systemSize;
    
    
    if(gravity == true) //makes particles fall
    {
        gravityForce = gravityStrength; //change this to affect the gravity
    }
    if(gravity == false)
    {
        gravityForce = 0; //drift around
    }
        
    
    soundSpectrum = ofSoundGetSpectrum(bands); // gets frequencies of a sound
    
    for(int i = 0; i < bands; i++)
    {
        fft[i] *= decay; //decays the value of each frequency band
        if(fft[i] < soundSpectrum[i]){
            fft[i] = soundSpectrum[i];
        }
    }
    
    //runs a for loop and first multiplies every frequenecy bands by the decay, then if the frequency bands volume is higher than what it was originally(which at setup is 0) it will match the soundSpectrum value at that frequency
    
    
        for(int i = 0; i < particles.size();i++){
            particles[i].update(gravityForce); //updates each particle and sends the gravity force which depends on gui variables
        }
    }

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255); //black
    
    ofDrawBitmapString("Press any key to stop and restart", 500, 50);
    
    float flickSpeed = spreadSpeed;
    
    
    
    for(int i = 1; i < 127; i++) //finds loudest frequency by running through every value other than 1 and compares this value to one,whichever value is th loudest becomes the first element in the array
    {
        if(fft[0] < fft[i])
        {
            fft[0] = fft[i];
        }
    }
    
    if(audioReactive == true){
        
        for(int i = 0; i < particles.size();i++){
            particles[i].draw(fft[0], flickSpeed); //updates each particle and will pas the value of the loudest frequency to the draw function which will then scale the size of the particle
            
            
        }
        
    }
    
    if(audioReactive == false){  //If non-audioReactive
        for(int i = 0; i < particles.size(); i++)
        {
            particles[i].draw(1,flickSpeed); //If not selected the particle remains the same size
        }
    }
    
    ofPolyline polyline; //Line
    
    for(int j = 0; j < bands; j++)
    {
        if(j <= 20)
        {
            relativeGain = 30.0; //low frequencies show up as louder so they are made to appear smaller
        }
        if(j > 20)
        {
            relativeGain = 560.0; //makes higher frequencies easier to see and lower, smaller
        }
        polyline.addVertex(j + 250,100 - fft[j] * relativeGain); //adds a vertex at each frequency band along the x position of the line
    }
    
    
    
    polyline.draw();
    
    
    
    if(hide == false){
        
        gui.draw(); //draws gui
        
    }
    
    if(particles.size() > cutoffAmount)
    {
      
    particles.erase(particles.begin()); //removes first element
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
       
    hide = !hide;
    if(hide == true)
    {
        sound.stop(); //stops sound
    }
    else{
        sound.play(); //restarts track
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    particle newParticle(mouseX,mouseY); //creates particle at the mouse X and Y value
    particles.push_back(newParticle); //adding to vector
}
    //--------------------------------------------------------------
    void ofApp::mousePressed(int x, int y, int button){
        
    }
    
    //--------------------------------------------------------------
    void ofApp::mouseReleased(int x, int y, int button){
        
    }
    
    //--------------------------------------------------------------
    void ofApp::mouseEntered(int x, int y){
        
    }
    
    //--------------------------------------------------------------
    void ofApp::mouseExited(int x, int y){
        
    }
    
    //--------------------------------------------------------------
    void ofApp::windowResized(int w, int h){
        
    }
    
    //--------------------------------------------------------------
    void ofApp::gotMessage(ofMessage msg){
        
    }
    
    //--------------------------------------------------------------
    void ofApp::dragEvent(ofDragInfo dragInfo){
        
    }
    
    particle::particle(int startX,int startY){
        
        position = glm::vec2(startX, startY); //creates a vec2 of the position
        
        direction = glm::vec2( ofRandom(-2.0, 2.0), ofRandom(-2.0,2.0)); //gives it a random starting diretion
        size = ofRandom(1,20); //random size
        
        shapefft = new float[128];
        
        
        
    }
    particle::~particle(){
        //destructor
    }
    
    
    void particle::update(int gravityForceClass){
        
        position += direction + glm::vec2(0,gravityForceClass); //adds nothing to x value but adds gravity force to Y value
        
    }
    
    void particle::draw(float frequency, float particleSpreadSpeed){
        
        ofSetColor(255 - (frequency * ofRandom(1,100)),255 - (frequency * ofRandom(1,100)),255, 200 + (frequency * 50));
        ofDrawCircle(position,size * frequency); //frequency is the loudest frequency
        //std::cout << frequency << std::endl;
        if(frequency > 1) // if audio reactive is turned on
        {
            direction = direction + glm::vec2(ofRandom(-20,20) * (frequency / particleSpreadSpeed),ofRandom(-20,20) * (frequency / particleSpreadSpeed));
        }
        
    };
