/***********************************************************************************************
*	  			  EEPROM I2C
* File name		: I2C_EEPROM 
* Programmer 	: 
* Web presence  :  
* Note			:  
* Language		: 
* Hardware		: 
* Date			:  
************************************************************************************************/ 
#include "i2c_eeprom.h"
#include "eeprom_define.h"
#include "delay.c"
//---------------------------------------------------------------------------------
uint8_t MAKE_8_FLOAT(float var,uint8_t offset){
union
{
uint8_t b[4];
float f;
} data;
data.f =var;


return data.b[offset];
}
//---------------------------------------------------------------------------------
float MAKE_FLOAT(uint8_t var1,uint8_t var2,uint8_t var3,uint8_t var4){
union
{
uint8_t b[4];
float f;
} data;
data.b[0]=var1;
data.b[1]=var2;
data.b[2]=var3;
data.b[3]=var4;


return data.f;
}
//----------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void I2C_init(void)
{
 GPIO_InitTypeDef GPIO_InitStruct;
	
		I2C_SCL_RCC_ENABLE;
	  I2C_SDA_RCC_ENABLE;
/*I2C_SDA*/
  GPIO_InitStruct.Pin = I2C_SDA_BIT;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;	
  HAL_GPIO_Init(I2C_SDA_PORT, &GPIO_InitStruct);	
/*I2C_SCL*/
  GPIO_InitStruct.Pin = I2C_SCL_BIT;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;	
  HAL_GPIO_Init(I2C_SCL_PORT, &GPIO_InitStruct);
	

}
//-----------------------------------------------------------------------------------
void I2C_start()
{
	delay_us(1000);
SET_SDA;
	delay_us(100);
SET_SCL;
delay_us(100);
RESET_SDA;
	delay_us(100);
RESET_SCL;
	delay_us(100);
}
//-----------------------------------------------------------------------------------
void I2C_stop()
{
		delay_us(100);
RESET_SCL;	
		delay_us(100);
RESET_SDA;	
		delay_us(100);
SET_SCL;
		delay_us(100);
SET_SDA;	
		delay_us(1000);
}
//-----------------------------------------------------------------------------------
uint8_t I2C_RW(uint8_t data,uint8_t ACK)
{
uint8_t i,j,k=0;	
 RESET_SCL;	
	    for(i=0,j=128;i<8;i++)
      {
      
       if((data&j)>0)	
       SET_SDA;							 
       else
       RESET_SDA;	
       delay_us(100);			 
       SET_SCL; 
			 delay_us(100);	
			 RESET_SCL;	
			     if((I2C_SDA_PORT->IDR & I2C_SDA_BIT)!=0)k|=j;
			 j>>=1;	
      }	
RESET_SDA;	

if(ACK==1)
{			
SET_SCL; 	
			 delay_us(100);		
RESET_SCL;
       delay_us(100);		
}

delay_us(100);	

	
return k;			
}
//-----------------------------------------------------------------------------------
uint8_t EEPROM_WRIGHT(uint16_t address,uint8_t data)
{

uint8_t device_address=0xA0,k=0;	
	
k=address/256;	
k=k<<1;
device_address|=k;	

I2C_start();
I2C_RW(device_address,1);
I2C_RW(address,1);
I2C_RW(data,1);	
I2C_stop();		
	delay_ms(15);
return 0;
}
//------------------------------------------------------------------------------------
uint8_t EEPROM_READ(uint16_t address)
{
	
uint8_t device_address;
uint8_t i,k[10];	

	for(i=0;i<9;i++){

k[i]=0;	
device_address=0xA0;	
k[i]=address/256;	
k[i]=k[i]<<1;
device_address|=k[i];	
		
I2C_start();
I2C_RW(device_address,1);		
I2C_RW(address,1);		
I2C_start();	

device_address=0xA1;	
k[i]=address/256;	
k[i]=k[i]<<1;
device_address|=k[i];	
	
I2C_RW(device_address,1);		
k[i]=I2C_RW(0xFF,0);	
	
	
I2C_stop();
delay_ms(1);
if(i!=0)if(k[i-1]==k[i])return k[i];	
}

return k[0];

	
	
}
//************************************************************************************
uint8_t eeprom_write_int8(uint8_t var,uint16_t eeprom_i){
	EEPROM_WRIGHT(eeprom_i,(uint8_t) var);	
	return 0;
}
//************************************************************************************
//************************************************************************************
uint8_t eeprom_write_int24(uint32_t var,uint16_t eeprom_i){
EEPROM_WRIGHT(eeprom_i,(uint8_t) var);
	var>>=8;
EEPROM_WRIGHT(eeprom_i+1,(uint8_t) var);
	var>>=8;
EEPROM_WRIGHT(eeprom_i+2,(uint8_t) var);	
	return 0;
}
//************************************************************************************
//************************************************************************************
uint32_t eeprom_read_int24(uint16_t eeprom_i){
	uint32_t var=0;
	
var=EEPROM_READ(eeprom_i+2);
var<<=8;
var+=EEPROM_READ(eeprom_i+1);	
var<<=8;
var+=EEPROM_READ(eeprom_i);		
		return var;
}
//************************************************************************************
//************************************************************************************
uint8_t eeprom_write_int16(uint16_t var,uint16_t eeprom_i){
EEPROM_WRIGHT(eeprom_i,(uint8_t) var);
	var>>=8;
EEPROM_WRIGHT(eeprom_i+1,(uint8_t) var);
return 0;	
}
//************************************************************************************
//************************************************************************************
uint8_t eeprom_write_float(float var,uint16_t eeprom_i)
{
  uint8_t i;
  for(i = 0; i < 4; i++)   // ? ???? 4 ????
  {
      EEPROM_WRIGHT(eeprom_i + i, MAKE_8_FLOAT(var, i));
  }
  return 0;
}
//************************************************************************************
//************************************************************************************
uint8_t eeprom_read_int8(uint16_t eeprom_i){
uint8_t var;	
var=EEPROM_READ(eeprom_i);	
	return var;
}
//************************************************************************************
//************************************************************************************
uint16_t eeprom_read_int16(uint16_t eeprom_i){
	uint16_t var=0;
	
var=EEPROM_READ(eeprom_i+1);
var<<=8;
var+=EEPROM_READ(eeprom_i);	
		return var;
}
//************************************************************************************
//************************************************************************************
float eeprom_read_float(uint16_t eeprom_i){
uint8_t i[4];
float var=0;	
	
i[0]=EEPROM_READ(eeprom_i);
i[1]=EEPROM_READ(eeprom_i+1);
i[2]=EEPROM_READ(eeprom_i+2);
i[3]=EEPROM_READ(eeprom_i+3);	
var=MAKE_FLOAT(i[0],i[1],i[2],i[3]);	
	return var;
}


 
  uint8_t eeprom_write_phone(uint8_t index, const char *phone)
{
    uint16_t addr;
    uint8_t i;

    if(index >= PHONE_COUNT) return 1; // ???

    addr = PHONE_BASE_ADDR + (index * PHONE_MAX_LEN);

    for(i = 0; i < PHONE_MAX_LEN - 1; i++)
    {
        if(phone[i] == '\0')
            break;

        EEPROM_WRIGHT(addr + i, (uint8_t)phone[i]);
    }

    // ????? ????
    EEPROM_WRIGHT(addr + i, '\0');

    return 0;
}


