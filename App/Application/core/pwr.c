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

#include "pwr.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Состояние VDD */
static volatile bool vdd_is_lower;

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Инициализировать PWR
 */
void pwr_init(void)
{
    /* Выключить защиту домена резервного копирования */
    SET_BIT(PWR->CR1, PWR_CR1_DBP_Msk);

    /* Включить регулятор домена резервного копирования */
    SET_BIT(PWR->CSR1, PWR_CSR1_BREN_Msk);
    while (!READ_BIT(PWR->CSR1, PWR_CSR1_BRRDY_Msk))
        continue;

    /* Включить и настроить PVD */
    MODIFY_REG(PWR->CR1,
               PWR_CR1_PLS_Msk,
               PWR_CR1_PVDE_Msk
             | 0x06 << PWR_CR1_PLS_Pos);

    /* Включить и настроить PVD output (EXTI16) */
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM16_Msk);
    SET_BIT(EXTI->RTSR1, EXTI_RTSR1_RT16_Msk);
    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT16_Msk);

    /* Включить и настроить NVIC */
    NVIC_SetPriority(PVD_PVM_IRQn, 5);
    NVIC_EnableIRQ(PVD_PVM_IRQn);
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Обработать прерывание PWR PVD
 */
void pwr_pvd_pvm_it_handler(void)
{
    /* Проверить прерывание EXTI16 - PVD output */
    if (READ_BIT(EXTI->PR1, EXTI_PR1_PR16_Msk)) {
        /* Сбросить прерывание */
        SET_BIT(EXTI->PR1, EXTI_PR1_PR16_Msk);

        /* Изменить состояние VDD */
        vdd_is_lower = READ_BIT(PWR->SR1, PWR_SR1_PVDO_Msk) ?
                true : false;

        /* Вызвать функцию обратного вызова */
        pwr_pvd_status_changed_callback();
    }
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Получить состояние VDD
 *
 * @return          Состояние VDD
 */
inline bool pwr_vdd_is_lower(void)
{
    return vdd_is_lower;
}
/* ------------------------------------------------------------------------- */

__WEAK void pwr_pvd_status_changed_callback(void)
{

}
/* ------------------------------------------------------------------------- */
