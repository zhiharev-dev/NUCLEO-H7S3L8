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

#include "flash.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

static void flash_setup_option(void);

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Инициализировать FLASH
 */
void flash_init(void)
{
    /* Настроить LATENCY = 7WS и WRHIGHFREQ = 3 */
    WRITE_REG(FLASH->ACR,
              0x07 << FLASH_ACR_LATENCY_Pos
            | 0x03 << FLASH_ACR_WRHIGHFREQ_Pos);

    flash_setup_option();
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Настроить опции FLASH
 */
static void flash_setup_option(void)
{
    /* Настроить High Speed Low Voltage для XSPI2 */
    if (READ_BIT(FLASH->OBW1SR, FLASH_OBW1SR_XSPI2_HSLV_Msk))
        return;

    /* Разблокировать OPTCR */
    WRITE_REG(FLASH->OPTKEYR, 0x08192A3B);
    WRITE_REG(FLASH->OPTKEYR, 0x4C5D6E7F);

    while (READ_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK_Msk))
        continue;

    /* Включить запись опций */
    SET_BIT(FLASH->OPTCR, FLASH_OPTCR_PG_OPT_Msk);

    /* Записать High Speed Low Voltage для XSPI2 */
    SET_BIT(FLASH->OBW1SRP, FLASH_OBW1SRP_XSPI2_HSLV_Msk);

    /* Ожидание завершения записи */
    while (READ_BIT(FLASH->SR, FLASH_SR_QW_Msk))
        continue;

    /* Выключить запись опций */
    CLEAR_BIT(FLASH->OPTCR, FLASH_OPTCR_PG_OPT_Msk);

    /* Заблокировать OPTCR */
    SET_BIT(FLASH->OPTCR, FLASH_OPTCR_OPTLOCK_Msk);
}
/* ------------------------------------------------------------------------- */
