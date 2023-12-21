int trig = 7;
int echo = 6;
int tank_height=350;  //cm
float tank_loaded;    //%
float space;

void setup() {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    Serial.begin(9600);
    
}

void loop() {

  mesaureWaterPerc();

  Serial.print("Space=");
  Serial.print(space);
  Serial.print('\n');

  Serial.print("Tank Loaded=");
  Serial.print(tank_loaded);
  Serial.print('\n');

}

void measureSpace()
{
  digitalWrite(trig, HIGH);
  delay(0.01);
  digitalWrite(trig, LOW);
  space=pulseIn(echo, HIGH)*0.0332/2;  //in cm
}

void mesaureWaterPerc()
{
  measureSpace();
  int available_water=tank_height-50;
  Serial.print("available_water=");
  Serial.print(available_water);
  Serial.print('\n');
  tank_loaded=(available_water/tank_height)*100;
  Serial.print("tank_loaded=");
  Serial.print((tank_height));
  Serial.print('\n');
}
