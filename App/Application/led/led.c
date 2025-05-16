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

#include "led.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define LED_COUNT       3

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

static struct led led[LED_COUNT] = {
    /* GREEN */
    {
        .gpio = GPIOD,
        .pin = GPIO_ODR_OD10,
    },
    /* YELLOW */
    {
        .gpio = GPIOD,
        .pin = GPIO_ODR_OD13,
    },
    /* RED */
    {
        .gpio = GPIOB,
        .pin = GPIO_ODR_OD7,
    },
};

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Включить светодиод
 *
 * @param[in]       id: Идентификатор светодиода
 */
void led_on(int32_t id)
{
    assert(id < LED_COUNT && id > LED_NONE);

    SET_BIT(led[id].gpio->BSRR, led[id].pin);
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Выключить светодиод
 *
 * @param[in]       id: Идентификатор светодиода
 */
void led_off(int32_t id)
{
    assert(id < LED_COUNT && id > LED_NONE);

    SET_BIT(led[id].gpio->BSRR, led[id].pin << 16);
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Переключить состояние светодиода
 *
 * @param[in]       id: Идентификатор светодиода
 */
void led_toggle(int32_t id)
{
    assert(id < LED_COUNT && id > LED_NONE);

    XOR_BIT(led[id].gpio->ODR, led[id].pin);
}
/* ------------------------------------------------------------------------- */
