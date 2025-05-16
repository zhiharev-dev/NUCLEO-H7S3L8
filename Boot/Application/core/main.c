/*
 * Copyright (C) 2025 zhiharev-dev <zhiharev.dev@mail.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/* Includes ---------------------------------------------------------------- */

#include "main.h"
#include "systick.h"
#include "pwr.h"
#include "flash.h"
#include "rcc.h"
#include "gpio.h"
#include "xspi.h"
#include "led.h"
#include "mx25uw.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define VTOR_ADDRESS            0x08000000

#define HSI_CLOCK               64000000

#define APP_ADDRESS             0x70000000

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

static void setup_hardware(void);

static void setup_vector_table(void);

static void setup_fpu(void);

static void app_main(void);

static void jump_app(void);

/* Private user code ------------------------------------------------------- */

int main(void)
{
    setup_hardware();
    app_main();
}
/* ------------------------------------------------------------------------- */

void error(void)
{
    __disable_irq();

    /* Выключить светодиоды */
    led_off(LED_GREEN);
    led_off(LED_YELLOW);
    led_off(LED_RED);

    while (true) {
        /* Включить красный светодиод - Ошибка */
        led_on(LED_RED);
    }
}
/* ------------------------------------------------------------------------- */

static void app_main(void)
{
    if (mx25uw_init() != MX25UW_OK) {
        error();
    } else if (mx25uw_setup_opi_dtr() != MX25UW_OK) {
        error();
    }

    xspi_setup_max_frequency();

    if (mx25uw_setup_memory_mapped_mode() != MX25UW_OK) {
        error();
    } else {
        jump_app();
    }
}
/* ------------------------------------------------------------------------- */

static void setup_hardware(void)
{
    setup_vector_table();
    setup_fpu();

    systick_init(HSI_CLOCK);
    pwr_init();
    flash_init();
    rcc_init();
    gpio_init();
    xspi_init();
}
/* ------------------------------------------------------------------------- */

static void setup_vector_table(void)
{
    __disable_irq();
    __set_PRIMASK(1);

    WRITE_REG(SCB->VTOR, VTOR_ADDRESS);

    __set_PRIMASK(0);
    __enable_irq();
}
/* ------------------------------------------------------------------------- */

static void setup_fpu(void)
{
    SET_BIT(SCB->CPACR, (0x03 << 20) | (0x03 << 22));
}
/* ------------------------------------------------------------------------- */

static void jump_app(void)
{
    __disable_irq();

    __ISB();
    __DSB();

    typedef void (*p_function)(void);
    p_function app = (p_function) *(uint32_t *) (APP_ADDRESS + 4);

    __set_MSP(*(uint32_t *) APP_ADDRESS);

    app();
}
/* ------------------------------------------------------------------------- */
