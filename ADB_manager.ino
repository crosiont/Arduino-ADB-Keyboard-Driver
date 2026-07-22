/*
 */

int dataPin = 8;


void ADB_talk(int dev_addr, int dev_reg) {
  digitalWrite(dataPin, LOW);
  delayMicroseconds(800); //attention signal
  pinMode(dataPin, INPUT);
  delayMicroseconds(70); //sync signal
  if(dev_addr == 2) { //keyboard is address $2
    Serial.println("starting command");
    pinMode(dataPin, OUTPUT); //send device address
    digitalWrite(dataPin, LOW); //0
    delayMicroseconds(65);
    pinMode(dataPin, INPUT);
    delayMicroseconds(35);
    
    pinMode(dataPin, OUTPUT);
    digitalWrite(dataPin, LOW); //1
    delayMicroseconds(35);
    pinMode(dataPin, INPUT);
    delayMicroseconds(65);
    
    pinMode(dataPin, OUTPUT);
    digitalWrite(dataPin, LOW); //0
    delayMicroseconds(65);
    pinMode(dataPin, INPUT);
    delayMicroseconds(35);
    
    pinMode(dataPin, OUTPUT);
    digitalWrite(dataPin, LOW); //0
    delayMicroseconds(65);
    pinMode(dataPin, INPUT);
    delayMicroseconds(35);
  }
  
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW); //1 //send talk command
  delayMicroseconds(35);
  pinMode(dataPin, INPUT);
  delayMicroseconds(65);

  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW); //1 (11 is talk command)
  delayMicroseconds(35);
  pinMode(dataPin, INPUT);
  delayMicroseconds(65);
  Serial.println("sent talk command");

  if (dev_reg == 0) {
  Serial.println("sending register info");
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW); //0
  delayMicroseconds(65);
  pinMode(dataPin, INPUT);
  delayMicroseconds(35);
  
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW); //0 (register 0 is where keypresses are stored)
  delayMicroseconds(65);
  pinMode(dataPin, INPUT);
  delayMicroseconds(35);
  }
  
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW); //0 (stop bit)
  delayMicroseconds(65);
  pinMode(dataPin, INPUT);
  delayMicroseconds(35);
}

void ADB_reset(void) { //reset on startup
  pinMode(dataPin, OUTPUT);
  digitalWrite(dataPin, LOW);
  delayMicroseconds(1000);
  pinMode(dataPin, INPUT);
}

char keyMap[128] = {
  /*00*/ 'a','s','d','f','h','g','z','x',
  /*08*/ 'c','v', 0 ,'b','q','w','e','r',
  /*10*/ 'y','t','1','2','3','4','6','5',
  /*18*/ '=','9','7','-','8','0',']','o',
  /*20*/ 'u','[','i','p','\n','l','j','\'',
  /*28*/ 'k',';','\\',',','/','n','m','.',
  /*30*/ '\t',' ','`','\b', 0 , 0 , 0 , 0 ,
  /*38*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,

  /*40*/ 0 , 0 , 0 ,'*', 0 ,'+', 0 , 0 ,
  /*48*/ 0 , 0 , 0 ,'/', '\r', 0 ,'-', 0 ,
  /*50*/ 0 ,'=', '0','1','2','3','4','5',
  /*58*/ '6','7', 0 ,'8','9', 0 , 0 , 0 ,

  /*60*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
  /*68*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
  /*70*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
  /*78*/ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
};

void setup() {
  Serial.begin(9600);
  Serial.println("serial monitor test");
  ADB_reset(); //perform bus reset
  delayMicroseconds(100);
  
}

void loop() {
  ADB_talk(2, 0);
  delayMicroseconds(250);
  pinMode(dataPin, INPUT);

  int x = 0;
  uint8_t bits[8];

  for (int i = 0; i < 8; i++) {
    while (digitalRead(dataPin) == HIGH);
    unsigned long start = micros();

    while (digitalRead(dataPin) == LOW);
    unsigned long lowDuration = micros() - start;
    
    if (lowDuration < 50) {
     bits[x] = 1;
     x ++;
   }  else {
     bits[x] = 0;
     x ++;
   }
  }
  
  uint8_t keycode = 0;
  
  for (int i = 0; i < 8; i++) {
    keycode = keycode * 2 + bits[i]; 
  }

 bool released = keycode & 0x80;
 keycode &= 0x7F;

 if (!released && keyMap[keycode] != 0) {
   Serial.print(keyMap[keycode]);
 }
  
}
