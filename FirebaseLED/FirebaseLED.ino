#include <WiFi.h>
#include <FirebaseESP32.h>

const char* ssid = "Eon33i";
const char* password = "11111111";

int led = 2;                                                               

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(2, OUTPUT);
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println(".......");
  Serial.println("WiFi Connected....IP Address:");
  Serial.println(WiFi.localIP());
   
  Firebase.begin("https://led-control-84415.firebaseio.com/", "198tu63LjujFpji6EvwJJAteWNeX235K5XbOd7gi");
  Serial.println("Firebase connected");
}
 
void loop() {
 
  if (Firebase.getInt(firebaseData, "/led")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val == 0) {
       digitalWrite(2,LOW);
       Serial.println("LED OFF");
       delay(1000);
      }
      else if(val==1){
        digitalWrite(2,HIGH);
        Serial.println("LED ON");
        delay(1000);
      }
      else{
       digitalWrite(2,LOW);
       Serial.println("Error..");
       delay(1000);
      }
    }
  }
   else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
}
