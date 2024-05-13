/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId DisplayHandle;
osMutexId Data_mutexHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void DisplayTask(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of Data_mutex */
  osMutexDef(Data_mutex);
  Data_mutexHandle = osMutexCreate(osMutex(Data_mutex));

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
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Display */
  osThreadDef(Display, DisplayTask, osPriorityIdle, 0, 1024);
  DisplayHandle = osThreadCreate(osThread(Display), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  pointInit();
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_DisplayTask */
/**
* @brief Function implementing the Display thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DisplayTask */
void DisplayTask(void const * argument)
{
  /* USER CODE BEGIN DisplayTask */
  /* Infinite loop */
  if (Acc_Init()){
	  LED_Green_Write(1);
  }
  // Pall
  point pall;
  point pall_vana;
  pall.x=120;
  pall.y=160;
  uint8_t x_suund = 0;
  uint8_t y_suund = 0;
  acc_data_xy data;
  // Auk
  point auk;
  // Takistus
  point p1;
  point p2;
  uint8_t sein=0;
  uint8_t paksus=5;
  // Mäng
  uint8_t reset = 1;
  uint32_t colorbackup = BSP_LCD_GetTextColor();
  for(;;)
  {
	  if (Acc_HasData()){
		// Loe andmed
		Acc_ReadXY(&data);

		// Random asukohad
		if (reset){
			auk = randPoint();
			p1 = randPoint();
			p2 = randPoint();
			reset=0;

			// Tühjenda ekraan
			BSP_LCD_SetTextColor(BSP_LCD_GetBackColor());
			BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
			BSP_LCD_SetTextColor(colorbackup);
		}

		// Salvesta vana palli asukoht
		pall_vana.x=pall.x;
		pall_vana.y=pall.y;

		// Arvuta asukoht
		if (data.y>32767){
			x_suund=(65535-data.y)/200;
			if (sein && x_suund>paksus) x_suund = paksus;
			pall.x-=x_suund;
		}else{
			x_suund=data.y/200;
			if (sein && x_suund>paksus) x_suund = paksus;
			pall.x+=x_suund;
		}

		if (data.x>32767){
			y_suund=(65535-data.x)/200;
			if (sein && y_suund>paksus) y_suund = paksus;
			pall.y-=y_suund;
		}else{
			y_suund=data.x/200;
			if (sein && y_suund>paksus) y_suund = paksus;
			pall.y+=y_suund;
		}
		//Kas asukoht läks ekraanist välja
		if (pall.x<5 || pall.x>1000){
			pall.x=5;
		}else if (pall.x>235){
			pall.x=235;
		}

		if (pall.y<5 || pall.y>1000){
			pall.y=5;
		}else if (pall.y>315){
			pall.y=315;
		}

		// Kontrolli, kas pall läks auku
		if (pall.x<auk.x+5 && pall.x>auk.x-5 && pall.y<auk.y+5 && pall.y>auk.y-5) reset=1;

		// Kontrolli, kas pall läks vastu joont
		if (dist(p1, p2, pall)<paksus){
			pall.x=pall_vana.x;
			pall.y=pall_vana.y;
			sein=1;
		} else sein=0;

		//LOG_PRINT("%u",dist(p1, p2, pall));
		// Joonista
		BSP_LCD_SetTextColor(BSP_LCD_GetBackColor());
		BSP_LCD_FillCircle(pall_vana.x, pall_vana.y, 4); //Eemalda pall
		BSP_LCD_SetTextColor(colorbackup);

		BSP_LCD_FillCircle(pall.x, pall.y, 4); //Pall
		BSP_LCD_FillCircle(auk.x, auk.y, 6); //Auk
		BSP_LCD_DrawLine(p1.x, p1.y, p2.x, p2.y); //Takistus

  	  }
	  osDelay(5);
  }
  /* USER CODE END DisplayTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
