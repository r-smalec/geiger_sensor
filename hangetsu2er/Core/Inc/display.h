#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "stm32f031x6.h"

#define CMD_SYS_DIS     0x00  // SYS DIS    (0000-0000-X) Turn off both system oscillator and LCD bias generator [Yes Default]
#define CMD_SYS_EN      0x01  // SYS EN     (0000-0001-X) Turn on system oscillator
#define CMD_LCD_OFF     0x02  // LCD OFF    (0000-0010-X) Turn off LCD display [Yes Default]
#define CMD_LCD_ON      0x03  // LCD ON     (0000-0011-X) Turn on LCD display
#define CMD_TIMER_DIS   0x04  // TIMER DIS  (0000-0100-X) Disable time base output [Yes Default]
#define CMD_WDT_DIS     0x05  // WDT DIS    (0000-0101-X) Disable WDT time-out flag output [Yes Default]
#define CMD_TIMER_EN    0x06  // TIMER EN   (0000-0110-X) Enable time base output
#define CMD_WDT_EN      0x07  // WDT EN     (0000-0111-X) Enable WDT time-out flag output
#define CMD_TONE_OFF    0x08  // TONE OFF   (0000-1000-X) Turn off tone outputs Turn on tone outputs [Yes Default]
#define CMD_CLR_TIMER   0x0D  // CLR TIMER  (0000-1101-X) Clear the contents of the time base generator
#define CMD_CLR_WDT     0x0F  // CLR WDT    (0000-1111-X) Clear the contents of WDT stage
#define CMD_RC_32K      0x18  // RC 32K     (0001-10XX-X) System clock source, on-chip RC oscillator [Yes Default]
#define CMD_EXT_32K     0x1C  // EXT 32K    (0001-11XX-X) System clock source, external clock source
#define CMD_TONE_4K     0x40  // TONE 4K    (010X-XXXX-X) Tone frequency output: 4kHz
#define CMD_TONE_2K     0x60  // TONE 2K    (0110-XXXX-X) Tone frequency output: 2kHz
#define CMD_IRQ_DIS     0x80  // IRQ DIS    (100X-0XXX-X) Disable IRQ output [Yes Default]
#define CMD_IRQ_EN      0x88  // IRQ EN     (100X-1XXX-X) Enable IRQ output

#define CMD_F1          0xA0  // F1         (101X-0000-X) Time base clock output: 1Hz   The WDT time-out flag after: 4s
#define CMD_F2          0xA1  // F2         (101X-0001-X) Time base clock output: 2Hz   The WDT time-out flag after: 2s
#define CMD_F4          0xA2  // F4         (101X-0010-X) Time base clock output: 4Hz   The WDT time-out flag after: 1s
#define CMD_F8          0xA3  // F8         (101X-0011-X) Time base clock output: 8Hz   The WDT time-out flag after: 1/2s
#define CMD_F16         0xA4  // F16        (101X-0100-X) Time base clock output: 16Hz  The WDT time-out flag after: 1/4s
#define CMD_F32         0xA5  // F32        (101X-0101-X) Time base clock output: 32Hz  The WDT time-out flag after: 1/8s
#define CMD_F64         0xA6  // F64        (101X-0110-X) Time base clock output: 64Hz  The WDT time-out flag after: 1/16s
#define CMD_F128        0xA7  // F128       (101X-0111-X) Time base clock output: 128Hz The WDT time-out flag after: 1/32s [Yes Default]
#define CMD_TEST        0xE0  // TEST       (1110-0000-X) Test mode, user don't use.
#define CMD_NORMAL      0xE3  // NORMAL     (1110-0011-X) Normal mode [Yes Default]

#define SEG0_0   0x00
#define SEG0_4   0x01
#define SEG1_0   0x02
#define SEG1_4   0x03
#define SEG2_0   0x04
#define SEG2_4   0x05
#define SEG3_0   0x06
#define SEG3_4   0x07
#define SEG4_0   0x08
#define SEG4_4   0x09
#define SEG5_0   0x0A
#define SEG5_4   0x0B
#define SEG6_0   0x0C
#define SEG6_4   0x0D
#define SEG7_0   0x0E
#define SEG7_4   0x0F
#define SEG8_0   0x10
#define SEG8_4   0x11
#define SEG9_0   0x12
#define SEG9_4   0x13
#define SEG10_0  0x14
#define SEG10_4  0x15
#define SEG11_0  0x16
#define SEG11_4  0x17
#define SEG12_0  0x18
#define SEG12_4  0x19
#define SEG13_0  0x1A
#define SEG13_4  0x1B
#define SEG14_0  0x1C
#define SEG14_4  0x1D
#define SEG15_0  0x1E
#define SEG15_4  0x1F
#define SEG16_0  0x20
#define SEG16_4  0x21
#define SEG17_0  0x22
#define SEG17_4  0x23

#define SEG_NO 18

typedef struct {

    GPIO_TypeDef *_dat_port;
    uint16_t      _dat_pin;

    GPIO_TypeDef *_wr_port;
    uint16_t      _wr_pin;

    GPIO_TypeDef *_rd_port;
    uint16_t      _rd_pin;

    GPIO_TypeDef *_cs_port;
    uint16_t      _cs_pin;
    
} HT1622_HandleTypeDef;

uint8_t seg_data[SEG_NO * 2]; // twice number cause each segment is split into two subsegments

void HT1622_Init(HT1622_HandleTypeDef *ht,
                 GPIO_TypeDef *dat_port, uint16_t dat_pin,
                 GPIO_TypeDef *wr_port,  uint16_t wr_pin,
                 GPIO_TypeDef *rd_port,  uint16_t rd_pin,
                 GPIO_TypeDef *cs_port,  uint16_t cs_pin);

void HT1622_Config(HT1622_HandleTypeDef *ht);

void HT1622_WriteBit(HT1622_HandleTypeDef *ht, uint8_t bit);
void HT1622_WriteBits(HT1622_HandleTypeDef *ht, uint16_t data, uint8_t bits);
void HT1622_SendCommand(HT1622_HandleTypeDef *ht, uint8_t cmd);
void HT1622_WriteData(HT1622_HandleTypeDef *ht, uint8_t addr, uint8_t data);
void HT1622_WriteAllData(HT1622_HandleTypeDef *ht);

#endif
