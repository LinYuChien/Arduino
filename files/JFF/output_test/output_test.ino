//6位元數字跑馬燈

int BASE = 2;
int NUM = 6;
int index = 0;

void setup() {
  for ( int i = BASE ; i < BASE + NUM ; i++ ){
    pinMode( i, OUTPUT );
  }

}

void loop() {
  for ( int i = BASE ; i < BASE + NUM ; i++){
    digitalWrite( i , LOW );
  }

  digitalWrite( BASE + index , HIGH );
  index = ( index + 1 ) % NUM ;
  delay(100);
}
