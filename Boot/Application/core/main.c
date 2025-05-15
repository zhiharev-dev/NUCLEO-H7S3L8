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

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define VTOR_ADDRESS        0x08000000

#define HSI_CLOCK           64000000

#define APP_ADDRESS         0x70000000

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Системный таймер */
volatile uint32_t systick;

/* Private function prototypes --------------------------------------------- */

static void setup_hardware(void);

static void setup_vector_table(void);

static void setup_fpu(void);

static void app_main(void);

static void jump_app(void);

static void systick_init(const uint32_t frequency);

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

    while (true)
        ;
}
/* ------------------------------------------------------------------------- */

static void app_main(void)
{
    while (true)
        ;
}
/* ------------------------------------------------------------------------- */

static void setup_hardware(void)
{
    setup_vector_table();
    setup_fpu();

    systick_init(HSI_CLOCK);
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

__unused static void jump_app(void)
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

/**
 * @brief           Инициализировать SysTick
 */
static void systick_init(const uint32_t frequency)
{
    /* Сбросить настройки */
    CLEAR_REG(SysTick->CTRL);

    /* Установить значение перезагрузки счетчика = 1 мс */
    WRITE_REG(SysTick->LOAD, (frequency / 1000) - 1);

    /* Установить текущее значение счетчика = 0 */
    CLEAR_REG(SysTick->VAL);

    /* Настроить тактирование от CPU и запустить таймер */
    WRITE_REG(SysTick->CTRL,
              SysTick_CTRL_CLKSOURCE_Msk
            | SysTick_CTRL_TICKINT_Msk
            | SysTick_CTRL_ENABLE_Msk);
}
/* ------------------------------------------------------------------------- */
