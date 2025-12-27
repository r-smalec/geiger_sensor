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

    for(int i = 0; i < SEG_NO; i++) {
        seg_data[i] = 0x0F;
    }

    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 1);
    HAL_GPIO_WritePin(ht->_wr_port, ht->_wr_pin, 1);
    HAL_GPIO_WritePin(ht->_rd_port, ht->_rd_pin, 1);
}

void HT1622_Config(HT1622_HandleTypeDef *ht) {

	HAL_Delay(10);
	HT1622_SendCommand(ht, CMD_SYS_EN);

    HAL_Delay(10);
    HT1622_SendCommand(ht, CMD_LCD_ON);
}

void HT1622_WriteBit(HT1622_HandleTypeDef *ht, uint8_t bit) {


	HT1622_Delay();
	HAL_GPIO_WritePin(ht->_wr_port, ht->_wr_pin, 0);

	HAL_GPIO_WritePin(ht->_dat_port, ht->_dat_pin,
                      bit ? 1 : 0);

    HT1622_Delay();
    HAL_GPIO_WritePin(ht->_wr_port, ht->_wr_pin, 1);
}

void HT1622_WriteBits(HT1622_HandleTypeDef *ht, uint16_t data, uint8_t bits) {

    for (int8_t i = bits - 1; i >= 0; i--) {
        HT1622_WriteBit(ht, (data >> i) & 0x01);
    }
}

void HT1622_SendCommand(HT1622_HandleTypeDef *ht, uint8_t cmd) {

    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 0);

    HT1622_WriteBits(ht, 0b100, 3);

    HT1622_WriteBits(ht, cmd, 8);

    HT1622_WriteBit(ht, 0);

    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 1);
}

void HT1622_WriteData(HT1622_HandleTypeDef *ht, uint8_t addr, uint8_t data) {

    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 0);

    HT1622_WriteBits(ht, 0b101, 3);

    HT1622_WriteBits(ht, (addr & 0x3F), 6);

    HT1622_WriteBits(ht, (data & 0x0F), 4);

    HAL_GPIO_WritePin(ht->_cs_port, ht->_cs_pin, 1);
}

void HT1622_WriteAllData(HT1622_HandleTypeDef *ht) {
    for(uint8_t i = 0; i < SEG_NO * 2; i++) {
        HT1622_WriteData(ht, i, seg_data[i]);
        HAL_Delay(50);
    }
}

void Display_7Seg_Upper(HT1622_HandleTypeDef *ht, uint8_t col, uint8_t digit) {
    uint8_t addr;
    switch(col) {
        case 1:
            addr = SEG0_0;
            break;
        case 2:
            addr = SEG1_0;
            break;
        case 3:
            addr = SEG2_0;
            break;
        case 4:
            addr = SEG3_0;
            break;
    }

    uint8_t tmp = seg_data[addr] & 0x01; // 1st bit is COL
    
    switch(digit) {
        case 0: seg_data[addr] = 0b1110; // ECDx
                seg_data[addr + 1] = 0b1110; // AFBG
                break;
        case 1: seg_data[addr] = 0b0100;
                seg_data[addr + 1] = 0b0010;
                break;
        case 2: seg_data[addr] = 0b1010;
                seg_data[addr + 1] = 0b1011;
                break;
        case 3: seg_data[addr] = 0b0110;
                seg_data[addr + 1] = 0b1011;
                break;
        case 4: seg_data[addr] = 0b0100;
                seg_data[addr + 1] = 0b0111;
                break;
        case 5: seg_data[addr] = 0b0110;
                seg_data[addr + 1] = 0b1101;
                break;
        case 6: seg_data[addr] = 0b1110;
                seg_data[addr + 1] = 0b1101;
                break;
        case 7: seg_data[addr] = 0b0100;
                seg_data[addr + 1] = 0b1010;
                break;
        case 8: seg_data[addr] = 0b0000;
                seg_data[addr + 1] = 0b0000;
                break;
        case 9: seg_data[addr] = 0b0000;
                seg_data[addr + 1] = 0b0000;
                break;
        default: break;
    }

    seg_data[addr] |= tmp;

    HT1622_WriteData(ht, addr,          (seg_data[addr]     & 0x0F));
    HT1622_WriteData(ht, (addr + 1),    (seg_data[addr + 1] & 0x0F));
}
