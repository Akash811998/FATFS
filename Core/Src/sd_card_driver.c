
#include <sd_card_driver.h>
#include "diskio.h" //some functions are implemented using the weak attributes and we will initialise those API's here


extern SPI_HandleTypeDef hspi1;

//variables
extern volatile uint8_t g_fatfs_cnt;
volatile uint16_t g_timer_cnt1;
static volatile DSTATUS g_disk_stat = STA_NODISK;

static uint8_t g_power_flg=0;
/*Card Type MMC=0, SDC=1 */
static uint8_t g_card_type;


//Useful MACROS
#define SD_CARD_SPI_HANDLE &hspi1
#define SD_SPI_TIMEOUT 10
#define SD_WAKEUP_CMD 0x00

#define CMD_PACKET_SZ 	6

volatile uint16_t g_timer_cnt2;

void fatfs_tmr_callback(void)
{
	if(g_timer_cnt1 > 0)
		g_timer_cnt1--;
	if(g_timer_cnt2>0)
		g_timer_cnt2--;
}


/*Slave Select
 */
static void slave_select(void)
{
	cs_pin_reset();
	HAL_Delay(1);
}


/*Slave Deselect
 */
static void slave_deselect(void)
{
	cs_pin_set();
	HAL_Delay(1);
}

static void sd_spi_tx_byte(uint8_t data)
{
	//Wait for TXE flag to be set
	while(!(__HAL_SPI_GET_FLAG(SD_CARD_SPI_HANDLE, SPI_FLAG_TXE ))){}

	//Transmit byte
	HAL_SPI_Transmit(SD_CARD_SPI_HANDLE, data, 1,SD_SPI_TIMEOUT );

}

static void sd_spi_tx_buffer(uint8_t *buffer, uint32_t len)
{
	//Wait for TXE flag to be set
	while(!(__HAL_SPI_GET_FLAG(SD_CARD_SPI_HANDLE, SPI_FLAG_TXE ))){}

	//Transmit byte
	HAL_SPI_Transmit(SD_CARD_SPI_HANDLE, &buffer, len, SD_SPI_TIMEOUT );
}

static uint8_t sd_spi_rx_byte()
{
	uint8_t temp;
	uint8_t rcv_data;

	temp= 0xFF;

	//Wait for TXE flag to be set
	while(!(__HAL_SPI_GET_FLAG(SD_CARD_SPI_HANDLE, SPI_FLAG_TXE ))){}

	//Transmit byte
	HAL_SPI_Transmit(SD_CARD_SPI_HANDLE, temp, 1,SD_SPI_TIMEOUT );

	//Receive byte
	HAL_SPI_Receive(&hspi1, &rcv_data, 1, SD_SPI_TIMEOUT);

	return rcv_data;
}

static uint8_t sd_spi_rx_byte_ptr(uint8_t *buff)
{
	*buff =  sd_spi_rx_byte();
}

static void sd_pwr_on(void)
{
	//array to hold each command packet which is of 6 bytes
	uint8_t cmd_packet[CMD_PACKET_SZ];

	uint32_t cnt=1000;

	//deselect slave
	slave_deselect();

	//Transmit byte to wakeup
	for(int i=0; i<10 ; i++)
	{
		sd_spi_tx_byte(SD_WAKEUP_CMD);
	}

	////select slave
	slave_select();

	//prepare cmd packet
	cmd_packet[0]=CMD0; //Start bit + Transmision + Command bit pattern
	cmd_packet[1]=0;  //Start bit + Transmision + Command bit pattern
	cmd_packet[2]=0;  //argument
	cmd_packet[3]=0;	//argument
	cmd_packet[4]=0;	//argument
	cmd_packet[5]=CMD0_CRC;  //CRC + End bit

	//Transmit the buffer
	sd_spi_tx_buffer(cmd_packet, sizeof(cmd_packet));

	//Wait for response till you receive a R1 response of 0x01 which says that the card has gone to Idle state
	while((sd_spi_rx_byte() != R1_IDLE_STATE_RESP) && cnt)
	{
		cnt--;
	}

	//deselect slave
	slave_deselect();

	//Set power flah
	g_power_flg=1;
}


