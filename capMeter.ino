#define analogPin 0          
#define chargePin 13         
#define dischargePin 11        
//#define resistorValue 1000000.0F
#define resistorValue 560.0F
#define refVoltagePin 1

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;                
float nanoFarads;
int currentVal = 0;
int refVoltTarget = 0;

void setup(){
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, HIGH);  
  Serial.begin(9600);             
}

void loop(){
  int refVolt = analogRead(refVoltagePin);
  refVoltTarget = refVolt * 0.632;
  Serial.print("Target: ");
  Serial.println(refVoltTarget);
  Serial.print("Ref: ");
  Serial.println(refVolt);
  digitalWrite(chargePin, LOW);  
  startTime = millis();
  currentVal = analogRead(analogPin);
  Serial.println(currentVal);
//  float volts = currentVal * (5.0 / 1023.0);
//  Serial.print("a: ");
//  Serial.println(volts);
  while(currentVal < refVoltTarget){
    return;
  }

  elapsedTime= millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000;   
  Serial.print(elapsedTime);       
  Serial.print(" mS    ");         

  if (microFarads > 1){
    Serial.print((long)microFarads);       
    Serial.println(" microFarads");         
  }

  else{
    nanoFarads = microFarads * 1000.0;      
    Serial.print((long)nanoFarads);         
    Serial.println(" nanoFarads");          
    delay(500); 
  }

  Serial.println("Discharging");
  digitalWrite(chargePin, HIGH);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);          
  while(analogRead(analogPin) > 0){         
  }

  pinMode(dischargePin, INPUT);            
} 
