#include <PCD8544.h>

const int analogInPin = A0;
int adcValue = 0;
float real_value = 0;
float p_ch0 = -24;
float p_ch1 = -24;
float p_ch2 = -24;
float p_ch3 = -24;
float p_ch0_2 = -24;
float p_ch1_2 = -24;
float p_ch2_2 = -24;
float p_ch3_2 = -24;
float v_ch0 = 0;
float v_ch1 = 0;
float v_ch2 = 0;
float v_ch3 = 0;
static PCD8544 lcd;
uint8_t ac_dc = 0;
uint8_t curr_ch = 0;
uint8_t counter_1 = 0;
uint8_t counter_2 = 0;

void setup () {

  lcd.begin();

  analogReference(DEFAULT);

  // Enable the ADC and set the prescaler to 128 (for 16MHz clock)
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Set the ADC interrupt enable bit
  ADCSRA |= (1 << ADIE);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  // start first conversion
  Serial.begin(115200 , SERIAL_8N1 ) ;
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB
  }
}
void loop () {
  //ADCSRA |= (1 << ADSC);
  //Serial.write(45) ; // send a byte with the value 45
  //int bytesSent = Serial.write( "hello\n" ) ; //send the string "hello" and return the length of the string.
// send data only when you receive data:
  lcd.clear();
  lcd.setCursor(0 ,0);
  lcd.print("4ch voltmeter ");
  ADCSRA |= (1 << ADSC);
  //lcd.setCursor(0, 1);
  //lcd.print("Bye");
  while(true) {
    if (digitalRead(2) == 1) {
      lcd.setCursor(0 ,1);
      lcd.print("   AC (RMS)   ");
      lcd.setCursor(0 ,2);
      lcd.print("V1 ");
      lcd.print(p_ch0);
      lcd.print("   ");
      lcd.setCursor(0 ,3);
      lcd.print("V2 ");
      lcd.print(p_ch1);
      lcd.print("   ");
      lcd.setCursor(0 ,4);
      lcd.print("V3 ");
      lcd.print(p_ch2);
      lcd.print("   ");
      lcd.setCursor(0 ,5);
      lcd.print("V4 ");
      lcd.print(p_ch3);
      lcd.print("   ");
    } else if (digitalRead(2) == 0) {
      lcd.setCursor(0 ,1);
      lcd.print("   DC         ");
      lcd.setCursor(0 ,2);
      lcd.print("V1 ");
      lcd.print(v_ch0);
      lcd.print("   ");
      lcd.setCursor(0 ,3);
      lcd.print("V2 ");
      lcd.print(v_ch1);
      lcd.print("   ");
      lcd.setCursor(0 ,4);
      lcd.print("V3 ");
      lcd.print(v_ch2);
      lcd.print("   ");
      lcd.setCursor(0 ,5);
      lcd.print("V4 ");
      lcd.print(v_ch3);
      lcd.print("   ");      
    }
  }
}

void adc_isr() {
  // Get the ADC value
  adcValue = ADC;
  real_value = (adcValue*0.0469208)-24;
  curr_ch = ADMUX;
  if (digitalRead(2) == 1) {
    if (curr_ch == 0) {
      if (real_value*0.7071 > p_ch0) {
        p_ch0 = real_value*0.7071;
        if (real_value >= 20) {
          digitalWrite(8, 1);
        } else {
          digitalWrite(8, 0);
        }
      } else if ( real_value*0.7071 > p_ch0_2) {
        p_ch0_2 = real_value*0.7071;
      }
    } else if (curr_ch == 1) {
      if (real_value*0.7071 > p_ch1) {
        p_ch1 = real_value*0.7071;
        if (real_value >= 20) {
          digitalWrite(9, 1);
        } else {
          digitalWrite(9, 0);
        }
      } else if ( real_value*0.7071 > p_ch1_2) {
        p_ch1_2 = real_value*0.7071;
      }
    } else if (curr_ch == 2) {
      if (real_value*0.7071 > p_ch2) {
        p_ch2 = real_value*0.7071;
        if (real_value >= 20) {
          digitalWrite(10, 1);
        } else {
          digitalWrite(10, 0);
        }
      } else if ( real_value*0.7071 > p_ch2_2) {
        p_ch2_2 = real_value*0.7071;
      }
    } else {
      if (real_value*0.7071 > p_ch3) {
        p_ch3 = real_value*0.7071;
        if (real_value >= 20) {
          digitalWrite(11, 1);
        } else {
          digitalWrite(11, 0);
        }
      } else if ( real_value*0.7071 > p_ch3_2) {
        p_ch3_2 = real_value*0.7071;
      }
      if (digitalRead(1) == 1) {
        Serial.print( p_ch0 );
        Serial.print( "," );
        Serial.print( p_ch1 );
        Serial.print( "," );
        Serial.print( p_ch2 );
        Serial.print( "," );
        Serial.println( p_ch3 );
      }
    }
  } else if (digitalRead(2) == 0) {
    if (curr_ch == 0) {
      v_ch0 = real_value;
      if (v_ch0 >= 20) {
        digitalWrite(8, 1);
      } else if (v_ch0 <= -20) {
        digitalWrite(8, 1);
      } else {
        digitalWrite(8, 0);
      }
    } else if (curr_ch == 1) {
      v_ch1 = real_value;
      if (v_ch1 >= 20) {
        digitalWrite(9, 1);
      } else if (v_ch1 <= -20) {
        digitalWrite(9, 1);
      } else {
        digitalWrite(9, 0);
      }
    } else if (curr_ch == 2) {
      v_ch2 = real_value;
      if (v_ch2 >= 20) {
        digitalWrite(10, 1);
      } else if (v_ch2 <= -20) {
        digitalWrite(10, 1);
      } else {
        digitalWrite(10, 0);
      }
    } else {
      v_ch3 = real_value;
      if (v_ch3 >= 20) {
        digitalWrite(11, 1);
      } else if (v_ch3 <= -20) {
        digitalWrite(11, 1);
      } else {
        digitalWrite(11, 0);
      }
      if (digitalRead(1) == 1) {
        Serial.print( v_ch0 );
        Serial.print( "," );
        Serial.print( v_ch1 );
        Serial.print( "," );
        Serial.print( v_ch2 );
        Serial.print( "," );
        Serial.println( v_ch3 );
      }
    }
  }

  counter_1++;
  if (counter_1 == 0) {
    if (counter_2 == 2) {
      p_ch0 = p_ch0_2;
      p_ch1 = p_ch1_2;
      p_ch2 = p_ch2_2;
      p_ch3 = p_ch3_2;
      p_ch0_2 = -24;
      p_ch1_2 = -24;
      p_ch2_2 = -24;
      p_ch3_2 = -24;
      counter_2=0;
    }
    counter_2++;
  }

  ADMUX++;
  ADMUX &= 0x03;
  ADCSRA |= (1 << ADSC);

}

ISR(ADC_vect) {
  adc_isr();
}
