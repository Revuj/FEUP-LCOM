#ifndef  _RTC_MACROS_H_
#define  _RTC_MACROS_H_


#ifndef _BIT_
#define BIT(n) (0x01<<(n))
#endif
#define RTC_ADRESS_REGISTER          0x70
#define RTC_DATA_REGISTER            0x71
#define RTC_REGISTER_A               0x0A
#define RTC_REGISTER_B               0x0B 
#define RTC_REGISTER_C               0x0C
#define RTC_REGISTER_D               0x0D
#define RTC_UIP                     BIT(7)
#define RTC_IRQ_LINE                    8
#define RTC_SECOND                      0
#define RTC_MINUTE                      2
#define RTC_HOUR                        4
#define RTC_DAY                         7
#define RTC_MONTH                       8
#define RTC_YEAR                        9



#endif
