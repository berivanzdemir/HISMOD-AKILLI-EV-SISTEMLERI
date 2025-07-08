// ---------- PIN TANIMLARI ----------
const int flameDigitalPin = D0;   // Alev sensörü DO
const int flameAnalogPin  = A0;   // Alev sensörü AO
const int gasDigitalPin   = D1;   // Gaz sensörü DO
const int quakeSensorPin  = D4;   // Deprem sensörü 
#define TRIG_PIN D12              // Ultrasonik TRIG
#define ECHO_PIN D13              // Ultrasonik ECHO
const int buzzerPin       = D9;   // Ortak buzzer pini

// ---------- EŞİK DEĞERLER ----------
const int MESAFE_ESIK     = 20;   // Radar için mesafe eşiği (cm)
const int flameThreshold  = 150;  // Alev için analog eşik (deneyimle ayarla)

// ---------- DEPREM KONTROL ----------
volatile bool quakeDetected = false;
unsigned long quakeLastTime = 0;
const unsigned long quakeHoldTime = 2000; // Alarm süresi (ms)

// ---------- ISR: Deprem Sensörü ----------
void IRAM_ATTR onQuakeDetected() {
  quakeDetected = true;
}

// ---------- ALARM FONKSİYONLARI ----------
void flameAlarm() {
  tone(buzzerPin, 1000);
  delay(1000);
  noTone(buzzerPin);
  delay(200);
}

void gasAlarm() {
  for (int i = 0; i < 2; i++) {
    tone(buzzerPin, 1500);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }
}

void quakeAlarm() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 700);
    delay(200);
    noTone(buzzerPin);
    delay(200);
  }
}

void proximityAlarm() {
  tone(buzzerPin, 2000);
  delay(300);
  noTone(buzzerPin);
  delay(200);
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);

  pinMode(flameDigitalPin, INPUT);
  pinMode(flameAnalogPin, INPUT);
  pinMode(gasDigitalPin, INPUT_PULLUP);
  pinMode(quakeSensorPin, INPUT_PULLUP); // D4 pini INPUT_PULLUP ile tanımlandı
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buzzerPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(quakeSensorPin), onQuakeDetected, FALLING);
}

// ---------- LOOP ----------
void loop() {
  bool alarm = false;

  // --------- ALEV SENSÖRÜ ---------
  int flameDigital = digitalRead(flameDigitalPin);
  int flameAnalog  = analogRead(flameAnalogPin);
  Serial.print("🔥 Flame Digital: ");
  Serial.print(flameDigital);
  Serial.print(" | Analog: ");
  Serial.println(flameAnalog);

  if (flameDigital == LOW && flameAnalog < flameThreshold) {
    Serial.println("🔥 ALEV ALGILANDI!");
    flameAlarm();
    alarm = true;
  } else {
    Serial.println("🔥 Alev yok");
  }

  // --------- GAZ SENSÖRÜ ---------
  int gasValue = digitalRead(gasDigitalPin);
  if (gasValue == LOW) {
    Serial.println("💨 GAZ ALGILANDI!");
    gasAlarm();
    alarm = true;
  } else {
    Serial.println("💨 Gaz yok");
  }

  // --------- DEPREM SENSÖRÜ ---------
  int quakeState = digitalRead(quakeSensorPin);
  unsigned long now = millis();

  if (quakeDetected) {
    Serial.println("🌐 TİTREŞİM / DEPREM ALGILANDI! (interrupt)");
    quakeAlarm();
    quakeLastTime = now;
    quakeDetected = false;
    alarm = true;
  } else if (quakeState == LOW && (now - quakeLastTime) > quakeHoldTime) {
    Serial.println("🌐 TİTREŞİM / DEPREM ALGILANDI! (loop detect)");
    quakeAlarm();
    quakeLastTime = now;
    alarm = true;
  } else {
    Serial.println("🌐 Titreşim yok");
  }

  // --------- ULTRASONİK MESAFE SENSÖRÜ ---------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long sure = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  float mesafe = sure * 0.034 / 2;

  Serial.print("📏 Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");

  if (mesafe > 0 && mesafe < MESAFE_ESIK) {
    Serial.println("📍 YAKINLIK ALGILANDI!");
    proximityAlarm();
    alarm = true;
  }

  Serial.println("---------------------------");
  delay(2000);
}


