
#include <machine/asm.h>
#include "i8042.h"

.intel_syntax

.global  _C_LABEL(kbc_asm_ih) 
//.global _C_LABEL(data)
//.global _C_LABEL(error_flag)
.text
_C_LABEL(kbc_asm_ih):
    pushad
    in al, KBC_STAT_REG
    mov dl, al
    mov cl, OBF
    cmp dl, cl
    jz error 
    in al, KBC_OUT_BUF
    and cl, (PAR_ERR | TO_ERR)
    cmp cl, dl
    jz error
    mov _C_LABEL(data), al
    jmp end
error:
    mov al, 1
    mov _C_LABEL(error_flag), al
end:
    popad
    ret
.end
