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

#include "systick.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

static volatile uint32_t tick;

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Инициализировать SysTick
 */
void systick_init(const uint32_t frequency)
{
    /* Сбросить регистр управления */
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

/**
 * @brief           Обработать прерывания SysTick
 */
void systick_it_handler(void)
{
    /* Если счетчик таймера достиг нулевого значения */
    if (READ_BIT(SysTick->CTRL, SysTick_CTRL_COUNTFLAG_Msk)) {
        /* Изменить значение системного таймера */
        ++tick;

        /* Вызвать функцию обратного вызова */
        systick_period_elapsed_callback();
    }
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Получить значение системного таймера
 *
 * @return          Значение таймера
 */
inline uint32_t systick_get_tick(void)
{
    return tick;
}
/* ------------------------------------------------------------------------- */

__WEAK void systick_period_elapsed_callback(void)
{

}
/* ------------------------------------------------------------------------- */
