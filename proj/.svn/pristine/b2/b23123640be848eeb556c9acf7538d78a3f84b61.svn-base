#ifndef __VBE_H
#define __VBE_H

#include <machine/int86.h>

/** @defgroup Vbe Vbe
 * @{
 * Related to the VBE standard
 */


#define VBE_LM_INIT_FAIL 1
#define VBE_LM_ALLOC_FAIL 2
#define VBE_SYSINT86_FAIL 3
#define VBE_MODE_INFO_FAIL 4

#define BIOS_VIDEO_SERVICE 0x10
#define BIOS_VBE_SET_MODE  0x4F02
#define BIOS_VBE_GET_MODE_INFO 0x4F01
#define CALL_SUCCESSED 0x00
#define CALL_SUPPORTED 0x4F

/**
 * @brief Returns information on the input VBE mode, including screen dimensions, color depth and VRAM physical address
 *
 * @param mode mode whose information should be returned
 * @param vmi_p address of vbe_mode_info_t structure to be initialized
 * 
 * @return Returns 0 on success, non-zero otherwise
 */
int vbe_get_mode_inf(uint16_t mode, vbe_mode_info_t *vmi_p);
/** @} end of Vbe */

#endif /* __VBE_H*/
