const int motorPin = 11; // pin 1 på L293D
const int retningsPin1 = 13; // pin 2 på L293D
const int retningsPin2 = 12; // pin 7 på L293D
const int SWPin = 9;

int motorFart = 0;
int retning = HIGH;

void setup() {
    // put your setup code here, to run once:
    pinMode(motorPin, OUTPUT);
    pinMode(retningsPin1, OUTPUT);
    pinMode(retningsPin2, OUTPUT);
    pinMode(SWPin, INPUT);
    Serial.begin(9600);
    analogWrite(motorPin, motorFart);
    digitalWrite(retningsPin1, retning);
    digitalWrite(retningsPin2, !retning);
}

int forrigeSW = LOW;

void loop() {
    // put your main code here, to run repeatedly:
    int SWstatus = digitalRead(SWPin);

    if (SWstatus == HIGH && forrigeSW == LOW)
    {
        retning = !retning;
        digitalWrite(retningsPin1, retning);
        digitalWrite(retningsPin2, !retning);
        if (retning == HIGH)
        {
            Serial.println("Retning mot klokka");
        }
        else
            Serial.println("Retning med klokka");
    }
    forrigeSW = SWstatus;

    if (Serial.available() > 0)
    {
        char kommando = Serial.read();
        motorFart = Serial.read();
        /*if (kommando == '+')
        {
            motorFart += 10;
            if (motorFart > 255)
                motorFart = 255;
        }
        else if (kommando == '-')
        {
            motorFart -= 10;
            if (motorFart < 0)
                motorFart = 0;
        }*/

        switch (kommando) {
        case 'B':
            retning = !retning;
            digitalWrite(retningsPin1, retning);
            digitalWrite(retningsPin2, !retning);
            if (retning == HIGH)
            {
                Serial.println("Retning mot klokka");
            }
            else {
                Serial.println("Retning med klokka");
            }
            break;
        case 'F':
            
            break;
        default:
            // code block
        }
        
        analogWrite(motorPin, motorFart);
        Serial.print("Fart: ");
        Serial.println(motorFart);
    }

    // Bremsing hvis den ikke mottar kommando
    else if (Serial.available() == 0) {
        if (motorFart > 10) {
            motorFart -= 10;
            delay(50);
        }
        else {
            motorFart = 0;
        }
    }
}
