import processing.serial.*;

int facesNum = 0;
PFont f;
float liters = 0;
float facesTimer;
int lastFaces;


Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port

void setup() {
  //size(640, 480);
  fullScreen();
  frameRate(24);
  
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  println(Serial.list());
  
  f = createFont("Futura-Medium.ttc", 64);
  textFont(f);
  facesNum = 0;
  lastFaces = 0;
  
  //myPort.write('A');

}

void draw() {
  //image(video, 0, 0 );
  background(220);
  //scale(2);

  //facesNum = faces.length;

  //liters = facesNum * 6.45;
  
  if ( myPort.available() > 0) {  // If data is available,
    facesNum = myPort.read();         // read it and store it in val
  }
  println(facesNum);
  
  changeLiters(facesNum * 645);
  fill(120, 20, 20);
  text(nf((liters/100), 0, 2) + " litros de sangue ao ano.", width/6, height/2);

  //println(facesNum);

  //for (int i = 0; i < faces.length; i++) {
  //  //println(faces[i].x + "," + faces[i].y);
  //  rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
  //}
}

void changeLiters(float thisLiters) {

  if (liters != thisLiters) {
    if (liters > thisLiters) {

      liters -= 15;
    } else {

      if (liters < thisLiters) {

        liters += 15;
      }
    }
  }
  println(liters + " "+ thisLiters);
}