#include "rwip_config.h"
#include "rwip.h"
#include "arch_sleep.h"
#include "app_task.h"                // Application task Definition
#include "gapm_task.h"
#include "gapc.h"
#include "gattc_task.h"
#include "app_api.h"
#include "sample128.h"
#include "app_sample128_task.h"


uint8_t sample128_placeholder = 0;
My_new_t sample128_my_new = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38};

/** 
 **************************************************************************************** 
 * @brief Handles sample128 profile database creation confirmation. 
 * @return If the message was consumed or not. 
 **************************************************************************************** 
 */ 
                                    
int sample128_create_db_cfm_handler(ke_msg_id_t const msgid, 
                                   struct sample128_create_db_cfm const *param, 
                                   ke_task_id_t const dest_id, 
                                   ke_task_id_t const src_id)
{
	if(ke_state_get(dest_id) == APP_DB_INIT)
	{
		// Inform the Application Manager 
		struct app_module_init_cmp_evt *cfm = KE_MSG_ALLOC(APP_MODULE_INIT_CMP_EVT,
		                                                   TASK_APP,TASK_APP,
																											 app_module_init_cmp_evt);
		
    cfm->status = param->status; 
		
		ke_msg_send(cfm);
		
	}
	 return (KE_MSG_CONSUMED); 
}
                                    
/** 
 **************************************************************************************** 
 * @brief Handles disable indication from the sample128 profile. 
 * @return If the message was consumed or not. 
 **************************************************************************************** 
 */ 
                                    
int sample128_disable_ind_handler(ke_msg_id_t const msgid, 
                                   struct sample128_disable_ind const *param, 
                                   ke_task_id_t const dest_id, 
                                   ke_task_id_t const src_id)
{
	 return (KE_MSG_CONSUMED); 
}
																		 
/** 
 **************************************************************************************** 
 * @brief Handles write of 1st characteristic event indication from sample128 profile 
 * @return If the message was consumed or not. 
 **************************************************************************************** 
 */ 
 
int sample128_val_ind_handler(ke_msg_id_t const msgid, 
															struct sample128_val_ind const *param, 
															ke_task_id_t const dest_id, 
															ke_task_id_t const src_id)
{
	 //sample128_placeholder = param->val;
	 memcpy(&sample128_my_new,&param->val,sizeof(My_new_t));
	 return (KE_MSG_CONSUMED); 
	
}



																																					
int sample128_timer_handler(ke_msg_id_t const msgid, 
														struct gapm_cmp_evt const *param, 
														ke_task_id_t const dest_id, 
														ke_task_id_t const src_id)
{
	
	ke_timer_set(APP_SAMPLE128_TIMER,TASK_APP,50); 
	
	sample128_placeholder += 1; 
					
	struct sample128_upd_char2_req *req = KE_MSG_ALLOC( 
																									   SAMPLE128_UPD_CHAR2_REQ, 
																									   TASK_SAMPLE128, 
	                                                   TASK_APP, 
																									   sample128_upd_char2_req 
																								    ); 
	req->val = sample128_placeholder; 
	req->conhdl = app_env.conhdl; 
	ke_msg_send(req); 
		
	 return (KE_MSG_CONSUMED); 
}