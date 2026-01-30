
//**************************************
//    Send SMS
//**************************************
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





void battry() 
{
  sprintf(str, "GSM BATTERY:%d%c\r\nGSM ANTEN:%d%c\r\n", batt_sms,37, anten_send,37);
  show_uart(str);
  strcpy(sms_text, str);
  send_sms();
}

void Rele1_on() 
{
  HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_SET);
  strcpy(sms_text, "Out1 is on");
  send_sms();
}

void Rele1_off() 
{
  HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
  strcpy(sms_text, "Out1 is off");
  send_sms();
}




//=================================================
//                 Read SMS Data
//=================================================
void InputSMS()
{
  
  if (strstr(char_test3, "BT") != NULL || strstr(char_test3, "Bt") != NULL)
  {
    battry();
    
  }
  
  if (strstr(char_test3, "out1 on") != NULL || strstr(char_test3, "Out1 on") != NULL)
  {
    Rele1_on();
    
  }
  
  if (strstr(char_test3, "out1 off") != NULL || strstr(char_test3, "Out1 off") != NULL)
  {
    Rele1_off();
    
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
    else if (strstr(CharMain, server_number2) != NULL)     /////////////////number1 send sms
    {
      number = 6;
      show_uart("SERVER NUMBER2");
    }
   else if (strstr(CharMain,(char *)  number1) != NULL)     /////////////////number1 send sms
    {
      number = 1;
      show_uart("NUMBER1");
    }
    
   else if (strstr(CharMain,(char *) number2) != NULL)   /////////////////number2 send sms
    {
      number = 2;
      show_uart("NUMBER2");
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
    else if (strstr(CharMain, server_number2) != NULL)     /////////////////number1 send sms
    {
      number = 6;
      show_uart("SERVER NUMBER2");
    }
    else if (strstr(CharMain,(char *)  number1) != NULL)     /////////////////number1 send sms
    {
      number = 1;
      show_uart("NUMBER1");
    }
//    
//    else if (strstr(CharMain,(char *)  number2) != NULL)   /////////////////number2 send sms
//    {
//      number = 2;
//      show_uart("NUMBER2");
//    }
    
    strcpy(input_number, CharMain);
    show_uart(input_number);
    
  }
  
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
//  ++FirstStartError;
//  if(FirstStartError>=6)ResetMicro();
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

  }
  
  if(chek_count2 >= 3) {
    chek_count2 = 0;
    ResetMC60();
  }
}

int FirstStartError;

//void ResetMicro(){
//  show_uart("RESET MICRO");
//  hang = 1;
//  HAL_Delay(5000);
//}

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