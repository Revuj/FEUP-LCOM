#ifndef __RTC_H
#define __RTC_H
#include <minix/drivers.h>


/** @defgroup Rtc Rtc
 * @{
 * Functions to manipulate the rtc
 */



/** @name Date */
/** @{struct that holds the information about a date */
typedef struct {
 uint32_t seconds;
  uint32_t minutes;
  uint32_t hours;
  uint32_t day;
  uint32_t month;
  uint32_t year;
    
} Date; /** @} end of the Date struct*/



/**
 * @brief Converts a binary number to base case decimal
 * 
 * @param x - number to be converted
 * 
 * @return Returns converted number
 */
uint32_t convert_binary_to_bcd(uint32_t x);


//int check_uip();

/**
 * @brief Checks if rtc is being updated
 * 
 * @return Returns 0 if rtc is not being updated or 1 otherwhise
 */
extern int rtc_check_iup_asm();

/**
 * @brief Updates de current date
 * 
 * @return Returns 0 upon success or 1 otherwhise
 */
int update_date();

/**
 * @brief Returns the current date
 */
char *get_date();

/**
 * @brief Returns the current hour
 */
uint32_t get_hour();

/**
 * @brief Returns the current minute
 */
uint32_t get_minute();

/**
 * @brief Returns the current seconds
 */
uint32_t get_seconds();

// int rtc_subscribe_int(uint8_t *bit_no);
// int rtc_unsubscribe_int();

/** @} end of Rtc */



#endif /*__RCT_H*/
