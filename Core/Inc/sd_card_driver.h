#ifndef __SD_CARD_DRIVER_H__
#define __SD_CARD_DRIVER_H__


#include <sd_card_spi.h>


void fatfs_tmr_callback(void);
static void slave_deselect(void);
static void slave_select(void);
static void sd_spi_tx_byte(uint8_t data);
static void sd_spi_tx_buffer(uint8_t *buffer, uint32_t len);

static uint8_t sd_spi_rx_byte();
static uint8_t sd_spi_rx_byte_ptr(uint8_t *buff);
static void sd_spi_rx_buffer(uint8_t data);

static void sd_pwr_on(void);

static void sd_pwr_off(void);
static void sd_get_pwr_flag(void);

//command maccros

#define CMD0 (0x40+0) /*GO_IDLE_STATE*/
#define CMD1 (0x40+1) /*SEND_OP_COND*/
#define CMD8 (0x40+8) /*SEND_IF_COND*/
#define CMD9 (0x40+9) /*SEND_CSD*/
#define CMD10 (0x40+10) /*SEND_CID*/
#define CMD12 (0x40+12) /*STOP_TRANSMISSION*/
#define CMD16 (0x40+16) /*SET_BLOCKLEN*/
#define CMD17 (0x40+17) /*READ_SINGLE_BLOCK*/
#define CMD18 (0x40+18) /*READ_MULTIPLE_BLOCK*/
#define CMD23 (0x40+23) /*SET_BLOCK_COUNT*/
#define CMD24 (0x40+24) /*WRITE_BLOCK*/
#define CMD25 (0x40+25) /*WRITE_MULTIPLE_BLOCK*/
#define CMD41 (0x40+41) /*SEND_OP_COND (ACMD)*/
#define CMD55 (0x40+55) /*APP_CMD*/
#define CMD58 (0x40+58) /*READ_OCR*/

#define CMD0_CRC (0x95) //FOR CMD0 THE CRC SHOULD ALWAYS BE 0X95
#define CMD8_CRC (0x87)  //FOR CMD8 THE CRC SHOULD ALWAYS BE 0X87


//Look at the Response format in notes
#define R1_IDLE_STATE_RESP 0x01


#define SD_RDY_FLAG 0xFF
#define SD_STOP_FLAG 0xFD

/*MMC Card Type*/
#define CT_MMC 0x01 /*MMC ver 3*/
#define CT_SD1 0x02 /*sd ver 1*/
#define CT_SD2 0x04 /*sd ver 2*/
#define CT_SDC 0x06 /*sd*/
#define CT_BLOCK 0x08 /*Block Addressing*/

#endif
