/********************************************************************************************
 * Dual ARM core Hello World
 * Aouther: FPGAPS
 * Date: 12/DEC/2024
 * ARM0: A53_0 FreeRTOS
 ********************************************************************************************/

#include "xparameters.h"
#include "xil_io.h"
#include "sleep.h"

/********************************************************************************************
 * Address of AXI GPIOs here, you can find them in xparameters.h or in Vivado address editor *
 ********************************************************************************************/
#define LED_GPIO_ADDR        XPAR_ARM0_LED_CTRL_BASEADDR //0xA0000000
#define PUSHBUTTON_GPIO_ADDR XPAR_ARM0_SW_POLL_BASEADDR  //0xA0010000

/*********************************
 * Amount of delay in loop in us *
 *********************************/
#define loop_delay_us 250000

int main() {
	u32 pushbutton_state;
	u32 led_state = 0; // Initially, LED is off
	xil_printf("\r\n ******************* ARM0: A53_0 ****************.\r\n");
	xil_printf(
			" ARM0 A53_0: Polling pushbutton for LED control and message display.\r\n");
	xil_printf("*****************************************************.\r\n");
	u32 counter = 0;
	while (1) {
		// Read the pushbutton state
		pushbutton_state = Xil_In32(PUSHBUTTON_GPIO_ADDR);

		// Check if the pushbutton is pressed (assuming active-high logic)
		if (pushbutton_state != 0) {
			// Toggle the LED state
			led_state ^= 1;
			Xil_Out32(LED_GPIO_ADDR, led_state);

			// Print "Hello World"
			xil_printf("%d-Hello world from ARM0: A53_0 FreeRTOS\r\n",counter);
			counter++;

		} else {
			//turn off the LED if push button is not pressed
			Xil_Out32(LED_GPIO_ADDR, 0);
		}
		// Add a small delay in our loop
		usleep(loop_delay_us);
	}

	return 0;
}
