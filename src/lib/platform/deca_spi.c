#include <deca_spi.h>
#include <deca_device_api.h>
#include <port.h>

void print_buffer(uint32 readlength, uint8 *readBuffer){
    int j = 0;
    printf("Payload is: ");
    for(int loop = readlength; loop > 0; loop--){
        j = (j << 8) | readBuffer[loop];
    } 
    printf("0x%.8X \t\n", j);
}

/*! ----------------------------------------------------------------------------------------------------------
 * Function: writetospi()
 *
 * Low level abstract function to write to the SPI
 * Takes two separate byte buffers for write header and write data
 * returns 0 for success, or -1 for error
 */
#pragma GCC optimize ("O3")
int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer)
{
    uint8 * p1;
    uint32 idatalength=0;

    idatalength= headerLength + bodylength;

    uint8 idatabuf[idatalength];
    uint8 itempbuf[idatalength];

    memset(idatabuf, 0, idatalength);
    memset(itempbuf, 0, idatalength);		 
    
    p1=idatabuf;	
    memcpy(p1,headerBuffer, headerLength);
    p1 += headerLength;
    memcpy(p1,bodyBuffer,bodylength);

    spi_xfer_done = false;

    nrfx_spim_xfer_desc_t xfer_desc = NRFX_SPIM_XFER_TRX(idatabuf, idatalength, itempbuf, idatalength);
    nrf_gpio_pin_clear(DW1000_CS);
    nrfx_err_t err_code = nrfx_spim_xfer(&spim, &xfer_desc, 0);
    if (err_code != NRFX_SUCCESS) {
        // Handle transfer error
        nrfx_spim_uninit(&spim);
        printf("ERROR TRANSMITING DATA\t\n");
        return err_code;
    }
    // Tal vez poner un while de espera
    //printf("DATA TRANSMITED\t\n");
    deca_sleep(10);
    //while(!spi_xfer_done);
    nrf_gpio_pin_set(DW1000_CS);
    return 0;
}

/*! ---------------------------------------------------------------------------------------------------------
 * Function: readfromspi()
 *
 * Low level abstract function to read from the SPI
 * Takes two separate byte buffers for write header and read data
 * returns the offset into read buffer where first byte of read data may be found,
 * or returns -1 if there was an error
 */
#pragma GCC optimize ("O3")
int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer)
{
    uint8 * p1;
    uint32 idatalength=0;

    idatalength= headerLength + readlength;

    uint8 idatabuf[idatalength];
    uint8 itempbuf[idatalength];

    memset(idatabuf, 0, idatalength);
    memset(itempbuf, 0, idatalength);	

    p1=idatabuf;	
    memcpy(p1,headerBuffer, headerLength);

    p1 += headerLength;
    memset(p1,0x00,readlength);

    spi_xfer_done = false;

    nrfx_spim_xfer_desc_t xfer_desc = NRFX_SPIM_XFER_TRX(idatabuf, idatalength, itempbuf, idatalength);
    nrf_gpio_pin_clear(DW1000_CS);
    nrfx_err_t err_code = nrfx_spim_xfer(&spim, &xfer_desc, 0);
    if (err_code != NRFX_SUCCESS) {
        // Handle transfer error
        nrfx_spim_uninit(&spim);
        printf("ERROR READING DATA\t\n");
        return err_code;
    }
    // Tal vez poner un while de espera
    //printf("DATA READ\t\n");
    deca_sleep(10);
    print_buffer(readlength, itempbuf);
    //while(!spi_xfer_done);
    nrf_gpio_pin_set(DW1000_CS);
    
    p1=itempbuf + headerLength;
    memcpy(readBuffer, p1, readlength);
    return 0;
}