int activePin = 9;
int dirPin = 10; 
int stepPin = 11; 
String in;

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup() {
  // put your setup code here, to run once:
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(activePin, OUTPUT);

  digitalWrite(dirPin, HIGH);
  digitalWrite(stepPin, HIGH);
  digitalWrite(activePin, LOW);

  Serial.begin(115200);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {

    in = Serial.readString();
    if (in == "s\n"){
      digitalWrite(activePin, HIGH);
    }else if (in == "st\n"){
      digitalWrite(activePin, LOW);
    }else if (in == "f\n"){
      digitalWrite(dirPin, HIGH);
    }else if (in == "b\n"){
      digitalWrite(dirPin, LOW);
    }else if (in[0] == 'q'){
      int k = getValue(in, ' ', 1).toInt();
      int d = getValue(in, ' ', 2).toInt();
      for(int i = 0; i < k; i++){
        digitalWrite(stepPin, LOW);
        // Could be replaced with delaymicroseconds
        delay(d);
        digitalWrite(stepPin, HIGH);
      }
       digitalWrite(stepPin, HIGH);
      
      
    }
  }
}
