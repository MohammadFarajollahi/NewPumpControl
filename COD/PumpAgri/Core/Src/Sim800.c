
//**************************************
//    Send SMS
//**************************************

void ucs2_convert() {
  memcpy(send_number_ucs2, "", sizeof(1));
  strcat(send_number_ucs2, "0030");
  for(int i = 3 ; i <13 ; i++) {
    substring(send_number, i, i+1);
    strcpy(CharMain, str_cut);
    int number_send=atoi(CharMain);
    switch(number_send) {
    case 1:
      strcat(send_number_ucs2, "0031");
      break;
    case 2:
      strcat(send_number_ucs2, "0032");
      break;
    case 3:
      strcat(send_number_ucs2, "0033");
      break;
    case 4:
      strcat(send_number_ucs2, "0034");
      break;
    case 5:
      strcat(send_number_ucs2, "0035");
      break;
    case 6:
      strcat(send_number_ucs2, "0036");
      break;
    case 7:
      strcat(send_number_ucs2, "0037");
      break;
    case 8:
      strcat(send_number_ucs2, "0038");
      break;
    case 9:
      strcat(send_number_ucs2, "0039");
      break;
    case 0:
      strcat(send_number_ucs2, "0030");
      break;
      
    }
  }
  
}

void sms_done() {
  number = 5;      
  SMS_Check_point = 0;
  SMS_CHECK_Timer = 0;
  SMS_Check_Count = 0;
  send_atcammand("AT+CMGD=1,4");
  HAL_Delay(500);
  send_atcammand("AT+CMGD=1,4");
  HAL_Delay(500);
  SMSDone = 1;
  exti_sms = 0;
}

void send_sms()
{
  char ch[5];
  sprintf(ch, "%c", 34); //sakht char "
  
  if (number == 0)
    strcpy(send_number, server_number);
  if (number == 6)
    strcpy(send_number, server_number2);
  if (number == 1)
    strcpy(send_number, (char *)number1);
  if (number == 2)
    strcpy(send_number, (char *)number2);
  
  if (number != 0 && number != 1 && number != 2 && number != 6 ) {
    strcpy(send_number, input_number);
  }
  
  substring(send_number, 0, 13);
  strcpy(send_number, str_cut);
  
  sprintf(CharMain, "AT+CMGS=");
  strcat(CharMain, ch);
  strcat(CharMain, send_number);
  strcat(CharMain, ch);
  strcat(CharMain, "\r\n");
  
  show_uart(CharMain);
  HAL_IWDG_Refresh(&hiwdg);
  HAL_UART_Transmit(&huart1, (uint8_t *)CharMain, strlen(CharMain), HAL_MAX_DELAY);
  HAL_Delay(1000);
  HAL_UART_Transmit(&huart1, (uint8_t *)sms_text, strlen(sms_text), HAL_MAX_DELAY);
  uint8_t sms_send = 0x1A;
  HAL_Delay(500);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(4000);
  sms_done();
}

void send_sms_fars() {

  //		send_atcammand("ATH");
  //		HAL_Delay(500);
  send_atcammand("AT+CSCS=\"UCS2\"");
  HAL_Delay(300);
  send_atcammand("AT+CSMP=49,167,0,8"); // 17,167,0,8
  HAL_Delay(500);
  
  HAL_IWDG_Refresh(&hiwdg);
  char ch[5];
  sprintf(ch, "%c", 34); //sakht char "
  
  if (number == 0)
    strcpy(send_number, server_number);
  if (number == 6)
    strcpy(send_number, server_number2);
  if (number == 1)
    strcpy(send_number, (char *)number1);
  if (number == 2)
    strcpy(send_number, (char *)number2);
  if (number == 3)
    strcpy(send_number, (char *)number3);
  if (number == 4)
    strcpy(send_number, (char *)number4);
  
  ucs2_convert();
  
  
  sprintf(CharMain, "AT+CMGS=");
  strcat(CharMain, ch);
  strcat(CharMain, send_number_ucs2);
  strcat(CharMain, ch);
  strcat(CharMain, "\r\n");
  
  show_uart(CharMain);
  
  HAL_UART_Transmit(&huart1, (uint8_t *)CharMain, strlen(CharMain), HAL_MAX_DELAY);
  HAL_Delay(1000);
  HAL_UART_Transmit(&huart1, (uint8_t *)sms_text, strlen(sms_text), HAL_MAX_DELAY);
  HAL_Delay(500);
  uint8_t sms_send = 0x1A;
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
  HAL_Delay(100);
  HAL_Delay(6000);
  HAL_IWDG_Refresh(&hiwdg);
  //send_atcammand("AT+CMGD=1,4");
  HAL_Delay(500);
  send_atcammand("AT+CSMP=17,167,0,0");
  HAL_Delay(500);
  send_atcammand("AT+CSCS=\"GSM\"");
  HAL_Delay(500);
  sms_done();
}



