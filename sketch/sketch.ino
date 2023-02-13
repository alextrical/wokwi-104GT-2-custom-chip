// Steinheart example equations based on https://robertvicol.com/tech/arduino-measuring-temperature-with-ntc-steinhart-hart-formula/

//Measure NTC value
byte NTCPin = A0;
const long seriesResistor = 4700;

// ~~~~~~ A,B,C ~~~~~~
#define A1 7.97110609710217e-4 //104GT-2
#define B1 2.13433144381270e-4 //104GT-2
#define C1 6.5338987554e-8     //104GT-2

void setup()
{
	Serial.begin(9600);
	pinMode(NTCPin, INPUT);
	delay(1);
}
void loop()
{
	Serial.print("Temperature: ");
	Serial.println(f_ReadTemp_ThABC(NTCPin, seriesResistor, A1, B1, C1));  // 100k 104GT-2 thermistor; ABC parameters were calculated using the data sheet !
	delay(1000);
}

// TPin = Analog Pin 
// R1 = R Serries resistor
// A, B , C = the Steinhart–Hart coefficients, which vary depending on the type and model of thermistor and the temperature range of interest.
float f_ReadTemp_ThABC(byte TPin, float R1, float A, float B, float C) {

	float R2 = R1 / ((1023.0 / analogRead(TPin)) - 1);             // for pull-up configuration
	
	float logR2 = log(R2);           // Pre-Calcul for Log(R2)
	float T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2)); 
	T =  T - 273.15;             // convert Kelvin to *C
	return T;
}