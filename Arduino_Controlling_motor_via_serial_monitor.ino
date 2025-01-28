#define RELAY_PIN 8
#define LED_PIN 13
#define BUZZER_PIN 7

bool systemOnline = false; // System state

void setup() {
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
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
            digitalWrite(BUZZER_PIN, HIGH);
            delay(3000);
            digitalWrite(BUZZER_PIN, LOW);
            digitalWrite(LED_PIN, HIGH);
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
            }
        } 
        else if (command == "MOTOR OFF") {
            if (systemOnline) {
                Serial.println("Turning Off Motor...");
                digitalWrite(RELAY_PIN, HIGH);
                digitalWrite(BUZZER_PIN, HIGH);
                delay(500);
                digitalWrite(BUZZER_PIN, LOW);
                Serial.println("Motor is OFF");
            } else {
                Serial.println("System is Offline. Turn it ON first.");
            }
        } 
        else if (command == "OFF") {
            if (systemOnline) {
                Serial.println("Shutting Down...");
                digitalWrite(BUZZER_PIN, HIGH);
                delay(3000);
                digitalWrite(BUZZER_PIN, LOW);
                digitalWrite(RELAY_PIN, HIGH);
                digitalWrite(LED_PIN, LOW);
                systemOnline = false; // System is now offline
                Serial.println("System Offline");
            } else {
                Serial.println("System is already OFF");
            }
        } 
        else {
            Serial.println("Invalid Command");
        }
    }
}
