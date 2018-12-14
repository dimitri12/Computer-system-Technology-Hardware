#include "system_sam3x.h"
#include "at91sam3x8.h"
#include <stdio.h>
#include <math.h>
#include "core_cm3.h"
#define AT91C_TC0_RA    (AT91_CAST(AT91_REG *) 	0x40080014)
#define AT91C_TC0_RB    (AT91_CAST(AT91_REG *) 	0x40080018)
volatile unsigned int column[3]={0x100,0x200,0x80};
volatile unsigned int row[4]={0x20,0x4,0x8,0x10};
double day1[1440];
int pointer1=0;
double day2[1440];
int pointer2=0;
double day3[1440];
int pointer3=0;
double day4[1440];
int pointer4=0;
double day5[1440];
int pointer5=0;
double day6[1440];
int pointer6=0;
double day7[1440];
int pointer7=0;
double average[7];
double minim[7];
double maxim[7];
int func(void);
void Minimum(void);
void MenuText(void);
void Delete(void);
void InitText(void);
void Maximum(void);
void Temp_Mode(void);
void Servo_Mode(void);
void Fast_Mode(void);
void Servo(int val);
void Average(void);
int Choice(void);
void RegisterEnable(void);
unsigned int ButtonReader(void);
void Space(void);
void ColEnable(unsigned int value);
void ColumnInput(void);
void ColumnOutput(void);
void SetColHigh(void);
void ColDisable(unsigned int value);
unsigned int OutPutReader(void);
void Write_Data_2_Display(unsigned char data);
void Write_Command_2_Display(unsigned char command);
unsigned char Read_Status_Display(void);
void DatabusInput(void);
void Welcome(void);
void Insert(double a);
void SetReset(void);
void ClearReset(void);
void SetWrite(void);
void ClearDatabus(void);
void DatabusOutput(void);
void EnableDIR(void);
void Init_Display(void);
void DisableDIR(void);
void OEoutput(void);
void ClearWrite(void);
void DisableOE(void);
void SetRead(void);
void SetChipSelect(void);
void Delay(int Value);
void ClearRead(void);
void View_Mode(void);
void ClearChipSelect(void);
void ClearCD(void);
void setCD(void);
void OEoutput(void);
void bitstarter(unsigned char data);
void InitPWM(void);
void Measure(void);
void TimerInit(void);
void SystickInit(void);
void TempTest(void);
void ADCinit(void);
void Menu(void);
int ADCmeasure(void);
double Temping(void);
void Larm(double value);
int time=0;
int ticks =0;
int max=22;
int min=19;
  void main(void){
SystemInit();
//int b,c;
 //double a;
 ADCinit();
 //c=0;
 TimerInit();
InitPWM();
*AT91C_PMC_PCER=1<<12;
*AT91C_PMC_PCER=1<<13;
*AT91C_PMC_PCER=1<<14;
RegisterEnable();
Init_Display();
InitText();
SystickInit();
Welcome();
MenuText();
while(1){
  Menu();
 /* /AT91C_PIOD_SODR=0x8; //LED
  //Servo(1001);//0
  double volt;
  Delay(840000);
  b=ADCmeasure();
 volt=((b*3.3)/(4095));
  printf("%f\n",volt);
   double temp2;
 //a= TC0_Handler();
  */ 
}// while(1)
} // main()
void SystickInit(void){
  SysTick_Config(84000);
}
void SysTick_Handler(void){
  ticks++;
}
double Temping(void){
  double temp2;
  Measure();
  temp2=(((time)/(5.0*42.5))-273.15);
  if(temp2<0){
return NULL;
  }
  return temp2;
}
void RegisterEnable(void){
  *AT91C_PIOD_PER=1<<3;
  *AT91C_PIOD_OER=1<<3;
*AT91C_PIOD_CODR=1<<3;

  //display databus
*AT91C_PIOC_PER=0x3FC;
  *AT91C_PIOD_PER=1<<2;
  *AT91C_PIOD_OER=1<<2;

   //FS
  *AT91C_PIOC_PER=1<<18;
  *AT91C_PIOC_OER=1<<18;
  *AT91C_PIOC_SODR=1<<18;
  //RV
  *AT91C_PIOC_PER=1<<19;
  *AT91C_PIOC_OER=1<<19;
  *AT91C_PIOC_SODR=1<<19;
  //C/D
  *AT91C_PIOC_PER=1<<17;
  *AT91C_PIOC_OER=1<<17;
  //dir
  *AT91C_PIOC_PER=1<<13;
  *AT91C_PIOC_OER=1<<13;
  //OE
  *AT91C_PIOC_PER=1<<12;
  *AT91C_PIOC_OER=1<<12;
  //chip select
  *AT91C_PIOC_PER=1<<16;
   *AT91C_PIOC_OER=1<<16;
  //read
  *AT91C_PIOC_PER=1<<15;
  *AT91C_PIOC_OER=1<<15;
  //write
  *AT91C_PIOC_PER=1<<14;
  *AT91C_PIOC_OER=1<<14;
  //reset
  *AT91C_PIOD_PER=1;
  *AT91C_PIOD_OER=1;
}
void ColumnInput(void){
  //kol1
  *AT91C_PIOC_ODR=1<<8;
  //kol2
  *AT91C_PIOC_ODR=1<<9;
   //kol3
  *AT91C_PIOC_ODR=1<<7;
}
void ColumnOutput(void){
  //kol1
  *AT91C_PIOC_OER=1<<8;
  //kol2
  *AT91C_PIOC_OER=1<<9;
  //kol3
  *AT91C_PIOC_OER=1<<7;
}
void SetColHigh(void){
  //kol1
  *AT91C_PIOC_SODR=1<<8;
  //kol2
  *AT91C_PIOC_SODR=1<<9;
  //kol3
  *AT91C_PIOC_SODR=1<<7;
}
void ColDisable(unsigned int value){
  *AT91C_PIOC_CODR=value;
}
void ColEnable(unsigned int value){
  *AT91C_PIOC_SODR=value;
}
unsigned int ButtonReader(void){
  volatile unsigned int val;
 val=*AT91C_PIOC_PDSR;
 return val;
}
unsigned int OutPutReader(void){
  volatile unsigned int val;
 val=*AT91C_PIOC_ODSR;
 return val;
}
int func(void){
  *AT91C_PIOD_CODR=0x8;
  int value,i,j,co,ro;
  value=0;
  co=0;
  ro=0;
  volatile unsigned int w,x,y,z;
  *AT91C_PIOD_CODR=1<<2;
  ColumnOutput();
  SetColHigh();
  for(i=0; i<3; i++){
    ColDisable(column[i]);
    for(j=0; j<4; j++){
      w=ButtonReader();
      x=w&0xF00;
      y=w&0xF0;
      z=w&0xF;
       if(x==0xE00){
        if(y==0xF0&&z==0xA){
        co=0; ro=1;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(y==0xF0&&z==0x6){
        co=0; ro=2;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(z==0xE&&y==0xD0){
        co=0; ro=0;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(z==0xE&&y==0xE0){
        co=0; ro=3;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("*");
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
      }
      if(x==0xD00){
        if(y==0xF0&&z==0xA){
        co=1; ro=1;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(y==0xF0&&z==0x6){
        co=1; ro=2;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(z==0xE&&y==0xD0){
        co=1; ro=0;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(z==0xE&&y==0xE0){
        co=1; ro=3;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
      }
      if(x==0xF00){
        if(y==0x70&&z==0xA){
        co=2; ro=1;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(y==0x70&&z==0x6){
        co=2; ro=2;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(z==0xE&&y==0x50){
        co=2; ro=0;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("%d",value);
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }
        else if(z==0xE&&y==0x60){
        co=2; ro=3;
        value = ro*3+co+1;
        *AT91C_PIOD_SODR=0x8;
        printf("#");
        ColEnable(column[i]);
        ColumnInput();
        *AT91C_PIOD_SODR=1<<2;
        return value;
        }}}   
    *AT91C_PIOD_CODR=0x8;
    ColEnable(column[i]);
  }
  ColumnInput();
  *AT91C_PIOD_SODR=1<<2;
  return value;
}
void DisableDIR(void){
  *AT91C_PIOC_SODR=1<<13;
}
void OEoutput(void){
  *AT91C_PIOC_CODR=1<<12;
}
void setCD(void){
  *AT91C_PIOC_SODR=1<<17;
}
void ClearCD(void){
 *AT91C_PIOC_CODR=1<<17;
}
void ClearChipSelect(void){
  *AT91C_PIOC_CODR=1<<16;
}
void ClearRead(void){
  *AT91C_PIOC_CODR=1<<15; 
}
void Delay(int Value){
    int i;
    for(i=0; i<Value;i++){
      asm("nop");
    }
}
void SetChipSelect(void){
  *AT91C_PIOC_SODR=1<<16; 
}
void SetRead(void){
   *AT91C_PIOC_SODR=1<<15; 
}
void DisableOE(void){
  *AT91C_PIOC_SODR=1<<12; 
}
void EnableDIR(void){
   *AT91C_PIOC_CODR=1<<13;
}
void DatabusInput(void){
    *AT91C_PIOC_ODR=0x3FC;
}
void DatabusOutput(void){
  *AT91C_PIOC_OER=0x3FC;
}
void ClearDatabus(void){
  *AT91C_PIOC_CODR=0x3FC;
}
void SetWrite(void){
  *AT91C_PIOC_SODR=1<<14;
}
void ClearWrite(void){
  *AT91C_PIOC_CODR=1<<14;
}
void ClearReset(void){
   *AT91C_PIOD_CODR=1;
}
void SetReset(void){
   *AT91C_PIOD_SODR=1;
}
unsigned char Read_Status_Display(void){
  volatile unsigned int x;
  unsigned char temp;
  DatabusInput();
  DisableDIR();
  OEoutput();
  setCD();
  ClearChipSelect();
  Delay(10);
  x=*AT91C_PIOC_PDSR>>2;
  temp =x;
  SetChipSelect();
  SetRead();
  DisableOE();
  EnableDIR();
  return temp;
}
void Write_Command_2_Display(unsigned char command){
  unsigned char x,y;
  x=Read_Status_Display();
  y=x&0x3;
  while(y!=0x3){
    x=Read_Status_Display();
  y=x&0x3;}
  if(y==0x3){
  ClearDatabus();
  command=((unsigned int)command);
  *AT91C_PIOC_SODR=command<<2;
  EnableDIR();
  OEoutput();
  DatabusOutput();
  setCD();
  ClearChipSelect();
  ClearWrite();
  Delay(10);
  SetChipSelect();
  SetWrite();
  DisableOE();
  DatabusInput();
  }else{
  }
}
void Write_Data_2_Display(unsigned char data){
  unsigned char x,y;
  volatile unsigned int z;
  x=Read_Status_Display();
  y=(x&0x3);
  while(y!=0x3){
    x=Read_Status_Display();
  y=x&0x3;
  }
  if(y==0x3){
  ClearDatabus();
 data=((unsigned int)data);
 *AT91C_PIOC_SODR =data<<2;
  EnableDIR();
  OEoutput();
  DatabusOutput();
  ClearCD();
  ClearChipSelect();
  ClearWrite();
  Delay(10);
  SetChipSelect();
  SetWrite();
  DisableOE();
  DatabusInput();
  }
}
void Init_Display(void){
  int i;
   ClearReset();
   Delay(10);
   SetReset();
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x40);//Set text home address
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x42);//graphic home adress
  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x41);//Set text home address
  Write_Data_2_Display(0x28);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x43);//Set text home address
  Write_Command_2_Display(0x80);//Set text home address
  Write_Command_2_Display(0x94);//Set text home address
  Write_Data_2_Display(0x00);//x
     Write_Data_2_Display(0x00);//x
     Write_Command_2_Display(0x24);//adresspointer
      for(i=0;i<640;i++){
      Write_Data_2_Display(0x00);//y
      Write_Command_2_Display(0xC0); //clear displays
      }
}
void TimerInit(void){
  *AT91C_PMC_PCER = 1<<27;
  *AT91C_TC0_CMR=0x0; //Enable TIMER_CLOCK1
  *AT91C_PIOB_PER=1<<25; 
    NVIC_ClearPendingIRQ(TC0_IRQn);
  NVIC_SetPriority(TC0_IRQn,200); 
  NVIC_EnableIRQ(TC0_IRQn);
}
void Measure(void){
*AT91C_TC0_IER=1<<6;
  *AT91C_PIOB_OER=1<<25;
   *AT91C_PIOB_CODR=1<<25;
   Delay(25);
   *AT91C_PIOB_SODR=1<<25;
    *AT91C_PIOB_ODR=1<<25;
   *AT91C_TC0_CCR=0x5;
*AT91C_TC0_CMR=0x60000; 
}
void TC0_Handler(void){
  volatile unsigned int x,y;
  *AT91C_TC0_IDR=1<<6;
  x=*AT91C_TC0_RB;
  y=*AT91C_TC0_RA;
  time=x-y;  
}
void ADCinit(void){
  *AT91C_PMC_PCER=1<<11;
  *AT91C_PMC_PCER1=1<<5;
  *AT91C_ADCC_MR=2<<8;
}
int ADCmeasure(void){
  int x;
  *AT91C_PIOA_PER=1<<23;
  *AT91C_ADCC_CHER=0x20;
  *AT91C_ADCC_CR=1<<1;
  while(*AT91C_ADCC_SR&0x01000000==(0x01000000));
  x=(*AT91C_ADCC_LCDR&0xFFF);
  return x;
}
void InitPWM(void){
  *AT91C_PMC_PCER1=1<<4;
  *AT91C_PIOC_PDR=1<<24;
  *AT91C_PIOC_ABMR=1<<24;
  *AT91C_PWMC_ENA=1<<7;
  *AT91C_PWMC_CH7_CMR=0x05;
  *AT91C_PWMC_CH7_CPRDR=52500;
  *AT91C_PWMC_CH7_CDTYR=1;
}
void Servo(int val){
  *AT91C_PWMC_CH7_CDTYR=val;
}
void Larm(double value){
  int not;
  not=0;
  if(value<min){
    while(not<10){
      if(ticks%2==0){
    *AT91C_PIOD_SODR=1<<3;
    }
    else{*AT91C_PIOD_CODR=1<<3;}
    not++;
    }
    value=min;
  }
  else if(value>max){
     while(not<10){
      if(ticks%2==0){
    *AT91C_PIOD_SODR=1<<3;
    }
    else{*AT91C_PIOD_CODR=1<<3;}
    not++;
    }value=max;}
  else{*AT91C_PIOD_CODR=1<<3;}
}
void Insert(double a){
  if(pointer1!=sizeof(day1)){
      day1[pointer1]=a;
      pointer1++;
    }
  else if(pointer1==sizeof(day1)&&pointer2!=sizeof(day2)){
    day2[pointer2]=a;
    pointer2++;
    }
  else if(pointer2==sizeof(day2)&&pointer3!=sizeof(day3)){
    day3[pointer3]=a;
    pointer3++;
    }
  else if(pointer3==sizeof(day3)&&pointer4!=sizeof(day4)){
    day4[pointer4]=a;
    pointer4++;
    }
  else if(pointer4==sizeof(day4)&&pointer5!=sizeof(day5)){
    day5[pointer5]=a;
    pointer5++;
    }
  else if(pointer5==sizeof(day5)&&pointer6!=sizeof(day6)){
    day6[pointer6]=a;
    pointer2++;
    }
  else if(pointer6==sizeof(day6)&&pointer7!=sizeof(day7)){
    day7[pointer7]=a;
    pointer2++;
    }
  else if(pointer7==sizeof(day7)){
    pointer1=0;
    pointer2=0;
    pointer3=0;
    pointer4=0;
    pointer5=0;
    pointer6=0;
    pointer7=0;
    }
  else{printf("something went wrong");
  }
}
void Average(void){
  int i;
  double sum;
  sum=0;
  for(i=0;i<=pointer1;i++){
    sum=sum+day1[i];
  }
  average[0]=sum/pointer1;
  sum=0;
  for(i=0;i<=pointer2;i++){
    sum=sum+day2[i];
  }
  average[1]=sum/pointer2;
  sum=0;
  for(i=0;i<=pointer3;i++){
    sum=sum+day3[i];
  }
  average[2]=sum/pointer3;
  sum=0;
  for(i=0;i<=pointer4;i++){
    sum=sum+day4[i];
  }
  average[3]=sum/pointer4;
  sum=0;
  for(i=0;i<=pointer5;i++){
    sum=sum+day5[i];
  }
  average[4]=sum/pointer5;
  sum=0;
  for(i=0;i<=pointer6;i++){
    sum=sum+day6[i];
  }
  average[5]=sum/pointer6;
  sum=0;
  for(i=0;i<=pointer7;i++){
    sum=sum+day7[i];
  }
  average[6]=sum/pointer7;
}
void Minimum(void){
  double minimalv =100000;
  int i;
  for(i=0;i<=pointer1;i++){
    if(day1[i]<minimalv){
      minimalv=day1[i];
    }
  }
  minim[0]=minimalv;
  minimalv =100000;
  for(i=0;i<=pointer2;i++){
    if(day2[i]<minimalv){
      minimalv=day2[i];
    }
}
minim[1]=minimalv;
minimalv =100000;
  for(i=0;i<=pointer3;i++){
    if(day3[i]<minimalv){
      minimalv=day3[i];
    }
    }
  minim[2]=minimalv;
  minimalv =100000;
  for(i=0;i<=pointer4;i++){
    if(day4[i]<minimalv){
      minimalv=day4[i];
    }
    }
  minim[3]=minimalv;
  minimalv =100000;
  for(i=0;i<=pointer5;i++){
    if(day5[i]<minimalv){
      minimalv=day5[i];
    }
    }
  minim[4]=minimalv;
  minimalv =100000;
  for(i=0;i<=pointer6;i++){
    if(day6[i]<minimalv){
      minimalv=day6[i];
    }
    }
  minim[5]=minimalv;
  minimalv =100000;
  for(i=0;i<=pointer7;i++){
    if(day7[i]<minimalv){
      minimalv=day7[i];
    }
    }
  minim[6]=minimalv;

}
void Maximum(void){
  double maximalv;
  int i;
  maximalv=0;
  for(i=0; i<pointer1;i++){
    if(day1[i]>maximalv){
      maximalv=day1[i];
    }
    maxim[0]=maximalv;
  }
  maximalv=0;
  for(i=0; i<pointer2;i++){
    if(day2[i]>maximalv){
      maximalv=day2[i];
    }
    maxim[1]=maximalv;
  }
  maximalv=0;
  for(i=0; i<pointer3;i++){
    if(day3[i]>maximalv){
      maximalv=day3[i];
    }
    maxim[2]=maximalv;
  }
  maximalv=0;
  for(i=0; i<pointer4;i++){
    if(day4[i]>maximalv){
      maximalv=day4[i];
    }
    maxim[3]=maximalv;
  }
  maximalv=0;
  for(i=0; i<pointer5;i++){
    if(day5[i]>maximalv){
      maximalv=day5[i];
    }
    maxim[4]=maximalv;
  }
  maximalv=0;
  for(i=0; i<pointer6;i++){
    if(day6[i]>maximalv){
      maximalv=day6[i];
    }
    maxim[5]=maximalv;
  }
  maximalv=0;
  for(i=0; i<pointer7;i++){
    if(day7[i]>maximalv){
      maximalv=day7[i];
    }
    maxim[6]=maximalv;
  }
}
void InitText(void){
  int i;
Write_Data_2_Display(0x00);//x
Write_Data_2_Display(0x00);//y
Write_Command_2_Display(0x24);//ADP den som skriver text
for(i=0; i<11; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
Write_Data_2_Display(0x24);//D
Space();
Write_Data_2_Display(0x49);//i
Space();
Write_Data_2_Display(0x4D);//m
Space();
Write_Data_2_Display(0x49);//i
Space();
Write_Data_2_Display(0x54);//t
Space();
Write_Data_2_Display(0x52);//r
Space();
Write_Data_2_Display(0x49);//i
Space();
Write_Data_2_Display(0x53);//s
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x30);//P
Space();
Write_Data_2_Display(0x52);//r
Space();
Write_Data_2_Display(0x4F);//o
Space();
Write_Data_2_Display(0x4A);//j
Space();
Write_Data_2_Display(0x45);//e
Space();
Write_Data_2_Display(0x4B);//k
Space();
Write_Data_2_Display(0x54);//t
Space();
}
void Space(void){
  Write_Command_2_Display(0xC0);
}
void MenuText(void){
  int i;
for(i=0; i<13; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
//1.Temp Mode
Write_Data_2_Display(0x11);
Space();
Write_Data_2_Display(0x0E);
Space();
Write_Data_2_Display(0x34);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x4D);
Space();
Write_Data_2_Display(0x50);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x2D);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();
//2.Servo Mode
for(i=0; i<29; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}

Write_Data_2_Display(0x12);
Space();
Write_Data_2_Display(0x0E);
Space();
Write_Data_2_Display(0x33);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x52);
Space();
Write_Data_2_Display(0x56);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x2D);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();
//3.Fast Mode
for(i=0; i<28; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}

Write_Data_2_Display(0x13);
Space();
Write_Data_2_Display(0x0E);
Space();
Write_Data_2_Display(0x26);
Space();
Write_Data_2_Display(0x41);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x54);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x2D);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();
//4.View Mode
for(i=0; i<29; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
Write_Data_2_Display(0x14);
Space();
Write_Data_2_Display(0x0E);
Space();
Write_Data_2_Display(0x36);
Space();
Write_Data_2_Display(0x49);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x57);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x2D);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();

//Introduction text(visas på redovisningen)
for(i=0; i<69; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
Write_Data_2_Display(0x24);
Space();
Write_Data_2_Display(0x41);
Space();
Write_Data_2_Display(0x54);
Space();
Write_Data_2_Display(0x41);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x59);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x54);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x4D);
Space();
Write_Data_2_Display(0x54);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x4B);
Space();
Write_Data_2_Display(0x4E);
Space();
Write_Data_2_Display(0x49);
Space();
Write_Data_2_Display(0x4B);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x29);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x28);
Space();
Write_Data_2_Display(0x79);
Space();
Write_Data_2_Display(0x47);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x4B);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x4C);
Space();
Write_Data_2_Display(0x41);
Space();
Write_Data_2_Display(0x4E);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x29);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x28);
Space();
Write_Data_2_Display(0x41);
Space();
Write_Data_2_Display(0x4C);
Space();
Write_Data_2_Display(0x4D);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x54);
Space();
Write_Data_2_Display(0x41);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x36);
Space();
Write_Data_2_Display(0x64);
Space();
Write_Data_2_Display(0x4C);
Space();
Write_Data_2_Display(0x4A);
Space();
Write_Data_2_Display(0x5C);
Space();
}
int Choice(void){
  int data;
  data = func();
  if(data!=0){
   if(data!=0&&data<10){Write_Data_2_Display(0x10+data);}
  else if(data==10){Write_Data_2_Display(0x0A);}
  else if(data==11){Write_Data_2_Display(0x10);}
  else if(data==12){Write_Data_2_Display(0x03);}
  Write_Command_2_Display(0xC0);
  }
  return data;
}
void Temp_Mode(void){
  int i,s;
  for(i=0; i<44; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
Write_Data_2_Display(0x34);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x4D);
Space();
Write_Data_2_Display(0x50);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x2D);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x49);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x4E);
Space();
  s=Choice();
 double variable;
 while(s!=9){
 if((ticks==60000)){
 ticks=0;
 variable=Temping();
 if(variable>0){
  variable=round(variable);
   printf("%f\n",variable);
   Insert(variable);
   Larm(variable);
 }else{variable = variable+20.59271;
 variable=round(variable);
 printf("%f\n",variable);}
 }
 s=Choice();
 }
  for(i=0; i<62; i++){
Delete();
}
}
void Servo_Mode(void){
  int i;
  for(i=0; i<29; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
  Write_Data_2_Display(0x33);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x52);
Space();
Write_Data_2_Display(0x56);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x2D);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x49);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x56);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x4C);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x50);
Space();
Write_Data_2_Display(0x49);
Space();
Write_Data_2_Display(0x4E);
Space();
Write_Data_2_Display(0x47);
Space();
}
void Fast_Mode(void){
  int i,s;
   for(i=0; i<44; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
Write_Data_2_Display(0x26);
Space();
Write_Data_2_Display(0x41);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x54);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x2D);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x44);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x49);
Space();
Write_Data_2_Display(0x53);
Space();
Write_Data_2_Display(0x00);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x4E);
Space();
  s=Choice();
  double variable;
  while(s!=9){
 if((ticks==1000)){
 ticks=0;
 variable=Temping();
 if(variable>0){
  variable=round(variable);
   printf("%f\n",variable);
   Insert(variable);
   Larm(variable);
 }else{variable = variable+20.59271;
 variable=round(variable);
 printf("%f\n",variable);}
 }
s=Choice();
 }

  for(i=0; i<62; i++){
Delete();
}
}
void View_Mode(void){
  int s;
  s=Choice();
  while(s!=9){
  Average();
  Minimum();
  Maximum();
  int i;
  Write_Data_2_Display(0x00);//x
  Write_Data_2_Display(0x00);//x
  Write_Command_2_Display(0x24);//adresspointer
      for(i=0;i<640;i++){
      Write_Data_2_Display(0x00);//y
      Write_Command_2_Display(0xC0); //clear displays
      }
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x24);//adresspointer
  
  Write_Data_2_Display(0x24);
  Space();
  Write_Data_2_Display(0x41);
  Space();
  Write_Data_2_Display(0x59);
  Space();
  Write_Data_2_Display(0x53);
  Space();
  for(i=0;i<10;i++){
      Write_Data_2_Display(0x00);//y
      Write_Command_2_Display(0xC0); //clear displays
      }
  Write_Data_2_Display(0x21);
  Space();
  Write_Data_2_Display(0x56);
  Space();
  Write_Data_2_Display(0x45);
  Space();
  Write_Data_2_Display(0x52);
  Space();
  Write_Data_2_Display(0x41);
  Space();
  Write_Data_2_Display(0x47);
  Space();
  Write_Data_2_Display(0x45);
  Space();
  for(i=0;i<7;i++){
      Write_Data_2_Display(0x00);//y
      Write_Command_2_Display(0xC0); //clear displays
      }
   Write_Data_2_Display(0x2D);
  Space();
   Write_Data_2_Display(0x49);
  Space();
   Write_Data_2_Display(0x4E);
  Space();
  for(i=0;i<5;i++){
      Write_Data_2_Display(0x00);
      Write_Command_2_Display(0xC0); 
      }
  Write_Data_2_Display(0x2D);
  Space();
  Write_Data_2_Display(0x41);
  Space();
  Write_Data_2_Display(0x58);
  Space();
  Write_Data_2_Display(0x00);
  Space();
  Write_Data_2_Display(0x24);
  Space();
  Write_Data_2_Display(0x41);
  Space();
  Write_Data_2_Display(0x59);
  Space();
  Write_Data_2_Display(0x11);
  Space();
  for(i=0;i<13;i++){
      Write_Data_2_Display(0x00);//y
      Write_Command_2_Display(0xC0); //clear displays
      }
  double avg1;
  int a1,b1;
  avg1=average[0];
  a1=(int)avg1/10;
  b1=(int)avg1%10;
  Write_Data_2_Display(0x10+a1);
  Space();
  Write_Data_2_Display(0x10+b1);
  Space();
  for(i=0;i<7;i++){
      Write_Data_2_Display(0x00);//y
      Write_Command_2_Display(0xC0); //clear displays
      }
  double min1;
  int c1,d1;
  min1=minim[0];
  c1=(int)min1/10;
  d1=(int)min1%10;
  Write_Data_2_Display(0x10+c1);
  Space();
  Write_Data_2_Display(0x10+d1);
  Space();
  for(i=0;i<5;i++){
      Write_Data_2_Display(0x00);//y
      Write_Command_2_Display(0xC0); //clear displays
      }
  double max1;
  int e1,f1;
  max1=maxim[0];
  e1=(int)max1/10;
  f1=(int)max1%10;
  Write_Data_2_Display(0x10+e1);
  Space();
  Write_Data_2_Display(0x10+f1);
  Space();
  s=Choice();
  }
}
void Delete(void){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC2);
}
void Menu(void){
    int s,i;
    s=Choice();
    while(s!=0){
      if(s==1){
        Temp_Mode();
      }
      else if(s==2){
      Servo_Mode();
      }
      else if(s==3){
      Fast_Mode();
      }
      else if(s==4){
      View_Mode();
      }
      else if(s>4){
      Write_Data_2_Display(0x29);
      Space();
      Write_Data_2_Display(0x4E);
      Space();
      Write_Data_2_Display(0x56);
      Space();
      Write_Data_2_Display(0x41);
      Space();
      Write_Data_2_Display(0x4C);
      Space();
      Write_Data_2_Display(0x49);
      Space();
      Write_Data_2_Display(0x44);
      Space();
      for(i=0;i<8;i++){
      Delete();
      }
      }
      s=Choice();
    }
}
void Welcome(void){
    int i;
for(i=0; i<13; i++){
Write_Data_2_Display(0x00);
Write_Command_2_Display(0xC0);
}
Write_Data_2_Display(0x37);
Space();
Write_Data_2_Display(0x45);
Space();
Write_Data_2_Display(0x4C);
Space();
Write_Data_2_Display(0x43);
Space();
Write_Data_2_Display(0x4F);
Space();
Write_Data_2_Display(0x4D);
Space();
Write_Data_2_Display(0x45);
Space();
for(i=0; i<20; i++){
Delete();
}
}