//Power off
static void sd_pwr_off(void)
{
	g_power_flg=0;
}

//Get power
static void sd_get_pwr_flag(void)
{
	return g_power_flg;
}


//Wait for SD card to be ready
static uint8_t sd_rdy_wait(void)
{
	uint8_t res;

	//Timeout of 500ms
	g_timer_cnt2=50; //  fatfs_tmr_callback() executes every 10ms. Refer to systick_handler()

	//0xFF is received when SD card is ready
	do
	{
		res= sd_spi_rx_byte();
	}while((res != SD_RDY_FLAG) && g_timer_cnt2);

	return res;
}

//Receive data in bulk
static bool sd_spi_rx_data_bulk(uint8_t* buff, uint32_t len)
{
	uint8_t flg;

	//Timeout of 200ms
	g_timer_cnt1=20; //  fatfs_tmr_callback() executes every 10ms. Refer to systick_handler()

	//0xFF is received when SD card is ready
	do
	{
		flg= sd_spi_rx_byte();
	}while((flg != SD_RDY_FLAG) && g_timer_cnt1);

	do
	{
		sd_spi_rx_byte_ptr(buff++);
	}while(len--);

	//discard CRC
	sd_spi_rx_byte();
	sd_spi_rx_byte();

	return 1;
}


//Transmit data blocks

static bool sd_spi_tx_data_bulk(const uint8_t* buff, uint8_t flg)
{
	uint8_t itr=0;
	uint8_t resp;

	//Check if SD is ready
	if(sd_rdy_wait() != SD_RDY_FLAG)
	{
		return 0;
	}

	//Transmit flag
	sd_spi_tx_byte(flg);

	//If flg is not stop flah then transmit data
	if(flg != SD_STOP_FLAG)
	{
		sd_spi_tx_buffer((uint8_t*)buff, 512); //512 byte sector

		//discard CRC
		sd_spi_rx_byte();
		sd_spi_rx_byte();

		//receive responses
		while(itr <= 50)
		{
			resp= sd_spi_rx_byte();
			if((resp & 0x1f) == 0x05)  //Why 0x05
				break;

			itr++;

		}
		while(sd_spi_rx_byte() == 0){}
	}
	if((resp & 0x1f) == 0x05)
	{
		return 1;
	}

	return 0;
}

static uint8_t sd_send_cmd(uint8_t cmd, uint32_t arg)
{
	uint8_t crc;
	uint8_t res;

	uint8_t cnt=10;

	/*Check for SD Ready*/
	if(sd_rdy_wait() != SD_RDY_FLAG)
	{
	    return 0xFF;
	}

	/*Transmit command*/
	sd_spi_tx_byte(cmd);

	/*Transmit Arguments*/
	sd_spi_tx_byte((uint8_t)(arg >> 24)); /* Argument[31..24] */
	sd_spi_tx_byte((uint8_t)(arg >> 16)); /* Argument[23..16] */
	sd_spi_tx_byte((uint8_t)(arg >> 8)); /* Argument[15..8] */
	sd_spi_tx_byte((uint8_t)(arg));      /* Argument[7..0] */

	/*Prepare CRC*/
	if(cmd == CMD0)
	{
	    crc = CMD0_CRC;
	}
	else if(cmd == CMD8)
	{
	    crc = CMD8_CRC;
	}
	else
	{
		crc=1;
	}
	/*Transmit crc*/
	sd_spi_tx_byte(crc);

	/*Check for STOP_TRANSMISSION command*/
	/*Skip stuff byte*/
	if(cmd == CMD12)
	{
	    sd_spi_rx_byte();
	}

	/*Receive response*/
	do{
	    res = sd_spi_rx_byte();
	}while((res & 0x80) && --cnt);

	return res;
}

