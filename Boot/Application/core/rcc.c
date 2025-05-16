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

static void rcc_setup_hse(void);

static void rcc_setup_pll(void);

static void rcc_setup_bus(void);

static void rcc_setup_clksource_cpu(void);

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Инициализировать RCC
 */
void rcc_init(void)
{
    rcc_setup_hse();
    rcc_setup_pll();
    rcc_setup_bus();
    rcc_setup_clksource_cpu();
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Настроить HSE
 */
static void rcc_setup_hse(void)
{
    /* Включить HSE */
    SET_BIT(RCC->CR, RCC_CR_HSEON_Msk);

    /* Ожидание готовности HSE */
    uint32_t tickstart = systick_get_tick();

    while (!READ_BIT(RCC->CR, RCC_CR_HSERDY_Msk)) {
        if (systick_get_tick() - tickstart >= RCC_HSERDY_TIMEOUT)
            error();
    }

    /* Включить CSS HSE */
    SET_BIT(RCC->CR, RCC_CR_HSECSSON_Msk);
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Настроить PLL
 */
static void rcc_setup_pll(void)
{
    /* Выключить PLL1..3 перед настройкой */
    CLEAR_BIT(RCC->CR,
              RCC_CR_PLL1ON_Msk
            | RCC_CR_PLL2ON_Msk
            | RCC_CR_PLL3ON_Msk);

    /* Настроить источник тактирования и делители DIVM */
    WRITE_REG(RCC->PLLCKSELR,
              0x02 << RCC_PLLCKSELR_PLLSRC_Pos                  /* Источник тактирования = HSE (24MHz) */
            | 0x0C << RCC_PLLCKSELR_DIVM1_Pos                   /* DIVM1 = 24MHz / 12 = 2MHz */
            | 0x04 << RCC_PLLCKSELR_DIVM2_Pos);                 /* DIVM2 = 24MHz / 4 = 6MHz */


    /* PLL1 ---------------------------------------------------------------- */

    /* Настроить RGE и VCO */
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLL1RGE_Msk,                         /* RGE = 1MHz..2MHz */
               RCC_PLLCFGR_PLL1VCOSEL_Msk);                     /* VCO = High (384MHz..1672MHz, ref1_ck = 2MHz..16MHz) */

    /* Настроить Fractional */
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN_Msk);

    CLEAR_REG(RCC->PLL1FRACR);                                  /* Fractional = 0 */

    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1FRACEN_Msk);

    /* Настроить DIVN */
    MODIFY_REG(RCC->PLL1DIVR1,
               RCC_PLL1DIVR1_DIVN_Msk,
               (300 - 1) << RCC_PLL1DIVR1_DIVN_Pos);            /* DIVN = 2MHz * 300 = 600MHz */

    /* Включить и настроить DIVP */
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN_Msk);

    MODIFY_REG(RCC->PLL1DIVR1,
               RCC_PLL1DIVR1_DIVP_Msk,
               (1 - 1) << RCC_PLL1DIVR1_DIVP_Pos);              /* DIVP = 600MHz / 1 = 600MHz */

    /* Включить PLL */
    SET_BIT(RCC->CR, RCC_CR_PLL1ON_Msk);
    while (!READ_BIT(RCC->CR, RCC_CR_PLL1RDY_Msk))
        continue;


    /* PLL2 ---------------------------------------------------------------- */

    /* Настроить RGE и VCO */
    MODIFY_REG(RCC->PLLCFGR,
               RCC_PLLCFGR_PLL2RGE_Msk,
               RCC_PLLCFGR_PLL2VCOSEL_Msk                       /* VCO = High (384MHz..1672MHz, ref2_ck = 2MHz..16MHz) */
             | 0x02 << RCC_PLLCFGR_PLL2RGE_Pos);                /* RGE = 4MHz..8MHz */

    /* Настроить Fractional */
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN_Msk);

    CLEAR_REG(RCC->PLL2FRACR);                                  /* Fractional = 0 */

    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2FRACEN_Msk);

    /* Настроить DIVN */
    MODIFY_REG(RCC->PLL2DIVR1,
               RCC_PLL2DIVR1_DIVN_Msk,
               (100 - 1) << RCC_PLL2DIVR1_DIVN_Pos);            /* DIVN = 6MHz * 100 = 600MHz */

    /* Включить и настроить DIVT */
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2TEN_Msk);

    MODIFY_REG(RCC->PLL2DIVR2,
               RCC_PLL2DIVR2_DIVT_Msk,
               (3 - 1) << RCC_PLL2DIVR2_DIVT_Pos);              /* DIVT = 600MHz / 3 = 200MHz */

    /* Включить PLL */
    SET_BIT(RCC->CR, RCC_CR_PLL2ON_Msk);
    while (!READ_BIT(RCC->CR, RCC_CR_PLL2RDY_Msk))
        continue;
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Настроить BUS
 */
static void rcc_setup_bus(void)
{
    /* Настроить делитель CPU */
    CLEAR_REG(RCC->CDCFGR);                         /* CPU = 600MHz / 1 = 600MHz */

    /* Настроить делитель Bus Matrix */
    MODIFY_REG(RCC->BMCFGR,
               RCC_BMCFGR_BMPRE_Msk,
               0x08 << RCC_BMCFGR_BMPRE_Pos);       /* Bus Matrix = 600MHz / 2 = 300MHz */

    /* Настроить делители APB */
    WRITE_REG(RCC->APBCFGR,
              0x04 << RCC_APBCFGR_PPRE1_Pos         /* APB1 = 300MHz / 2 = 150MHz */
            | 0x04 << RCC_APBCFGR_PPRE2_Pos         /* APB2 = 300MHz / 2 = 150MHz */
            | 0x04 << RCC_APBCFGR_PPRE4_Pos         /* APB4 = 300MHz / 2 = 150MHz */
            | 0x04 << RCC_APBCFGR_PPRE5_Pos);       /* APB5 = 300MHz / 2 = 150MHz */
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Настроить источник тактирования CPU
 */
static void rcc_setup_clksource_cpu(void)
{
    /* Настроить источник тактирования CPU = PLL1P */
    MODIFY_REG(RCC->CFGR,
               RCC_CFGR_SW_Msk,
               0x03 << RCC_CFGR_SW_Pos);

    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS_Msk) !=
            0x03 << RCC_CFGR_SWS_Pos)
        continue;
}
/* ------------------------------------------------------------------------- */
