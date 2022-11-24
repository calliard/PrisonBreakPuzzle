#define NumPairs 3
#define NumLEDPins 2
#define CHECK_PIN_FREQ 10000
#define PIN_IO_DELAY 500
#define ANALOG_HIGH 1000 //>1000 seems to be a valid signal connect
#define RAND_MAX NumPairs - 1

typedef struct {
  int red;
  int blue;
  int green;
} color;

struct LED
{
  int rPin;
  int gPin;
  int bPin;
  color color;
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
  {A2, 2, {5, 6, 7}},
  //GREEN Pair
  {A3, 3, {8, 9, 10}},
  //BLUE Pair
  {A4, 4, {11, 12, 13}}
};


color colors[] = {
  //RED
  {255, 0, 0},
  //BLUE
  {0, 0, 255},
  //GREEN
  {0, 255, 0}/*,
  //YELLOW
  {122, 122, 122}*/
};


void setup() {
  randomSeed(analogRead(1));
  Serial.begin(9600);
  for (int x = 0; x < NumPairs; x++) {
    Serial.println("Initiated pin");
    pinPair initiatePin = pinPairs[x];
    pinMode(initiatePin.outPin, OUTPUT);
    shuffleColors();

    //Add a color
    pinPairs[x].rgb.color = colors[x];
    ledOn(pinPairs[x].rgb);
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
    Serial.println(currentCheck ? "ON" : "OFF");
    Serial.println("-----------END------------\n");
  }
}

bool checkLoop(pinPair checkPin) {

  bool success = false;
  //SET HIGHPIN
  if (counter % 2 == 0) {
    digitalWrite(checkPin.outPin, HIGH);
    Serial.println("SET HIGH");
  }
  counter++;

  delay(PIN_IO_DELAY);

  //check if inputPin is High
  int readValue = analogRead(checkPin.inPin);

  if (readValue > ANALOG_HIGH) {
    Serial.print("HIGH READ PIN: ");
    Serial.println(checkPin.inPin);
    success =  true;
  }

  //TURN IT AT ALL OFF
  digitalWrite(checkPin.outPin, LOW);

  delay(PIN_IO_DELAY);
  return success;
}

void shuffleColors() {
  const int colorCount = sizeof colors / sizeof colors[0];
  for (int i = 0; i < colorCount; i++) {
    int n = random(0, colorCount);  // Integer from 0 to colorCount-1
    color temp = colors[n];
    colors[n] =  colors[i];
    colors[i] = temp;
  }
}

void ledOn(LED led) {
  pinMode(led.rPin,   OUTPUT);
  pinMode(led.gPin, OUTPUT);
  pinMode(led.bPin,  OUTPUT);
  analogWrite(led.rPin, led.color.red);
  analogWrite(led.gPin, led.color.green);
  analogWrite(led.bPin, led.color.blue);
}

void ledOff(LED led) {
  analogWrite(led.rPin, LOW);
  analogWrite(led.gPin, LOW);
  analogWrite(led.bPin, LOW);
}
