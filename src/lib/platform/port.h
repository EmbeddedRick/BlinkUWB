#ifndef PORT_h
#define PORT_h

#include <zephyr/kernel.h>
#include <hal/nrf_gpio.h>
#include <nrfx_spim.h>

// SPI communication pins
#define DW1000_CLK             NRF_GPIO_PIN_MAP(1, 15) // output
#define DW1000_MISO            NRF_GPIO_PIN_MAP(1, 14) // input
#define DW1000_MOSI            NRF_GPIO_PIN_MAP(1, 13) // output
#define DW1000_CS              NRF_GPIO_PIN_MAP(1, 12) // ouput
// Clock configuration pins
#define DW1000_POL             NRF_GPIO_PIN_MAP(1, 2) // ouput
#define DW1000_PHA             NRF_GPIO_PIN_MAP(1, 1) // ouput
// Additional pins for functionality
#define DW1000_RST             NRF_GPIO_PIN_MAP(1, 8)
#define DW1000_IRQ             NRF_GPIO_PIN_MAP(1, 10)
// define instances of the SPI ports
#define SPI_INSTANCE           3 // Estabamos usando el SPIM3
static const nrfx_spim_t spim = NRFX_SPIM_INSTANCE(SPI_INSTANCE);
static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */

/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_event_handler(nrfx_spim_evt_t const * p_event, void * p_context);

void deca_sleep(unsigned int time_ms);

void configure_gpio(void);
//void configure_spim(uint8_t freq, nrfx_spim_config_t* p_spim);

int spim_lowrate(void);
int spim_fastrate(void);

void setup_DW1000IRQ(void);
void reset_DW1000(void);

#endif