//**************************************
//    INPUT SMS
//**************************************
void change_pass()
{
  substring(char_test3, 2, 6);
  strcpy(CharMain, str_cut);
  substring(char_test3, 21, 22);//R 1111 1111 12345678 +989025088863
  strcpy(str, str_cut);
  show_uart(str);
  if (strstr(CharMain,(char *) pass) != NULL && strstr(str, "+") != NULL)
  {
    substring(char_test3, 12, 20);
    strcpy(CharMain, str_cut);
    if (strstr(CharMain,(char *) id) != NULL)
    {
      char NumberDelet[25];
      strcpy(NumberDelet,(char *)number1);
      substring(char_test3, 21, 34);
      strcpy((char *)car_number, str_cut);
      show_uart((char *)car_number);
      substring(char_test3, 7, 11);
      strcpy(CharMain, str_cut);
      strcpy((char *)pass, CharMain);  ///***save new pass***///
      strcpy((char *)number1, input_number);  ///***save new number***///
      sprintf((char *)number2, "+981111111111");
      sprintf((char *)number3, "+981111111111");
      sprintf((char *)number4, "+981111111111");
      number = 1;
      sprintf(sms_text, "002A002A002A062E06480634002006220645062F06CC062F002A002A002A");
      send_sms_fars();
      HAL_IWDG_Refresh(&hiwdg);
      sprintf(sms_text, "062D063306270628002006A9062706310628063106CC0020062C062F06CC062F0020062706CC062C0627062F00200634062F");
      send_sms_fars();
      SET_Number(0, (char *)number1);
      HAL_Delay(10);
      SET_Number(1, (char *)number2);
      HAL_Delay(10);
      SET_Number(2, (char *)number3);
      HAL_Delay(10);
      SET_Number(3, (char *)number4);
      HAL_Delay(10);
      HAL_IWDG_Refresh(&hiwdg);
      PackData(str);
      show_uart("Sending config:");
      show_uart(str);
      strcpy(sms_text, str);
      number = 0;
      send_sms();
      send_atcammand("AT+CMGD=1,4");
      HAL_Delay(500);
      main_chek_count = 0;
      if(model_simcard == 1) {
        send_atcammand("AT+CUSD=1,\"*555*4*3*2*2#\"");               
        HAL_Delay(2000);
        HAL_IWDG_Refresh(&hiwdg);
        send_atcammand("AT+CUSD=1,\"*555*3*4*1#\"");
        HAL_Delay(2000);
      }              
      if(model_simcard == 2) {
        send_atcammand("AT+CUSD=1,\"*100*114#\"");
        HAL_Delay(3000);
        HAL_IWDG_Refresh(&hiwdg);  
        send_atcammand("AT+CUSD=1,\"1\"");
        HAL_Delay(2000);
      }
      HAL_IWDG_Refresh(&hiwdg);  
      show_uart("register done");
    }
    
  }
}

void Config(){
  number = 0;
  sprintf(sms_text, "PUMP CONFIG OK");
  send_sms();
  FirstConfig();
  HAL_IWDG_Refresh(&hiwdg);
}

void battry() 
{
  sprintf(str, "GSM BATTERY:%d%c\r\nGSM ANTEN:%d%c", batt_sms,37, anten_send,37);
  show_uart(str);
  strcpy(sms_text, str);
  send_sms();
}

void Rele1_on() 
{
  ReleState1 = 1;
  SET_Relay(ReleState1, ReleState2);
  HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_SET);
  sprintf(sms_text, "067E0645067E00310020063106480634064600200634062F");
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
    HAL_Delay(500);
  
}

void Rele1_off() 
{
  ReleState1 = 0;
  SET_Relay(ReleState1, ReleState2);
  HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
  sprintf(sms_text, "067E0645067E00310020062E062706450648063400200634062F");
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
    HAL_Delay(500);
}

void Rele2_on() 
{
  ReleState2 = 1;
  SET_Relay(ReleState1, ReleState2);
  HAL_GPIO_WritePin(Rele2_GPIO_Port, Rele2_Pin, GPIO_PIN_SET);
  sprintf(sms_text, "067E0645067E00320020063106480634064600200634062F");
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
  HAL_Delay(500);
}

void Rele2_off() 
{
  ReleState2 = 0;
  SET_Relay(ReleState1, ReleState2);
  HAL_GPIO_WritePin(Rele2_GPIO_Port, Rele2_Pin, GPIO_PIN_RESET);
  sprintf(sms_text, "067E0645067E00320020062E062706450648063400200634062F");
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
    HAL_Delay(500);
}

void info(){
  PackData(str);
  show_uart("Sending config:");
  show_uart(str);
  strcpy(sms_text, str);
  send_sms();
}

