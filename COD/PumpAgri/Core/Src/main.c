/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : main.c
* @brief          : Main program body
******************************************************************************
* @attention
*
* Copyright (c) 2026 STMicroelectronics.
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
*/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>    
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

WWDG_HandleTypeDef hwwdg;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
static void MX_IWDG_Init(void);
static void MX_WWDG_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */




//**************************************
//    Uart
//**************************************
#define RX_BUFFER_SIZE 290
uint8_t rx_buffer1[RX_BUFFER_SIZE];
uint8_t rx_data1;
volatile uint16_t rx_index1 = 0;
int UartTrigTime;
int UartTrig;
char char_test1[295];
uint32_t last_time;
int uartTimeTest;

#define RX_BUFFER_SIZE3 290
uint8_t rx_buffer3[RX_BUFFER_SIZE3];
uint8_t rx_data3;
volatile uint16_t rx_index3 = 0;
int UartTrigTime3;
int UartTrig3;
char char_test3[295];
uint32_t last_time3;
int uartTimeTest3;






//**************************************
//    Sim800
//**************************************
//**** First Start ***
int MC60_FirstStart_Count;
int MC60_Ready=0;
int MC60_FirstStart_Timer;
int MC60_FirstStart_Error;
int model_simcard;
//main var
int reset_count;
char CharMain[300];
char str[200];
char str_cut[50];
int hang;
//sms
char sms_text[250];
char server_number[20] = "+989372425086";
const char server_number2[20] = "+989114764806";
char input_number[24];
char send_number[25];
int exti_sms;
int SMS_Check_point;
int SMS_CHECK_Timer;
int SMS_Check_Count;
int TimeSMSDone;
int SMSDone;
char send_number_ucs2[45];
int SMSCheck;
int main_chek_count;
int number = 5;
//***Check mc60***
int chek_count2;
int chek;
int chek_count;
int main_chek_count;
int sim_error_count1;
int batt_sms;
int anten;
float voltag_battery1;
char battery_cbc[10];
int red_led_count;
int chek_sim_ok;
int voltag_battery;
//****eeprom***
//eeprom_24hc01
uint8_t pass[10]="1111";
uint8_t security_save[5];
uint8_t sleep_mode_save[5];
uint8_t rele_state_save[5];
uint8_t speed_user_save[5];
uint8_t vibrate_state_save[5]; // vibrate_state_save
uint8_t number1[20] = "+981111111111";
uint8_t number2[20]= "+981111111111";
uint8_t number3[20] = "+981111111111";
uint8_t number4[20]= "+981111111111";
uint8_t id[20];
uint8_t gprs_save[5];
uint8_t auto_security_save[5];
uint8_t car_mode[5];
uint8_t Mode[5];
uint8_t loc_save[22];
uint8_t car_number[20];
int anten_send;
int FirstStartError;
int security=0;
int ReleState1;
int ReleState2;
int Security = 0;
float lowCur, highCur;
uint16_t curTime, relTime;
int DeviceMode;
int RemoteMode , AlarmMode;
int EEpromFault;
int DMA_Ready;


//ADC Var
#define ADC_CHANNEL_COUNT 2
uint16_t adc_dma_buffer[ADC_CHANNEL_COUNT];
uint16_t adc[10];
int AdcChannelCount = 2;
int adc1[10];
float Current;
float InputVoltage;
int ADCReady;
int ShowCurrentCount;
int AutoCurrentSet=0;
int AutoCurrentTimer = 0;

int LowCurrentArlarmCount=0;
int LowCurrentArlarmTimer=0;
int HighCurrentAlarmCount=0;
int HighCurrentAlarmTimer=0;

int ReleazeCount = 0;
int RealizeTimr = 0;


//eeprom  
#define PHONE_MAX_LEN   16
#define PHONE_COUNT     10   // ?????? 10 ?????
#define PHONE_BASE_ADDR 0x000   // ???? ???? EEPROM
char phone1[] = "09372425086";
char phone2[] = "+989372425086";
char buffer[PHONE_MAX_LEN];
#define EEPROM_SIZE 512   // ?? ??? ????

/******** EEPROM CONFIG MAP ********/

#define EEPROM_MAGIC_ADDR      0x000   // 1 byte
#define EEPROM_MAGIC_VALUE     0x5A

#define EEPROM_ID_ADDR         0x001   // 8 bytes

#define EEPROM_NUM1_ADDR       0x010   // 16 bytes
#define EEPROM_NUM2_ADDR       0x020   // 16 bytes
#define EEPROM_NUM3_ADDR       0x030   // 16 bytes
#define EEPROM_NUM4_ADDR       0x040   // 16 bytes

#define EEPROM_RELAY1_ADDR     0x050   // 1 byte
#define EEPROM_RELAY2_ADDR     0x051   // 1 byte
#define EEPROM_SECURITY_ADDR  0x052   // 1 byte

#define EEPROM_LOW_CUR_ADDR    0x060   // 4 bytes float
#define EEPROM_HIGH_CUR_ADDR   0x064   // 4 bytes float

#define EEPROM_CUR_TIME_ADDR   0x068   // 2 bytes uint16
#define EEPROM_REL_TIME_ADDR   0x06A   // 2 bytes uint16

#define EEPROM_REMOTE_ADDR    0x06C   // 1 byte
#define EEPROM_ALARM_ADDR     0x06D   // 1 byte
#define EEPROM_MODE_ADDR      0x06E   // 1 byte

#define EEPROM_END_ADDR       0x080

