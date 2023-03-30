/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.21.1. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
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

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>
#include "main.h"
#include "stm32h743i_eval_ts.h"

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
    TS_Init_t hTS;
    hTS.Width = 640;
    hTS.Height = 480;
    hTS.Orientation = TS_SWAP_NONE;
    hTS.Accuracy = 5;
    
    BSP_TS_Init(0, &hTS);
}

static int32_t lastX, lastY;
static uint32_t lastTime;

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
    TS_State_t state;
    unsigned int time;
    BSP_TS_GetState(0, &state);
    if(state.TouchDetected)
    {
        x = lastX = state.TouchX;
        y = lastY = state.TouchY;
        lastTime = HAL_GetTick();
        return true;
    }
    time = HAL_GetTick();
    if(((lastTime + 120) > time) && (lastX > 0) && (lastY > 0))
    {
        x = lastX;
        y = lastY;
        return true;
    }    
    
    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
