// Sound pin numbers
int MicPin = A0; // X-Achse-Signal
int Digital_Input = 4; // DO
int MicSamples = (1024*2);



//Joystick
int buttonPin = 2; // digital pin connected to switch output

///OUTPUT

//Vib pin numbers
#define VIBRA 3

//RGB pin numbers
int redPin= 7;
int greenPin = 6;
int bluePin = 5;

//fire or door bell
int threshold1 = 70;
int threshold2 = 4;
int threshold;
int fire_threshold = 50;
int in_a_row = 0 ;
int fire_row = 0;
int measurevalue;
int minvalue = 1000;

boolean doorbell = false;
boolean fire = false;

void setup() {
  
  //Mic setup
  pinMode (MicPin, INPUT);
  pinMode (Digital_Input, INPUT);
  
  //Joytsick setup
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  
  //Vib setup
  pinMode(VIBRA, OUTPUT);
  digitalWrite(VIBRA, LOW);

  //RGB setup
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  setColor(240,70,220); //white

  //fire or door bell
  int threshold=threshold1;
       
  Serial.begin (9600); // Start seriell monitor with 9600 bps 
}

void loop() {

  //Mic
  float Analog;
  int Digital;
    
  Analog = analogRead (MicPin) * (5.0 / 1023.0); //Input values are transformed to voltage values
  Digital = digitalRead (Digital_Input);
    
  Serial.print ("Analog voltage level: "); Serial.print (Analog, 4);  Serial.print ("V, "); //... and showed in seriel monitor
  Serial.print ("Limit: ");

  //Joystick
  int buttonState;
  buttonState=digitalRead(buttonPin);
  Serial.print(buttonState);
    
  //Kevin
int measurevalue = MeasureAnalog();
  //Logik für Doorbell
  if (measurevalue > threshold) {
    in_a_row ++;
    if(in_a_row <=4) {
      minvalue = min(minvalue, measurevalue);
    }
    if(in_a_row > 4 && measurevalue > minvalue) {
      in_a_row = 0;
    }
    if(in_a_row == 6) {
      doorbell = true;
    }
    /*if(fire_row > 15) {
      fire = true;
    }*/
  }
  else {
    in_a_row = 0;
    fire_row = 0;
    minvalue = 1000;
  }
  //Logik für Fire
  if (measurevalue > fire_threshold) {
    fire_row ++;
    if (fire_row > 12) {
      fire = true;
    }
  }
  else {
    fire_row == 0;
  }
  
  if (in_a_row >= 3) {
    threshold = threshold2;
  }
  else {
    threshold = threshold1;
  }
  Serial.println(in_a_row);
  Serial.println(fire_row);
  Serial.println("Minvalue "+ String(minvalue));

// Output
  if (doorbell == true) {
    //fire=false;
    in_a_row =0;
    fire_row = 0;
    Serial.println (" Status: Door bell");
    setColor(0, 255, 0); //green
    
    for (int i = 0; i <= 2; i++)
      {
      digitalWrite(VIBRA,HIGH);
      delay(500);
      digitalWrite(VIBRA,LOW);
      delay(500);
      }
      doorbell = false;
      //fire = false;
      //digitalWrite(VIBRA,LOW);
      setColor(240,70,220); //rosa
  }
  else if(fire == true) {
    in_a_row =0;
    fire_row = 0;
    
    Serial.println (" Status: Fire");
    setColor(255, 0, 0); //red
    digitalWrite(VIBRA,HIGH);
    
    if (buttonState==LOW) {
        digitalWrite(VIBRA,LOW);
        setColor(240,70,220); //rosa
        fire = false;
        doorbell=false;
        delay(1000);
    }
    else {
    }
  }
  else {
    Serial.println (" All ok");
    setColor(240,70,220); //rosa
    digitalWrite(VIBRA, LOW);
  }
  

}

void setColor(int redValue, int greenValue, int blueValue)
{
analogWrite(redPin, redValue);
analogWrite(greenPin, greenValue);
analogWrite(bluePin, blueValue);
}

// measure basic properties of the input signal
// determine if analog or digital, determine range and average.
int MeasureAnalog()
{
    long signalAvg = 0, signalMax = 0, signalMin = 1024, t0 = millis();
    for (int i = 0; i < MicSamples; i++)
    {
        int k = analogRead(MicPin);
        signalMin = min(signalMin, k);
        signalMax = max(signalMax, k);
        signalAvg += k;
    }
    signalAvg /= MicSamples;
 
    // print
    Serial.print("Time: " + String(millis() - t0));
    Serial.print(" Span: " + String(signalMax - signalMin));
    //Serial.print(", " + String(signalMax - signalAvg));
    //Serial.print(", " + String(signalAvg - signalMin));
    Serial.println("");
    return(signalMax - signalMin);
}
