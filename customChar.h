#ifndef CUSTOMCHAR_H
#define CUSTOMCHAR_H
#include <LiquidCrystal.h>
#include <Arduino.h>
extern byte line_div[8];
extern byte U_line[8];
extern byte U_a[8];
extern byte U_A[8];
extern byte U_b[8];
extern byte U_B[8];
extern byte U_c[8];
extern byte U_C[8];
extern byte U_d[8];
extern byte U_D[8];
extern byte U_e[8];
extern byte U_E[8];
extern byte U_f[8];
extern byte U_F[8];
extern byte U_g[8];
extern byte U_G[8];
extern byte U_h[8];
extern byte U_H[8];
extern byte U_i[8];
extern byte U_I[8];
extern byte U_j[8];
extern byte U_J[8];
extern byte U_k[8];
extern byte U_K[8];
extern byte U_l[8];
extern byte U_L[8];
extern byte U_m[8];
extern byte U_M[8];
extern byte U_n[8];
extern byte U_N[8];
extern byte U_o[8];
extern byte U_O[8];
extern byte U_p[8];
extern byte U_P[8];


void initChar(LiquidCrystal &LCD_obj);
void print_Uline(LiquidCrystal &LCD_obj, const char msg[]);


#endif