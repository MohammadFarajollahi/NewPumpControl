int PowerCount;
int SendToMember,ResetCount;

void PowerCheck(){
  
  if(InputVoltage < 7 && PowerCount == 1){
    HAL_GPIO_WritePin(Rele1_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Rele2_GPIO_Port, Rele1_Pin, GPIO_PIN_RESET);
    PowerCount = 0;
    show_uart("Power Off");
    sprintf(sms_text, "06470634062F06270631000D000A062806310642002006420637063900200634062F");
    if(Security == 1){
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
    }
    HAL_Delay(500);
    SendToMember = 0;
    ResetCount = 1;
      if(Security == 1)call();
  }
  
  
  if(InputVoltage > 7 && PowerCount == 0){
    PowerCount = 1;
    show_uart("Power On");
    sprintf(sms_text, "062806310642002006480635064400200634062F");
    if(ResetCount == 1)
    {
      if(Security == 1){
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
      }
      
      HAL_Delay(1000);
      hang = 1;
    }
    SendToMember = 0;
  }
  
}