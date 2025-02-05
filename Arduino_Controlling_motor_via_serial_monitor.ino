#define RELAY_PIN 8
#define GREEN_LED 13
#define BUZZER_PIN 7
#define RED_LED 12

bool systemOnline = false; // System state

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(RELAY_PIN,HIGH);
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim(); // Remove extra spaces or newlines

        if (command == "ON") {
            Serial.println("System Initializing...");
            digitalWrite(RED_LED,HIGH);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(2000);
            digitalWrite(BUZZER_PIN, LOW);
                //  STARTING BEEP AS A STARTUP SIGNAL

            delay(500);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(100);
            digitalWrite(BUZZER_PIN, LOW);
            delay(100);
            digitalWrite(BUZZER_PIN, HIGH);
            delay(100);
            digitalWrite(BUZZER_PIN, LOW);

                // //  ENDING BEEP AS A STARTUP SIGNAL

            digitalWrite(RED_LED,LOW);
            digitalWrite(GREEN_LED, HIGH);
            systemOnline = true; // System is now online
            Serial.println("System Online");
        } 
        else if (command == "MOTOR ON") {
            if (systemOnline) {
                Serial.println("Motor Starting...");
                digitalWrite(BUZZER_PIN, HIGH);
                delay(500);
                digitalWrite(BUZZER_PIN, LOW);
                digitalWrite(RELAY_PIN, LOW);
                Serial.println("Motor is ON");
            } else {
                Serial.println("System is Offline. Turn it ON first.");
                digitalWrite(BUZZER_PIN, HIGH);
                digitalWrite(RED_LED,HIGH);
                delay(300);
                digitalWrite(BUZZER_PIN, LOW);
                digitalWrite(RED_LED,LOW);
            }
        } 
        else if (command == "MOTOR OFF") {
            if (systemOnline) {
                Serial.println("Turning Off Motor...");
                digitalWrite(RELAY_PIN, HIGH);
                digitalWrite(BUZZER_PIN, HIGH);
                delay(100);
                digitalWrite(BUZZER_PIN, LOW);
                delay(100);
                digitalWrite(BUZZER_PIN, HIGH);
                delay(100);
                digitalWrite(GREEN_LED, LOW);
                digitalWrite(BUZZER_PIN, LOW);
                Serial.println("Motor is OFF");
            } else {
                Serial.println("System is Offline. Turn it ON first.");
                digitalWrite(BUZZER_PIN, HIGH);
                digitalWrite(RED_LED,HIGH);
                delay(300);
                digitalWrite(BUZZER_PIN, LOW);
                digitalWrite(RED_LED,LOW);
            }
        } 
        else if (command == "OFF") {
            if (systemOnline) {
                Serial.println("Shutting Down...");
                
                digitalWrite(RED_LED,HIGH);
                // delay(700);
                digitalWrite(RELAY_PIN, HIGH);
                digitalWrite(BUZZER_PIN, HIGH);
                delay(100);
                digitalWrite(BUZZER_PIN, LOW);
                delay(100);
                digitalWrite(BUZZER_PIN, HIGH);
                delay(100);
                digitalWrite(GREEN_LED, LOW);
                // delay(3000);
                digitalWrite(BUZZER_PIN, LOW);
                digitalWrite(RED_LED,LOW);
                systemOnline = false; // System is now offline
                Serial.println("System Offline");
            } else {
                Serial.println("System is already OFF");
                digitalWrite(RED_LED,HIGH);
                digitalWrite(BUZZER_PIN, HIGH);
                delay(300);
                digitalWrite(RED_LED,LOW);
                digitalWrite(BUZZER_PIN, LOW);
            }
        } 
        else {
            Serial.println("Invalid Command");
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(RED_LED,HIGH);
            delay(300);
            digitalWrite(BUZZER_PIN, LOW);
            digitalWrite(RED_LED,LOW);
        }
    }
}
