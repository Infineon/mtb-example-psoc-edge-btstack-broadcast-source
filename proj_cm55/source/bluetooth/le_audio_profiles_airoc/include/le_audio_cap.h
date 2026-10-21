/******************************************************************************
* File Name        : le_audio_cap.h
*
* Description      : Common Audio Profile stream control and volume
*                    management.
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

#ifndef __WICED_BT_GA_CAP_H__
#define __WICED_BT_GA_CAP_H__

/******************************************************************************
* Header Files
*******************************************************************************/
#include "wiced_bt_isoc.h"
#include "wiced_bt_types.h"

#include "wiced_bt_ga_ascs.h"
#include "wiced_bt_ga_bap.h"
#include "le_audio_bap_broadcast.h"
#include "wiced_bt_ga_mics.h"
#include "wiced_bt_ga_pacs.h"
#include "wiced_bt_ga_vcs.h"
#include "wiced_bt_ga_bass.h"

/******************************************************************************
* Macros
*******************************************************************************/
/**
 * @addtogroup Stream_Control_APIs
 * @{
 */

/**
 * @addtogroup wiced_bt_ga_cap
 * @{
 */

#define WICED_BT_CAP_DIRECTION_SOURCE 1 /**< The device is acting in source role */
#define WICED_BT_CAP_DIRECTION_SINK 2 /**< The device is acting in sink role */

#define MAX_NUM_ASE_ID 5 /**< Maximum number of ASEs supported */

#define CAP_TRACE(...) WICED_BT_TRACE(__VA_ARGS__) /**< Enable this to get CAP library traces */
#define CAP_TRACE_CRIT(...) WICED_BT_TRACE(__VA_ARGS__) /**< Enable this to get CAP library traces */

/******************************************************************************
* Data Types
*******************************************************************************/

/**
* @brief CAP Events
*/
enum le_audio_cap_event_t
{
    WICED_BT_GA_CAP_STATE_CHANGED_EVENT, /**< CAP ASE State  */
    WICED_BT_GA_CAP_ERROR_EVENT,         /**< CAP Error Event */
};

typedef uint8_t le_audio_cap_event_t; /**< CAP Events (see #le_audio_cap_event_t) */

/**
* @brief CAP Device data
*/
typedef struct
{
    uint16_t conn_id;                   /**< Connection Id */
    wiced_bt_ga_pacs_data_t *pacs_data; /**< PACS Data */
    uint8_t num_ase;                    /**< Number of ASE ID */
    uint8_t ase_notification_count;     /**< Number of Notifications which has been sent to ASEs */
    wiced_bt_ga_ascs_ase_t *ascs_data[MAX_NUM_ASE_ID]; /**< ASCS Data */
    wiced_bt_ga_vcs_volume_state_t *vcs_data;          /**< VCS Data */
    wiced_bt_ga_mute_val_t mics_mute_val;              /**< MICS Mute State */
} le_audio_cap_device_data_t;

/**
* @brief CAP APP data
*/
typedef struct
{
    wiced_bool_t is_bonded;                          /**< Is device bonded */
    uint8_t num_devices;                             /**< Number of Devices */
    le_audio_cap_device_data_t *device_info_list; /**< Device Info List */
    wiced_bool_t is_disconnecting;                   /**< DO NOT SET IN APP. Used by profile internally */
    wiced_bool_t is_disabling;                       /**< DO NOT SET IN APP. Used by profile internally */
} le_audio_cap_app_data_t;

/**
* @brief CAP Profile data
*/
typedef struct
{
    uint16_t conn_id;              /**<Connection Id */
    gatt_intf_attribute_t *p_char; /**<Char pointer */
} le_audio_cap_req_profile_data_t;

/**
* @brief CAP Event Data
*/
typedef struct {
    le_audio_cap_app_data_t *p_app_data;                /**< App data */
    wiced_bt_ga_ascs_state_t group_state;         /**< CAP Group state */
} le_audio_cap_event_data_t;

