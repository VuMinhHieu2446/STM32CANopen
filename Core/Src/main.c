/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

FDCAN_HandleTypeDef hfdcan1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FDCAN1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
FDCAN_TxHeaderTypeDef   TxHeader;
FDCAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8];
uint8_t               RxData[8];

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    /* Retreive Rx messages from RX FIFO0 */
    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
    /* Reception Error */
    Error_Handler();
    }
    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
      /* Notification Error */
      Error_Handler();
    }
  }
}

/*
 * @brief: Convert from CAN frame to CANopen Frame
 * @param: id: Node ID
 * @param: index: 2bytes index + 1byte sub index
 * @param: data: maximum 4bytes of transceiving data
 * @param: len: data lenght, maximum 4 bytes
 * @param: rw: 0 to read (x40), 1 to write (x20)
 * @reval: HAL_Status
 */

HAL_StatusTypeDef CANopenSendSDO(uint8_t id, uint8_t command_byte, uint32_t index, uint32_t data, uint8_t len, uint8_t rw)
{
	uint8_t txbuf[8];
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;	// so byte data truyen di la 8
	TxHeader.IdType = FDCAN_STANDARD_ID;		// standard ID
	TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
	TxHeader.FDFormat = FDCAN_CLASSIC_CAN;		//choose transmit frame
	TxHeader.MessageMarker = 0;
	TxHeader.Identifier = 0x600+id;				//Specific ID
	TxHeader.TxFrameType = FDCAN_DATA_FRAME;				//Data_frame
	TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;

	txbuf[0] = command_byte;
	txbuf[1] = (index>>8)&0xff;		//index
	txbuf[2] = (index>>16)&0xff;	//index
	txbuf[3] = index&0xff;			//sub_index

	txbuf[4] = data & 0xff;
	txbuf[5] = (data>>8)&0xff;
	txbuf[6] = (data>>16)&0xff;
	txbuf[7] = (data>>24)&0xff;
	return HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, txbuf);
}
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
  MX_FDCAN1_Init();
  /* USER CODE BEGIN 2 */
if(HAL_FDCAN_Start(&hfdcan1)!= HAL_OK)
 {
	  Error_Handler();
 }
 if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
 {
   /* Notification Error */
   Error_Handler();
 }
 //Switch On Disabled (basic state)
 CANopenSendSDO(1,0x2B, 0x604000, 0x00, 4, 1);
 HAL_Delay(100);

// //Request of the status word
//  CANopenSendSDO(1,0x40, 0x604100, 0x00, 4, 1);
//   HAL_Delay(5000);

// Ready to Switch On
 CANopenSendSDO(1,0x2B, 0x604000, 0x06, 4, 1);
 HAL_Delay(100);

// //Request of the status word
//  CANopenSendSDO(1,0x40, 0x604100, 0x00, 4, 1);
//   HAL_Delay(5000);

 //Switch On (power drive on)
 CANopenSendSDO(1,0x2B, 0x604000, 0x07, 4, 1);
 HAL_Delay(100);

 //Operation Enabled
 CANopenSendSDO(1,0x2B, 0x604000, 0x0F, 4, 1);			// dong co da chuyen sang mode run duoc roi anh a
 HAL_Delay(100);

// //Request of the status word
// CANopenSendSDO(1,0x40, 0x604100, 0x00, 4, 1);
//  HAL_Delay(5000);

// //Mode: Profile Position (PP)
// CANopenSendSDO(1,0x2F, 0x606000, 0x01, 4, 1);
// HAL_Delay(2000);
//
// //End position to 0x12345
// CANopenSendSDO(1,0x27, 0x607A00, 0x12345, 4, 1);
//  HAL_Delay(100);
//
//// Start of a movement
// CANopenSendSDO(1,0x2F, 0x604000, 0x1F, 4, 1);
// HAL_Delay(100);
////
//// Reset of the start bit
// CANopenSendSDO(1,0x2F, 0x604000, 0x0F, 4, 1);
// HAL_Delay(100);

//  Mode: Torque
  CANopenSendSDO(1,0x2F, 0x606000, 0x04, 4, 1);
  HAL_Delay(100);

//  Target torque
  CANopenSendSDO(1,0x2B, 0x607100, 0x150, 4, 1);
  HAL_Delay(100);

// Start of a movement
  CANopenSendSDO(1,0x2F, 0x604000, 0x1F, 4, 1);
  HAL_Delay(100);

// Reset of the start bit
  CANopenSendSDO(1,0x2F, 0x604000, 0x0F, 4, 1);
  HAL_Delay(100);

  HAL_Delay(5000);

