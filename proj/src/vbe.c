#include <lcom/lcf.h>
#include "vbe.h"

int vbe_get_mode_inf(uint16_t mode, vbe_mode_info_t *vmi_p)
{

    void *virtual_adress = lm_init(false);
    if (virtual_adress == NULL)
    {
        return VBE_LM_INIT_FAIL;
    }

    mmap_t map;

    virtual_adress = lm_alloc(sizeof(vbe_mode_info_t), &map);
    if (virtual_adress == NULL)
    {
        return VBE_LM_ALLOC_FAIL;
    }

    struct reg86u reg;
    memset(&reg, 0, sizeof(reg));

    reg.u.w.ax = BIOS_VBE_GET_MODE_INFO ;
    reg.u.w.es = PB2BASE(map.phys);
    reg.u.w.di = PB2OFF(map.phys);
    reg.u.w.cx = mode;
    reg.u.b.intno = BIOS_VIDEO_SERVICE;


    if (sys_int86(&reg) != OK)  {
        return VBE_SYSINT86_FAIL;
    }

    if (reg.u.b.al != CALL_SUPPORTED) {
        return VBE_MODE_INFO_FAIL;
    }

    if (reg.u.b.ah != CALL_SUCCESSED) {
        return VBE_MODE_INFO_FAIL;
    }

    *vmi_p = * (vbe_mode_info_t *) map.virt;

    lm_free(&map);

    return OK; 
}
