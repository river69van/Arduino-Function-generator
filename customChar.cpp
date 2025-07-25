#include "customChar.h"

byte U_line[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};


byte U_a[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b00001,
  0b01111,
  0b10001,
  0b01111,
  0b11111
};

byte U_A[8] = {
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b10001,
  0b10001,
  0b11111
};


byte U_b[8] = {
  0b10000,
  0b10000,
  0b10110,
  0b11001,
  0b10001,
  0b10001,
  0b11110,
  0b11111
};


byte U_B[8] = {
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b10001,
  0b10001,
  0b11110,
  0b11111
};


byte U_c[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10000,
  0b10000,
  0b10001,
  0b01110,
  0b11111
};

byte U_C[8] = {
  0b01110,
  0b10001,
  0b10000,
  0b10000,
  0b10000,
  0b10001,
  0b01110,
  0b11111
};

byte U_d[8] = {
  0b00001,
  0b00001,
  0b01101,
  0b10011,
  0b10001,
  0b10001,
  0b01111,
  0b11111
};

byte U_D[8] = {
  0b11100,
  0b10010,
  0b10001,
  0b10001,
  0b10001,
  0b10010,
  0b11100,
  0b11111
};

byte U_ee[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10001,
  0b11111,
  0b10000,
  0b01110,
  0b11111
};

byte U_E[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b11111,
  0b10000,
  0b10000,
  0b11111,
  0b11111
};

byte U_f[8] = {
  0b00110,
  0b01001,
  0b01000,
  0b11100,
  0b01000,
  0b01000,
  0b01000,
  0b11111
};

byte U_F[8] = {
  0b11111,
  0b10000,
  0b10000,
  0b11110,
  0b10000,
  0b10000,
  0b10000,
  0b11111
};

byte U_g[8] = {
  0b00000,
  0b01111,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b01110,
  0b11111
};

byte U_G[8] = {
  0b01110,
  0b10001,
  0b10000,
  0b10111,
  0b10001,
  0b10001,
  0b01111,
  0b11111
};

byte line_div[8] = {
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b01110
};



void initChar(LiquidCrystal &lcd) {
  // slot 1 = U_a, slot 2 = U_A
  lcd.createChar(1, line_div);
  lcd.createChar(2, U_A);
  lcd.createChar(3, U_b);
  lcd.createChar(4, U_B);
  lcd.createChar(5, U_c);
  lcd.createChar(6, U_C);
  lcd.createChar(7, U_d);
  
  //lcd.createChar(8, U_D);
  

  /*
  lcd.createChar(10, U_E);
  lcd.createChar(11, U_f);
  lcd.createChar(12, U_F);
  lcd.createChar(13, U_g);
  */
  //lcd.createChar(14, U_G);
  
}


void print_Uline(LiquidCrystal &LCD_obj, const char msg[]){
  size_t len = strlen(msg);
  //lcd.setCursor(col, row);

  for (size_t i = 0; i < len; i++) {
    char c = msg[i];

    if (c == 'a') {
      // overwrite slot 1 with underlined 'a'
      LCD_obj.createChar(1, U_a);
      LCD_obj.write(1);
    }
    else if (c == 'A') {
      // overwrite slot 2 with underlined 'A'
      LCD_obj.createChar(2, U_A);
      LCD_obj.write(2);
    }
    else {
      // normal ASCII character
      LCD_obj.write(c);
    }
  }
}

