#include <Wire.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,04);

/* int fm_stations[22] = {

  89.1,   // KBS Cool FM
  89.7,   // WBS
  91.9,   // MBC FM4U
  93.1,   // KBS Classic FM
  93.9,   // CBS
  94.5,   // YTN
  95.1,   // TBS
  95.9,   // MBC Standard FM
  96.7,   // Military
  97.3,   // KBS 1
  98.1,   // CBS Standard FM
  99.1,   // Korean Music FM
  101.3,  // TBS English FM
  101.9,  // BBS
  102.7,  // AFN Eagle FM
  103.5,  // SBS Love FM
  104.5,  // EBS
  104.9,  // KBS 3
  105.3,  // CPBC
  106.1,  // KBS Happy FM
  106.9,  // FEBC
  107.7   // SBS Power FM
}; */
extern volatile unsigned long timer0_millis; //타이머변수
unsigned long setTime = 0; //lcd 타이머 시간 변수


unsigned short scroll; //가변저항

unsigned char current_switch; // switch문 전환용
unsigned short last_switch = 30;

bool current_Button = LOW; //버튼
bool last_Button = LOW;
bool state = true;

float current_freq; //주파수
float last_freq = 0;


void setFrequency(float frequency){
  byte _address = 0x60;
  
  unsigned int frequencyB = 4 * (frequency * 1000000 + 225000) / 32768; 
  byte frequencyH = frequencyB >> 8;
  byte frequencyL = frequencyB & 0XFF;
  Wire.beginTransmission(_address); 
  Wire.write(frequencyH);
  Wire.write(frequencyL);
  Wire.write(0xB0);
  Wire.write(0x10);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);  
}

void radioAuto(){
  switch(current_switch){
    case 0 :
    lcd.setCursor(0,0);
    lcd.print("KBS Cool FM,        ");
    lcd.setCursor(0,1);
    lcd.print("FM 89.1Mhz          ");
    setFrequency(89.1);
    break;

    case 1 :
    lcd.setCursor(0,0);
    lcd.print("WBS,                ");
    lcd.setCursor(0,1);
    lcd.print("FM 89.7Mhz          ");
    setFrequency(89.7);
    break;

    case 2 :
    lcd.setCursor(0,0);
    lcd.print("MBC FM4U,           ");
    lcd.setCursor(0,1);
    lcd.print("FM 91.9Mhz          ");
    setFrequency(91.9);
    break;

    case 3 :
    lcd.setCursor(0,0);
    lcd.print("KBS Classic FM,     ");
    lcd.setCursor(0,1);
    lcd.print("FM 93.1Mhz          ");
    setFrequency(93.1);
    break;

    case 4 :
    lcd.setCursor(0,0);
    lcd.print("CBS Music FM,       ");
    lcd.setCursor(0,1);
    lcd.print("FM 93.9Mhz          ");
    setFrequency(93.9);
    break;

    case 5 :
    lcd.setCursor(0,0);
    lcd.print("YTN,                ");
    lcd.setCursor(0,1);
    lcd.print("FM 94.5Mhz          ");
    setFrequency(94.5);
    break;

    case 6 :
    lcd.setCursor(0,0);
    lcd.print("TBS,                ");
    lcd.setCursor(0,1);
    lcd.print("FM 95.1Mhz          ");
    setFrequency(95.1);
    break;

    case 7 :
    lcd.setCursor(0,0);
    lcd.print("MBC Standard FM,    ");
    lcd.setCursor(0,1);
    lcd.print("FM 95.9Mhz          ");
    setFrequency(95.9);
    break;

    case 8 :
    lcd.setCursor(0,0);
    lcd.print("Military,           ");
    lcd.setCursor(0,1);
    lcd.print("FM 96.7Mhz          ");
    setFrequency(96.7);
    break;

    case 9 :
    lcd.setCursor(0,0);
    lcd.print("KBS1,               ");
    lcd.setCursor(0,1);
    lcd.print("FM 97.3Mhz          ");
    setFrequency(97.3);
    break;

    case 10 :
    lcd.setCursor(0,0);
    lcd.print("CBS Standard FM,   ");
    lcd.setCursor(0,1);
    lcd.print("FM 98.1Mhz          ");
    setFrequency(98.1);
    break;

    case 11 :
    lcd.setCursor(0,0);
    lcd.print("Korean Music FM,    ");
    lcd.setCursor(0,1);
    lcd.print("FM 99.1Mhz          ");
    setFrequency(99.1);
    break;

    case 12 :
    lcd.setCursor(0,0);
    lcd.print("TBS English FM,     ");
    lcd.setCursor(0,1);
    lcd.print("FM 101.3Mhz         ");
    setFrequency(101.3);
    break;

    case 13 :
    lcd.setCursor(0,0);
    lcd.print("BBS,                ");
    lcd.setCursor(0,1);
    lcd.print("FM 101.9Mhz         ");
    setFrequency(101.9);
    break;

    case 14 :
    lcd.setCursor(0,0);
    lcd.print("AFN Eagle FM,       ");
    lcd.setCursor(0,1);
    lcd.print("FM 102.7Mhz         ");
    setFrequency(102.7);
    break;

    case 15 :
    lcd.setCursor(0,0);
    lcd.print("SBS Love FM,        ");
    lcd.setCursor(0,1);
    lcd.print("FM 103.5Mhz         ");
    setFrequency(103.5);
    break;

    case 16 :
    lcd.setCursor(0,0);
    lcd.print("EBS,                ");
    lcd.setCursor(0,1);
    lcd.print("FM 104.5Mhz         ");
    setFrequency(104.5);
    break;

    case 17 :
    lcd.setCursor(0,0);
    lcd.print("KBS3,               ");
    lcd.setCursor(0,1);
    lcd.print("FM 104.9Mhz         ");
    setFrequency(104.9);
    break;

    case 18 :
    lcd.setCursor(0,0);
    lcd.print("CPBC                ");
    lcd.setCursor(0,1);
    lcd.print("FM 105.3Mhz         ");
    setFrequency(105.3);
    break;

    case 19 :
    lcd.setCursor(0,0);
    lcd.print("KBS Happy FM,       ");
    lcd.setCursor(0,1);
    lcd.print("FM 106.1Mhz         ");
    setFrequency(106.1);
    break;

    case 20 :
    lcd.setCursor(0,0);
    lcd.print("FEBC,               ");
    lcd.setCursor(0,1);
    lcd.print("FM 106.9Mhz         ");
    setFrequency(106.9);
    break;

    case 21 :
    case 22 :
    case 23 :
    lcd.setCursor(0,0);
    lcd.print("SBS Power FM,       ");
    lcd.setCursor(0,1);
    lcd.print("FM 107.7Mhz         ");
    setFrequency(107.7);
    break;
  }
}

