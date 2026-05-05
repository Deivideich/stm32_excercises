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
- Reset arrays with memset(array, 0, sizeof(array))
- It seems like arrays are treated like pointers by default when referencing their name
- UART is not exempt from sending trash if no countermeasures to clean its buffer are taken. Even if the consolo is not showing any strange behaviors, it could be the case that many CPU cycles are being wasted
- Directives are embedded directly into instructions, so they require no RAM usage. Meanwhile, static global variables are intended to be shared among many files, so they use SRAM
- For constants or pin mappings, it is better to use directives instead of traditional global variables

### Day 2 (04/05/2026):

- memset for resetting arrays makes no sense actually, wouldn't it be better to use circular buffers instead to update the array contents without wasting CPU cycles?
- A basic snippet that allows enter to be the termination char 

```
  while (1)
  {

	if(HAL_UART_Receive(&huart3, &uart_rx,1,1000) == HAL_OK){
		data_rx[iterator] = uart_rx;
		iterator++;
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14,GPIO_PIN_RESET);
		if (iterator == sizeof(data_rx) || uart_rx == TERMINATION_CHAR){

			// This is done to NOT SEND the termination flag char into the return buffer
			uint8_t size_to_send = (uart_rx == TERMINATION_CHAR) ? (iterator - 1) : iterator;

			if(size_to_send>0){
				HAL_UART_Transmit(&huart3, data_rx, size_to_send, 1000);
			}
			memset(&data_rx,0,sizeof(data_rx));
			iterator = 0;
		}
	}
	else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

	}
}
```

- Even though chars can be represented as uint8_t, it is worth noting that for the compiler it is not the same to compare char vars to uint8_t vars because of the sign, aka, chars can go from -127 to 127, and uint8_t is from 0 to 256. To overcome this, we can use a cast operation in C
- It is possible to use the strcmp operator with char arrays (strings) as long as they are properly casted into the compatible variable type
- Always check the ASCII equivalence for chars and their values; it might be confusing when dealing with /r and /n for endline in UART reception mode

### Day 3 (05/05/05/2026):

- Adding the \r\n at the end of the strings make the carriage return and string end attach to the string buffers as expected
- Use size_t to ensure maximum capacitr iterators are being used for their type
- It is fundamental to put the string termination (ASCII 0) to identify the end of a string and use the string functions like strcmp
- Even the integrated push buttons in the board are susceptible to noise due to the main processor speed while reading the button press
- Do not confuse logical operators with bitshift operatios (& and && are different)
- sizeof does NOT measure the length of a string
- strings have their own embedded functions within <string.h>, among them strlen to return the actual size of a string. Otherwise, by using sizeof it will always return 4 bytes since its the size of the point (32 bit architecture)
