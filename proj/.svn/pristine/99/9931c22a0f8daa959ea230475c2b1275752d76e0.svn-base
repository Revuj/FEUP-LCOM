#include "rtc_macros.h"
#include <machine/asm.h>


.intel_syntax

.global _C_LABEL(rtc_check_iup_asm)
.global _C_LABEL(asm_reg)


.text 

_C_LABEL(rtc_check_iup_asm):

    xor eax , eax
    mov   eax, RTC_REGISTER_A
    out RTC_ADRESS_REGISTER,eax
    xor eax , eax
    in  eax , RTC_DATA_REGISTER
    mov _C_LABEL(asm_reg), eax
    mov eax, _C_LABEL(asm_reg) 
    and eax , RTC_UIP
    xor eax,eax
    ret

.end

