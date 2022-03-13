#include "stdint.h"
#include <string.h>
#include "can.h"
#include "stm32f4xx_hal_cortex.h"
#include "usart.h"
#include "protocol.h"
#include "pid.h"
#include "tim.h"

extern PID_TypeDef motor_pid[4];
extern UART_HandleTypeDef huart2;
extern float set_point;

struct prot_frame_parser_t
{  
 uint8_t *recv_ptr;
 uint16_t r_oft;
 uint16_t w_oft;
 uint16_t frame_len;
 uint16_t found_frame_head;
};

static struct prot_frame_parser_t parser;
static uint8_t recv_buf[PROT_FRAME_LEN_RECV];


static int32_t recvbuf_find_header(uint8_t *buf, uint16_t ring_buf_len, uint16_t start, uint16_t len)
{
	uint16_t i = 0;
	for (i = 0; i < (len - 3); i++)
	{
		if (((buf[(start + i + 0) % ring_buf_len] << 0) |
				(buf[(start + i + 1) % ring_buf_len] << 8) |
				(buf[(start + i + 2) % ring_buf_len] << 16) |
				(buf[(start + i + 3) % ring_buf_len] << 24)) == FRAME_HEADER)
			{
				return ((start + i) % ring_buf_len);
			}
	}
 return -1;
}


static int32_t recvbuf_get_len_to_parse(uint16_t frame_len, uint16_t ring_buf_len,uint16_t start, uint16_t end)
{
	uint16_t unparsed_data_len = 0;
	if (start <= end)
		unparsed_data_len = end - start;
	else
		unparsed_data_len = ring_buf_len - start + end;

	if (frame_len > unparsed_data_len)
		return 0;
	else
		return unparsed_data_len;
}



 
 int32_t protocol_init(void)
 {
 memset(&parser, 0, sizeof(struct prot_frame_parser_t));

 parser.recv_ptr = recv_buf;

 return 0;
 }

 
 
 uint8_t check_sum(uint8_t init, uint8_t *ptr, uint8_t len)
 {
	 uint8_t sum = init;
	 while(len--)
	 {
		 sum += *ptr;
		 ptr++;
	 }
	 return sum;
 }
 
 
 static uint8_t get_frame_type(uint8_t *frame, uint16_t head_oft)
{ 
	return (frame[(head_oft + CMD_INDEX_VAL) % PROT_FRAME_LEN_RECV] & 0xFF);
}


 static uint8_t get_frame_checksum(uint8_t *frame, uint16_t head_oft, uint16_t frame_len)
{ 
	return (frame[(head_oft + frame_len - 1) % PROT_FRAME_LEN_RECV]);
}

 
 static uint16_t get_frame_len(uint8_t *frame, uint16_t head_oft)
{
	return ((frame[(head_oft + LEN_INDEX_VAL + 0) % PROT_FRAME_LEN_RECV] << 0) |
					(frame[(head_oft + LEN_INDEX_VAL + 1) % PROT_FRAME_LEN_RECV] << 8) |
					(frame[(head_oft + LEN_INDEX_VAL + 2) % PROT_FRAME_LEN_RECV] << 16) |
					(frame[(head_oft + LEN_INDEX_VAL + 3) % PROT_FRAME_LEN_RECV] << 24));
}
 
 

 

static uint8_t protocol_frame_parse(uint8_t *data, uint16_t *data_len)
{  
	uint8_t frame_type = CMD_NONE;
  uint16_t need_to_parse_len = 0;
  int16_t header_oft = -1;
  uint8_t checksum = 0;
	
	need_to_parse_len = recvbuf_get_len_to_parse(parser.frame_len, PROT_FRAME_LEN_RECV, parser.r_oft, parser.w_oft);
	if (need_to_parse_len < 9)
		return frame_type;
	if (0 == parser.found_frame_head)
	{
		header_oft = recvbuf_find_header(parser.recv_ptr, PROT_FRAME_LEN_RECV,parser.r_oft, need_to_parse_len);
  if (0 <= header_oft)
	{
		parser.found_frame_head = 1;
	  parser.r_oft = header_oft;
		if (recvbuf_get_len_to_parse(parser.frame_len, PROT_FRAME_LEN_RECV, parser.r_oft, parser.w_oft) < 9)
		return frame_type;
	}
  else
 {
	 parser.r_oft = ((parser.r_oft + need_to_parse_len - 3) % PROT_FRAME_LEN_RECV);
	 return frame_type;
 }
 }
	if (0 == parser.frame_len)
{
 parser.frame_len = get_frame_len(parser.recv_ptr, parser.r_oft);
 if(need_to_parse_len < parser.frame_len)
 return frame_type;
}
if ((parser.frame_len + parser.r_oft - PROT_FRAME_LEN_CHECKSUM) > PROT_FRAME_LEN_RECV)
{
 checksum = check_sum(checksum, parser.recv_ptr + parser.r_oft, PROT_FRAME_LEN_RECV - parser.r_oft);
 checksum = check_sum(checksum, parser.recv_ptr, parser.frame_len - PROT_FRAME_LEN_CHECKSUM + parser.r_oft - PROT_FRAME_LEN_RECV);
}
else
{
checksum = check_sum(checksum, parser.recv_ptr + parser.r_oft, parser.frame_len - PROT_FRAME_LEN_CHECKSUM);
}
if (checksum == get_frame_checksum(parser.recv_ptr, parser.r_oft, parser.frame_len))
{
	if ((parser.r_oft + parser.frame_len) > PROT_FRAME_LEN_RECV)
	{
		uint16_t data_len_part = PROT_FRAME_LEN_RECV - parser.r_oft;
		memcpy(data, parser.recv_ptr + parser.r_oft, data_len_part);
		memcpy(data + data_len_part, parser.recv_ptr, parser.frame_len - data_len_part);
	}
	else
	{
		memcpy(data, parser.recv_ptr + parser.r_oft, parser.frame_len);
  }
 *data_len = parser.frame_len;
 frame_type = get_frame_type(parser.recv_ptr, parser.r_oft);

 parser.r_oft = (parser.r_oft + parser.frame_len) % PROT_FRAME_LEN_RECV;
}
else
{
	parser.r_oft = (parser.r_oft + 1) % PROT_FRAME_LEN_RECV;
}
 parser.frame_len = 0;
 parser.found_frame_head = 0;

 return frame_type;
}
 







