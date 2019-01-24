#include <machine/asm.h>

.intel_syntax

.global _C_LABEL(timer_int_asm)

.text

_C_LABEL(timer_int_asm):

    mov eax, _C_LABEL(counter_timer)
    inc eax
    mov _C_LABEL(counter_timer),eax

    ret

.end