void add_member()
{
   substring(char_test3, 2, 6); // A 1111 2 +989372425086
    strcpy(CharMain, str_cut);
    substring(char_test3, 9, 10); // A 1111 2 +989372425086
    strcpy(str, str_cut);
    if (strstr(CharMain,(char *) pass) != NULL && strstr(str,"+") != NULL)
    {
      substring(char_test3, 9, 22);
      strcpy(CharMain, str_cut);
      strcpy(send_number, CharMain); //shomare telephon user
      char NumberCh[10];
      substring(char_test3, 7, 8); // A 1111 2 +989372425086
      strcpy(NumberCh, str_cut);
      if(strstr(NumberCh,"2") != NULL){
        strcpy((char *)number2, send_number);
        SET_Number(1, (char *)number2);
      }
      if(strstr(NumberCh,"3") != NULL){
        strcpy((char *)number3, send_number);
        SET_Number(2, (char *)number3);
      }
      if(strstr(NumberCh,"4") != NULL){
        strcpy((char *)number4, send_number);
        SET_Number(3, (char *)number4);
      }
      sprintf(sms_text, "06A906270631062806310020062C062F06CC062F00200627063606270641064700200634062F");
      send_sms_fars();
      HAL_Delay(500);
      PackData(str);
      show_uart("Sending config:");
      show_uart(str);
       number = 1;
      strcpy(sms_text, str);
      send_sms();
      send_atcammand("AT+CMGD=1,4");
      HAL_Delay(500);
    }
}

void ServerEEPROM()
{
  UnpackData(char_test3);
  strcpy(sms_text, "EEPROM CONFIG OK");
  send_sms();
  HAL_Delay(4000);
  hang = 1;
}

void CurrentSetting()
{
  substring(char_test3, 8, 15); // Current 2.36
  strcpy(CharMain, str_cut);
  lowCur = atof(CharMain);
  SET_LowCurrent(lowCur);
  sprintf(sms_text, "062C063106CC06270646002006470648062706A9063406CC0020067E0645067E00200630062E06CC0631064700200634062F");
  send_sms_fars();
  HAL_Delay(500);
  sprintf(sms_text , "Current: %.2f A" , lowCur);
  send_sms();
  
}

void OverCurrent()
{
  substring(char_test3, 13, 20); // Over current 2.36
  strcpy(CharMain, str_cut);
  highCur = atof(CharMain);
  SET_HighCurrent(highCur);
  sprintf(sms_text, "062A0646063806CC06450627062A0020062706360627064106470020062C063106CC0627064600200630062E06CC0631064700200634062F");
  send_sms_fars();
  HAL_Delay(500);
  sprintf(sms_text , "Over Current: %.2f A" , highCur);
  send_sms();
  
}

void TimeSetting()
{
  substring(char_test3, 5, 10); // time 10
  strcpy(CharMain, str_cut);
  curTime = atoi(CharMain);
  SET_CurrentTime(curTime);
  sprintf(sms_text, "0632064506270646002006470648062706A9063406CC0020062A0646063806CC064500200634062F");
  send_sms_fars();
  HAL_Delay(500);
  sprintf(sms_text , "Time: %d S" , curTime);
  send_sms();
}

void Reset(){
  sprintf(sms_text , "Reset Pump");
  send_sms();
  HAL_Delay(2000);
  HAL_GPIO_WritePin(MC60_Start_GPIO_Port, MC60_Start_Pin, GPIO_PIN_SET);
  HAL_Delay(2000);
  HAL_GPIO_WritePin(MC60_Start_GPIO_Port, MC60_Start_Pin, GPIO_PIN_RESET);
  HAL_Delay(2000);
  hang = 1;
}


void AutoCurrentSetting(){
  sprintf(sms_text, "062A0646063806CC064500200627062A064806450627062A06CC06A90020067E0645067E000D000A06440637064106270020064806310648062F06CC0020062206280020063106270020064806350644002006A9064606CC062F00200648002006450646062A063806310020062806450627064606CC062F");
  send_sms_fars();
  HAL_Delay(500);
  AutoCurrentSet = 1;
  AutoCurrentTimer = 0;
  HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_SET);
  
}


void SendPumpCurrent(){
  sprintf(sms_text , "Current: %.2f A" , Current);
  send_sms();
}

void  RealizeSetting(){
  substring(char_test3, 8, 20); //Realize 10
  strcpy(CharMain, str_cut);
  relTime = atoi(CharMain);
  SET_ReleaseTime(relTime);
  sprintf(sms_text, "06320645062706460020068606A9002006A90631062F064600200645062C062F062F00200630062E06CC0631064700200634062F");
  send_sms_fars();
  HAL_Delay(500);
  sprintf(sms_text , "Time: %d S" , relTime);
  send_sms();
  
}

void Security_on(){
  Security = 1;
  show_uart("Security On");
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  SET_Security(1);
  sprintf(sms_text, "062D06270644062A002006270645064606CC062A06CC0020064106390627064400200634062F");
  send_sms_fars();
  
  
}

void Security_off(){
  Security = 0;
  show_uart("Security Off");
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  SET_Security(0);
  sprintf(sms_text, "062D06270644062A002006270645064606CC062A06CC0020063A06CC06310020064106390627064400200634062F");
  send_sms_fars();
  
  
}


void  DeviceMode1(){
  DeviceMode = 1;
  sprintf((char *)Mode, "1");
  EEPROM_WRIGHT(EEPROM_MODE_ADDR, 0);
  sprintf(sms_text, "062D06270644062A002000310020062A0646063806CC064500200634062F000D000A06320645062706460020003100350020062B0627064606CC0647");
  send_sms_fars();
}

