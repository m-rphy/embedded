#include "stm32f1xx_hal.h" // Might change based on STM32 series.

TIM_HandleTypeDef htim2; // Using a TIM2.

void SystemClock_Config(void);
void TIM2_Init(void);
void Error_Handler(void);

int main(void) 
{
    HAL_Init();
    SystemClock_Config();

    TIM2_Init();

    HAL_TIM_Base_Start_IT(&htim2); // start timer interrupts
    
    while (1) 
    {
        // Main Loop Here
    }
}

void TIM2_Init(void) 
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 7199; // Assuming 72 MHz system clock 
                                 //   -> Divides clock to 10kHz
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 10000; // 10 kHz / 10000 = 1Hz => 1 second period.
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    if (HAL_TIM_BAse_Init(&htim2) != HAL_OK) 
    {
        // Initialization of Error
        Error_Handler();
    }
    
    sCLockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) 
    {
        // Initialization of Error
        Error_Handler();
    }

    sMasterConfig.MasterOutputTigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

    if (HAL_TIMWx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) 
    {
        // Initialization of Error
        Error_Handler();
    }
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandlerTypeDef *htim)
{
    if (htim-> Instance == TIM2)
    {
        // This Callback is called every 1 second.
        // add logic/functions to be called very sec
    }
}

void Error_Hander(void) 
{
    while (1) 
    {
        // Stay here if there is an error    
    }
}

void SystemClock_Config(void) 
{
    // Set system clock here 
    // Specific to STM32 micro controller series
}
