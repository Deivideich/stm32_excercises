# Logs for UART excercisess

### Day 1 (03/05/2026):

- STM32CubeIDE and STM32CubeMX are completely different softwares
  - STM32CubeIDE works as the main debugger and program runner for STM32 boards through Eclipse IDE
  - STM32CubeMX is the macro runner to declare timers, peripherals, connections, etc. It is essentially a GUI that initializes code for specific MCUs or boards
- UART transmit and receive instructions need the length of the data to be received be explictily declared in order to work
- It is very useful to take note about the compiled HAL instructions and functions that are generated within the main program
- UART Protocol may send trash if not properly initialized, even when the amount of data to be sent is less than the one declared in the HAL_UART_Init function
- It is extremely important to check the domain and initializer MCU for each peripheral
- Use the HAL status for HAL handlers as a standard way to evaluate the state of a peripheral managed by this library; it might be a good idea to leverage this for custom driver implementation
- HAL: Hardware Abstraction Library; this is a extremely useful library containing functions to enable, use and configure peripherals without having to deal with register set manually. Even though it is useful, it needs to implement differenet checks to ensure it works on every STM32 platform, which causes overhead.
- Bare metal: Usage of peripheral through direct registers and bitshifting operations. There is no way to beat the speed of this approach, but it can get quite difficult to set up.
- LL (Low-Layer Drivers): Essentially macros for bitshifting operations that reduce overhead a lot. It could be useful to learn too, but maybe using bare-metal again would be good.
- GPIOs handle are tied to physical addresses in the MCU, but UART handles are declareda as static instantiates in RAM

- Small snippiet I made to echo some data

``` 
#endif /* DUAL_CORE_BOOT_SYNC_SEQUENCE */
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  //uint8_t data_tx = 'a';
  uint8_t data_rx;
  // uint8_t data_rx_index = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	if(HAL_UART_Receive(&huart3, &data_rx,1,1000) == HAL_OK){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14,GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
	}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
```

- iIs possible to see the HAL function definitions in their compiled libraries, very useful for GPIO and peripheral operations