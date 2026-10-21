/******************************************************************************
* File Name        : le_audio_bap_broadcast.h
*
* Description      : Basic Audio Profile broadcast announcements and stream
*                    configuration.
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

#ifndef __WICED_BT_GA_BROADCAST_H__
#define __WICED_BT_GA_BROADCAST_H__

/******************************************************************************
* Header Files
*******************************************************************************/
#include "wiced_bt_ga_bap.h"
#include "wiced_data_types.h"
#include "le_audio_pbp.h"

/******************************************************************************
* Macros
*******************************************************************************/
/**
 * @addtogroup Stream_Control_APIs
 * @{
 */

/**
 * @addtogroup wiced_bt_ga_bap_broadcast
 * @{
 */


#define BROADCAST_MAX_SUB_GROUP 2 /**< Max subgroups */
#define BROADCAST_MAX_BIS_PER_SUB_GROUP 2 /**< Max BIS per sub group */
#define BROADCAST_AUDIO_ANNOUNCEMENT_SIZE 6 /**< Size of Broadcast Announcement */
#define SOLICITATION_REQ_SIZE 3 /**< Size of Solicitation request */

#define BAP_BROADCAST_TRACE(...) /**< Enable this to get BAP Broadcast traces */
#define BAP_BROADCAST_TRACE_CRIT(...) /**< Enable this to get BAP Broadcast traces */

/******************************************************************************
* Data Types
*******************************************************************************/

/**
* @brief Broadcast States
*/
typedef enum
{
    BAP_BROADCAST_STATE_IDLE, /**< Broadcast Source is in idle state */
    BAP_BROADCAST_STATE_CONFIGURED, /**< Broadcast Source is in configured state */
    BAP_BROADCAST_STATE_STREAMING, /**< Broadcast Source is in Streaming state */
} le_audio_bap_broadcast_state_t;

/**
* @brief Broadcast BIS information
*/
typedef struct
{
    uint8_t bis_idx; /**< Index of the bis */
    wiced_bool_t b_bis_data_path_setup; /**< is datapath setup */
    wiced_bt_ga_bap_csc_t bis_csc; /**< BIS codec specific configuration */
} le_audio_bap_broadcast_bis_group_t;

/**
* @brief Broadcast Subgroup information
*/
typedef struct
{
    wiced_bt_ga_bap_codec_id_t codec_id; /**< codec id for the subgroup */
    wiced_bt_ga_bap_csc_t csc; /**< codec specific configuration */
    wiced_bt_ga_bap_metadata_t metadata; /**< metadata specific for subgroup */
    uint8_t bis_cnt; /**< Num of BIS in the subgroup */
    le_audio_bap_broadcast_bis_group_t bis_config[BROADCAST_MAX_BIS_PER_SUB_GROUP];/**< List of BIS configuraiton*/
} le_audio_bap_broadcast_sub_group_t;

/**
* @brief Broadcast BASE configuration
*/
typedef struct
{
    uint32_t broadcast_id;                                                 /**< Broadcast id of the stream */
    uint32_t presentation_delay;                                           /**< Presentation delay value to be used */
    le_audio_bap_broadcast_sub_group_t sub_group[BROADCAST_MAX_SUB_GROUP]; /**< List of Subgroups */
    le_audio_bap_broadcast_state_t state;                                  /**< Broadcast state */
    uint8_t sub_group_cnt;                                                 /**< Number of subgroups*/
} le_audio_bap_broadcast_base_t;


/******************************************************************************
* Function Prototypes
*******************************************************************************/
wiced_bool_t le_audio_bap_broadcast_is_broadcast_announcement(uint16_t adv_len, uint8_t *p_adv_data, uint32_t *p_br_id);

wiced_result_t le_audio_bap_broadcast_configure(uint8_t adv_sid, le_audio_bap_broadcast_base_t *p_base, uint8_t *p_ext_adv, uint8_t adv_len);

uint8_t *le_audio_bap_broadcast_is_basic_announcement(uint8_t *p_adv_data, uint16_t adv_len, uint8_t *p_base_len);



wiced_result_t le_audio_bap_broadcast_parse_base_info(uint8_t *p_adv_data,
                                                      uint8_t adv_data_len,
                                                      le_audio_bap_broadcast_base_t *p_base);


wiced_result_t le_audio_bap_broadcast_reconfigure(uint8_t adv_sid, le_audio_bap_broadcast_base_t *p_base);

wiced_result_t le_audio_bap_broadcast_update_metadata(uint8_t adv_sid, le_audio_bap_broadcast_base_t *p_base);

wiced_result_t le_audio_bap_broadcast_start_solicitation_requests(uint8_t adv_sid,
                                                                     char *dev_name,
                                                                     uint8_t name_length);

wiced_result_t le_audio_bap_build_broadcast_annoncement_adv_data(uint8_t *p_data,
                                                                    uint8_t *len,
                                                                    uint32_t broadcast_id);

uint8_t le_audio_bap_build_base_data(le_audio_bap_broadcast_base_t *p_base, uint8_t *p_dst, uint32_t dst_len);
/**@} wiced_bt_ga_mics */
/**@} Volume_Control_APIs */

#endif /* __WICED_BT_GA_BROADCAST_H__ */

/* [] END OF FILE */
