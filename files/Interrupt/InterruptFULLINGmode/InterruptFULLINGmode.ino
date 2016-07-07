//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// Interrupt 0 FULLING mode
// 
// Made by 宇謙 林
// License: CC-BY-SA 3.0
// Downloaded from: https://circuits.io/circuits/2074143-interrupt-0-fulling-mode

//interrupt test

int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);
  attachInterrupt(0, stuffHappened, FALLING);
}

void loop()
{
}

void stuffHappened()
{
  digitalWrite(ledPin, !(digitalRead(ledPin)));
}
