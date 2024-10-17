/* add user code begin Header */
/**
  **************************************************************************
  * @file     at32f403a_407_wk_config.c
  * @brief    work bench config program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

#include "at32f403a_407_wk_config.h"

/* private includes ----------------------------------------------------------*/
/* add user code begin private includes */

/* add user code end private includes */

/* private typedef -----------------------------------------------------------*/
/* add user code begin private typedef */

/* add user code end private typedef */

/* private define ------------------------------------------------------------*/
/* add user code begin private define */

/* add user code end private define */

/* private macro -------------------------------------------------------------*/
/* add user code begin private macro */

/* add user code end private macro */

/* private variables ---------------------------------------------------------*/
/* add user code begin private variables */

/* add user code end private variables */

/* private function prototypes --------------------------------------------*/
/* add user code begin function prototypes */

/* add user code end function prototypes */

/* private user code ---------------------------------------------------------*/
/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         system clock (sclk)   = hick / 12 * pll_mult
  *         system clock source   = HICK_VALUE
  *         - sclk                = 240000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 240000000
  *         - apb1div             = 2
  *         - apb1clk             = 120000000
  *         - apb2div             = 2
  *         - apb2clk             = 120000000
  *         - pll_mult            = 60
  *         - pll_range           = GT72MHZ (greater than 72 mhz)
  * @param  none
  * @retval none
  */
void wk_system_clock_config(void)
{
  /* reset crm */
  crm_reset();

  /* enable lick */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);

  /* wait till lick is ready */
  while(crm_flag_get(CRM_LICK_STABLE_FLAG) != SET)
  {
  }

  /* enable hick */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);

  /* wait till hick is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) != SET)
  {
  }

  /* config pll clock resource */
  crm_pll_config(CRM_PLL_SOURCE_HICK, CRM_PLL_MULT_60, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk, the maximum frequency of APB2 clock is 120 MHz  */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk, the maximum frequency of APB1 clock is 120 MHz  */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}

/**
  * @brief  config periph clock
  * @param  none
  * @retval none
  */
void wk_periph_clock_config(void)
{
  /* enable iomux periph clock */
  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

  /* enable gpioa periph clock */
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  /* enable gpiob periph clock */
  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

  /* enable gpioc periph clock */
  crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);

  /* enable bpr periph clock */
  crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);

  /* enable pwc periph clock */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
}

/**
  * @brief  nvic config
  * @param  none
  * @retval none
  */
void wk_nvic_config(void)
{
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
}

/**
  * @brief  init rtc function.
  * @param  none
  * @retval none
  */
void wk_rtc_init(void)
{
  /* add user code begin rtc_init 0 */
  
  /* add user code end rtc_init 0 */

  calendar_type time_struct;

  calendar_type alarm_struct;

  gpio_init_type gpio_init_struct;
  exint_init_type exint_init_struct;

  gpio_default_para_init(&gpio_init_struct);

  /* add user code begin rtc_init 1 */

  /* add user code end rtc_init 1 */

  /* configure the TAMPER pin */
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_pins = GPIO_PINS_13;
  gpio_init(GPIOC, &gpio_init_struct);

  pwc_battery_powered_domain_access(TRUE);
  
  crm_rtc_clock_select(CRM_RTC_CLOCK_LICK);
  crm_rtc_clock_enable(TRUE);
  rtc_wait_update_finish();
  rtc_wait_config_finish();
  rtc_divider_set(32767);
  rtc_wait_config_finish();

  time_struct.year  = 2024;
  time_struct.month = 10;
  time_struct.date  = 1;
  time_struct.hour  = 0;
  time_struct.min   = 0;
  time_struct.sec   = 0;
  rtc_time_set(&time_struct);

  bpr_rtc_output_select(BPR_RTC_OUTPUT_ALARM);

  /* configure Alarm */
  alarm_struct.year  = 2024;
  alarm_struct.month = 10;
  alarm_struct.date  = 9;
  alarm_struct.hour  = 0;
  alarm_struct.min   = 0;
  alarm_struct.sec   = 0;

  rtc_alarm_clock_set(&alarm_struct);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable   = TRUE;
  exint_init_struct.line_mode     = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select   = EXINT_LINE_17;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);
  /**
   * Users need to configure this interrupt functions according to the actual application.
   * 1. Call the below function to enable this  interrupt.
   *     --rtc_interrupt_enable(RTC_TA_INT, TRUE)
   * 2. Add the user's interrupt handler code into the below function in the at32f403a_407_int.c file.
   *     --void RTCAlarm_IRQHandler (void)
   */

  /* add user code begin rtc_init 2 */

  /* add user code end rtc_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
