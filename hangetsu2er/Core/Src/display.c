#include "display.h"

static inline void HT1622_Delay(void)
{
    for (volatile uint16_t i = 0; i < 20; i++);
}

void HT1622_Init(HT1622_HandleTypeDef *ht,
                 GPIO_TypeDef *dat_port, uint16_t dat_pin,
                 GPIO_TypeDef *wr_port,  uint16_t wr_pin,
                 GPIO_TypeDef *rd_port,  uint16_t rd_pin,
                 GPIO_TypeDef *cs_port,  uint16_t cs_pin)
{
    ht->_dat_port = dat_port;
    ht->_dat_pin  = dat_pin;

    ht->_wr_port  = wr_port;
    ht->_wr_pin   = wr_pin;

    ht->_rd_port  = rd_port;
    ht->_rd_pin   = rd_pin;

    ht->_cs_port  = cs_port;
    ht->_cs_pin   = cs_pin;

    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 1);
    HAL_GPIO_WritePin(ht->_wr_port, ht->_wr_pin, 1);
    HAL_GPIO_WritePin(ht->_rd_port, ht->_rd_pin, 1);
}

void HT1622_WriteBit(HT1622_HandleTypeDef *ht, uint8_t bit)
{
    HAL_GPIO_WritePin(ht->_dat_port, ht->_dat_pin,
                      bit ? 1 : 0);

    HT1622_Delay();

    HAL_GPIO_WritePin(ht->_wr_port, ht->_wr_pin, 0);
    HT1622_Delay();
    HAL_GPIO_WritePin(ht->_wr_port, ht->_wr_pin, 1);
}

void HT1622_WriteBits(HT1622_HandleTypeDef *ht, uint16_t data, uint8_t bits)
{
    for (uint8_t i = 0; i < bits; i++)
    {
        HT1622_WriteBit(ht, data & 0x01);
        data = data >> 1;
    }
}

void HT1622_SendCommand(HT1622_HandleTypeDef *ht, uint8_t cmd)
{
    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 0);

    HT1622_WriteBits(ht, 0b100, 3);

    HT1622_WriteBits(ht, cmd, 8);

    HT1622_WriteBit(ht, 0);

    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 1);
}
