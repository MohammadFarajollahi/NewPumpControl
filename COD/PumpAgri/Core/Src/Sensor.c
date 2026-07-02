





void Sensor(){
  
  
  //************  PIR ************
  if (HAL_GPIO_ReadPin(Sensor1_GPIO_Port, Sensor1_Pin) == 0 && Pulse1State == 0 ){
    DetectPulse1 = 1;
    if(DetectTimerPulse1 >= 2){
      DetectTimerPulse1 = 0;
      DetectPulse1 = 0;
      Pulse1State = 1;
      Pulse1Timer = 0;
      
      if(AlarmMode == 1){
        HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
      }
      
      show_uart("Sensor PIR Warning");
      sprintf(sms_text, "06470634062F062706310020063306310642062A");
      
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
      HAL_IWDG_Refresh(&hiwdg);
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
      HAL_IWDG_Refresh(&hiwdg);
      HAL_Delay(500);
      call();
      
    }
  }
  
  
  if (HAL_GPIO_ReadPin(Sensor1_GPIO_Port, Sensor1_Pin) == 1 ){
    ++RelizeCount;
    if(RelizeCount >= 500){
      DetectPulse1 = 0;
      DetectTimerPulse1 = 0;
      RelizeCount = 0;
    }
  }
  
  if(Pulse1Timer >= 60){
    Pulse1Timer = 0;
    Pulse1State = 0;
    show_uart("Sensor1 Realized...");
  }
  
  
  
  //************  Larzesh ************
  if (HAL_GPIO_ReadPin(Sensor2_GPIO_Port, Sensor2_Pin) == 0 && Pulse2State == 0 ){
    //DetectPulse2 = 1;
    ++DetectTimerPulse2;
    if(DetectTimerPulse2 >= 50000){
      DetectTimerPulse2 = 0;
      DetectPulse2 = 0;
      Pulse2State = 1;
      Pulse2Timer = 0;
      
      if(AlarmMode == 1){
        HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
      }
      
     show_uart("Sensor Larzesh Warning");
      sprintf(sms_text, "06470634062F062706310020063306310642062A");
      
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
      HAL_IWDG_Refresh(&hiwdg);
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
      HAL_IWDG_Refresh(&hiwdg);
      HAL_Delay(500);
      call();
      
    }
  }
  
  
  if (HAL_GPIO_ReadPin(Sensor2_GPIO_Port, Sensor2_Pin) == 1 ){
    ++RelizeCount2;
    if(RelizeCount2 >= 500){
      DetectPulse2 = 0;
      DetectTimerPulse2 = 0;
      RelizeCount2 = 0;
    }
  }
  
  if(Pulse2Timer >= 60){
    Pulse2Timer = 0;
    Pulse2State = 0;
    show_uart("Sensor2 Realized...");
  }
  
}