uint8_t eeprom_read_phone(uint8_t index, char *phone)
{
    uint16_t addr;
    uint8_t i;

    if(index >= PHONE_COUNT) return 1; // ???

    addr = PHONE_BASE_ADDR + (index * PHONE_MAX_LEN);

    for(i = 0; i < PHONE_MAX_LEN - 1; i++)
    {
        phone[i] = EEPROM_READ(addr + i);
        if(phone[i] == '\0')
            break;
    }

    phone[PHONE_MAX_LEN - 1] = '\0';
    return 0;
}

void eeprom_clear_all(void)
{
    uint16_t i;

    for(i = 0; i < EEPROM_SIZE; i++)
    {
        EEPROM_WRIGHT(i, 0xFF);
    }
}

void eeprom_write_string(uint16_t addr, const char *str, uint8_t max_len)
{
    uint8_t i;
    for(i = 0; i < max_len - 1; i++)
    {
        if(str[i] == '\0') break;
        EEPROM_WRIGHT(addr + i, str[i]);
    }
    EEPROM_WRIGHT(addr + i, '\0');
}

void eeprom_read_string(uint16_t addr, char *buf, uint8_t max_len)
{
    uint8_t i;
    for(i = 0; i < max_len - 1; i++)
    {
        buf[i] = EEPROM_READ(addr + i);
        if(buf[i] == '\0') break;
    }
    buf[max_len - 1] = '\0';
}


