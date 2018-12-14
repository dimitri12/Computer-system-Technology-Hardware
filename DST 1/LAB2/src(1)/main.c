#include "system_sam3x.h"
#include "at91sam3x8.h"
void main(void){
SystemInit();
*AT91C_PMC_PCER=1<<13;
*AT91C_PMC_PCER=1<<14;
volatile unsigned int column[3]={0x40,0x80,0x100};
volatile unsigned int row[4]={0x4,0x8,0x10,0x20};
while(1){
// to do
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
int func(void){
  volatile unsigned int column[3]={0x40,0x80,0x100};
  volatile unsigned int row[4]={0x4,0x8,0x10,0x20};
  int value,i,j;
  *AT91C_PIOD_CODR=1<<2;
  ColumnOutput();
  SetColHigh();
  for(i=0; i<3; i++){
    ColDisable(column[i]);
    for(j=0; j<4; j++){
      if(row[j]==0){
    //    value = 
      }
    }
  }
  return value;
}