/******************************************************************************
* File Name        : wiced_bt_ga_vcp.h
*
* Description      : Volume Control Profile (VCP) Application Programming
*                    Interface
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

#ifndef __WICED_BT_GA_VCP_H__
#define __WICED_BT_GA_VCP_H__

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
#include "wiced_bt_ga_common.h"
#include "wiced_bt_ga_aics.h"

/******************************************************************************
* Macros
*******************************************************************************/
#define VCP_TRACE(...)
#define VCP_TRACE_CRIT(...)

/******************************************************************************
* Extern Variables
*******************************************************************************/
/**
 * @addtogroup Volume_And_Gain_Control_APIs
 * @{
 */

/**
 * @addtogroup wiced_bt_ga_vcp
 * @{
 */

/** VCS Structure */
extern gatt_intf_service_methods_t vcs_methods;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void wiced_bt_ga_vcp_set_change_counter (uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t change_counter);

void wiced_bt_ga_vcp_vocs_set_change_counter(gatt_intf_service_object_t* p_service, uint8_t vocs_index, uint8_t change_counter);

wiced_bt_gatt_status_t wiced_bt_ga_vcp_set_volume_offset (uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t vocs_index, int16_t volume_offset);

wiced_bt_gatt_status_t wiced_bt_ga_vcp_set_audio_location (uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t vocs_index, wiced_bt_ga_volume_audio_location_t audio_location);

wiced_bt_gatt_status_t wiced_bt_ga_vcp_set_audio_output_description (uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t vocs_index, char *description);

wiced_bt_gatt_status_t wiced_bt_ga_vcp_set_gain_setting(uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t aics_index, int8_t gain_val);

wiced_bt_gatt_status_t wiced_bt_ga_vcp_set_mute_mode(uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t aics_index, wiced_bt_ga_aics_mute_t mute_mode);

wiced_bt_gatt_status_t wiced_bt_ga_vcp_set_gain_mode(uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t aics_index, wiced_bt_ga_aics_gain_mode_t gain_mode);

wiced_bt_gatt_status_t wiced_bt_ga_vcp_set_audio_description(uint16_t conn_id, gatt_intf_service_object_t* p_service, uint8_t aics_index, char *audio_desc);

void wiced_bt_ga_vcp_aics_set_change_counter(gatt_intf_service_object_t* p_service, uint8_t aics_index, uint8_t change_counter);



#ifdef __cplusplus
}
#endif
/**@} wiced_bt_ga_vcp */
/**@} Volume_And_Gain_Control_APIs */

#endif /* __WICED_BT_GA_VCP_H__ */

/* [] END OF FILE */
