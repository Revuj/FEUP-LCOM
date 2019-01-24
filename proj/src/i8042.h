#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#ifndef _BIT_
#define BIT(n) (0x01<<(n))  
#endif

#define NOT_OK 1
#define KBC_ESC 0x81

#define KBC_STAT_REG 0x64             /* kbc status register */
#define KBC_OUT_BUF 0x60              /* kbc outputt buffer register */
#define KBC_IN_BUF 0X60               /*kbc input buffer register*/
#define KBC_CMD_REGISTER 0X64         /*kbc commmand register */
#define KBC_WRITE_TO_MOUSE 0xD4       /*allows us to write a byte to mouse*/

#define MOUSE_ENABLE_DATA_REPORTING_COMMAND 0xF4
#define MOUSE_DISABLE_DATA_REPORTING_COMMAND 0xF5
#define MOUSE_ENABLE_STREAM_MODE_COMMAND 0xEA
#define MOUSE_ENABLE_REMOTE_MODE_COMMAND 0xF0
#define MOUSE_READ_DATA_COMMAND 0xEB
#define ENABLE_MOUSE_COMMAND 0xA8
#define DISABLE_MOUSE_COMMAND 0xA7

#define MOUSE_ACK      0xFA   
#define MOUSE_NACK     0xFE   
#define MOUSE_ERROR    0xFC  
  
#define KBC_READ_COMMAND 0x20           /* read command byte*/
#define KBC_WRITE_COMMAND 0x60          /*write command byte*/

#define KBC_IRQ 1                     /*_MAKECODEboard IRQ line*/
#define KBC_HOOK_BIT_SELECT 1

#define MOUSE_IRQ 12                 /*Aux/Mouse IRQ line*/
#define MOUSE_HOOK_BIT_SELECT 2

#define OBF BIT(0) 
#define IBF BIT(1)                  /*output buffer bit*/
#define PAR_ERR BIT(7)                /*parity bit*/            
#define TO_ERR BIT(6)                 /*timeout error bit*/  
#define AUX BIT(5)                     /*auxiliar bit*/

#define INT BIT(0)                 /*enable interrupt on OBF, from _MAKECODEboard*/
#define INT2 BIT(1)                /*enable interrupt on OBF, from mouse*/

#define Y_OVF BIT(7)
#define X_OVF BIT(6)
#define Y_SIGN BIT(5)
#define X_SIGN BIT(4)
#define MB_BIT BIT(2)
#define RB_BIT BIT(1)
#define LB_BIT BIT(0)

#define MAKE_BIT BIT(7)             

#define DELAY_US 20000 /* 20ms delay */

#define LS_BYTE BIT(0) |BIT(1) | BIT(2) | BIT(3) | BIT(4) |BIT(5) | BIT(6) | BIT(7)          
#define MS_BYTE BIT(8) | BIT(9) | BIT(10) | BIT(11) |BIT(12) | BIT(13) | BIT(14) | BIT(15)
#define COMMON_BYTE BIT(7) | BIT(6) | BIT(5) /* 0XE0 BYTE*/
#define COMMON_BYTE2 BIT(7) | BIT(6) | BIT(5) | BIT(0) /*0XE1 BYTE*/
#define ALL_BUT_OBF_MASK 0xFD;
#define DELETE 0xE


#define W_BREAKCODE 0x91
#define A_BREAKCODE 0x9E
#define S_BREAKCODE 0x9F
#define D_BREAKCODE 0xA0
#define R_BREAKCODE 0x93
#define SHIFT_MAKECODE 0x2A
#define DASH_SPEED 225
#define ESC_MAKECODE 0X81

#define SPEED   8

#define A_MAKECODE 0x1E
#define B_MAKECODE 0x30
#define C_MAKECODE 0x2E
#define D_MAKECODE 0x20
#define E_MAKECODE 0x12
#define F_MAKECODE 0x21
#define G_MAKECODE 0x22
#define H_MAKECODE 0x23
#define I_MAKECODE 0x17
#define J_MAKECODE 0x24
#define K_MAKECODE 0x25
#define L_MAKECODE 0x26
#define M_MAKECODE 0x32
#define N_MAKECODE 0x31
#define O_MAKECODE 0x18
#define P_MAKECODE 0x19
#define Q_MAKECODE 0x10
#define R_MAKECODE 0x13
#define S_MAKECODE 0x1F
#define T_MAKECODE 0x14
#define U_MAKECODE 0x16
#define V_MAKECODE 0x2F
#define W_MAKECODE 0x11
#define X_MAKECODE 0x2D
#define Y_MAKECODE 0x15
#define Z_MAKECODE 0x2C


#endif  /* _LCOM_I8042_H */
