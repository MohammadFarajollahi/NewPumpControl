//===========================
// UART Rx Callback
//===========================
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {    
    if(rx_index3 >= RX_BUFFER_SIZE3 -1){    
      rx_index3 = 0;
    }       
    if (rx_index3 < RX_BUFFER_SIZE3 - 1)
    {
      rx_buffer3[rx_index3++] = rx_data3;
      uartTimeTest3 = 0;
      UartTrig3 = 1;
    }   
    HAL_UART_Receive_IT(&huart1, &rx_data3, 1);
  }
  
}


void Sim800_Uart(void)
{  
  uint32_t now = HAL_GetTick();
  if (now - last_time3 >= 100)
  {
    last_time3 = now;  // ریست تایمر
    ++uartTimeTest3;
  }
  
  if(uartTimeTest3 >=2 && UartTrig3 == 1){
    uartTimeTest3 = 0;
    char *token;
    char *rest = (char*)rx_buffer3;
    while ((token = strtok_r(rest, "\r\n", &rest)) != NULL)
    { 
      snprintf(char_test3, sizeof(char_test3), "%s\r\n", token);
      show_uart2(char_test3);
      Sim800_Check();
    }
    UartTrig3=0;
    memset(rx_buffer3, 0, sizeof(rx_buffer3));
    rx_index3 = 0; 
  }
}