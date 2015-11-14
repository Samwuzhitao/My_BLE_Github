#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include "app.h"
#include "ke_msg.h" // string manipulation and functions
#include "rwip_config.h"            // SW configuration
#include "sample128.h"
#include "sample128_task.h"
#include "app_sample128.h"
#include "uart_sps.h"

extern My_new_t sample128_my_new;

void app_sample128_create_db_send(void)
{
  struct sample128_create_db_req *req = KE_MSG_ALLOC( 
	                                                    SAMPLE128_CREATE_DB_REQ,
	                                                    TASK_SAMPLE128, 
	                                                    TASK_APP,
	                                                    sample128_create_db_req		
																					          );
	// send the message		
	ke_msg_send(req);
	
} 


void app_sample128_enable(void)
{
	struct sample128_enable_req* req =    KE_MSG_ALLOC(
	                                                    SAMPLE128_ENABLE_REQ,
	                                                    TASK_SAMPLE128, TASK_APP,
	                                                    sample128_enable_req
																									   );
	
	req->conhdl  = app_env.conhdl;
	req->sec_lvl = PERM(SVC, ENABLE);
	//req->sample128_1_val = 0x01; // default value for sample128 characteristic 1
	memcpy(&req->sample128_1_val,&sample128_my_new,sizeof(My_new_t));
	req->sample128_2_val = 0xff; // default value for sample128 characteristic 2
	req->feature         = 0x00; // client CFG notify/indication
  printf_string(" app_sample128_enable \r\n");
	// send the message
	ke_msg_send(req);
	
}