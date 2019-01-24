PROG=proj

SRCS = proj.c video_gr.c vbe.c kbc_asm_ih.S keyboard.c timer_asm.S timer.c  bitmap.c mouse.c Game.c asteroid.c satellite.c rtc_asm_uip.S rtc.c Score.c bullet.c Colision.c health.c 

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