void  DeviceMode2(){
  DeviceMode = 2;
  sprintf((char *)Mode, "2");
  EEPROM_WRIGHT(EEPROM_MODE_ADDR, 1);
  sprintf(sms_text, "062D06270644062A002000320020062A0646063806CC064500200634062F000D000A06320645062706460020003300300020062B0627064606CC0647");
  send_sms_fars();
}

void  DeviceMode3(){
  DeviceMode = 3;
  sprintf((char *)Mode, "3");
  EEPROM_WRIGHT(EEPROM_MODE_ADDR, 2);
  sprintf(sms_text, "062D06270644062A002000330020062A0646063806CC064500200634062F000D000A06320645062706460020003600300020062B0627064606CC0647");
  send_sms_fars();
}

void  DeviceMode4(){
  DeviceMode = 4;
  sprintf((char *)Mode, "4");
  EEPROM_WRIGHT(EEPROM_MODE_ADDR, 3);
  sprintf(sms_text, "062D06270644062A002000340020062A0646063806CC064500200634062F000D000A063206450627064600200031003200300020062B0627064606CC0647");
  send_sms_fars();
}


void  AlarmOn(){
  AlarmMode = 1;
  EEPROM_WRIGHT(EEPROM_ALARM_ADDR, 1);
  sprintf(sms_text, "0622069806CC06310020064106390627064400200634062F");
  send_sms_fars();
}

void  AlarmOff(){
  AlarmMode = 0;
  EEPROM_WRIGHT(EEPROM_ALARM_ADDR, 0);
  sprintf(sms_text, "0622069806CC063100200020063A06CC06310020064106390627064400200634062F");
  send_sms_fars();
}

//=================================================
//                 Read SMS Data
//=================================================
void InputSMS()
{
  
  if (strstr(char_test3, "CONFIG") != NULL)
  {
    Config();
  }
  
   if (strstr(char_test3, "ID=") != NULL)
  {
    ServerEEPROM();
  }
  
  if (strstr(char_test3, "info") != NULL)
  {
    info();
  }
  
  substring(char_test3, 0, 1);
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "R") != NULL)
  {
    change_pass();
  }
  
  //**add member***//
  substring(char_test3, 0, 1);
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "A") != NULL)
  {
    add_member();
  }
  
  if (strstr(char_test3, "BT") != NULL || strstr(char_test3, "Bt") != NULL)
  {
    battry();
  }
  
  substring(char_test3, 0, 3);
  strcpy(CharMain, str_cut);
 if (strstr(CharMain, "ON1") != NULL || strstr(CharMain, "On1") != NULL || strstr(char_test3, "0631064806340646") != NULL || strstr(char_test3, "067E0645067E003100200631064806340646") != NULL || strstr(char_test3, "on1") != NULL)
  // if (strstr(CharMain, "ON1") != NULL || strstr(CharMain, "On1") != NULL || strstr(char_test3, "062E06270646064700200631064806340646") != NULL || strstr(char_test3, "on1") != NULL)
  {
    Rele1_on();
    
  }
  
  substring(char_test3, 0, 3);
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "OF1") != NULL || strstr(CharMain, "Of1") != NULL || strstr(char_test3, "062E0627064506480634") != NULL || strstr(char_test3, "067E0645067E00310020062E0627064506480634") != NULL || strstr(char_test3, "of1") != NULL)
  //if (strstr(CharMain, "OF1") != NULL || strstr(CharMain, "Of1") != NULL || strstr(char_test3, "062E0627064606470020062E0627064506480634") != NULL || strstr(char_test3, "of1") != NULL)
  {
    Rele1_off();
    
  }
  
  substring(char_test3, 0, 2);
  strcpy(CharMain, str_cut);
  if (strstr(char_test3, "OF2") == NULL && strstr(char_test3, "Of2") == NULL && strstr(char_test3, "of2") == NULL){
    if (strstr(CharMain, "OF") != NULL || strstr(CharMain, "Of") != NULL )
    {
      Rele1_off();
      
    }
  }
  
    substring(char_test3, 0, 3);
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "ON2") != NULL || strstr(CharMain, "On2") != NULL || strstr(char_test3, "06280627063A00200631064806340646") != NULL || strstr(char_test3, "on2") != NULL)
  {
    Rele2_on();
    
  }
  
  substring(char_test3, 0, 3);
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "OF2") != NULL || strstr(CharMain, "Of2") != NULL || strstr(char_test3, "06280627063A0020062E0627064506480634") != NULL || strstr(char_test3, "of2") != NULL)
  {
    Rele2_off();
    
  }
  
  substring(char_test3, 0, 7);
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "Current") != NULL || strstr(CharMain, "current") != NULL)
  {
    CurrentSetting();
  }
  
    substring(char_test3, 0, 7);
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "Uc") != NULL || strstr(CharMain, "UC") != NULL ||  strstr(CharMain, "uc") != NULL)
  {
    SendPumpCurrent();
  }
  
   if (strstr(char_test3, "over current") != NULL || strstr(char_test3, "Over current") != NULL)
  {
    OverCurrent();
  }
  
   if (strstr(char_test3, "Time") != NULL || strstr(char_test3, "TIME") != NULL || strstr(char_test3, "time") != NULL)
  {
    TimeSetting();
  }
  
     if (strstr(char_test3, "Realize") != NULL )
  {
    RealizeSetting();
  }
  
   if (strstr(char_test3, "Auto current") != NULL || strstr(char_test3, "062A0646063806CC064500200627062A064806450627062A06CC06A9") != NULL)
  {
    AutoCurrentSetting();
  }
  
   if (strstr(char_test3, "reset") != NULL || strstr(char_test3, "Reset") != NULL ||  strstr(char_test3, "063106CC0633062A") != NULL)
  {
    Reset();
  }
  
  
    if (strstr(char_test3, "S1") != NULL || strstr(char_test3, "s1") != NULL ||  strstr(char_test3, "062F0632062F06AF06CC063100200641063906270644") != NULL)
  {
    Security_on();
  }
  
      if (strstr(char_test3, "S2") != NULL || strstr(char_test3, "s2") != NULL ||  strstr(char_test3, "062F0632062F06AF06CC06310020063A06CC06310641063906270644") != NULL)
  {
    Security_off();
  }
  
   if (strstr(char_test3, "D1") != NULL || strstr(char_test3, "d1") != NULL)
  {
    DeviceMode1();
  }
  
   if (strstr(char_test3, "D2") != NULL || strstr(char_test3, "d2") != NULL)
  {
    DeviceMode2();
  }
  
   if (strstr(char_test3, "D3") != NULL || strstr(char_test3, "d3") != NULL)
  {
    DeviceMode3();
  }
  
   if (strstr(char_test3, "D4") != NULL || strstr(char_test3, "d4") != NULL)
  {
    DeviceMode4();
  }
  
    if (strstr(char_test3, "Alarm on") != NULL || strstr(char_test3, "0622069806CC063100200641063906270644") != NULL)
  {
    AlarmOn();
  }
  
    if (strstr(char_test3, "Alarm off") != NULL || strstr(char_test3, "0622069806CC06310020063A06CC063100200641063906270644") != NULL || strstr(char_test3, "0622069806CC06310020063A06CC06310641063906270644") != NULL)
  {
    AlarmOff();
  }
  
}