void SET_ID(char *id) {
    eeprom_write_string(EEPROM_ID_ADDR, id, 9);
}

void SET_Number(uint8_t index, char *num)
{
    uint16_t addr = EEPROM_NUM1_ADDR + (index * 0x10);
    eeprom_write_string(addr, num, 16);
}

void SET_LowCurrent(float val) {
    eeprom_write_float(val, EEPROM_LOW_CUR_ADDR);
}

void SET_HighCurrent(float val) {
    eeprom_write_float(val, EEPROM_HIGH_CUR_ADDR);
}

void SET_CurrentTime(uint16_t t) {
    eeprom_write_int16(t, EEPROM_CUR_TIME_ADDR);
}

void SET_ReleaseTime(uint16_t t) {
    eeprom_write_int16(t, EEPROM_REL_TIME_ADDR);
}

void SET_Relay(uint8_t r1, uint8_t r2) {
    EEPROM_WRIGHT(EEPROM_RELAY1_ADDR, r1);
    EEPROM_WRIGHT(EEPROM_RELAY2_ADDR, r2);
}

void SET_Security(uint8_t s) {
    EEPROM_WRIGHT(EEPROM_SECURITY_ADDR, s);
}


//*********************************Get**********************************
void GET_ID(char *buf)
{
    eeprom_read_string(EEPROM_ID_ADDR, buf, 9);
}

void GET_Number1(char *buf)
{
    eeprom_read_string(EEPROM_NUM1_ADDR, buf, 16);
}

void GET_Number2(char *buf)
{
    eeprom_read_string(EEPROM_NUM2_ADDR, buf, 16);
}

void GET_Number3(char *buf)
{
    eeprom_read_string(EEPROM_NUM3_ADDR, buf, 16);
}

void GET_Number4(char *buf)
{
    eeprom_read_string(EEPROM_NUM4_ADDR, buf, 16);
}

uint8_t GET_RelayState1(void)
{
    return EEPROM_READ(EEPROM_RELAY1_ADDR);
}

uint8_t GET_RelayState2(void)
{
    return EEPROM_READ(EEPROM_RELAY2_ADDR);
}

uint8_t GET_SecurityState(void)
{
    return EEPROM_READ(EEPROM_SECURITY_ADDR);
}

uint8_t GET_RemoteState(void)
{
    return EEPROM_READ(EEPROM_REMOTE_ADDR);
}

uint8_t GET_AlarmMode(void)
{
    return EEPROM_READ(EEPROM_ALARM_ADDR);
}

uint8_t GET_DeviceMode(void)
{
    return EEPROM_READ(EEPROM_MODE_ADDR);
}


float GET_LowCurrent(void)
{
    return eeprom_read_float(EEPROM_LOW_CUR_ADDR);
}

float GET_HighCurrent(void)
{
    return eeprom_read_float(EEPROM_HIGH_CUR_ADDR);
}


uint16_t GET_CurrentTime(void)
{
    return eeprom_read_int16(EEPROM_CUR_TIME_ADDR);
}

uint16_t GET_ReleaseTime(void)
{
    return eeprom_read_int16(EEPROM_REL_TIME_ADDR);
}

void GET_Number(uint8_t index, char *buf)
{
    switch(index)
    {
        case 0: GET_Number1(buf); break;
        case 1: GET_Number2(buf); break;
        case 2: GET_Number3(buf); break;
        case 3: GET_Number4(buf); break;
        default:
            buf[0] = '\0';
            break;
    }
}
//***********************************init******************************
void EEPROM_Init_Config(void)
{
    if(EEPROM_READ(EEPROM_MAGIC_ADDR) != EEPROM_MAGIC_VALUE)
    {
      eepromFualt = 1;
        eeprom_clear_all();   // ???? ????? ?? ????? ?????

        EEPROM_WRIGHT(EEPROM_MAGIC_ADDR, EEPROM_MAGIC_VALUE);

        SET_ID("12345678");

        SET_Number(0, "+989111111111");
        SET_Number(1, "+989111111111");
        SET_Number(2, "+989111111111");
        SET_Number(3, "+989111111111");

        SET_Relay(0, 0);
        SET_Security(0);

        SET_LowCurrent(1.5f);
        SET_HighCurrent(13.5f);

        SET_CurrentTime(10);
        SET_ReleaseTime(60);

        EEPROM_WRIGHT(EEPROM_REMOTE_ADDR, 0);
        EEPROM_WRIGHT(EEPROM_ALARM_ADDR, 0);
        EEPROM_WRIGHT(EEPROM_MODE_ADDR, 1);
    }
}


  

