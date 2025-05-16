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

#ifndef LED_H_
#define LED_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "main.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

/* Exported types ---------------------------------------------------------- */

/**
 * @brief           Определение перечисления идентификаторов светодиодов
 */
enum led_id {
    LED_GREEN,
    LED_YELLOW,
    LED_RED,
    /* --- */
    LED_NONE = -1,
};


/**
 * @brief           Определение перечисления состояний светодиода
 */
enum led_state {
    LED_OFF,
    LED_ON,
};


/**
 * @brief           Определение структуры данных светодиода
 */
struct led {
    GPIO_TypeDef *gpio;                         /*!< Указатель на стрктуру данных GPIO */

    uint32_t pin;                               /*!< Номер порта ввода-вывода GPIO */
};

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void led_on(int32_t id);

void led_off(int32_t id);

void led_toggle(int32_t id);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LED_H_ */