void SMS_Check(){
  
  if(SMS_CHECK_Timer >= 2){
    show_uart("**Check SMS**");
    SMS_CHECK_Timer = 0;
    ++SMS_Check_Count;   
    send_atcammand("AT+CMGL=\"ALL\"");
  }
  
  if(SMS_Check_Count >= 2){
    
    HAL_Delay(500);
    send_atcammand("AT+CSMP=17,167,0,0");
    HAL_Delay(200);
    send_atcammand("AT+CSCS=\"GSM\"");
    HAL_Delay(1500);
    send_atcammand("AT+CPMS=\"ME\",\"ME\",\"ME\"");
    HAL_Delay(200);
    send_atcammand("AT+CMGD=1,4");
    HAL_Delay(200);
    send_atcammand("AT+CPMS=\"SM\",\"SM\",\"SM\"");
    HAL_Delay(200);
    send_atcammand("AT+CMGD=1,4");
    SMS_CHECK_Timer = 0;
    SMS_Check_Count = 0;
    SMS_Check_point = 0;
    show_uart("**DELLETE All SMS**");
  }
  
  if(SMS_Check_point == 0 && exti_sms == 1){    
    show_uart("**SMS FROM EXTI**");
    SMS_CHECK_Timer = 0;
    exti_sms = 0;
    SMS_Check_point = 1;
    send_atcammand("AT+CMGL=\"ALL\"");
  }
  
  if(SMSDone == 1 && TimeSMSDone >= 4){
    show_uart("SMS Done");
    send_atcammand("AT+CMGD=1,4");
    SMSDone = 0;
    TimeSMSDone = 0;
    SMS_Check_point = 0;
    HAL_Delay(500);    
  } 
}