void EEPROM_Warning(char *msg)
{
    show_uart("? EEPROM WARNING:");
    show_uart(msg);
}

uint8_t is_valid_string(char *s)
{
    if(s[0] == 0xFF || s[0] == '\0')
        return 0;

    for(uint8_t i = 0; i < 20; i++)
    {
        if(s[i] == '\0') return 1;
        if(s[i] < 32 || s[i] > 126) return 0;
    }
    return 0;
}


void EEPROM_Load_Check_Print(void)
{
    char buf[20];
    char ss[100];

    float lowCur, highCur;
    uint16_t curTime, relTime;
    uint8_t val;

    show_uart("===== EEPROM CONFIG DUMP =====");

    /* -------- ID -------- */
    GET_ID(buf);
    if(!is_valid_string(buf))
        EEPROM_Warning("Invalid Device ID");
    sprintf(ss, "ID: %s", buf);
    show_uart(ss);

    /* -------- Numbers -------- */
    for(uint8_t i = 0; i < 4; i++)
    {
        GET_Number(i, buf);
        if(!is_valid_string(buf))
        {
            sprintf(ss, "Phone %d invalid", i+1);
            EEPROM_Warning(ss);
        }
        sprintf(ss, "Phone%d: %s", i+1, buf);
        show_uart(ss);
    }

    /* -------- Relay States -------- */
    val = GET_RelayState1();
    if(!VALID_0_1(val)) EEPROM_Warning("Relay1 state invalid");
    sprintf(ss, "Relay1: %d", val);
    show_uart(ss);

    val = GET_RelayState2();
    if(!VALID_0_1(val)) EEPROM_Warning("Relay2 state invalid");
    sprintf(ss, "Relay2: %d", val);
    show_uart(ss);

    /* -------- Security -------- */
    val = GET_SecurityState();
    if(!VALID_0_1(val)) EEPROM_Warning("Security state invalid");
    sprintf(ss, "Security: %d", val);
    show_uart(ss);

    /* -------- Currents -------- */
    lowCur = GET_LowCurrent();
    if(isnan(lowCur) || lowCur < MIN_CURRENT || lowCur > MAX_CURRENT)
        EEPROM_Warning("Low current invalid");
    sprintf(ss, "LowCurrent: %.2f A", lowCur);
    show_uart(ss);

    highCur = GET_HighCurrent();
    if(isnan(highCur) || highCur < MIN_CURRENT || highCur > MAX_CURRENT)
        EEPROM_Warning("High current invalid");
    sprintf(ss, "HighCurrent: %.2f A", highCur);
    show_uart(ss);

    /* -------- Times -------- */
    curTime = GET_CurrentTime();
    if(curTime == 0 || curTime > MAX_TIME_SEC)
        EEPROM_Warning("CurrentTime invalid");
    sprintf(ss, "CurrentTime: %d sec", curTime);
    show_uart(ss);

    relTime = GET_ReleaseTime();
    if(relTime == 0 || relTime > MAX_TIME_SEC)
        EEPROM_Warning("ReleaseTime invalid");
    sprintf(ss, "ReleaseTime: %d sec", relTime);
    show_uart(ss);

    /* -------- Modes -------- */
    val = GET_RemoteState();
    if(!VALID_0_1(val)) EEPROM_Warning("RemoteState invalid");
    sprintf(ss, "RemoteState: %d", val);
    show_uart(ss);

    val = GET_AlarmMode();
    if(!VALID_0_1(val)) EEPROM_Warning("AlarmMode invalid");
    sprintf(ss, "AlarmMode: %d", val);
    show_uart(ss);

    val = GET_DeviceMode();
    if(val > 3) EEPROM_Warning("DeviceMode invalid");
    sprintf(ss, "DeviceMode: %d", val);
    show_uart(ss);

    show_uart("===== EEPROM CHECK DONE =====");
}

