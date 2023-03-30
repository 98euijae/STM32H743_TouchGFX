/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : main.c
* @brief          : Main program body
******************************************************************************
* @attention
*
* Copyright (c) 2023 STMicroelectronics.
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
#include "cmsis_os.h"
#include "fatfs.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)
#define SDRAM_TIMEOUT                    ((uint32_t)0xFFFF)
#define REFRESH_COUNT                    ((uint32_t)0x0603)   /* SDRAM refresh counter */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

CRC_HandleTypeDef hcrc;

DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c1;

LTDC_HandleTypeDef hltdc;

SD_HandleTypeDef hsd1;

TIM_HandleTypeDef htim2;

SDRAM_HandleTypeDef hsdram1;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for GUI_Task */
osThreadId_t GUI_TaskHandle;
const osThreadAttr_t GUI_Task_attributes = {
    .name = "GUI_Task",
    .stack_size = 2048 * 4,
    .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
FMC_SDRAM_CommandTypeDef command;
uint32_t TIMStart = 0;
uint32_t TIMEnd = 0;
int g_iTaskCnt = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void MX_CRC_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
static void MX_SDMMC1_SD_Init(void);
void StartDefaultTask(void *argument);
void TouchGFX_Task(void *argument);

/* USER CODE BEGIN PFP */
static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
    MX_DMA2D_Init();
    MX_FMC_Init();
    MX_LTDC_Init();
    MX_CRC_Init();
    MX_I2C1_Init();
    MX_TIM2_Init();
    MX_SDMMC1_SD_Init();
    MX_FATFS_Init();
    MX_TouchGFX_Init();
    /* Call PreOsInit function */
    MX_TouchGFX_PreOSInit();
    /* USER CODE BEGIN 2 */
    BSP_SD_Init();
    HAL_TIM_Base_Start(&htim2);
    /* USER CODE END 2 */
    
    /* Init scheduler */
    osKernelInitialize();
    
    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */
    
    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */
    
    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */
    
    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */
    
    /* Create the thread(s) */
    /* creation of defaultTask */
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
    
    /* creation of GUI_Task */
    GUI_TaskHandle = osThreadNew(TouchGFX_Task, NULL, &GUI_Task_attributes);
    
    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */
    
    /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
    /* USER CODE END RTOS_EVENTS */
    
    /* Start scheduler */
    osKernelStart();
    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
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
    
    /** Supply configuration update enable
    */
    HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
    
    /** Configure the main internal regulator output voltage
    */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    
    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
    
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 5;
    RCC_OscInitStruct.PLL.PLLN = 160;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
            |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
* @brief CRC Initialization Function
* @param None
* @retval None
*/
static void MX_CRC_Init(void)
{
    
    /* USER CODE BEGIN CRC_Init 0 */
    
    /* USER CODE END CRC_Init 0 */
    
    /* USER CODE BEGIN CRC_Init 1 */
    
    /* USER CODE END CRC_Init 1 */
    hcrc.Instance = CRC;
    hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
    hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
    hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
    hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
    hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
    if (HAL_CRC_Init(&hcrc) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN CRC_Init 2 */
    
    /* USER CODE END CRC_Init 2 */
    
}

/**
* @brief DMA2D Initialization Function
* @param None
* @retval None
*/
static void MX_DMA2D_Init(void)
{
    
    /* USER CODE BEGIN DMA2D_Init 0 */
    
    /* USER CODE END DMA2D_Init 0 */
    
    /* USER CODE BEGIN DMA2D_Init 1 */
    
    /* USER CODE END DMA2D_Init 1 */
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_R2M;
    hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
    hdma2d.Init.OutputOffset = 0;
    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DMA2D_Init 2 */
    
    /* USER CODE END DMA2D_Init 2 */
    
}

/**
* @brief I2C1 Initialization Function
* @param None
* @retval None
*/
static void MX_I2C1_Init(void)
{
    
    /* USER CODE BEGIN I2C1_Init 0 */
    
    /* USER CODE END I2C1_Init 0 */
    
    /* USER CODE BEGIN I2C1_Init 1 */
    
    /* USER CODE END I2C1_Init 1 */
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x10C0ECFF;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
    }
    
    /** Configure Analogue filter
    */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        Error_Handler();
    }
    
    /** Configure Digital filter
    */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C1_Init 2 */
    
    /* USER CODE END I2C1_Init 2 */
    
}

/**
* @brief LTDC Initialization Function
* @param None
* @retval None
*/
static void MX_LTDC_Init(void)
{
    
    /* USER CODE BEGIN LTDC_Init 0 */
    
    /* USER CODE END LTDC_Init 0 */
    
    LTDC_LayerCfgTypeDef pLayerCfg = {0};
    
    /* USER CODE BEGIN LTDC_Init 1 */
    
    /* USER CODE END LTDC_Init 1 */
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
    hltdc.Init.HorizontalSync = 28;
    hltdc.Init.VerticalSync = 1;
    hltdc.Init.AccumulatedHBP = 142;
    hltdc.Init.AccumulatedVBP = 33;
    hltdc.Init.AccumulatedActiveW = 782;
    hltdc.Init.AccumulatedActiveH = 513;
    hltdc.Init.TotalWidth = 798;
    hltdc.Init.TotalHeigh = 523;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
        Error_Handler();
    }
    pLayerCfg.WindowX0 = 0;
    pLayerCfg.WindowX1 = 640;
    pLayerCfg.WindowY0 = 0;
    pLayerCfg.WindowY1 = 480;
    pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
    pLayerCfg.Alpha = 255;
    pLayerCfg.Alpha0 = 0;
    pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
    pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
    pLayerCfg.FBStartAdress = 0xD0000000;
    pLayerCfg.ImageWidth = 640;
    pLayerCfg.ImageHeight = 480;
    pLayerCfg.Backcolor.Blue = 0;
    pLayerCfg.Backcolor.Green = 0;
    pLayerCfg.Backcolor.Red = 0;
    if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN LTDC_Init 2 */
    
    /* USER CODE END LTDC_Init 2 */
    
}

