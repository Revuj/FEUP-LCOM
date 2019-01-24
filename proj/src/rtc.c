#include <lcom/lcf.h>
#include "rtc.h"
#include "rtc_macros.h"
int hook_id_rtc = RTC_IRQ_LINE;
static Date date;


uint32_t asm_reg = 0;


uint32_t convert_bcd_to_binary(uint32_t x)
{
  return ((x & 0xF0) >> 4) * 10 + (x & 0x0F);
}

// int check_uip() {

//   if (sys_outb(RTC_ADRESS_REGISTER, RTC_REGISTER_A) != OK) {
//     return 1;
//   }

//   uint32_t reg=0;
//   if(sys_inb(RTC_DATA_REGISTER, &reg) != OK) {
//     return 1;
//   }

//   if((reg & RTC_UIP) != OK) {
//     return 1;
//   }

//   return OK;

// }


int update_date()
{ 
  
  while(rtc_check_iup_asm()) {
  }



  uint32_t v[6] = {0, 0, 0, 0, 0, 0};
  uint32_t data[6] = {RTC_SECOND, RTC_MINUTE, RTC_HOUR, RTC_DAY, RTC_MONTH, RTC_YEAR};

  for (unsigned i = 0; i < 6; i++)
  {
    if (sys_outb(RTC_ADRESS_REGISTER, data[i]) != OK)
    {
      return 1;
    }
    if (sys_inb(RTC_DATA_REGISTER, &v[i]) != OK)
    {
      return 1;
    }
    v[i] = convert_bcd_to_binary(v[i]);
  }
  date.seconds = v[0];
  date.minutes = v[1];
  date.hours = v[2];
  date.day = v[3];
  date.month = v[4];
  date.year = v[5];

  return OK;
}

char *get_date()
{

  if (update_date() != OK)
  {
    return NULL;
  }
  char *date_return = NULL;
  asprintf(&date_return, "%02d %02d %02d %02d %02d %02d", date.hours, date.minutes, date.seconds,
           date.day, date.month, date.year);
  return date_return;
}

uint32_t get_hour() {
  return date.hours;
}

uint32_t get_minute() {
  return date.minutes;
}
uint32_t get_seconds() {
  return date.seconds;
}

// int rtc_subscribe_int(uint8_t *bit_no)
// {
//   uint32_t data_reg_b;

//   *bit_no = hook_id_rtc;
//   if (sys_irqsetpolicy(RTC_IRQ_LINE, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_rtc) != OK)
//   {
//     return 1;
//   }

//   if (sys_outb(RTC_ADRESS_REGISTER, RTC_REGISTER_B) != OK)
//   {
//     return 1;
//   }
//   if (sys_inb(RTC_DATA_REGISTER, &data_reg_b) != OK)
//   {
//     return 1;
//   }
//   data_reg_b = data_reg_b | RTC_UF;
//   data_reg_b = data_reg_b & ~RTC_SET;
//   if (sys_outb(RTC_ADRESS_REGISTER, RTC_REGISTER_B) != OK)
//   {
//     return 1;
//   }
//   if (sys_outb(RTC_DATA_REGISTER, data_reg_b) != OK)
//   {
//     return 1;
//   }
//   return OK;
// }


// int rtc_unsubscribe_int()
// {
//   if (sys_irqdisable(&hook_id_rtc) != OK)
//   {
//     return 1;
//   }
//   if (sys_irqrmpolicy(&hook_id_rtc) != OK)
//   {
//     return 1;
//   }
//   uint32_t data_reg_b = 0;
//   if (sys_outb(RTC_ADRESS_REGISTER, RTC_REGISTER_B) != OK)
//   {
//     return 1;
//   }
//   if (sys_inb(RTC_DATA_REGISTER, &data_reg_b) != OK)
//   {
//     return 1;
//   }
//   data_reg_b = data_reg_b & ~RTC_UF;
//   if (sys_outb(RTC_ADRESS_REGISTER, RTC_REGISTER_B) != OK)
//   {
//     return 1;
//   }
//   if (sys_outb(RTC_DATA_REGISTER, data_reg_b) != OK)
//   {
//     return 1;
//   }
//   return OK;
// }
