#define NumPairs 3
#define NumLEDPins 2
#define CHECK_PIN_FREQ 10000
#define PIN_IO_DELAY 500

struct LED
{
  int rPin;
  int gPin;
  int bPin;
  int LEDPins[NumLEDPins];
};

typedef struct
{
  int inPin;
  byte outPin;
  struct LED rgb;
} pinPair;

int counter = 1;

pinPair pinPairs[NumPairs] = {
  //RED Pair
  {A0, 3, {255, 0, 0}},
  //GREEN Pair
  {A1, 5, {0, 255, 0}},
  //BLUE Pair
  {A2, 7, {0, 0, 255}}
};


void setup() {
  Serial.begin(9600);
  for (int x = 0; x < NumPairs; x++) {
    Serial.println("Initiated pin");
    pinPair initiatePin = pinPairs[x];
    pinMode(initiatePin.outPin, OUTPUT);
    //pinMode(initiatePin.inPin, INPUT);
  }

  //TODO SET ALL PINS OFF/LO/WHATEVER
  //SET RGB LED FLASH STATES
}

void loop() {
  // put your main code here, to run repeatedly:
  //Check pin states
  delay(CHECK_PIN_FREQ);
  for (int x = 0; x < NumPairs; x++) {
    pinPair currentPin = pinPairs[x];
    Serial.println("----------BEGIN-------------");
    Serial.print("Reading Pin Pair: " );
    Serial.print(currentPin.inPin);
    Serial.print(", ");
    Serial.println(currentPin.outPin);


    bool currentCheck = checkLoop(currentPin);
    Serial.print("Current State: ");
    Serial.println(currentCheck);
    Serial.println("-----------END------------\n");
  }
}

bool checkLoop(pinPair checkPin) {

  bool success = false;
  //SET HIGHPIN
  if(counter %2 == 0){
    digitalWrite(checkPin.outPin, HIGH);
    Serial.println("SET HIGH");
    }
  counter++;
  
  delay(PIN_IO_DELAY);

  //check if inputPin is High
  Serial.print("Reading... ");
  Serial.println(analogRead(checkPin.inPin));
  if (analogRead(checkPin.inPin) == HIGH) {
    Serial.print("HIGH READ PIN: ");
    Serial.println(checkPin.inPin);
    success =  true;
  }

  //TURN IT AT ALL OFF
  digitalWrite(checkPin.outPin, LOW);
  
  delay(PIN_IO_DELAY);
  return success;
}
