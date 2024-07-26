#include <LiquidCrystal.h>
const int rs = 3, e=4, d7 = 5, d6 = 6, d5 = 7, d4 = 8;

const int backlightPin=2;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

String inputString; // Gelen verileri tutacak string

#define red 22
#define blue 10
#define yellow 9

#define red_rgb 11
#define green_rgb 12
#define blue_rgb 13


// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(yellow,OUTPUT);

  pinMode(red_rgb,OUTPUT);
  pinMode(blue_rgb,OUTPUT);
  pinMode(green_rgb,OUTPUT);

  pinMode(backlightPin,OUTPUT);

  analogWrite(red_rgb,255);
  analogWrite(blue_rgb,255);
  analogWrite(green_rgb,255);

  analogWrite(backlightPin,0);


  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();

}

// the loop function runs over and over again until power down or reset
void loop() {

   /*for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(backlightPin, brightness);
    delay(10);
  }                                                                 //nefes alma 
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(backlightPin, brightness);
    delay(10);
  }
*/
  if(Serial.available()>0)
  {
   /* char led_secici = Serial.read();
    int led_parlakligi = Serial.parseInt();
    */
    String input = Serial.readStringUntil('\n'); // Yeni satıra kadar oku

    // Gelen veri "LCD" ile başlıyorsa, LCD'ye yaz
    if(input.startsWith("LCD"))
    {
      lcd.clear();
      lcd.print(input.substring(3));// "LCD" kelimesini atla
      if(input.length()>16)
      {
        lcd.setCursor(0,2);
        lcd.print(input.substring(16));
      }

    }
    else if(input == "LED1ON")
    {
      digitalWrite(red,HIGH);
    }
    else if(input == "LED1OFF")
    {
      digitalWrite(red,LOW);
    }
    else if(input == "LED2ON")
    {
      digitalWrite(blue,HIGH);
    }
    else if(input == "LED2OFF")
    {
      digitalWrite(blue,LOW);
    }
    else if(input == "LED3ON")
    {
      digitalWrite(yellow,HIGH);
    }
    else if(input == "LED3OFF")
    {
      digitalWrite(yellow,LOW);
    }
    else if(input.startsWith("r"))
    {
      int parlaklik = input.substring(1).toInt();
      analogWrite(red_rgb,255-parlaklik);
    }
    else if(input.startsWith("g"))
    {
      int parlaklik = input.substring(1).toInt();
      analogWrite(green_rgb,255-parlaklik);
    }
    else if(input.startsWith("b"))
    {
      int parlaklik = input.substring(1).toInt(); // stringden ilk karakteri atıp kalan değerleri integere çevirdi 
      analogWrite(blue_rgb,255-parlaklik);
    }
    else if(input.startsWith("l"))
    {
      int lcdParlaklik = input.substring(1).toInt();
      analogWrite(backlightPin,255-lcdParlaklik);
    }
    
  }  
    
}


void write_leds(String led,int parlaklik)
{
  if(led =='r')
  {
    analogWrite(red_rgb,255-parlaklik);
    return;
  }
  if(led == 'g')
  {
    analogWrite(green_rgb,255-parlaklik);
    return;
  }
  if(led =='b')
  {
    analogWrite(blue_rgb,255-parlaklik);
    return;
  }

  return;
}




