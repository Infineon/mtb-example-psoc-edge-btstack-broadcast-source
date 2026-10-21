/******************************************************************************
* File Name        : gatt_interface_methods.h
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

#ifndef __GATT_INTERFACE_METHODS_H__
#define __GATT_INTERFACE_METHODS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************
* Header Files
*******************************************************************************/
#include "gatt_interface_types.h"

/******************************************************************************
* Function Prototypes
*******************************************************************************/
wiced_result_t gatt_intf_method_create_service_instances(const struct gatt_intf_service_methods_t_ *p_methods,
    int num_instances, int object_instance_size);

int gatt_intf_method_get_included_service_index(gatt_intf_service_object_t *p_service, int service_index_type, gatt_intf_service_object_t *p_inc_service);

void gatt_intf_method_set_included_service_data(gatt_intf_service_object_t *p_service, wiced_bt_gatt_included_service_t *p_result, gatt_intf_service_object_t *p_inc_service);

int gatt_intf_method_get_nvram_peer_db(gatt_intf_service_object_t *p_service, uint8_t *p_data, int len);

void gatt_intf_method_set_service_callback(gatt_intf_service_object_t *p_service, gatt_intf_service_cb_t callback, void *p_app_ctx);

void gatt_intf_method_print_handles(gatt_intf_service_object_t *p_service);

/******************************************************************************
* Data Types
*******************************************************************************/
/**
 * @brief Profile/Service callback function called to init the service with data stored in NVRAM
 * @param p_service : GATT Profile Instance
 * @param bdaddr: Bluetooth device adddress
 * @param characteristic_type : The characteristic type to write the data to
 * @param p_data : The stored data from NVRAM
 * @param len : The length of the data pointed by p_data
 * @return : The number of bytes read from \p p_data
*/
typedef int (*write_server_characteristic_t)(gatt_intf_service_object_t *p_service, wiced_bt_device_address_t bdaddr, int characteristic_type,
    uint8_t *p_data, int len);

int gatt_intf_method_write_server_characteristics_to_nvram(gatt_intf_service_object_t *p_service, wiced_bt_device_address_t bdaddr,
    uint8_t *p_data, int remaining,
    gatt_intf_characteristic_handles_t *p_handle_list, int num_handles, write_server_characteristic_t pfn_write_char);

int gatt_intf_method_get_characteristic_type_from_handle(const gatt_intf_characteristic_handles_t *p_handles,
    int max, uint16_t handle, int *p_type_uuid);





wiced_bt_gatt_status_t gatt_intf_method_send_write_value_handle(gatt_intf_characteristic_handles_t *p_handle, uint16_t conn_id,
    wiced_bt_gatt_opcode_t opcode, uint16_t len, uint8_t *p_data, void *pv_ctx);

wiced_bt_gatt_status_t gatt_intf_method_send_read(const gatt_intf_characteristic_handles_t *p_handles, uint16_t conn_id, uint16_t max_read_len);

wiced_bt_gatt_status_t gatt_intf_method_send_read_descriptor(const gatt_intf_characteristic_handles_t *p_handles, uint16_t conn_id,
    uint16_t descriptor_type, uint16_t max_len);

wiced_bt_gatt_status_t gatt_intf_method_set_descriptor_value(const gatt_intf_characteristic_handles_t *p_handles, uint16_t conn_id,
    uint16_t descriptor_type, uint16_t value_len, uint8_t *p_value);

wiced_bt_gatt_status_t gatt_intf_method_send_notification( uint16_t conn_id,
    const gatt_intf_characteristic_handles_t *p_handle,
    uint16_t data_len,
    uint8_t *p_data,
    void *pv_ctx);

wiced_bt_gatt_status_t gatt_intf_method_send_indication(uint16_t conn_id,
                                                        const gatt_intf_characteristic_handles_t *p_handle,
                                                        uint16_t data_len,
                                                        uint8_t *p_data,
                                                        void *pv_ctx);

wiced_bt_gatt_status_t gatt_intf_method_send_write_response(const gatt_intf_characteristic_handles_t *p_char, uint16_t conn_id,
    wiced_bt_gatt_opcode_t opcode, wiced_bt_gatt_status_t status);

enum
{
    SUBSCRIPTION_NONE,         /**< Does not allow both notifications and indications */
    SUBSCRIPTION_NOTIFICATION, /**< Allows notifications  */
    SUBSCRIPTION_INDICATION    /**< Allows indications  */
};
typedef uint16_t subscription_enums_t;

int gatt_intf_method_get_subscription_value_conn_id(uint16_t conn_id,
                                                    const gatt_intf_characteristic_handles_t *p_handle);

int gatt_intf_method_set_subscription_value_conn_id(uint16_t conn_id,
                                                    const gatt_intf_characteristic_handles_t *p_handle,
                                                    uint16_t value);

uint8_t *gatt_intf_method_get_buffer(int len);


uint8_t *gatt_intf_method_alloc_server_notification_packet(uint16_t conn_id,
                                                           gatt_intf_characteristic_handles_t *p_handle,
                                                           subscription_enums_t type,
                                                           int req_len);

void gatt_intf_method_free_buffer(uint8_t *ptr);

wiced_bt_gatt_status_t gatt_intf_notify_characteristic_to_all_clients(
    uint16_t conn_id,
    gatt_intf_service_object_t *p_service,
    gatt_intf_attribute_t *p_characteristic,
    void *p_n,
    on_gatt_interface_operation_complete_t pfn_op_cmpl);
#ifdef __cplusplus
}
#endif

#endif /* __WICED_BT_GA_GATT_INTERFACE_H__ */

/* [] END OF FILE */
