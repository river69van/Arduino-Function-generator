


#include <AD9833.h>     // Include the library
#include <SimpleRotary.h>
#include <LiquidCrystal.h>
#include "customChar.h"
#define FNC_PIN 4

SimpleRotary rotary(9,8,7);
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);
AD9833 gen(FNC_PIN);

volatile bool X = false;
volatile bool Y = false;
bool outputOn = false;

//default vals
float freq = 290000;
float freq_min = 100000;  
float freq_max = 300000;



volatile int menu_num = 0;
volatile int wave_from_num = 0;
volatile int freq_sweep_counter = 0;
volatile int freq_adj_indicator = 0;

bool freq_sweep_trigger_start = false;
bool menu_select = true;
volatile bool freq_sweep_s = false;
volatile bool manual_adj_frequency = false;

bool sig_gen_start = false;
int waveform = 0;
bool stop_sweep = false;

void funcISR(){

  //pag pili frequency range pati pag start han "Frequency Sweep" mode
  if(freq_sweep_s && !menu_select)freq_sweep_counter++;
  if(freq_sweep_counter > 2)freq_sweep_counter = 2;

  if(manual_adj_frequency && !menu_select)freq_adj_indicator++;
  if(freq_adj_indicator > 2)freq_adj_indicator = 2;

  //dd active an karan "Wave Form" adjust 
  if(menu_num == 0)wave_from_num++;
  if(wave_from_num > 2)wave_from_num = 0;

  //dd active an karan "Frequency Sweep" mode
  if(menu_num == 1)freq_sweep_s = true;
  if(freq_sweep_s)menu_select = false;

  //dd active an karan "Manual Frequency Adjustment" mode
  if(menu_num == 2)manual_adj_frequency = true;
  if(manual_adj_frequency)menu_select = false;
  
  if(freq_sweep_trigger_start){
    stop_sweep = true;
    sig_gen_start = false;
    }




  

	X = true;
  Y ^=1;
	
}


