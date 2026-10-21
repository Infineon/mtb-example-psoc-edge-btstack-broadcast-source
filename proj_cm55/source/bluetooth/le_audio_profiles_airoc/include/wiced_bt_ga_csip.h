/******************************************************************************
* File Name        : wiced_bt_ga_csip.h
*
* Description      : Co-ordinate Set Identification Profile (CSIP) Application
*                    Programming Interface
*
* Related Document : See README.md
*
*******************************************************************************
* (c) 2026, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
*
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

#ifndef __WICED_BT_GA_CSIP_H__
#define __WICED_BT_GA_CSIP_H__

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
* Header Files
*******************************************************************************/
#include "wiced_bt_dev.h"
#include "wiced_bt_ble.h"
#include "wiced_bt_gatt.h"
#include "wiced_bt_ga_csis_common.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define CSIP_TRACE(...)
#define CSIP_TRACE_CRIT(...)
#define CSIP_TRACE_ARRAY(...)

/**
 * @addtogroup Coordinate_Set_APIs
 * @{
 */

/**
 * @addtogroup wiced_bt_ga_csip
 * @{
 */


#define WICED_BT_GA_CSIP_SET_MEMBER_DISCOVERY_TIMEOUT_IN_SEC      10 /**< CSIP timeout to discover the set members set at 10 seconds */

/******************************************************************************
* Data Types
*******************************************************************************/

/** Ordered Access complete callback to be set by the application, this will be invoked once the ordered access procedure is complete */
    typedef wiced_bt_gatt_status_t (*wiced_bt_ordered_access_procedure_cmpl_cb)(gatt_intf_service_object_t *p_csip_inst,
                                                                                void *data,
                                                                                wiced_bt_gatt_status_t status);
    /** Lock procedure complete callback to be set by the application, this will be invoked once the lock procedure is complete */
typedef wiced_bt_gatt_status_t (*wiced_bt_lock_procedure_cmpl_cb)(gatt_intf_service_object_t *p_csip_inst,
                                                                  void *data,
                                                                  wiced_bt_gatt_status_t status);

/** CSIP set entry per set memeber */
typedef struct {
    uint16_t conn_id; /**< GATT Connection ID */
    gatt_intf_service_object_t* p_service; /**< instance of the coordinated set identification client */
} wiced_bt_ga_csip_set_entry;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
wiced_bool_t wiced_bt_ga_csip_check_if_belongs_to_coordinated_set(wiced_ble_ext_scan_results_t *p_adv_report,
                                                                  uint16_t adv_len,
                                                                  uint8_t *p_adv_data,
                                                                  SIRK *p_sirk);

wiced_bt_gatt_status_t wiced_bt_ga_csip_read_set_identity_resolving_key(uint16_t conn_id, gatt_intf_service_object_t * p_service);

wiced_bt_gatt_status_t wiced_bt_ga_csip_read_lock_value(uint16_t conn_id, gatt_intf_service_object_t * p_service);

wiced_bt_gatt_status_t wiced_bt_ga_csip_request_lock(uint16_t conn_id, gatt_intf_service_object_t * p_service, wiced_bt_ga_csis_lock_val_t lock_val);

wiced_bt_gatt_status_t wiced_bt_ga_csip_start_lock_procedure(wiced_bt_ga_csip_set_entry *p_set,
                                                             int num_instances,
                                                             wiced_bt_ga_csis_lock_val_t lock_val,
                                                             wiced_bt_lock_procedure_cmpl_cb cb,
                                                             void *data);

void wiced_bt_ga_csip_start_ordered_access_procedure(wiced_bt_ga_csip_set_entry* p_set, int num_instances, wiced_bt_ordered_access_procedure_cmpl_cb cb, void *data);

wiced_bool_t wiced_bt_ga_csip_is_lock_procedure_in_progress(void);

/**@} wiced_bt_ga_csip */
/**@} Coordinate_Set_APIs */

#ifdef __cplusplus
}
#endif

#endif /* __WICED_BT_GA_CSIP_H__ */

/* [] END OF FILE */
