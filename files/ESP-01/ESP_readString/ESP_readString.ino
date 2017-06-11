//zoomkat 6-29-14 Simple serial echo test
//type or paste text in serial monitor and send

String readString;

void setup() {
  Serial.begin(9600);
  Serial.println("Simple serial echo test"); // so I can keep track of what is loaded
}

void loop() {

  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the String readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured String 
    readString="";
  } 
}

