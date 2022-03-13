 #include "stdint.h"
 #include "stm32f4xx.h"
																
 #define PROT_FRAME_LEN_RECV 128
 #define PROT_FRAME_LEN_CHECKSUM 1
 
 typedef __packed struct 
 {
	 uint32_t head;
	 uint8_t ch;
	 uint32_t len;
	 uint8_t cmd;
 }packet_head_t;
 
 #define FRAME_HEADER   0x59485A53
 
 
 // Channel
 #define CURVES_CH1   0x01
 #define CURVES_CH2   0x02
 #define CURVES_CH3   0x03
 #define CURVES_CH4   0x04
 #define CURVES_CH5   0x05
 
 
 //CMD	(LOW->HIGH)
  #define SEND_TARGET_CMD   0x01
  #define SEND_FACT_CMD     0x02
  #define SEND_P_I_D_CMD    0x03
  #define SEND_START_CMD    0x04
  #define SEND_STOP_CMD     0x05
  #define SEND_PERIOD_CMD   0x06
 
  
 //CMD	(HIGH->LOW)
  #define SET_P_I_D_CMD    0x10
  #define SET_TARGET_CMD   0x11
  #define START_CMD        0x12
  #define STOP_CMD         0x13
	#define RESET_CMD        0x14
  #define SET_PERIOD_CMD   0x15
 
 #define CMD_NONE 0xFF

#define CMD_INDEX_VAL	0x9u
#define LEN_INDEX_VAL	0x5u
#define CHX_INDEX_VAL	0x4u
#define HEAD_INDEX_VAL	0x3u

#define EXCHANGE_H_L_BIT(data)  ((((data)<<24) & 0xFF000000)|\
																 (((data)<< 8) & 0x00FF0000)|\
																 (((data)>> 8) & 0x0000FF00)|\
																 (((data)>>24) & 0x000000FF))
				
				
 #define COMPOUND_32BIT(data)	(((*(data-0)<<24) & 0xFF000000)|\
															 ((*(data-1)<<16) & 0x00FF0000)|\
															 ((*(data-2)<< 8) & 0x0000FF00)|\
															 ((*(data-3)<< 0) & 0x000000FF))			//compound to one data

 
 /**
 * @brief Receive data deal
 * @param *data: related array
 * @param data_len: array size
 * @return void.
 */
 void protocol_data_recv(uint8_t *data, uint16_t data_len);
 
 
 
 
 /**
 * @brief Initialization
 * @param void
 * @return Initialization result
 */
 int32_t protocol_init(void);



 /**
 *@brief???????
 *@paramvoid
 *@return-1:???????????.*/
int8_t receiving_process(void);




/**
*@brief???????
*@paramcmd:??
*@paramch:????
*@paramdata:????
*@paramnum:????
*@retval?
*/
void set_computer_value(uint8_t cmd,uint8_t ch,void*data,uint8_t num);