void Read_Input_SMS(){
  substring(char_test3, 10, 18);//+CMGL: 1,"REC READ","+989372425086","","26/01/28,00:32:02+14"
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "REC READ") != NULL) {
    show_uart("read SMS");
    substring(char_test3, 21, 34);
    strcpy(CharMain, str_cut);
    show_uart(CharMain);
    
    
    if (strstr(CharMain, server_number) != NULL)   //server send sms
    {
      number = 0;
      show_uart("SERVER NUMBER1");
    }
     if (strstr(CharMain, server_number2) != NULL)     /////////////////number1 send sms
    {
      number = 6;
      show_uart("SERVER NUMBER2");
    }
    if (strstr(CharMain,(char *)  number1) != NULL)     /////////////////number1 send sms
    {
      number = 1;
      show_uart("NUMBER1");
    }
    
    if (strstr(CharMain,(char *) number2) != NULL)   /////////////////number2 send sms
    {
      number = 2;
      show_uart("NUMBER2");
    }
    
    if (strstr(CharMain,(char *) number3) != NULL)   /////////////////number2 send sms
    {
      number = 3;
      show_uart("NUMBER3");
    }
    
    if (strstr(CharMain,(char *) number4) != NULL)   /////////////////number2 send sms
    {
      number = 4;
      show_uart("NUMBER4");
    }
    
    strcpy(input_number, CharMain);
    show_uart(input_number);
  }
  
  substring(char_test3, 10, 20); ////+CMGL: 1,"REC UNREAD","+989372425086","","26/01/28,00:32:02+14"
  strcpy(CharMain, str_cut);
  if (strstr(CharMain, "REC UNREAD") != NULL) {
    show_uart("SMS unread");
    substring(char_test3, 23, 36);
    strcpy(CharMain, str_cut);
    show_uart(CharMain);
    
    if (strstr(CharMain, server_number) != NULL)   /////////////////server send sms
    {
      number = 0;
      show_uart("SERVER NUMBER1");
    }
    if (strstr(CharMain, server_number2) != NULL)     /////////////////number1 send sms
    {
      number = 6;
      show_uart("SERVER NUMBER2");
    }
    if (strstr(CharMain,(char *)  number1) != NULL)     /////////////////number1 send sms
    {
      number = 1;
      show_uart("NUMBER1");
    }
    
    if (strstr(CharMain,(char *)  number2) != NULL)   /////////////////number2 send sms
    {
      number = 2;
      show_uart("NUMBER2");
    }
    
    if (strstr(CharMain,(char *)  number3) != NULL)   /////////////////number2 send sms
    {
      number = 3;
      show_uart("NUMBER3");
    }
    
    if (strstr(CharMain,(char *)  number4) != NULL)   /////////////////number2 send sms
    {
      number = 4;
      show_uart("NUMBER4");
    }
    
    strcpy(input_number, CharMain);
    show_uart(input_number);
    
  }
  
}

void ResetMicro(){
  show_uart("RESET MICRO");
  hang = 1;
  HAL_Delay(5000);
}

void ResetMC60(){
  show_uart("##RESET MC60##");
  MC60_Ready = 0;
  HAL_Delay(2000);
  HAL_GPIO_WritePin(MC60_Start_GPIO_Port, MC60_Start_Pin, GPIO_PIN_SET);
  HAL_Delay(2000);
  HAL_GPIO_WritePin(MC60_Start_GPIO_Port, MC60_Start_Pin, GPIO_PIN_RESET);
  HAL_Delay(2000);
  send_atcammand("AT");
  HAL_Delay(250);
  send_atcammand("AT");
  HAL_Delay(100);
  MC60_FirstStart_Count = 0;
  MC60_FirstStart_Timer = 0;
  ++FirstStartError;
  if(FirstStartError>=6)ResetMicro();
}