void menu(){
  lcd.clear();
  if(menu_num == 0){
    lcd.setCursor(0, 0);
    lcd.print(">WF<");
    lcd.setCursor(4, 0); 
    lcd.write(1);
    lcd.setCursor(6, 0); 
    lcd.print("Fsw"); 
    lcd.setCursor(10, 0);
    lcd.write(1); 
    lcd.setCursor(12, 0);
    lcd.print("Fdj");

    /*
    lcd.setCursor(0, 1);
    if(wave_from_num == 0){
      lcd.print("sine");
    }else if(wave_from_num == 1){
      lcd.print("squr");
    }else{
      lcd.print("trgl");
    }
    */
    lcd.setCursor(10, 1);
    lcd.write(1);

  }else if(menu_num == 1){
    
    lcd.setCursor(1, 0);
    lcd.print("WF");
    lcd.setCursor(4, 0); 
    lcd.write(1);
    lcd.setCursor(5, 0); 
    lcd.print(">Fsw<");
    lcd.setCursor(10, 0);
    lcd.write(1);
    lcd.setCursor(12, 0);
    lcd.print("Fdj"); 
    lcd.setCursor(10, 1);
    lcd.write(1);
    

    
    if(freq_sweep_s){

    if(freq_sweep_counter == 0){ 
      lcd.setCursor(5, 1);
      lcd.print("min:"); 
      lcd.setCursor(9, 1);

      if(freq_min < 999){
        lcd.print(freq_min, 1);

      }else if(freq_min > 999){
        float freq_print = freq_min/1000;
        lcd.print(freq_print, 1);
        lcd.print("k");
      }

    }else if(freq_sweep_counter == 1){

      lcd.setCursor(5, 1);
      lcd.print("max:"); 
      lcd.setCursor(9, 1);
      if(freq_max < 999){
        lcd.print(freq_max, 1);

      }else if(freq_max > 999){
        float freq_print = freq_max/1000;
        lcd.print(freq_print, 1);
        lcd.print("k");
      }

    }else if(freq_sweep_counter == 2){

      freq_sweep_trigger_start = true;
      float print_max = 0;
      float print_min = 0;

      if(freq_min < 999){
        print_min = freq_min;

      }else if(freq_min > 999){
        print_min = freq_min/1000;
      }

      if(freq_max < 999){
        print_max = freq_max;

      }else if(freq_max > 999){
        print_max = freq_max/1000;
      }
      lcd.setCursor(5, 1);
      lcd.print(print_min, 1);
      lcd.print("-");
      lcd.print(print_max, 1);

    }
    lcd.setCursor(11, 0);
    if(freq_sweep_trigger_start){
      lcd.print("START");
      sig_gen_start = true;
      stop_sweep = false;
    }else if(!freq_sweep_trigger_start){
      lcd.print("STOP");
      sig_gen_start = false;
    }

  }


  }else{

    

      lcd.setCursor(1, 0);
      lcd.print("WF");
      lcd.setCursor(4, 0); 
      lcd.write(1);
    if(!manual_adj_frequency){

      
      lcd.setCursor(6, 0); 
      lcd.print("Fsw"); 
      lcd.setCursor(10, 0);
      lcd.write(1); 
      lcd.setCursor(11, 0);
      lcd.print(">Fdj<");
      lcd.setCursor(10, 1);
      lcd.write(1);

    }else{

      lcd.setCursor(5, 0);

      switch(freq_adj_indicator){
        case 0:
          lcd.print("STOP");
          sig_gen_start = false;
        break;
        case 1:
          lcd.print("START");
          sig_gen_start = true;
        break;
        case 2:
          lcd.print("EXT");
          sig_gen_start = false;
        break;
        default:
        break;
      }

      
      
      lcd.setCursor(10, 0);
      lcd.write(1); 
      lcd.setCursor(11, 0);
      lcd.print(">Fdj<");
      lcd.setCursor(5, 1);
      lcd.print("F=");
      float F_print = 0;

      if(freq < 999){
        F_print = freq;
        lcd.print(F_print, 1);
        lcd.print("Hz");

      }else if(freq > 999){
        F_print = freq/1000;
        lcd.print(F_print, 1);
        lcd.print("kHz");
  
      }

      

      

    }
  }

  lcd.setCursor(0, 1);
  if(wave_from_num == 0){
    lcd.print("sine");
    waveform = SINE_WAVE;
  }else if(wave_from_num == 1){
    lcd.print("squr");
    waveform = SQUARE_WAVE;
  }else{
    lcd.print("trgl");
    waveform = TRIANGLE_WAVE;
  }
  lcd.setCursor(4, 1);
  lcd.write(1);


  lcd.display();
}



void IncrementFrequencyTest ( void ) {

    float startHz = freq_min, stopHz = freq_max, incHz = 10, sweepTimeSec = 5.0;
 
    // Calculate the delay between each increment.
    uint16_t numMsecPerStep = (sweepTimeSec * 1000.0) / ((uint16_t)((stopHz - startHz) / incHz) + 1);
    if ( numMsecPerStep == 0 ) numMsecPerStep = 1;

    // Apply a signal to the output. If phaseReg is not supplied, then
    // a phase of 0.0 is applied to the same register as freqReg
    gen.ApplySignal(waveform,REG1,startHz);

    while ( true ) {
      
        gen.SetFrequency(REG1,startHz-incHz);

        for ( float i = startHz ; i <= stopHz; i += incHz ) {
            if(i == stopHz | stop_sweep == true)return;
            //YIELD_ON_CHAR
            gen.IncrementFrequency(REG1,incHz);
            delay(numMsecPerStep); 
        }
    }
}



