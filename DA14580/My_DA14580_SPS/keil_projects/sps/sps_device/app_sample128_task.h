#include "rwip_config.h"
#include "rwip.h"
#include "app.h"
#include "ke_msg.h" // string manipulation and functions
#include "arch_sleep.h"
#include "app_task.h"                // Application task Definition
#include "sample128_task.h"
#include "gapm_task.h"
#include "gapc.h"
#include "gattc_task.h"

/** 
 **************************************************************************************** 
 * @brief Handles sample128 profile database creation confirmation. 
 * @return If the message was consumed or not. 
 **************************************************************************************** 
 */ 
                                    
int sample128_create_db_cfm_handler(ke_msg_id_t const msgid, 
                                   struct sample128_create_db_cfm const *param, 
                                   ke_task_id_t const dest_id, 
                                   ke_task_id_t const src_id); 
                                    
/** 
 **************************************************************************************** 
 * @brief Handles disable indication from the sample128 profile. 
 * @return If the message was consumed or not. 
 **************************************************************************************** 
 */ 
                                    
int sample128_disable_ind_handler(ke_msg_id_t const msgid, 
                                   struct sample128_disable_ind const *param, 
                                   ke_task_id_t const dest_id, 
                                   ke_task_id_t const src_id); 
                                    
/** 
 **************************************************************************************** 
 * @brief Handles write of 1st characteristic event indication from sample128 profile 
 * @return If the message was consumed or not. 
 **************************************************************************************** 
 */ 
 
int sample128_val_ind_handler(ke_msg_id_t const msgid, 
                                      struct sample128_val_ind const *param, 
                                      ke_task_id_t const dest_id, 
                                      ke_task_id_t const src_id); 
																			
																			
int sample128_timer_handler(ke_msg_id_t const msgid, 
																			struct gapm_cmp_evt const *param, 
																			ke_task_id_t const dest_id, 
																			ke_task_id_t const src_id);
