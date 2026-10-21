/******************************************************************************
* File Name        : gatt_interface.h
*
* Description      : Definitions for the interface between BT stack GATT and
*                    services/applications. The GATT interface routes incoming
*                    GATT commands to the appropriate services or application.
*
*                    The GATT Interface library helps applications to:
*                    1. Discover remote services, included services,
*                       characteristics, and descriptors, and map them to
*                       registered service implementations.
*                    2. Set up local services, included services,
*                       characteristics, and descriptors, and map them to
*                       registered service implementations.
*                    3. Notify remote clients, set up notifications, and read
*                       characteristics.
*                    4. Organize nonvolatile data for storage in and retrieval
*                       from NVRAM.
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

#ifndef __WICED_BT_GATT_INTERFACE_H__
#define __WICED_BT_GATT_INTERFACE_H__

/******************************************************************************
* Header Files
*******************************************************************************/
#include "gatt_interface_methods.h"
#include "gatt_interface_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
* Function Prototypes
*******************************************************************************/
    wiced_result_t gatt_interface_init(int max_connections, int max_mtu, wiced_bt_gatt_auth_req_t default_auth_req);

    wiced_bt_gatt_status_t gatt_interface_invoke_gatt_handler(wiced_bt_gatt_evt_t event,
                                                              wiced_bt_gatt_event_data_t *p_event_data);

    wiced_bt_gatt_status_t gatt_interface_setup_services_from_local_db(fn_on_service_handle_check_to_save pfn_can_save,
                                                                       fn_on_service_handle_store pfn_store,
                                                                       void *p_app_ctx);

    wiced_result_t gatt_interface_start_discovery(uint16_t conn_id,
                                                  fn_on_service_handle_check_to_save pfn_can_save,
                                                  fn_on_service_handle_store pfn_save,
                                                  fn_on_discovery_complete pfn_on_complete,
                                                  void *p_app_ctx);

    discovery_state_t gatt_interface_get_discovery_state(uint16_t conn_id);

    wiced_result_t gatt_interface_set_callback_to_profile(gatt_intf_service_object_t *p_service,
                                                          gatt_intf_service_cb_t callback,
                                                          void *p_app_ctx);

    wiced_bt_gatt_status_t gatt_interface_read_characteristic(uint16_t conn_id,
                                                              gatt_intf_service_object_t *p_service,
                                                              gatt_intf_attribute_t *p_char);

    wiced_bt_gatt_status_t gatt_interface_write_characteristic(uint16_t conn_id,
                                                               gatt_intf_service_object_t *p_service,
                                                               gatt_intf_attribute_t *p_char,
                                                               void *p_write_data);

    wiced_bt_gatt_status_t gatt_interface_notify_characteristic(uint16_t conn_id,
                                                                gatt_intf_service_object_t *p_service,
                                                                gatt_intf_attribute_t *p_char,
                                                                void *p_notification);

    wiced_bt_gatt_status_t gatt_interface_enable_notifications(uint16_t conn_id,
                                                               gatt_intf_service_object_t *p_service,
                                                               gatt_intf_attribute_t *p_char,
                                                               uint16_t value);

    /* Utility functions to read/enable notifications for all */


wiced_bt_gatt_status_t gatt_interface_characteristic_operation(uint16_t conn_id,
                                                               gatt_intf_service_object_t *p_service,
                                                               gatt_intf_operation_t operation,
                                                               on_gatt_interface_operation_complete_t pfn_op_cmpl);

    /* nvram */
int gatt_interface_nvram_write(wiced_bt_device_address_t bdaddr,
                                   const gatt_interface_nvram_data_t *p_nv,
                                   int device_nvram_id);

int gatt_interface_nvram_read(wiced_bt_device_address_t bda,
                                  const gatt_interface_nvram_data_t *p_nv,
                                  int device_nvram_id,
                                  void *p_app_ctx);

void gatt_interface_free_client_device_ctx(wiced_bt_device_address_t bdaddr);


void gatt_interface_print_linked_handles(wiced_bt_device_address_t bdaddr);

gatt_intf_service_object_t *gatt_interface_get_service_by_uuid(wiced_bt_device_address_t bdaddr,
                                                                   const wiced_bt_uuid_t *p_uuid);


gatt_intf_service_object_t *gatt_interface_get_service_by_uuid_and_conn_id(uint16_t conn_id,
                                                                               const wiced_bt_uuid_t *p_uuid);

gatt_intf_service_object_t *gatt_interface_get_linked_client_profile_at(wiced_bt_device_address_t bdaddr,
                                                                            int index);

gatt_intf_service_object_t *gatt_interface_get_linked_server_profile_at(int index);


gatt_intf_service_object_t *gatt_interface_get_next_linked_profile(gatt_intf_service_object_t *p_service);


const wiced_bt_uuid_t *gatt_interface_get_service_uuid(gatt_intf_service_object_t *p_service);


const char *gatt_interface_get_service_name(gatt_intf_service_object_t *p_service);


/******************************************************************************
* Macros
*******************************************************************************/
#define GATT_INTERFACE_TRACE(...) WICED_BT_TRACE(__VA_ARGS__)
#define GATT_INTERFACE_TRACE_CRIT(...) WICED_BT_TRACE(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* __WICED_BT_GA_GATT_INTERFACE_H__ */

/* [] END OF FILE */