void setup(){
	
  initChar(lcd);
	Serial.begin(9600);
	gen.Begin();
  lcd.begin(16, 2);

  lcd.clear();
  menu();
	pinMode(2, INPUT_PULLUP);  // Enable pull-up resistor if needed
	attachInterrupt(digitalPinToInterrupt(2), funcISR, FALLING);
  //gen.ApplySignal(SINE_WAVE, REG1, freq);
  gen.EnableOutput(sig_gen_start);
  //gen.EnableOutput(true);
  //IncrementFrequencyTest();

}



void loop(){

  byte i = rotary.rotate();

  //gen.ApplySignal(SINE_WAVE, REG1, freq);

  if ( i == 1 ) {
    
    

    //pan exit ha "Frequency Sweep mode"
    if(freq_sweep_counter == 2){
      menu_select = true;
      freq_sweep_counter = 0;
      freq_sweep_s = false;
      freq_sweep_trigger_start = false;
      sig_gen_start = false;
    }

    //pan exit pati pan select frequency han "Manual Frequency Adjustment" mode
    if(manual_adj_frequency){

      switch(freq_adj_indicator){
        case 0:
          freq-=100;;
        break;
        case 1:
          freq-=100;;
        break;
        case 2:
          menu_select = true;
          manual_adj_frequency = false;
          freq_adj_indicator = 0;
        break;
        default:
        break;
      }
      

    }

    if(freq < 0)freq = 0;

    //pan select mga mode
    if(menu_select)menu_num--;
    if(menu_num < 0)menu_num = 0;

    //pan select freq range han karan "Frequency Sweep" mode
    if(freq_sweep_s){
      switch(freq_sweep_counter){
        case 0:
          freq_min-=100;
        break;

        case 1:
          freq_max-=100;
        break;

        case 2:
        break;

        default:
        break;
      }
    }


    menu();
    gen.ApplySignal(waveform, REG1, freq);
    //if(menu_num == 0)wave_from_num--;
  }

//===============================================================


  if ( i == 2 ) {
    
    //if(menu_num == 0)wave_from_num++;

    //pan exit ha "Frequency Sweep mode"
    if(freq_sweep_counter == 2){
      menu_select = true;
      freq_sweep_counter = 0;
      freq_sweep_s = false;
      freq_sweep_trigger_start = false;
      sig_gen_start = false;
    }

    //pan exit pati pan select frequency han "Manual Frequency Adjustment" mode
    if(manual_adj_frequency){

      switch(freq_adj_indicator){
        case 0:
          freq+=100;
        break;
        case 1:
          freq+=100;
        break;
        case 2:
          menu_select = true;
          manual_adj_frequency = false;
          freq_adj_indicator = 0;
        break;
        default:
        break;
      }

    }

    if(freq < 0)freq = 0;

    //pan select mga mode
    if(menu_select)menu_num++;
    if(menu_num > 2)menu_num = 2;


    //pan select freq range han karan "Frequency Sweep" mode
    if(freq_sweep_s){
      switch(freq_sweep_counter){
        case 0:
          freq_min+=100;
        break;

        case 1:
          freq_max+=100;
        break;

        case 2:

        break;

        default:
        break;
      }
    }


    menu();
    gen.ApplySignal(waveform, REG1, freq);
    Serial.println(freq);
  }

  if(X){
    
    menu();
    
    //Serial.print("men num = ");
    //Serial.println(menu_num);
    //Serial.print("men sel = ");
    //Serial.println(menu_select);
    //Serial.print("freq c = ");
    //Serial.println(freq_sweep_counter);
    //Serial.print("freq_sweep_s = ");
    //Serial.println(freq_sweep_s);
    //if(freq_adj_indicator == 1 && manual_adj_frequency)gen.ApplySignal(waveform, REG1, freq);
    gen.EnableOutput(sig_gen_start);
    if(freq_sweep_trigger_start){
      IncrementFrequencyTest();
    }
    X = false;
  }
	


  
  //if(wave_from_num < 0)wave_from_num = 0; 

  
 
  

  //Serial.println(freq);




}