#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "stm32f031x6.h"

typedef struct
{
    GPIO_TypeDef *_dat_port;
    uint16_t      _dat_pin;

    GPIO_TypeDef *_wr_port;
    uint16_t      _wr_pin;

    GPIO_TypeDef *_rd_port;
    uint16_t      _rd_pin;

    GPIO_TypeDef *_cs_port;
    uint16_t      _cs_pin;
} HT1622_HandleTypeDef;

void HT1622_Init(HT1622_HandleTypeDef *ht,
                 GPIO_TypeDef *dat_port, uint16_t dat_pin,
                 GPIO_TypeDef *wr_port,  uint16_t wr_pin,
                 GPIO_TypeDef *rd_port,  uint16_t rd_pin,
                 GPIO_TypeDef *cs_port,  uint16_t cs_pin);

void HT1622_WriteBit(HT1622_HandleTypeDef *ht, uint8_t bit);
void HT1622_WriteBits(HT1622_HandleTypeDef *ht, uint16_t data, uint8_t bits);
void HT1622_SendCommand(HT1622_HandleTypeDef *ht, uint8_t cmd);

#endif
