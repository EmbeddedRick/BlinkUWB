#ifndef DECA_SPI_H_
#define DECA_SPI_H_ 

#include "port.h"
#include "deca_types.h"

void print_buffer(uint32 readlength, uint8 *readBuffer);

int readfromspi(uint16 headerLength, const uint8 *headerBuffer, 
                uint32 readlength, uint8 *readBuffer);

int writetospi(uint16 headerLength, const uint8 *headerBuffer, 
               uint32 bodylength, const uint8 *bodyBuffer);

#endif