static void recvbuf_put_data(uint8_t *buf, uint16_t ring_buf_len, uint16_t w_oft, uint8_t *data, uint16_t data_len)
{
	if((w_oft + data_len) >ring_buf_len)
	{
		uint16_t data_len_part = ring_buf_len - w_oft;
		memcpy(buf + w_oft, data, data_len_part);
		memcpy(buf, data + data_len_part, data_len - data_len_part);
	}
	else
		memcpy(buf + w_oft, data, data_len);
}
		
	
void protocol_data_recv(uint8_t *data, uint16_t data_len)
{ 
	recvbuf_put_data(parser.recv_ptr, PROT_FRAME_LEN_RECV, parser.w_oft, data, data_len);
	parser.w_oft = (parser.w_oft + data_len) % PROT_FRAME_LEN_RECV;
}






int8_t receiving_process(void) 
{  
	uint8_t frame_data[128]; 
	uint16_t frame_len = 0;
	uint8_t cmd_type = CMD_NONE;

 while(1)
 {
 cmd_type = protocol_frame_parse(frame_data, &frame_len);
 switch (cmd_type)
 {
 case CMD_NONE:
 {
 return -1;
 }

 case SET_P_I_D_CMD:
 {
 uint32_t temp0 = COMPOUND_32BIT(&frame_data[13]);
 uint32_t temp1 = COMPOUND_32BIT(&frame_data[17]);
 uint32_t temp2 = COMPOUND_32BIT(&frame_data[21]);

 float p_temp, i_temp, d_temp;

 p_temp = *(float *)&temp0;
 i_temp = *(float *)&temp1;
 d_temp = *(float *)&temp2;
	 for (int i = 0; i<4;i++)
	 {
			motor_pid[i].f_pid_reset(&motor_pid[i], p_temp, i_temp, d_temp); //  SET P\I\D !?
	 }
 }
 break;
 
	case SET_TARGET_CMD:
 {
 int actual_temp = COMPOUND_32BIT(&frame_data[13]); // get data

 set_point = (actual_temp); // set point
 }
 break;

 case START_CMD:
 {
// set_motor_enable(); //
 }
 break;

 case STOP_CMD:
 {
// set_motor_disable(); //
 }
 break;

 case RESET_CMD:
 {
 HAL_NVIC_SystemReset(); //
 }
 break;

 case SET_PERIOD_CMD:
 {
 uint32_t temp = COMPOUND_32BIT(&frame_data[13]);
 htim1.Init.Period = temp;
 }
break;

 default:
 return -1;
 }
 }
 }


 
void set_computer_value(uint8_t cmd, uint8_t ch, void *data, uint8_t num)
{
uint8_t sum = 0; 
num *= 4;
static packet_head_t set_packet;
set_packet.head = FRAME_HEADER;
set_packet.len = 0x0B + num;
set_packet.ch = ch;
set_packet.cmd = cmd;
	
sum = check_sum(0, (uint8_t *)&set_packet, sizeof(set_packet));
sum = check_sum(sum, (uint8_t *)data, num);
HAL_UART_Transmit(&huart2, (uint8_t *)&set_packet, sizeof(set_packet), 0xFFFFF);
HAL_UART_Transmit(&huart2, (uint8_t *)data, num, 0xFFFFF);
HAL_UART_Transmit(&huart2, (uint8_t *)&sum, sizeof(sum), 0xFFFFF);
}

 

