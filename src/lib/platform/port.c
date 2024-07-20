#include "port.h"

void spim_event_handler(nrfx_spim_evt_t const * p_event, void * p_context) {
    if (p_event->type == NRFX_SPIM_EVENT_DONE) {
        // Handle transfer completion
        spi_xfer_done = true;
        //printf("SPIM transfer completed.\t\n");
    }
}

void deca_sleep(unsigned int time_ms){
    k_msleep(time_ms);
}

void configure_gpio(){
    // Comunication pins GPIO configuration
	nrf_gpio_cfg_input(DW1000_MISO, NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_output(DW1000_MOSI);
	nrf_gpio_cfg_output(DW1000_CLK);
	nrf_gpio_cfg_output(DW1000_CS);
}

/*
void configure_spi(uint8_t freq, nrfx_spim_config_t* p_spim){
    nrfx_spim_config_t p_spim = {
    .sck_pin = DW1000_CLK,
    .mosi_pin = DW1000_MOSI,
    .miso_pin = DW1000_MISO, 
    .ss_pin = NRF_SPIM_PIN_NOT_CONNECTED,
    .frequency  = NRFX_MHZ_TO_HZ(freq),
    .mode = NRF_SPIM_MODE_0,
    .bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST,
    .miso_pull      = NRF_GPIO_PIN_NOPULL
    };
    //nrfx_spim_reconfigure(&spim, p_spim);
}
*/

#define NRF_DRV_SPI_CONFIG(freq)                \
{                                               \
    .sck_pin = DW1000_CLK,                      \
    .mosi_pin = DW1000_MOSI,                    \
    .miso_pin = DW1000_MISO,                    \
    .ss_pin = NRF_SPIM_PIN_NOT_CONNECTED,       \
    .frequency  = NRFX_MHZ_TO_HZ(freq),         \
    .mode = NRF_SPIM_MODE_0,                    \
    .bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST,  \
    .miso_pull      = NRF_GPIO_PIN_NOPULL       \
}               

int spim_lowrate(){
    nrfx_err_t status;
    (void)status;
    nrfx_spim_config_t spim_config = NRF_DRV_SPI_CONFIG(2);
    spim_config.ss_pin = DW1000_CS;
    status = nrfx_spim_init(&spim, &spim_config, spim_event_handler, NULL);
    if (status != NRFX_SUCCESS){
        return 0;
    }
    return 1;
}

int spim_fastrate(){
    nrfx_err_t status;
    (void)status;
    nrfx_spim_config_t spim_config = NRF_DRV_SPI_CONFIG(4);
    spim_config.ss_pin = DW1000_CS;
    status = nrfx_spim_init(&spim, &spim_config, spim_event_handler, NULL);
    if (status != NRFX_SUCCESS){
        return 0;
    }
    return 1;
}

void setup_DW1000IRQ(void);

void reset_DW1000(void){
  nrf_gpio_cfg_output(DW1000_RST);   
  //nrf_gpio_pin_set(DW1000_RST);  
  //k_msleep(50); 
  nrf_gpio_pin_clear(DW1000_RST);  
  k_msleep(2); 
  nrf_gpio_cfg_input(DW1000_RST, NRF_GPIO_PIN_NOPULL); 
  k_msleep(10); 
}