/**
* @brief SDMMC1 Initialization Function
* @param None
* @retval None
*/
static void MX_SDMMC1_SD_Init(void)
{
    
    /* USER CODE BEGIN SDMMC1_Init 0 */
    
    /* USER CODE END SDMMC1_Init 0 */
    
    /* USER CODE BEGIN SDMMC1_Init 1 */
    
    /* USER CODE END SDMMC1_Init 1 */
    hsd1.Instance = SDMMC1;
    hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
    hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
    hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
    hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
    hsd1.Init.ClockDiv = 0;
    /* USER CODE BEGIN SDMMC1_Init 2 */
    
    /* USER CODE END SDMMC1_Init 2 */
    
}

/**
* @brief TIM2 Initialization Function
* @param None
* @retval None
*/
static void MX_TIM2_Init(void)
{
    
    /* USER CODE BEGIN TIM2_Init 0 */
    
    /* USER CODE END TIM2_Init 0 */
    
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    
    /* USER CODE BEGIN TIM2_Init 1 */
    
    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 200000000-1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */
    
    /* USER CODE END TIM2_Init 2 */
    
}

/* FMC initialization function */
static void MX_FMC_Init(void)
{
    
    /* USER CODE BEGIN FMC_Init 0 */
    
    /* USER CODE END FMC_Init 0 */
    
    FMC_SDRAM_TimingTypeDef SdramTiming = {0};
    
    /* USER CODE BEGIN FMC_Init 1 */
    
    /* USER CODE END FMC_Init 1 */
    
    /** Perform the SDRAM1 memory initialization sequence
    */
    hsdram1.Instance = FMC_SDRAM_DEVICE;
    /* hsdram1.Init */
    hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
    hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
    hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
    hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_32;
    hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
    hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
    hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
    hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_3;
    hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
    hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
    /* SdramTiming */
    SdramTiming.LoadToActiveDelay = 2;
    SdramTiming.ExitSelfRefreshDelay = 7;
    SdramTiming.SelfRefreshTime = 4;
    SdramTiming.RowCycleDelay = 7;
    SdramTiming.WriteRecoveryTime = 3;
    SdramTiming.RPDelay = 2;
    SdramTiming.RCDDelay = 2;
    
    if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
    {
        Error_Handler( );
    }
    
    /* USER CODE BEGIN FMC_Init 2 */
    SDRAM_Initialization_Sequence(&hsdram1, &command);
    /* USER CODE END FMC_Init 2 */
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
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOK_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    
    /*Configure GPIO pin : PB15 */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
    __IO uint32_t tmpmrd =0;
    /* Step 1:  Configure a clock configuration enable command */
    Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = 0;
    
    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    
    /* Step 2: Insert 100 us minimum delay */
    /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
    HAL_Delay(1);
    
    /* Step 3: Configure a PALL (precharge all) command */
    Command->CommandMode = FMC_SDRAM_CMD_PALL;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = 0;
    
    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    
    /* Step 4 : Configure a Auto-Refresh command */
    Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
    Command->AutoRefreshNumber = 8;
    Command->ModeRegisterDefinition = 0;
    
    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    
    /* Step 5: Program the external memory mode register */
    tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
        SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
            SDRAM_MODEREG_CAS_LATENCY_3           |
                SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                    SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    
    Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
    Command->AutoRefreshNumber = 1;
    Command->ModeRegisterDefinition = tmpmrd;
    
    /* Send the command */
    HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);
    
    /* Step 6: Set the refresh rate counter */
    /* Set the device refresh rate */
    HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT); 
    
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief  Function implementing the defaultTask thread.
* @param  argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for(;;)
    {
        osDelay(1);
    }
    /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_TouchGFX_Task */
/**
* @brief Function implementing the GUI_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TouchGFX_Task */
__weak void TouchGFX_Task(void *argument)
{
    /* USER CODE BEGIN TouchGFX_Task */
    /* Infinite loop */
    for(;;)
    {
        osDelay(1);
    }
    /* USER CODE END TouchGFX_Task */
}

/**
* @brief  Period elapsed callback in non blocking mode
* @note   This function is called  when TIM7 interrupt took place, inside
* HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
* a global variable "uwTick" used as application time base.
* @param  htim : TIM handle
* @retval None
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* USER CODE BEGIN Callback 0 */
    
    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM7) {
        HAL_IncTick();
    }
    /* USER CODE BEGIN Callback 1 */
    
    /* USER CODE END Callback 1 */
}

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