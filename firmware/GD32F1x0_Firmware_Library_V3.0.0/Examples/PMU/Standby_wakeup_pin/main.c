/*!
    \file  main.c
    \brief standby wakeup through wakeup pin
*/

/*
    Copyright (C) 2016 GigaDevice

    2014-12-26, V1.0.0, firmware for GD32F1x0(x=3,5)
    2016-01-15, V2.0.0, firmware for GD32F1x0(x=3,5,7,9)
    2016-04-30, V3.0.0, firmware update for GD32F1x0(x=3,5,7,9)
*/

#include "gd32f1x0.h"
#include <stdio.h>
#include "gd32f1x0_eval.h"

void led_config(void);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* clock enable */
    rcu_periph_clock_enable(RCU_PMU);
    /* led configuration and turn on all led */
    led_config();
    gd_eval_ledon(LED1);
    gd_eval_ledon(LED3);
    gd_eval_ledon(LED2);
    gd_eval_ledon(LED4);
    /* tamper key configuration */
    gd_eval_keyinit(KEY_TAMPER,KEY_MODE_GPIO);
    /* wakeup pin enable */
    pmu_wakeup_pin_enable(PMU_WAKEUP_PIN0);
    /* press tamper key to enter standby mode and use wakeup key to wakeup mcu */
    while(1){
        if(RESET == gpio_input_bit_get(TAMPER_KEY_GPIO_PORT,TAMPER_KEY_PIN))
            pmu_to_stdbymode(WFI_CMD);
    }

}

/*!
    \brief      configure led 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void led_config(void)
{
    gd_eval_ledinit (LED1);
    gd_eval_ledinit (LED2);
    gd_eval_ledinit (LED3);
    gd_eval_ledinit (LED4);
}


