#include "system_sam3x.h"
#include "at91sam3x8.h"
volatile unsigned int column[3]={0x80,0x100,0x40};
volatile unsigned int row[4]={0x20,0x4,0x8,0x10};
int func(void);
void RegisterEnable(void);
unsigned int ButtonReader(void);
void ColEnable(unsigned int value);
void ColumnInput(void);
void ColumnOutput(void);
void SetColHigh(void);
void ColDisable(unsigned int value);
void main(void){
SystemInit();
*AT91C_PMC_PCER=1<<13;
*AT91C_PMC_PCER=1<<14;
RegisterEnable();
*AT91C_PIOD_PER=0x8;
*AT91C_PIOD_OER=0x8;
*AT91C_PIOD_CODR=0x8;
while(1){
  func();
}// while(1)
} // main()
void RegisterEnable(void){
  *AT91C_PIOD_PER=1<<2;
  *AT91C_PIOD_OER=1<<2;
  //rad2
  *AT91C_PIOC_PER=1<<2;
  *AT91C_PIOC_PPUDR=1<<2;
  *AT91C_PIOC_IDR=1<<2;
  //rad3
  *AT91C_PIOC_PER=1<<3;
  *AT91C_PIOC_PPUDR=1<<3;
  *AT91C_PIOC_IDR=1<<3;
  //rad4
  *AT91C_PIOC_PER=1<<4;
  *AT91C_PIOC_PPUDR=1<<4;
  *AT91C_PIOC_IDR=1<<4;
  //rad1
  *AT91C_PIOC_PER=1<<5;
  *AT91C_PIOC_PPUDR=1<<5;
  *AT91C_PIOC_IDR=1<<5;
  //kol3
  *AT91C_PIOC_PER=1<<7;
  *AT91C_PIOC_PPUDR=1<<7;
  *AT91C_PIOC_IDR=1<<7;
  //kol1
  *AT91C_PIOC_PER=1<<8;
  *AT91C_PIOC_PPUDR=1<<8;
  *AT91C_PIOC_IDR=1<<8;
  //kol2
  *AT91C_PIOC_PER=1<<9;
  *AT91C_PIOC_PPUDR=1<<9;
  *AT91C_PIOC_IDR=1<<9;
}
void ColumnInput(void){
  //rad2
  *AT91C_PIOC_ODR=1<<2;
  //rad3
  *AT91C_PIOC_ODR=1<<3;
  //rad4
  *AT91C_PIOC_ODR=1<<4;
  //rad1
  *AT91C_PIOC_ODR=1<<5;
  //kol3
  *AT91C_PIOC_ODR=1<<7;
  //kol1
  *AT91C_PIOC_ODR=1<<8;
  //kol2
  *AT91C_PIOC_ODR=1<<9;
}
void ColumnOutput(void){
  //rad2
  *AT91C_PIOC_OER=1<<2;
  //rad3
  *AT91C_PIOC_OER=1<<3;
  //rad4
  *AT91C_PIOC_OER=1<<4;
  //rad1
  *AT91C_PIOC_OER=1<<5;
  //kol3
  *AT91C_PIOC_OER=1<<7;
  //kol1
  *AT91C_PIOC_OER=1<<8;
  //kol2
  *AT91C_PIOC_OER=1<<9;
}
void SetColHigh(void){
   //rad2
  *AT91C_PIOC_SODR=1<<2;
  //rad3
  *AT91C_PIOC_SODR=1<<3;
  //rad4
  *AT91C_PIOC_SODR=1<<4;
  //rad1
  *AT91C_PIOC_SODR=1<<5;
  //kol3
  *AT91C_PIOC_SODR=1<<7;
  //kol1
  *AT91C_PIOC_SODR=1<<8;
  //kol2
  *AT91C_PIOC_SODR=1<<9;
}
void ColDisable(unsigned int value){
  *AT91C_PIOC_CODR=value;
}
void ColEnable(unsigned int value){
  *AT91C_PIOC_SODR=value;
}
unsigned int ButtonReader(void){
  volatile unsigned int val;
  
 val=*AT91C_PIOC_ODSR;
 return val;
}
int func(void){
  *AT91C_PIOD_CODR=0x8;
  int value,i,j;
  value=0;
  volatile unsigned int x,y;
  *AT91C_PIOD_CODR=1<<2;
  ColumnOutput();
  SetColHigh();
  for(i=0; i<3; i++){
    ColDisable(column[i]);
    for(j=0; j<4; j++){
      y=ButtonReader();
      if((~y&(row[j]))==(row[j])){
      value = (j)*3+(i)+1;
      *AT91C_PIOD_SODR=0x8;
      ColEnable(column[i]);
      ColumnInput();
      return value;
      }
    }
    *AT91C_PIOD_CODR=0x8;
    ColEnable(column[i]);
  }
  ColumnInput();
  return value;
}