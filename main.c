/*
  Irmak Ariçan 	181201039
	31_10_2021
	Bil 362 Arasinav
	
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/*
	Asagida yazilan fonksiyon bizim 1. soru için yazilan kodumuzdur. Bu kodda 16 satirlik bir diziyi girdi alan ve sonucu intiger olan bir fonksiyon 
	tanimlanmistir. 

*/
int command(int satir[16] ){
	int kontrol=0;
	int sayac;
	for(sayac=0;sayac<16;sayac++)
	{
	kontrol=kontrol+satir[sayac];
			
	}
	if ( (kontrol%2)==0 )
	{
		if(satir[15]==0){
			return 1;
		}else
			return 0;
		
		
	}else {
		if(satir[15]==1){
			return 1;
		}else
			return 0;
	}


}

void working (int command[16]){
int sayac;
int	path[3];
int	time[4];
int	speed[7];
int parity;
int bekleme;
int calculated_CCR;	
		calculated_CCR=(((64)*speed[0]+(32)*speed[1]+(16)*speed[2]+(8)*speed[3]+4*speed[4]+2*speed[5]+speed[6])*(90/100)*20000)-1;
	// CCR bulunmasi için [(duty cycle)*ARR] ARR=20000 olarak alinmistir. Duty cycle ise hiz ile ora oranti ile bulunmustur. PDF'de daha açiklayici bir 
	// sekilde görebilirsiniz.
	
		for(sayac=1;sayac<4;sayac++){
		path[sayac-1]=command[sayac];
		}
		for(sayac=4;sayac<8;sayac++){
		time[sayac-4]=command[sayac];
		}
		for(	sayac=8;sayac<15;sayac++){
		speed[sayac-8]=command[sayac];
		}
		
		if(path[2]==0 && path[1]==0&&path[0]==0){
		// 3 ve 4 channel çalisacak
		// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
				bekleme=(2^3)*time[0]+(2^2)*time[1]+(2^1)*time[2]+time[3];
				TIM2->CCR3=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
				TIM2->CCR4=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
				HAL_Delay(bekleme*1000);
			// Motorun çalistiktan bir süre sonra kapanmasi için delay konmustur.
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
		}else if(path[0]==0 && path[1]==0&&path[2]==1){
		// 3 channel çalisacak
					// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
				bekleme=(2^3)*time[3]+(2^2)*time[2]+(2^1)*time[1]+time[0];
				TIM2->CCR3=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
				HAL_Delay(bekleme*1000);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
			
		} else if(path[0]==0 && path[1]==1&&path[2]==0){
			//1 ve 3 channel çalisacak
			// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
				bekleme=(2^3)*time[3]+(2^2)*time[2]+(2^1)*time[1]+time[0];
				TIM2->CCR3=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
				TIM2->CCR1=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				HAL_Delay(bekleme*1000);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
		}else if(path[0]==0 && path[1]==1 &&path[2]==1){
			// 1 channel çalisacak
			// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
				bekleme=(2^3)*time[3]+(2^2)*time[2]+(2^1)*time[1]+time[0];
				TIM2->CCR1=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				HAL_Delay(bekleme*1000);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
			
		}else if(path[0]==1 && path[1]==0 &&path[2]==0){
			// 1 ve 2 channel çalisacak
			// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
				bekleme=(2^3)*time[3]+(2^2)*time[2]+(2^1)*time[1]+time[0];	
				TIM2->CCR1=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				TIM2->CCR2=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
				HAL_Delay(bekleme*1000);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
		}else if(path[0]==1 && path[1]==0 &&path[2]==1){
			// 2 channel çalisacak
			// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
				bekleme=(2^3)*time[3]+(2^2)*time[2]+(2^1)*time[1]+time[0];
				TIM2->CCR2=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
				HAL_Delay(bekleme*1000);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);


		}else if(path[0]==1 && path[1]==1 &&path[2]==0){
			// 2 ve 4 channel çalisacak
			// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
				bekleme=(2^3)*time[3]+(2^2)*time[2]+(2^1)*time[1]+time[0];
				TIM2->CCR2=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
				TIM2->CCR4=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
				HAL_Delay(bekleme*1000);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
		}else if(path[0]==1 && path[1]==1 &&path[2]==1){
			// 4 channel çalisacak
			// bit olarak aldigimiz zamani simdi 10'luk taban için hesapliyoruz.
			bekleme=(2^3)*time[3]+(2^2)*time[2]+(2^1)*time[1]+time[0];
				TIM2->CCR4=calculated_CCR;
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
				HAL_Delay(bekleme*1000);
				HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
		}
		
}
/* hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh
int command(int time[4],int speed[7],int path[3],int parity  ){
	int kontrol=0;
	int sayac;
	for(sayac=0;sayac<4;sayac++)
	{
	kontrol=kontrol+time[sayac];
			
	}
	for(sayac=0;sayac<7;sayac++)
	{
	kontrol=kontrol+speed[sayac];
			
	}
	for(sayac=0;sayac<3;sayac++)
	{
	kontrol=kontrol+path[sayac];
			
	}
	if ( (kontrol%2)==0 )
	{
		if(parity==0){
			return 1;
		}else
			return 0;
	}else {
		if(parity==1){
			return 1;
		}else
			return 0;
	}
}

*/
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
	 int yol_1[]={0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,1};
	 int yol_2[]={0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,1};
	 int yol_3[]={0,0,0,1,1,0,1,0,1,1,1,1,1,1,1,0};
	 int yol_4[]={0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0};
	 int yol_5[]={0,0,1,1,1,0,1,0,1,1,1,1,1,1,1,1};
	 int yol_6[]={0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0};
	 int yol_7[]={0,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0};
	 int yol_8[]={0,1,0,0,1,0,1,0,1,1,1,1,1,1,1,0};
	 int yol_9[]={0,1,0,0,1,0,1,0,1,1,1,1,1,1,1,0};
	 int yol_10[]={0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0};
	 int yol_11[]={0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1};
	 int yol_12[]={0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1};
	 int yol_13[]={0,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1};
	 int yol_14[]={0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1};
	// Yukaridaki kisimda 2.soru için her bir yol için farkli farkli komut dizileri yazilmistir. Bu komutlar yazilirken hizi maksimum yani 1m/s olarak 
	//alinmistir. 
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
  MX_TIM2_Init();
	HAL_TIM_PWM_Init(&htim2);
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
		int path[3];
		int time [4];
		int speed[7];
		int parity;
		int counter;
		// parity kontrolünden dogru sonucu alandiktan sonra wor
		if(command(yol_1)==1){
		working(yol_1);
		}
		
		if(command(yol_2)==1){
		working(yol_2);
		}
		if(command(yol_3)==1){
		working(yol_3);
		}
		if(command(yol_4)==1){
		working(yol_4);
		}	
		if(command(yol_5)==1){
		working(yol_5);
		}		
		
		if(command(yol_6)==1){
		working(yol_6);
		}
		if(command(yol_7)==1){
		working(yol_7);
		}
		
		if(command(yol_8)==1){
		working(yol_8);
		}
		if(command(yol_9)==1){
		working(yol_9);
		}
		if(command(yol_10)==1){
		working(yol_10);
		}
		if(command(yol_11)==1){
		working(yol_11);
		}
		if(command(yol_12)==1){
		working(yol_12);
		}
		if(command(yol_13)==1){
		working(yol_13);
		}
		if(command(yol_14)==1){
		working(yol_14);
		}
		// Timer 2, 4 adet channel olmasi nedeniyle seçilmistir. Herbir channel bir motoru temsil etmektedir. Biz bu motorlari yön bilgimizle açip kapatiyoruz
 		// Bunun için PSC+1 degerimiz 16 seçilmistir. ARR'de 19999 çikmistir.
		// CCR'da seçilen hiz için hesaplanmistir. Hizimiz maksimum olarak alinmistir. Bu durumda CRR 17999 çikmistir.
		// 
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 15;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 19999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
