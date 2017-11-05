#include <Thing.h>
#include <BlinkPattern.h>

#define PIR_PIN D3

using namespace g3rb3n;

Thing thing;

bool motion = false;

void setup()
{
  Serial.begin(230400);
  Serial.println();

  Serial.println("ClientID:" + thing.clientId());

  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  thing.onStateChange([](const String& msg){
    Serial.println(msg);
  });

  thing.begin();

  thing.addSensor(thing.clientId() + "/pir/motion", 1000, [](Value& value){
    value = motion;
    Serial.println(motion);
  });

}

void loop()
{
  handle();
  thing.handle();
}

void handle()
{
  motion = digitalRead(PIR_PIN);
  digitalWrite(BUILTIN_LED, !motion);
}
