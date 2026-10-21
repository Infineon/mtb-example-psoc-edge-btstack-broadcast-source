/******************************************************************************
* File Name        : audio_sample_lc3.h
*
* Description      : Pre-encoded LC3 audio sample access for the Broadcast
*                    Source application.
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
#pragma once

/******************************************************************************
* Header Files
*******************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
* Macros
*******************************************************************************/
#define AUDIO_LC3_SAMPLE_RATE 48000U
#define AUDIO_LC3_FRAME_US 10000U
#define AUDIO_LC3_FRAME_BYTES 100U

/******************************************************************************
* Function Prototypes
*******************************************************************************/
bool audio_lc3_format_supported(uint32_t sample_rate, uint32_t frame_us,
                               uint16_t frame_bytes, uint8_t channels);
bool audio_lc3_copy_frame(uint32_t *frame_index, uint8_t channels,
                         uint8_t *destination, uint16_t capacity);

/* [] END OF FILE */
