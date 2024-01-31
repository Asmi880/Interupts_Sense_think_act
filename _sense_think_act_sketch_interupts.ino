// Declare variables for baseline temperature, Celsius, and Fahrenheit
int baselineTemp = 0;
volatile int celsius = 0; // Make it volatile for use in interrupts
int fahrenheit = 0;

// LED pins
const int ledPin2 = 2;
const int ledPin3 = 3;
const int ledPin4 = 4;

// Setup function runs once when the Arduino starts
void setup() {
  // Set A0 pin as INPUT for temperature sensor
  pinMode(A0, INPUT);
  
  // Start serial communication at a baud rate of 9600
  Serial.begin(9600);

  // Set pins 2, 3, and 4 as OUTPUT for LEDs
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  // Attach interrupt to handle temperature sensor changes
  attachInterrupt(digitalPinToInterrupt(A0), updateTemperature, CHANGE);
}

// Interrupt Service Routine (ISR) to update temperature
void updateTemperature() {
  // Measure temperature in Celsius using the analog sensor
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
}

// Loop function runs repeatedly after setup
void loop() {
  // Set threshold temperature to activate LEDs
  baselineTemp = 40;

  // Convert Celsius to Fahrenheit
  fahrenheit = ((celsius * 9) / 5 + 32);

  // Print temperature values to Serial Monitor
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");

  // Control LEDs based on temperature conditions
  if (celsius < baselineTemp) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
  }
  if (celsius >= baselineTemp && celsius < baselineTemp + 10) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
  }
  if (celsius >= baselineTemp + 10 && celsius < baselineTemp + 20) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, LOW);
  }
  if (celsius >= baselineTemp + 20 && celsius < baselineTemp + 30) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
  }
  if (celsius >= baselineTemp + 30) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
  }

  // Delay for 1000 milliseconds (1 second)
  delay(1000);
}