void setup() {
  Wire.begin();
  pinMode(A1,INPUT);
  pinMode(13,INPUT);
  lcd.init();
  lcd.backlight();
  pinMode(2, OUTPUT);
  digitalWrite(2,HIGH);
  //Serial.begin(9600); //시리얼 시작 
}


//////////////////////////// LOOP START ////////////////////////////////////
void loop() {
  scroll = 1023 - analogRead(1);
  current_freq = 88.5 + (scroll // 50);
  current_switch = scroll // 42;
  
  current_Button = digitalRead(13);
  
  //Serial.println(scroll); //A1핀 입력값을 시리얼 모니터 출력


/////////////////////////// Switch State ///////////////////////////////////

  if(last_Button == LOW && current_Button == HIGH){
    state = !state;
  }
  last_Button = current_Button;
  
  //LCD 백라이트
  //if(state == true) lcd.backlight();
  //else lcd.noBacklight(); 


//-------------------------------------------------------------------------수정중


//////////////////////////// MODE CHOICE ////////////////////////////////////
  if(state == false) {

    //주파수 수동 선택 코드
    if(abs(current_freq - last_freq) >= 0.2) {
      setFrequency(current_freq);
      lcd.setCursor(0,0);
      lcd.print("Manual MODE         ");
      lcd.setCursor(0,1);
      lcd.print("FM ");
      lcd.print(current_freq);
      lcd.print("Mhz ");
    }
    
    last_freq = current_freq;
  }
    
  else{
    if(current_switch != last_switch){
      lcd.backlight();
      radioAuto();
       
    last_switch = current_switch;
    setTime = timer0_millis;
    }
    if(setTime + 15000 < timer0_millis && setTime + 15100 > timer0_millis) lcd.noBacklight();  
  }
}