/**
* @brief CAP Start Unicast Streaming Data
*/
typedef struct
{
    wiced_bt_ga_bap_context_type_t context_type;               /**< Targeted Context Type */
    wiced_bt_ga_bap_metadata_t metadata; /**< Metadata */
    uint8_t dir;                         /**< Direction of the stream */
    uint8_t num_of_cis;                  /**< Number of CIS */
    wiced_bt_ga_ascs_config_codec_args_t *p_codec_configuration; /**< Targeted Codec Configuration */
    wiced_bt_ga_ascs_config_qos_args_t *p_qos_configuration;     /**< Targeted QOS Configuration */
} le_audio_cap_start_unicast_param_t;

/**
* @brief Codec configuration
*/
typedef struct
{
    uint16_t min_data_per_frame; /**< Min data per codec frame */
    uint16_t max_data_per_frame; /**< Max data per codec frame */
    uint16_t sf;                 /**< Sampling frequency */
    uint8_t frame_duration;      /**< Frame duration */
    uint8_t audio_ch_count;      /**< Audio channel count */
    uint8_t frame_per_sdu;       /**< Frame per sdu */
    uint16_t octet_per_frame;    /**< Octects per frame */
    uint16_t blocks_per_sdu;     /**< Blocks per sdu */
} le_audio_cap_codec_param_t;

/** CAP APP Broadcast data */
typedef struct
{
    uint8_t adv_handle; /**< Adv Handle */
    uint8_t big_handle; /**< BIG Handle */
    uint16_t bis_conn_id_count; /**< Number of Bis connection ids in the list */
    uint16_t bis_conn_id_list[BROADCAST_MAX_BIS_PER_SUB_GROUP * BROADCAST_MAX_SUB_GROUP]; /**< BIS connection ID list */
    le_audio_bap_broadcast_base_t *p_base; /**< BASE Data */
} le_audio_cap_broadcast_app_data_t;

/** CAP Start Broadcast Streaming Data */
typedef struct
{
    wiced_ble_isoc_phy_t phy;            /**< ISOC LE PHY */
    wiced_ble_isoc_packing_t packing;    /**< ISOC packing methods  */
    wiced_ble_isoc_framing_t framing;    /**< ISOC Framing types */
    wiced_ble_isoc_encryption_t encrypt; /**< ISOC Encryption */
    uint8_t max_transport_latency;      /**< Maximmum Transport Latency */
    uint8_t rtn;                        /**<Retransmission Number */
    uint32_t sdu_interval;              /**<SDU Interval */
    uint16_t max_sdu;                   /**< MAX SDU to be used */
    uint8_t *broadcast_code;            /**< Broadcast Code */
} le_audio_cap_start_broadcast_param_t;

/**
 * @brief CAP event callback
 *
 * Callback for CAP event notification
 * Registered using #le_audio_cap_register_cb
 *
 * @param conn_id  : GATT connection id
 * @param event             : Event ID
 * @param p_event_data      : Event data
 *
 * @return none
 */
typedef void le_audio_cap_cback_t(uint16_t conn_id, le_audio_cap_event_t event, le_audio_cap_event_data_t *p_event_data);

/******************************************************************************
* Function Prototypes
*******************************************************************************/
void le_audio_cap_register_cb(le_audio_cap_cback_t *cb_ptr);

wiced_result_t le_audio_cap_start_unicast_streaming(le_audio_cap_app_data_t *app_data,
                                                       le_audio_cap_start_unicast_param_t *params);

wiced_result_t le_audio_cap_update_streaming(le_audio_cap_app_data_t *app_data,
                                                le_audio_cap_start_unicast_param_t *unicast_param,
                                                wiced_bt_ga_bap_context_type_t context_type,
                                                wiced_bt_ga_bap_metadata_t *metadata);

wiced_result_t le_audio_cap_disable_stream(le_audio_cap_app_data_t *app_data);


wiced_result_t le_audio_cap_release_stream(le_audio_cap_app_data_t *app_data);

wiced_result_t le_audio_cap_set_volume(le_audio_cap_app_data_t *app_data,
                                       volume_control_opcodes_t opcode,
                                       uint8_t abs_vol);

wiced_result_t le_audio_cap_set_volume_mute_state(le_audio_cap_app_data_t *app_data,
                                                     wiced_bt_ga_mute_val_t mute_state);

wiced_result_t le_audio_cap_set_volume_offset(le_audio_cap_app_data_t *app_data, int16_t volume_offset);

