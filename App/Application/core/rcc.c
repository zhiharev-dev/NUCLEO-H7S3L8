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

#include "rcc.h"
#include "systick.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define RCC_HSERDY_TIMEOUT       100
#define RCC_LSERDY_TIMEOUT       5000

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

static void rcc_setup_lse(void);

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Инициализировать RCC
 */
void rcc_init(void)
{
    rcc_setup_lse();
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Настроить LSE
 */
static void rcc_setup_lse(void)
{
    /* Включить LSE */
    SET_BIT(RCC->BDCR, RCC_BDCR_LSEON_Msk);

    /* Ожидание готовности HSE */
    uint32_t tickstart = systick_get_tick();

    while (!READ_BIT(RCC->BDCR, RCC_BDCR_LSERDY_Msk)) {
        if (systick_get_tick() - tickstart >= RCC_LSERDY_TIMEOUT)
            error();
    }

    /* Включить CSS LSE */
    SET_BIT(RCC->BDCR, RCC_BDCR_LSECSSON_Msk);
}
/* ------------------------------------------------------------------------- */
