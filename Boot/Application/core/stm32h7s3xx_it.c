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

#include "stm32h7s3xx_it.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Системный таймер */
extern volatile uint32_t systick;

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

void NMI_Handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void HardFault_Handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void MemManage_Handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void BusFault_Handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void UsageFault_Handler(void)
{
    error();
}
/* ------------------------------------------------------------------------- */

void SysTick_Handler(void)
{
    /*
     * Если счетчик SysTick достиг нулевого значения -
     * изменить значение системного таймера
     */
    if (READ_BIT(SysTick->CTRL, SysTick_CTRL_COUNTFLAG_Msk))
        systick++;
}
/* ------------------------------------------------------------------------- */