int eepromFualt;
#define MIN_CURRENT     0.1f
#define MAX_CURRENT     50.0f

#define MAX_TIME_SEC    10000

#define VALID_0_1(x)    ((x) == 0 || (x) == 1)
#define FLOAT_IS_VALID(x)   ((x) == (x))


void substring(char string[200], int x, int y)
{
  memcpy(str_cut, "", sizeof(1));
  int l = y - x;
  char sub_str[50];
  for (int i = 0; i < l; i++)
  {
    sub_str[i] = string[x + i];
  }
  sub_str[l] = '\0';
  sprintf(str_cut, sub_str);
}

void removeChar(char *str, char garbage)
{
  
  char *src, *dst;
  for (src = dst = str; *src != '\0'; src++)
  {
    *dst = *src;
    if (*dst != garbage)
      dst++;
  }
  *dst = '\0';
}

void show_uart(char *SendChar)
{
  char ss[200];
  strcpy(ss , SendChar);
  strcat(ss, "\r\n");
  HAL_UART_Transmit(&huart2, (uint8_t *) ss, strlen(ss), HAL_MAX_DELAY);
}

void show_uart2(char *SendChar)
{
  char test[300];
  strcpy(test, SendChar);
  int len = strlen (test);
  HAL_UART_Transmit(&huart2, (uint8_t *) test, len, HAL_MAX_DELAY);
}

void send_atcammand(char *SendChar)
{
  char test[200];
  strcpy(test, SendChar);
  strcat(test, "\r\n");
  int len = strlen (test);
  HAL_UART_Transmit(&huart1, (uint8_t *) test, len, HAL_MAX_DELAY);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  
  if(MC60_Ready == 0){
    ++MC60_FirstStart_Timer;//first start
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  }
  ++main_chek_count;
  ++chek_count;
  if(SMS_Check_point == 1)++SMS_CHECK_Timer;//check input sms
  if(SMSDone ==1)++TimeSMSDone;//delete sms
  if(AutoCurrentSet == 1)++AutoCurrentTimer;
  if(LowCurrentArlarmCount == 1)++LowCurrentArlarmTimer;
  if(HighCurrentAlarmCount == 1)++HighCurrentAlarmTimer;
  if(ReleazeCount == 1)++RealizeTimr;
  ++ShowCurrentCount;
}

void call(){
  char msg[50];
  if(strstr((char*)number1, "+98111111111") == NULL){
    sprintf(msg , "ATD");
    strcat(msg,(char *)number1);
    strcat(msg , ";");
    send_atcammand(msg);
  }
  HAL_Delay(10000);
  HAL_IWDG_Refresh(&hiwdg);
  send_atcammand("ATH");
  HAL_Delay(1000);
  if(strstr((char*)number2, "+98111111111") == NULL){
    sprintf(msg , "ATD");
    strcat(msg,(char *)number2);
    strcat(msg , ";");
    send_atcammand(msg);
  }
  
}


#include "delay.c"
#include "i2c_eeprom/i2c_eeprom.c"
#include "Member.c"
#include "Sim800.c"
#include "PowerCheck.c"
#include "CurrentControl.c"
#include "check.c"
#include "MC60_Uart.c"
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_IWDG_Init();
  MX_WWDG_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(1);
  ADC_DMA_Start();
  HAL_TIM_Base_Start_IT(&htim1); 
  HAL_UART_Receive_IT(&huart1, &rx_data3, 1);
  show_uart("****Start Program****");
  
  //eeprom config
  I2C_init();
  //eeprom_clear_all();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    
    Sim800_Uart();
    Sim800();
    if(MC60_Ready == 1){
      PowerCheck();
      CurrentControl();
       
    }
    HAL_IWDG_Refresh(&hiwdg);
    /* USER CODE END WHILE */
    
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */
  
  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */
  
  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */
  
  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_128;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */
  
  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */
  
  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 7199;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */
  
  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */
  
  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */
  
  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 100;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 200;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
  
  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */
  
  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */
  
  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
  
  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */
  
  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */
  
  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief WWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_WWDG_Init(void)
{

  /* USER CODE BEGIN WWDG_Init 0 */

  /* USER CODE END WWDG_Init 0 */

  /* USER CODE BEGIN WWDG_Init 1 */

  /* USER CODE END WWDG_Init 1 */
  hwwdg.Instance = WWDG;
  hwwdg.Init.Prescaler = WWDG_PRESCALER_1;
  hwwdg.Init.Window = 95;
  hwwdg.Init.Counter = 127;
  hwwdg.Init.EWIMode = WWDG_EWI_ENABLE;
  if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN WWDG_Init 2 */

  /* USER CODE END WWDG_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Rele1_Pin|Rele2_Pin|MC60_Start_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, WC_Pin|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Rele1_Pin Rele2_Pin MC60_Start_Pin */
  GPIO_InitStruct.Pin = Rele1_Pin|Rele2_Pin|MC60_Start_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : In__Pin */
  GPIO_InitStruct.Pin = In__Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(In__GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : in__Pin Remot4_Pin Remot3_Pin */
  GPIO_InitStruct.Pin = in__Pin|Remot4_Pin|Remot3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Remot2_Pin Remot1_Pin */
  GPIO_InitStruct.Pin = Remot2_Pin|Remot1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : WC_Pin */
  GPIO_InitStruct.Pin = WC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(WC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
  if(hang == 0) HAL_WWDG_Refresh(hwwdg);
  
}   
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