void Sim800_Check(){
  if(MC60_Ready == 0){
    if (strstr(char_test3, "OK") != NULL && MC60_FirstStart_Count == 1)
    {    
      MC60_FirstStart_Count = 2;   
    }
    
    if(MC60_FirstStart_Count == 3){
      //****network check****
      if (strstr(char_test3, "+CGREG: 0,1") != NULL || strstr(char_test3, "+CREG: 0,1") != NULL || strstr(char_test3, "+CREG: 2,1") != NULL || strstr(char_test3, "+CREG: 0,5") != NULL)
      {
        show_uart("Network ready");
        MC60_FirstStart_Count = 4;
      }
      
      if (strstr(char_test3, "+CGREG: 0,2") != NULL || strstr(char_test3, "+CREG: 0,2") != NULL || strstr(char_test3, "+CREG: 2,2") != NULL)
      {
        show_uart("Network not ready");
      }
      
    }
    
    if (MC60_FirstStart_Count == 5)
    {
      if (strstr(char_test3, "+COPS: 0,0,\"MTN Irancell\"") != NULL  ) { // 
        show_uart("SIM: IranCell");
        MC60_FirstStart_Count = 6;
        model_simcard = 1;
      }
      
      if (strstr(char_test3, "+COPS: 0,0,\"TCI\"") != NULL ||strstr(char_test3, "+COPS: 0,0,\"43235\"") != NULL) { // +COPS: 0,0,"TCI"
        show_uart("SIM: MCI");
        MC60_FirstStart_Count = 6;
        model_simcard = 2;
      }
    }
  }
  
  if(MC60_Ready == 1){
    
    //MAIN CHECK Count
    {
      //**********************chek_MC60*****************////
      if (strstr(char_test3, "OK") != NULL && chek == 1)
      {
        chek = 2;
      }
      
      //*********************ANTEN CHEK********************
      if (strstr(char_test3, "+CSQ") != NULL)
      {
        substring(char_test3, 6, 8);
        strcpy(CharMain, str_cut);
        anten = atoi(CharMain);
        if(chek==3)chek = 4;
      }
      
      //*****BATTERY CHECK*********
      if (strstr(char_test3, "+CBC") != NULL )
      {
        substring(char_test3, 8, 10);
        strcpy(battery_cbc, str_cut);
        batt_sms=atoi(battery_cbc);
        voltag_battery=atoi(battery_cbc);//
        if(batt_sms == 10)batt_sms = 100;
        if(voltag_battery == 10)voltag_battery = 100;
        sprintf(CharMain, "Battery:");
        strcat(CharMain, battery_cbc);
        strcat(CharMain, "%");
        show_uart(CharMain);
        if(chek==5)chek = 6;
      }
      
      //*****SIM CARD CHEK*********
      if (strstr(char_test3, "+COPS: 0,0,\"MTN Irancell\"") != NULL) {
        //show_uart("SIM: IranCell");
        model_simcard = 1;
        red_led_count = 1;
        chek_sim_ok = 1;
        if(chek==7)chek = 8;
      }
      
      if (strstr(char_test3, "+COPS: 0,0,\"TCI\"") != NULL ||strstr(char_test3, "+COPS: 0,0,\"43235\"") != NULL) {
        //show_uart("SIM: MCI");
        model_simcard = 2;
        red_led_count = 1;
        chek_sim_ok = 1;
        if(chek==7)chek = 8;
      }
      
      
      //*******network_check******
      if (strstr(char_test3, "+CGREG: 0,1") != NULL || strstr(char_test3, "+CREG: 0,1") != NULL || strstr(char_test3, "+CREG: 2,1") != NULL || strstr(char_test3, "+CREG: 0,5") != NULL)
      {
        //show_uart("***NETWORK CONNECT****");
        red_led_count = 1;
        sim_error_count1 = 0;
        if(chek==9)chek = 10;
      }
      
      
      if (strstr(char_test3, "+CGREG: 0,2") != NULL|| strstr(char_test3, "+CREG: 0,2") != NULL || strstr(char_test3, "+CREG: 2,2") != NULL)
      {
        show_uart("---Network not ready---");
        red_led_count = 0;
      }
      
      
      if (strstr(char_test3, "+CMGS") != NULL ) {
        show_uart("SMS SEND");
      }
    }
    
    
    //=================================================
    //                 InPut SMS
    //=================================================
    {
      if (strstr(char_test3, "+CMTI") != NULL ) 
      {
        chek = 0;
        SMS_CHECK_Timer = 0;
        show_uart("SMS FROM UART");
        SMSCheck = 1;
        SMS_Check_Count = 0;     
        SMS_Check_point = 1;
        send_atcammand("AT+CMGL=\"ALL\"");   
      }
      
      if (strstr(char_test3, "+CMGL") != NULL)  
      {
        show_uart("Input SMS");
        chek = 0;
        SMSCheck = 0;
        Read_Input_SMS();
      }
    }
    InputSMS();
  }
  
}

void MC60_Check(){
  
  
  if(main_chek_count >= 400) {
    show_uart("nothing for check->*reset device*");
    hang = 1;
    HAL_Delay(500);
  }
  
  if (sim_error_count1 >= 120)
  {
    sim_error_count1 = 0;
    show_uart("!Sim card Error!");
    ResetMC60();
  }
  
  if(chek_count >=60 && chek == 0) {
    send_atcammand("AT");
    chek = 1;
    chek_count = 0;
  }
  
  if(chek_count >= 3 && chek == 1) {
    show_uart("MC60 Check Error");
    ++chek_count2;
    chek = 1;
    chek_count = 0;
    send_atcammand("AT");
  }
  
  if (chek == 2)
  {
    //show_uart("***MC60 OK***");
    send_atcammand("AT+CSQ");
    chek_count2 = 0;
    chek_count = 0;
    chek = 3;
  }
  
  if(chek == 3 && chek_count >= 3) {
    ++chek_count2;
    chek = 3;
    chek_count = 0;
    send_atcammand("AT+CSQ");
  }
  
  if(chek == 4) {
    show_uart("***ANTEN OK***");
    chek = 5;
    chek_count = 0;
    chek_count2 = 0;
    send_atcammand("AT+CBC");
  }
  
  if(chek == 5 && chek_count >= 3) {
    ++chek_count2;
    chek = 5;
    chek_count = 0;
    send_atcammand("AT+CBC");
  }
  
  if(chek == 6) {
    chek = 7;
    chek_count = 0;
    chek_count2 = 0;
    send_atcammand("AT+COPS?");
  }
  
  if(chek == 7 && chek_count >= 3) {
    show_uart("-SIM CARD ERROR-");
    ++chek_count2;
    chek = 7;
    chek_count = 0;
    send_atcammand("AT+COPS?");
  }
  
  if(chek == 8) {
    show_uart("***Sim Card OK***");
    chek = 9;
    chek_count = 0;
    chek_count2 = 0;
    send_atcammand("AT+CREG?");
  }
  
  if(chek == 9 && chek_count >= 3) {
    show_uart("-NETWORK ERROR-");
    ++chek_count2;
    chek = 9;
    chek_count = 0;
    send_atcammand("AT+CREG?");
  }
  
  //***CHECK DONE***
  if(chek == 10) {
    chek = 0;
    chek_count = 0;
    chek_count2 = 0;
    sim_error_count1 = 0;
    red_led_count = 1;
    show_uart("***MC60 CHECK DONE***");
    sprintf(CharMain, "MC60_BAT=%d ANTEN:%d", batt_sms, anten);
    show_uart(CharMain);
    main_chek_count = 0;
    anten_send = (anten - 0) * (100 - 0) / (31 - 0) + 0;
    char ss3[100];
    sprintf(ss3 , "Voltage: %.2f | Current: %.2f" , InputVoltage , Current);
    show_uart(ss3);
  }
  
  if(chek_count2 >= 3) {
    chek_count2 = 0;
    ResetMC60();
  }
}

