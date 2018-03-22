#include <Thing.h>

#define PIR_PIN D3

using namespace ootb;

Thing thing;

bool motion = false;
bool lastState = false;

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
    if (motion != lastState)
    {
        Value value = motion;
        thing.publish("pir/motion/" + thing.clientId(), value);
        Serial.println(motion);
        lastState = motion;
    }
}
