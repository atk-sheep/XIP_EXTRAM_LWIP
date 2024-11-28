/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SDRAM_BANK_ADDR     ((uint32_t)0xC0000000)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
// uint32_t ttt;
// static uint8_t ttt2 = 0;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 1024,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

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

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

extern UART_HandleTypeDef huart1;

//SDRAM内存测试	    
void fsmc_sdram_test()
{  
	uint32_t i=0;  	  
	uint32_t temp=0;	   
	uint32_t sval=0;	//在地址0读到的数据	  				   
	//刚好是32M字节
	for(i=0;i<32*1024*1024;i+=4)
	{
		*(vu32*)(SDRAM_BANK_ADDR+i)=temp; 
		temp++;
	}
	//依次读出之前写入的数据,进行校验		  
 	for(i=0;i<32*1024*1024;i+=4) 
	{	
  		temp=*(vu32*)(SDRAM_BANK_ADDR+i);
		if(i==0)sval=temp;
 		else if(temp<=sval || ((i/4)!=temp) ){
      printf("sdram error\r\n");
      break;//后面读出的数据一定要比第一次读到的数据大.
    }
 	}					 
}	

// uint8_t arr1[] __attribute__((section(".arr1")))   = {0x1, 0x2, 0x3};
// uint8_t arr2[] __attribute__((section(".arr2")));

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  // memcpy(arr2, arr1, 3);
  // for(int i=0;i<3;++i){
  //   printf("one, %d \r\n", arr2[i]);
  // }
  /* init code for LWIP */
  MX_LWIP_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */

  //fsmc_sdram_test();
  /******测试external sdram是否读写正常*******/
  // uint8_t cnt[] = {123};
  // uint8_t *ptr = SDRAM_BANK_ADDR;
  // for(uint32_t i=0;i<4094304;++i){  //4094304
  //   *(uint8_t *)(ptr+i) = cnt[0];
  // }
  // printf("w over\r\n");

  // for(uint32_t i=0;i<4094304;++i){  //4094304
  //   if(memcmp(cnt, (uint8_t*)(0xC0000000+i), 1) != HAL_OK){
  //       printf("while, %d, %x\r\n", i, *(uint8_t*)(0xC0000000));
  //       while(1)
  //         ;
  //     }
  // }
  // printf("cmp over\r\n");
  /*************************************/

  for(;;)
  {
	  //HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_SET);
	  osDelay(500);
	  //HAL_GPIO_WritePin(GPIOB, LED0_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, LED1_Pin, GPIO_PIN_RESET);
	  osDelay(500);

	  printf("hello\r\n");

  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