//  Target torque
  CANopenSendSDO(1,0x2B, 0x607100, 0x0, 4, 1);
  HAL_Delay(100);

// Start of a movement
	CANopenSendSDO(1,0x2F, 0x604000, 0x1F, 4, 1);
	HAL_Delay(100);

// Reset of the start bit
	CANopenSendSDO(1,0x2F, 0x604000, 0x0F, 4, 1);
	HAL_Delay(100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  TxData[0] = 0x23;
//	  TxData[1] = 0x11;
//	  TxData[2] = 0x10;
//	  TxData[3] = 0x01;
//	  TxData[4] = 0x6C;
//	  TxData[5] = 0x6F;
//	  TxData[6] = 0x61;
//	  TxData[7] = 0x64;
//	  HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData);
//	  CANopenSendSDO(1,0x22, 0x60FF00, 0xFFFF, 0, 1);
	  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_8);
	  HAL_Delay(1000);
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOMEDIUM;
  RCC_OscInitStruct.PLL.PLLFRACN = 3072;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief FDCAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = ENABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 1;
  hfdcan1.Init.NominalSyncJumpWidth = 7;
  hfdcan1.Init.NominalTimeSeg1 = 42;
  hfdcan1.Init.NominalTimeSeg2 = 7;
  hfdcan1.Init.DataPrescaler = 10;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 3;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.MessageRAMOffset = 0;
  hfdcan1.Init.StdFiltersNbr = 1;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.RxFifo0ElmtsNbr = 64;
  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxFifo1ElmtsNbr = 0;
  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxBuffersNbr = 0;
  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.TxEventsNbr = 0;
  hfdcan1.Init.TxBuffersNbr = 0;
  hfdcan1.Init.TxFifoQueueElmtsNbr = 1;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */
FDCAN_FilterTypeDef sFilterConfig;

  sFilterConfig.IdType = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = 0x581;
  sFilterConfig.FilterID2 = 0x7FF;
  sFilterConfig.RxBufferIndex = 0;
  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }
  /**
  void CanOpen::fdcanConfigureFilter() {
  	FDCAN_FilterTypeDef sFilterConfig;
  	sFilterConfig.IdType = FDCAN_STANDARD_ID;
  	sFilterConfig.FilterIndex = 0;
  	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
  	sFilterConfig.FilterConfig = FDCAN_FILTER_DISABLE;
  	sFilterConfig.FilterID1 = 0;
  	sFilterConfig.FilterID2 = 0x7FF;
  	if (HAL_FDCAN_ConfigFilter(fdcanHandler, &sFilterConfig) != HAL_OK) {
  		// Filter configuration Error
  		fdcanErrorHandler();
  	}
  }
  **/
  /* USER CODE END FDCAN1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PD8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/*
 * typedef enum {
	INDEX_MANUFACTURER_DEVICE_NAME = 0x1008U,
	INDEX_MANUFACTURER_HARDWARE_VERSION = 0x1009U,
	INDEX_MANUFACTURER_SOFTWARE_VERSION = 0x1010U,
	INDEX_CONTROLWORD = 0x6040U,
	INDEX_STATUSWORD = 0x6041U,
	INDEX_OPERATION_MODE = 0x6060U,
	INDEX_ACTUAL_POSITION = 0x6064U,
	INDEX_TARGET_TORQUE = 0x6071U,
	INDEX_TORQUE_SLOPE = 0x6087U,
	INDEX_TORQUE_PROFILE_TYPE = 0x6088U,
	INDEX_CYCLE_PERIOD = 0x1006U,
	INDEX_SYNC_WINDOW = 0x1007U,
	INDEX_SYNC_COUNTER_OVERFLOW = 0x1019U,
	RPDO1_COMMUNICATION_PARAMETER = 0x1400U,
	RPDO2_COMMUNICATION_PARAMETER = 0x1401U,
	RPDO1_MAPPING = 0x1600U,
	RPDO2_MAPPING = 0x1601U,
	TPDO1_COMMUNICATION_PARAMETER = 0x1800U,
	TPDO2_COMMUNICATION_PARAMETER = 0x1801U,
	TPDO1_MAPPING = 0x1A00U,
	TPDO2_MAPPING = 0x1A01U,
//	CIA_DS301
	INDEX_CONTROL_MODE_DS301 = 0x2002U,
	INDEX_PLC_DS301 = 0x2004U,
	INDEX_MONITOR_DS301 = 0x2005U,
} OBJECT_INDEX;
 */
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

#ifdef  USE_FULL_ASSERT
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
