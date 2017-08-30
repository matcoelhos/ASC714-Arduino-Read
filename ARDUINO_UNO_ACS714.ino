/*
    Developed by: Mateus Coelho Silva
    source: https://www.filipeflop.com/blog/efeito-hall-acs714-corrente-com-arduino/
*/

//Define o pino analogico usado pelo ACS714
int AnalogInputPin = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Chama rotina que calcula a corrente
  double Current = currentSensor(analogRead(AnalogInputPin));
  Serial.println(Current);
  Serial.println("\n");
}

// Calculate current with Allegro ACS714
double currentSensor(int RawADC) 
{
  int    Sensitivity    = 66; // mV/A
  long   InternalVcc    = readInternalVcc();
  double ZeroCurrentVcc = InternalVcc / 2;
  double SensedVoltage  = (RawADC * InternalVcc) / 1024;
  double Difference     = SensedVoltage - ZeroCurrentVcc;
  double SensedCurrent  = Difference / Sensitivity;
  //Serial.println("Sen: ");
  //Serial.println(RawADC);
  //Serial.println("/1024");
  return SensedCurrent;            
}

long readInternalVcc() 
{
  long result;
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);                          // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);               // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result;       // Back-calculate AVcc in mV
  return result;
} 