void MC60_start(){
  
  //****MC60 Check***
  if(MC60_FirstStart_Count == 0){
    show_uart("MC60 First Start");
    UartTrig=0;
    memset(rx_buffer1, 0, sizeof(rx_buffer1));                                                                                                                                                                                                                                                               
    rx_index1 = 0; 
    send_atcammand("AT");
    HAL_Delay(100);
    send_atcammand("AT");
    //HAL_Delay(100);
   // send_atcammand("AT+IPR=9600");
    MC60_FirstStart_Timer = 0;
    MC60_FirstStart_Count = 1;
  }
  
  //***MC60 off***
  if (MC60_FirstStart_Count == 1 && MC60_FirstStart_Timer >= 3)
  {
    show_uart("No Response");
    ResetMC60();
  }
  
  if (MC60_FirstStart_Count == 2)
  {
    FirstStartError = 0;
    show_uart("MC60 OK");
    MC60_FirstStart_Error=0;
    MC60_FirstStart_Count = 3;
    MC60_FirstStart_Timer = 0;
    send_atcammand("AT+COPS=0");
    HAL_Delay(250);
    send_atcammand("AT+CFUN=1");
    HAL_Delay(250);
    send_atcammand("AT+CREG?");
  }
  
  
  //*** network check***
  if (MC60_FirstStart_Count == 3 && MC60_FirstStart_Timer >= 3)
  {
    show_uart("Network Error");
    send_atcammand("AT+CREG?");  
    //send_atcammand("AT+CSMINS?");  
    ++MC60_FirstStart_Error;
    //if(MC60_FirstStart_Error >= 13)MC60_FirstStart_Count = 4;
    if(MC60_FirstStart_Error >= 15)
    {
      show_uart("--Reset Mc60--");
      ResetMC60();
    }
    MC60_FirstStart_Timer = 0;
  }
  
  //*** Sim card check ***
  if (MC60_FirstStart_Count == 4)
  {        
    show_uart("Sim card?");
    send_atcammand("AT+COPS?");
    MC60_FirstStart_Timer  = 0;
    MC60_FirstStart_Count = 5;
    MC60_FirstStart_Error = 0;
  }
  
  if (MC60_FirstStart_Count == 5 && MC60_FirstStart_Timer >= 2)
  {
    show_uart("Sim Card Error");
    send_atcammand("AT+COPS?");
    MC60_FirstStart_Timer = 0;
    ++MC60_FirstStart_Error;
    if(MC60_FirstStart_Error >= 5)
    {
      ResetMC60();
    }       
  }
  
  //******************** Check Done*********************** 
  if (MC60_FirstStart_Count == 6)
  {       
    show_uart("Config MC60");     
//    send_atcammand("AT&F");
//    HAL_Delay(500);
    send_atcammand("AT+CMGF=1");
    HAL_Delay(100);
    send_atcammand("AT+CSCS=\"GSM\"");
    HAL_Delay(100);
    send_atcammand("AT+CSMP=17,167,0,0");
    HAL_Delay(100);
    send_atcammand("AT+CPMS=\"ME\",\"ME\",\"ME\"");
    HAL_Delay(100);
    send_atcammand("AT+CMGD=1,4");
    HAL_Delay(100);
    send_atcammand("AT+CPMS=\"SM\",\"SM\",\"SM\"");
    HAL_Delay(100);
    send_atcammand("AT+CMGD=1,4");
    HAL_Delay(100);
     send_atcammand("ATE0");
    HAL_Delay(100);
    send_atcammand("AT&W");
    HAL_Delay(100);   
    SMSCheck = 0;
    show_uart("*MC60 ready*");
    MC60_FirstStart_Error=0;
    MC60_FirstStart_Count = 0;
    MC60_FirstStart_Timer = 0;
    HAL_Delay(100);    
    main_chek_count = 0;
    MC60_Ready = 1;
    UartTrig=0;
    memset(rx_buffer3, 0, sizeof(rx_buffer3));
    memset(char_test3, 0, sizeof(char_test3));
    rx_index1 = 0; 
    chek_count = 54; 
    
     EEPROM_Init_Config();     // ??? ???? ??? ? Factory Default
     EEPROM_Load_Check_Print();// Load + Check + Print
     if(eepromFualt == 1){
       eepromFualt = 0;
       number = 0;
       sprintf(sms_text, "CONFIG PUMP");
       send_sms();
       FirstConfig();
     }
     
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
  }
  
}

void Sim800(){
  
  if(MC60_Ready == 0)MC60_start();
    if(MC60_Ready == 1){
      MC60_Check();
      SMS_Check();
    }
}