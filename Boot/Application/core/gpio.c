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

#include "gpio.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Private function prototypes --------------------------------------------- */

static void gpio_octospi_init(void);

static void gpio_led_init(void);

/* Private user code ------------------------------------------------------- */

/**
 * @brief           Инициализировать GPIO
 */
void gpio_init(void)
{
    /* Включить тактирование */
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOAEN_Msk);
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN_Msk);
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIODEN_Msk);
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIONEN_Msk);

    gpio_octospi_init();
    gpio_led_init();
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Инициализировать GPIO OCTOSPI
 */
static void gpio_octospi_init(void)
{
    /*
     * NCS GPION1
     * DQS GPION0
     * CLK GPION6
     * IO0 GPION2
     * IO1 GPION3
     * IO2 GPION4
     * IO3 GPION5
     * IO4 GPION8
     * IO5 GPION9
     * IO6 GPION10
     * IO7 GPION11
     */

    /* Настроить режим работы = AF */
    MODIFY_REG(GPION->MODER,
               GPIO_MODER_MODE0_Msk
             | GPIO_MODER_MODE1_Msk
             | GPIO_MODER_MODE2_Msk
             | GPIO_MODER_MODE3_Msk
             | GPIO_MODER_MODE4_Msk
             | GPIO_MODER_MODE5_Msk
             | GPIO_MODER_MODE6_Msk
             | GPIO_MODER_MODE8_Msk
             | GPIO_MODER_MODE9_Msk
             | GPIO_MODER_MODE10_Msk
             | GPIO_MODER_MODE11_Msk,
               0x02 << GPIO_MODER_MODE0_Pos
             | 0x02 << GPIO_MODER_MODE1_Pos
             | 0x02 << GPIO_MODER_MODE2_Pos
             | 0x02 << GPIO_MODER_MODE3_Pos
             | 0x02 << GPIO_MODER_MODE4_Pos
             | 0x02 << GPIO_MODER_MODE5_Pos
             | 0x02 << GPIO_MODER_MODE6_Pos
             | 0x02 << GPIO_MODER_MODE8_Pos
             | 0x02 << GPIO_MODER_MODE9_Pos
             | 0x02 << GPIO_MODER_MODE10_Pos
             | 0x02 << GPIO_MODER_MODE11_Pos);

    /* Настроить тип вывода = Push-Pull */
    CLEAR_BIT(GPION->OTYPER,
              GPIO_OTYPER_OT0_Msk
            | GPIO_OTYPER_OT1_Msk
            | GPIO_OTYPER_OT2_Msk
            | GPIO_OTYPER_OT3_Msk
            | GPIO_OTYPER_OT4_Msk
            | GPIO_OTYPER_OT5_Msk
            | GPIO_OTYPER_OT6_Msk
            | GPIO_OTYPER_OT8_Msk
            | GPIO_OTYPER_OT9_Msk
            | GPIO_OTYPER_OT10_Msk
            | GPIO_OTYPER_OT11_Msk);

    /* Настроить скорость работы вывода = Very High Speed */
    SET_BIT(GPION->OSPEEDR,
            GPIO_OSPEEDR_OSPEED0_Msk
          | GPIO_OSPEEDR_OSPEED1_Msk
          | GPIO_OSPEEDR_OSPEED2_Msk
          | GPIO_OSPEEDR_OSPEED3_Msk
          | GPIO_OSPEEDR_OSPEED4_Msk
          | GPIO_OSPEEDR_OSPEED5_Msk
          | GPIO_OSPEEDR_OSPEED6_Msk
          | GPIO_OSPEEDR_OSPEED8_Msk
          | GPIO_OSPEEDR_OSPEED9_Msk
          | GPIO_OSPEEDR_OSPEED10_Msk
          | GPIO_OSPEEDR_OSPEED11_Msk);

    /* Настроить подтяжку сигнала вывода = No-Pull */
    CLEAR_BIT(GPION->PUPDR,
              GPIO_PUPDR_PUPD0_Msk
            | GPIO_PUPDR_PUPD1_Msk
            | GPIO_PUPDR_PUPD2_Msk
            | GPIO_PUPDR_PUPD3_Msk
            | GPIO_PUPDR_PUPD4_Msk
            | GPIO_PUPDR_PUPD5_Msk
            | GPIO_PUPDR_PUPD6_Msk
            | GPIO_PUPDR_PUPD8_Msk
            | GPIO_PUPDR_PUPD9_Msk
            | GPIO_PUPDR_PUPD10_Msk
            | GPIO_PUPDR_PUPD11_Msk);

    /* Настроить альтернативную функцию = 9 */
    MODIFY_REG(GPION->AFR[0],
               GPIO_AFRL_AFSEL0_Msk
             | GPIO_AFRL_AFSEL1_Msk
             | GPIO_AFRL_AFSEL2_Msk
             | GPIO_AFRL_AFSEL3_Msk
             | GPIO_AFRL_AFSEL4_Msk
             | GPIO_AFRL_AFSEL5_Msk
             | GPIO_AFRL_AFSEL6_Msk,
               0x09 << GPIO_AFRL_AFSEL0_Pos
             | 0x09 << GPIO_AFRL_AFSEL1_Pos
             | 0x09 << GPIO_AFRL_AFSEL2_Pos
             | 0x09 << GPIO_AFRL_AFSEL3_Pos
             | 0x09 << GPIO_AFRL_AFSEL4_Pos
             | 0x09 << GPIO_AFRL_AFSEL5_Pos
             | 0x09 << GPIO_AFRL_AFSEL6_Pos);
    MODIFY_REG(GPION->AFR[1],
               GPIO_AFRH_AFSEL8_Msk
             | GPIO_AFRH_AFSEL9_Msk
             | GPIO_AFRH_AFSEL10_Msk
             | GPIO_AFRH_AFSEL11_Msk,
               0x09 << GPIO_AFRH_AFSEL8_Pos
             | 0x09 << GPIO_AFRH_AFSEL9_Pos
             | 0x09 << GPIO_AFRH_AFSEL10_Pos
             | 0x09 << GPIO_AFRH_AFSEL11_Pos);
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Инициализировать GPIO LED
 */
static void gpio_led_init(void)
{
    /*
     * LD1 GREEN GPIOD10
     * LD2 YELLOW GPIOD13
     * LD3 RED GPIOB7
     */

    /* GPIOB --------------------------------------------------------------- */

    /* Настроить режим работы = Output */
    MODIFY_REG(GPIOB->MODER,
               GPIO_MODER_MODE7_Msk,
               0x01 << GPIO_MODER_MODE7_Pos);

    /* Настроить тип вывода = Push-Pull */
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT7_Msk);

    /* Настроить скорость работы вывода = Low Speed */
    CLEAR_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED7_Msk);

    /* Настроить подтяжку сигнала = Pull-Up */
    MODIFY_REG(GPIOB->PUPDR,
               GPIO_PUPDR_PUPD7_Msk,
               0x02 << GPIO_PUPDR_PUPD7_Pos);


    /* GPIOD --------------------------------------------------------------- */

    /* Настроить режим работы = Output */
    MODIFY_REG(GPIOD->MODER,
               GPIO_MODER_MODE10_Msk
             | GPIO_MODER_MODE13_Msk,
               0x01 << GPIO_MODER_MODE10_Pos
             | 0x01 << GPIO_MODER_MODE13_Pos);

    /* Настроить тип вывода = Push-Pull */
    CLEAR_BIT(GPIOD->OTYPER,
              GPIO_OTYPER_OT10_Msk
            | GPIO_OTYPER_OT13_Msk);

    /* Настроить скорость работы вывода = Low Speed */
    CLEAR_BIT(GPIOD->OSPEEDR,
              GPIO_OSPEEDR_OSPEED10_Msk
            | GPIO_OSPEEDR_OSPEED13_Msk);

    /* Настроить подтяжку сигнала = Pull-Up */
    MODIFY_REG(GPIOD->PUPDR,
               GPIO_PUPDR_PUPD10_Msk
             | GPIO_PUPDR_PUPD13_Msk,
               0x02 << GPIO_PUPDR_PUPD10_Pos
             | 0x02 << GPIO_PUPDR_PUPD13_Pos);
}
/* ------------------------------------------------------------------------- */
