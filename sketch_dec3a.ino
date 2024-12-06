#include <Adafruit_CircuitPlayground.h>

int heartRate = 0;
const int NEUTRAL_LOW = 60;   // Lower bound for neutral mood
const int NEUTRAL_HIGH = 75;  // Upper bound for neutral mood
const int HAPPY_HIGH = 100;    // Upper bound for happy mood
const int PULSE_SENSOR_PIN = A0; // Pin connected to pulse sensor

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  
  // Initial welcome and input method selection
  Serial.println("Heart Rate Mood Tracker");
  Serial.println("Choose input method:");
  Serial.println("1. Manual Input");
  Serial.println("2. Sensor Detection");
}

void loop() {
  Serial.println("Enter your choice (1 or 2):");
  
  while (!Serial.available()) {
    // Wait for user input
  }
  
  int choice = Serial.parseInt();
  clearSerialBuffer();
  
  switch(choice) {
    case 1:
      manualInputMode();
      break;
    
    case 2:
      sensorDetectionMode();
      break;
    
    default:
      Serial.println("Invalid choice. Please select 1 or 2.");
      break;
  }
}

void manualInputMode() {
  Serial.println("Manual Input Mode Selected");
  Serial.println("Enter your heart rate (BPM):");
  
  while (!Serial.available()) {
    // Wait for user input
  }
  
  heartRate = Serial.parseInt();
  clearSerialBuffer();
  
  processHeartRate(heartRate);
}

void sensorDetectionMode() {
  Serial.println("Sensor Detection Mode Selected");
  
  // Read heart rate from sensor
  heartRate = getHeartRateFromSensor();
  
  processHeartRate(heartRate);
}

void processHeartRate(int rate) {
  Serial.print("Heart Rate: ");
  Serial.print(rate);
  
  String mood;

  // Determine mood based on heart rate
  if (rate < NEUTRAL_LOW) {
    mood = "invalid"; // Indicating an invalid state
    Serial.println(" - Mood: invalid");
    Serial.println(mood); // Send to Processing
    return; // Exit early if invalid
  } else if (rate >= NEUTRAL_LOW && rate <= NEUTRAL_HIGH) {
    mood = "neutral";
    Serial.println(" - Mood: neutral");
  } else if (rate > NEUTRAL_HIGH && rate <= HAPPY_HIGH) {
    mood = "happy";
    Serial.println(" - Mood: happy");
  } else {
    mood = "stressed";
    Serial.println(" - Mood: stressed");
  }
  
  // Send single word mood to Processing
  Serial.println(mood);
}

int getHeartRateFromSensor() {
   // Simulated sensor reading (replace with actual sensor code)
   int sensorValue = analogRead(PULSE_SENSOR_PIN);
   
   // Map sensor value to a reasonable BPM range
   int bpm = map(sensorValue, 0, 1023, 40, 220);
   
   return bpm;
}

void clearSerialBuffer() {
   while (Serial.available() > 0) {
       Serial.read(); // Clear the serial buffer
   }
}