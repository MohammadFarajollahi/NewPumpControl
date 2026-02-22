


void ADC_DMA_Start(void)
{
  HAL_ADC_Start_DMA(&hadc1,
                    (uint32_t *)adc_dma_buffer,
                    ADC_CHANNEL_COUNT);
}

int AdcReadCount;

void CurrentRead(){
  Current = (int)adc[1]; 
  Current =((float)Current * 3.3f / 4095.0f) / 0.085f;
  Current *= 2.8;
}

void InputVoltageRead(){
  InputVoltage = (int)adc[0]; 
  InputVoltage =((float)InputVoltage * 3.3f / 4095.0f) / 0.0955f;
}

void ReadAdc(){
  if(DMA_Ready == 1){
    adc[0] = adc1[0] / 20000;
    adc1[0] = 0;
    adc[1] = adc1[1] / 20000;
    adc1[1] = 0;
    InputVoltageRead();
    CurrentRead();
    if(ShowCurrentCount>=5){
      ShowCurrentCount = 0;
      char ss3[50];
      sprintf(ss3 , "Voltage: %.2f | Current: %.2f" , InputVoltage , Current);
      show_uart(ss3);
    }
    DMA_Ready = 0;
  }
}

void AutoCurrent(){
  if(AutoCurrentTimer >= 20 && Current >= .3){
    lowCur = Current - 0.5;
    SET_LowCurrent(lowCur);
    highCur = Current + 2;
    SET_HighCurrent(highCur);
    number = 1;
    sprintf(sms_text, "062C063106CC062706460020064706480627002006A9063406CC002006480020062C063106CC0627064600200627063606270641064700200628062706310020067E0645067E00200630062E06CC0631064700200634062F");
    send_sms_fars();
    number = 1;
    HAL_Delay(500);
    sprintf(sms_text , "Current: %.2f A" , lowCur);
    send_sms();
    number = 1;
    HAL_Delay(500);
    sprintf(sms_text , "Over Current: %.2f A" , highCur);
    send_sms();
    AutoCurrentTimer = 0;
    AutoCurrentSet = 0;
    HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
  }
  if(AutoCurrentTimer >= 20 && Current < .3){
    number = 1;
    sprintf(sms_text, "0645063406A906440020062F0631002006270646062F062706320647002006AF06CC063106CC000D000A067E0645067E002006480635064400200646064506CC0020062806270634062F");
    send_sms_fars();
    HAL_Delay(500);
    HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
  }
}

void ControlCurrent(){
  
  if(Current > 0.3){
    //LOW CURRENT
    if(Current <= lowCur && LowCurrentArlarmCount == 0 && ReleazeCount == 0){
      LowCurrentArlarmCount = 1;
      show_uart("Hava Keshi");
    }
    
    if(Current >  lowCur && Current < highCur && LowCurrentArlarmCount == 1){
      LowCurrentArlarmCount = 0;
      LowCurrentArlarmTimer = 0;
      ReleazeCount = 0;
      RealizeTimr = 0;
      show_uart("Current ok and Realize");
    }
    
    if(LowCurrentArlarmTimer >= curTime && ReleazeCount == 0){
      LowCurrentArlarmTimer = 0;
      LowCurrentArlarmCount = 0;
      ReleazeCount = 1;
      HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Rele2_GPIO_Port, Rele2_Pin, GPIO_PIN_RESET);
      HAL_Delay(250);
      ReleState1 = 0;
      SET_Relay(ReleState1, ReleState2);
      ReleState2 = 0;
      SET_Relay(ReleState1, ReleState2);
      sprintf(sms_text, "0645063406A90644002006470648062706A9063406CC0020067E0645067E000D000A067E0645067E0020062E062706450648063400200634062F");
      if(strstr((char*)number1, "+98111111111") == NULL)
      {
        number = 1;
        send_sms_fars();
      }
      if(strstr((char*)number2, "+98111111111") == NULL)
      {
        number = 2;
        send_sms_fars();
      }
      if(strstr((char*)number3, "+98111111111") == NULL)
      {
        number = 3;
        send_sms_fars();
      }
      if(strstr((char*)number4, "+98111111111") == NULL)
      {
        number = 4;
        send_sms_fars();
      }
      
      HAL_Delay(2000);
      call();
      RealizeTimr = 0;
    }
    
    
    //HIGH CURRENT
    if(Current >=  highCur && HighCurrentAlarmCount == 0 && ReleazeCount == 0)HighCurrentAlarmCount = 1; 
    if(HighCurrentAlarmTimer >= 5 && ReleazeCount == 0){
      HighCurrentAlarmCount = 0;
      HighCurrentAlarmTimer = 0;
      ReleazeCount = 1;
      HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(Rele2_GPIO_Port, Rele2_Pin, GPIO_PIN_RESET);
      HAL_Delay(250);
      ReleState1 = 0;
      SET_Relay(ReleState1, ReleState2);
      ReleState2 = 0;
      SET_Relay(ReleState1, ReleState2);
      sprintf(sms_text, "067E0645067E0020062A062D062A002006410634062706310020064506CC0020062806270634062F000D000A067E0645067E0020062E062706450648063400200634062F");
      if(strstr((char*)number1, "+98111111111") == NULL)
      {
        number = 1;
        send_sms_fars();
      }
      if(strstr((char*)number2, "+98111111111") == NULL)
      {
        number = 2;
        send_sms_fars();
      }
      if(strstr((char*)number3, "+98111111111") == NULL)
      {
        number = 3;
        send_sms_fars();
      }
      if(strstr((char*)number4, "+98111111111") == NULL)
      {
        number = 4;
        send_sms_fars();
      }
      
      HAL_Delay(2000);
      call();
      RealizeTimr = 0;
    }
    
    if(Current >  lowCur && Current < highCur && HighCurrentAlarmCount == 1){
      HighCurrentAlarmCount = 0;
      HighCurrentAlarmTimer = 0;
      ReleazeCount = 0;
      RealizeTimr = 0;
      show_uart("Current ok and Realize");
    }
  }
  
  if(ReleazeCount == 1 && RealizeTimr >= relTime){
    ReleazeCount = 0;
    RealizeTimr = 0;
    show_uart("Time Realize");
  }
  
}




void CurrentControl()
{
  ReadAdc();
  if(AutoCurrentSet == 1)AutoCurrent();
  if(AutoCurrentSet == 0){
    if(ReleState1 == 1  || ReleState2 == 1)ControlCurrent();
  }
}
