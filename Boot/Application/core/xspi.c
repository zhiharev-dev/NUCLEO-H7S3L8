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

#include "xspi.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Инициализировать XSPI
 */
void xspi_init(void)
{
    /* Включить XSPIM2 */
    SET_BIT(PWR->CSR2, PWR_CSR2_EN_XSPIM2_Msk);

    /* Включить тактирование SBS */
    SET_BIT(RCC->APB4ENR, RCC_APB4ENR_SBSEN_Msk);

    /* Установить High Speed Low Voltage XSPI2 */
    SET_BIT(SBS->CCCSR, SBS_CCCSR_XSPI2_IOHSLV_Msk);

    /* Включить тактирование XSPIM */
    SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPIMEN_Msk);

    /* Настроить источник тактирования XSPI2 */
    MODIFY_REG(RCC->CCIPR1,
               RCC_CCIPR1_XSPI2SEL_Msk,
               0x02 << RCC_CCIPR1_XSPI2SEL_Pos);

    /* Включить тактирование XSPI2 */
    SET_BIT(RCC->AHB5ENR, RCC_AHB5ENR_XSPI2EN_Msk);

    /* Включить защиту часов XSPI */
    SET_BIT(RCC->CKPROTR, RCC_CKPROTR_XSPICKP_Msk);


    /* Настроить XSPIM ----------------------------------------------------- */

    /* Выключить XSPI1..2 перед настройкой */
    CLEAR_BIT(XSPI1->CR, XSPI_CR_EN_Msk);
    CLEAR_BIT(XSPI2->CR, XSPI_CR_EN_Msk);

    /* Включить и настроить переопределение NCS */
    WRITE_REG(XSPIM->CR,
              0x01 << XSPIM_CR_CSSEL_OVR_O1_Pos         /* Для XSPI1 - NCS2 */
            | 0x00 << XSPIM_CR_CSSEL_OVR_O2_Pos         /* Для XSPI2 - NCS1 */
            | XSPIM_CR_CSSEL_OVR_EN_Msk);


    /* Настроить XSPI2 ----------------------------------------------------- */

    /* Настроить режим работы часов = Mode 0 */
    CLEAR_BIT(XSPI2->DCR1, XSPI_DCR1_CKMODE_Msk);

    /* Настроить делитель часов = /4 (200MHz / 4 = 50MHz) */
    MODIFY_REG(XSPI2->DCR2,
               XSPI_DCR2_PRESCALER_Msk,
               (4 - 1) << XSPI_DCR2_PRESCALER_Pos);

    /* Настроить тип и размер памяти = Macronix 32MB */
    MODIFY_REG(XSPI2->DCR1,
               XSPI_DCR1_MTYP_Msk
             | XSPI_DCR1_DEVSIZE_Msk,
               0x01 << XSPI_DCR1_MTYP_Pos
             | 0x18 << XSPI_DCR1_DEVSIZE_Pos);

    /* Настроить сигнал IO и NCS */
    CLEAR_BIT(XSPI2->CR,
              XSPI_CR_MSEL_Msk                  /* IO[7:0] */
            | XSPI_CR_CSSEL_Msk);               /* NCS1 */

    /* Настроить минимальное количество циклов,
     * при котором NCS должен оставаться высоким между командами */
    MODIFY_REG(XSPI2->DCR1,
               XSPI_DCR1_CSHT_Msk,
               (2 - 1) << XSPI_DCR1_CSHT_Pos);

    /* Настроить FIFO */
    MODIFY_REG(XSPI2->CR,
               XSPI_CR_FTHRES_Msk,
               (4 - 1) << XSPI_CR_FTHRES_Pos);

    /* Включить XSPI */
    SET_BIT(XSPI2->CR, XSPI_CR_EN_Msk);
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Настроить максимальное значение частоты для XSPI
 */
void xspi_setup_max_frequency(void)
{
    /* Настроить делитель часов = /1 (200MHz / 1 = 200MHz) */
    CLEAR_BIT(XSPI2->DCR2, XSPI_DCR2_PRESCALER_Msk);
}
/* ------------------------------------------------------------------------- */
