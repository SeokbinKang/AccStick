import processing.serial.*; 

Serial myPort;

void setup(){
  size(displayWidth, displayHeight, P3D);
  //size(800, 500, P3D);
  myPort = new Serial(this, Serial.list()[7], 115200);
  myPort.bufferUntil('\n');
  
  cellValue = new float[cWidth][cHeight];
}

int cWidth = 200;
int cHeight = 100;
float[] flex = {300, 0, 0, 0};
float flexMax = 300, flexMin = 0;
float[][] cellValue;
void draw(){
  background(0);
  stroke(255);
  int startX = (displayWidth - 800)/2;
  int startY = (displayHeight - 500)/2;
  int cellWidth = cWidth/8;
  int cellHeight = cHeight/2;
  
  for(int i=0; i<cWidth; i++){
      for(int j=0; j<cHeight; j++){
        cellValue[i][j] = 0;
      }
    }
  
  for (int k=0; k<4; k++){
    int centerX = cellWidth+k*cellWidth*2, centerY = cellHeight;
    for(int i=0; i<cWidth; i++){
      for(int j=0; j<cHeight; j++){
        cellValue[i][j] += flex[k]*gaussian(i-centerX, j-centerY);
      }
    }
  }
  
  camera(width/2+300, height+500, 500+(height/2) / tan(PI/6), width/2+300, height/2, 0, 0, 1, 0);
  
  //stroke(255);
  noStroke();
  //noFill();
  for(int i=0; i<cWidth; i++){
    int diff = 1;
    int base = 0;
    if ((i/(cellWidth))%2==1) {
      diff=-1;
      base = 255;
    }
    int r = base + diff*((i%cellWidth)*255/cellWidth);
    translate(10, 0, 0);
    for(int j=0; j<cHeight; j++){
      translate(0, 10, 0);
      fill(r, 0, cellValue[i][j]*0.2+50);
      //fill(r, 0, 0);
      box(10.0, 10.0, cellValue[i][j]);
    }
    translate(0, -cHeight*10, 0);
  }
  /*
  for(int i=0; i<80; i++){
    int diff = 1;
    int base = 0;
    if ((i/10)%2==1) {
      diff=-1;
      base = 255;
    }
    int r = base + diff*((i%10)*255/10);
    for(int j=0; j<50; j++){
      fill(r, 0, 0);
      rect(startX + i*10, startY+j*10,10,10);
    }
  }
  */
}

float alpha = 1;
float sigmaX = 15, sigmaY = 15;
float gaussian(float x, float y){
  return alpha*pow((float)Math.E, -(x*x/(2*sigmaX*sigmaX) + y*y/(2*sigmaY*sigmaY)));
}


float scale = 10;
void serialEvent(Serial p) { 
  String inString = myPort.readStringUntil('\n');
  String[] words = split(inString, ' ');
  if (words.length <9) return;
  flex[0] = (float(words[2])-550)*scale;
  flex[1] = (float(words[4])-500)*scale;
  flex[2] = (float(words[6])-500)*scale;
  flex[3] = (float(words[8])-500)*scale;
} 



boolean sketchFullScreen() {
  return true;
}

