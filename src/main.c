#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "deca_device_api.h"
#include "deca_regs.h"
#include "deca_spi.h"
#include "port.h"

int main(void)
{
    printf("INIT GPIOs\t\n");
    configure_gpio();
    printf("INIT SPI master3\t\n");
    spim_lowrate();
    // Reset and initialise DW1000 
    reset_DW1000(); // Target specific drive of RSTn line into DW1000 low for a period. 
    if (dwt_initialise(DWT_LOADNONE) == DWT_ERROR)
    {
        printf("INIT FAILED\t\n");
        while (1);
    }
    spim_fastrate();
    // 1st enable GPIO clocks 
    dwt_enablegpioclocks();
	// En este ejemplo, estamos usando GPIO2 y GPIO3 como salidas: (1) input y (0) output
    dwt_setgpiodirection(DWT_GxM2 | DWT_GxM3, 0);//~(DWT_GxP2|DWT_GxP3)); // Only changed if the GxM# mask bit has a value of 1 for the write operation
    printf("Begin with binky UWB\t\n");
    while(1)
    {
        dwt_setgpiovalue(DWT_GxM2, DWT_GxP2); // set GPIO2 high (LED4 will light up)
        dwt_setgpiovalue(DWT_GxM3, ~DWT_GxP3); // set GPIO3 low (LED4 will be off)
        k_msleep(400);
        dwt_setgpiovalue(DWT_GxM3, DWT_GxP3); // set GPIO3 high (LED4 will light up)
        dwt_setgpiovalue(DWT_GxM2, ~DWT_GxP2); // set GPIO2 low (LED4 will be off)
	    k_msleep(400);
    }
}
