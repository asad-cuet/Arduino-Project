/*
DO=Digital Output : 1 or 0
AO=Analog Output  : 0 to 1015 [1015 when dark,0 when bright,519 is division point]


*/


void setup() {
  // put your setup code here, to run once:
  pinMode(7,INPUT);
  pinMode(A2,INPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);

}

void loop() {

  int x;
  float an;
  x=digitalRead(7);
  an=analogRead(A2);
  if(x==1)
  {
    Serial.print("Dark");
    digitalWrite(11,HIGH);
  }
  else
  {
    digitalWrite(11,LOW);
  }

  Serial.println(an);
}