wiced_result_t le_audio_cap_set_mics_mute_state(le_audio_cap_app_data_t *app_data,
                                                   wiced_bt_ga_mute_val_t mute_state);

wiced_result_t le_audio_cap_set_mics_aics_mute_state(le_audio_cap_app_data_t *app_data,
                                                     uint32_t instance,
                                                     wiced_bt_ga_mute_val_t mute_state);

wiced_result_t le_audio_cap_set_mics_aics_gain(le_audio_cap_app_data_t *app_data, uint32_t instance, int8_t gain);

wiced_result_t le_audio_cap_vcs_update_event(le_audio_cap_app_data_t *app_data,
                                             uint16_t conn_id,
                                             wiced_bt_gatt_status_t status,
                                             uint32_t evt_type,
                                             gatt_intf_attribute_t *p_char,
                                             void *p_data,
                                             int len);

wiced_result_t le_audio_cap_mics_update_event(le_audio_cap_app_data_t *app_data,
                                                 uint16_t conn_id,
                                                 wiced_bt_gatt_status_t status,
                                                 uint32_t evt_type,
                                                 gatt_intf_attribute_t *p_char,
                                                 void *p_data,
                                                 int len);

wiced_result_t le_audio_cap_ascs_update_event(le_audio_cap_app_data_t *app_data,
                                              le_audio_cap_start_unicast_param_t *unicast_param,
                                              uint16_t conn_id,
                                              wiced_bt_gatt_status_t status,
                                              uint32_t evt_type,
                                              gatt_intf_attribute_t *p_char,
                                              void *p_data,
                                              int len);

wiced_result_t le_audio_cap_broadcast_configure_stream(le_audio_cap_broadcast_app_data_t *app_data);

wiced_result_t le_audio_cap_broadcast_start_stream(le_audio_cap_broadcast_app_data_t *app_data,
                                                      le_audio_cap_start_broadcast_param_t *start_param);

wiced_result_t le_audio_cap_broadcast_disable_stream(le_audio_cap_broadcast_app_data_t *app_data, uint8_t reason);

wiced_result_t le_audio_cap_broadcast_release_stream(le_audio_cap_broadcast_app_data_t *app_data);

wiced_result_t le_audio_cap_broadcast_update_stream_metadata(le_audio_cap_broadcast_app_data_t *app_data);

uint8_t le_audio_cap_mutiplex_audio_supported(wiced_bt_ga_ascs_config_codec_args_t *p_codec_param,
                                              wiced_bt_ga_pacs_data_t *p_pacs_data);
wiced_bool_t le_audio_cap_verify_codec(uint8_t dir,
                                       wiced_bt_ga_ascs_config_codec_args_t *p_codec_config,
                                       wiced_bt_ga_pacs_data_t *p_pacs_data,
                                       uint8_t is_server);

wiced_bool_t le_audio_cap_fill_metadata(uint8_t ccid_count,
                                           uint8_t *ccid_list,
                                           wiced_bt_ga_bap_context_type_t context_type,
                                           wiced_bt_ga_bap_metadata_t *metadata);


wiced_result_t le_audio_cap_bass_operation(le_audio_cap_app_data_t *cap_app_data,
                                              wiced_bt_ga_bass_operation_t *bass_operation_data);

wiced_result_t le_audio_cap_unicast_to_broadcast_handover(wiced_bt_ga_bap_metadata_t *unicast_metadata,
                                                             le_audio_cap_broadcast_app_data_t *p_cap_br_data,
                                                             le_audio_cap_app_data_t *app_data,
                                                             wiced_bt_ga_bass_operation_t *bass_operation_data);

wiced_result_t le_audio_cap_broadcast_to_unicast_handover(wiced_bt_ga_bap_metadata_t *unicast_metadata,
                                                             wiced_bt_ga_bap_metadata_t *br_metadata,
                                                             le_audio_cap_app_data_t *app_data,
                                                             wiced_bt_ga_bass_operation_t *bass_operation_data);

/**@} wiced_bt_ga_cap */
/**@} Stream_Control_APIs */

#endif /* __WICED_BT_GA_CAP_H__ */

/* [] END OF FILE */
