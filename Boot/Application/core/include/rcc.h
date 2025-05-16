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

#ifndef RCC_H_
#define RCC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "main.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

#define RCC_CPU_CLOCK            600000000
#define RCC_BUS_MATRIX_CLOCK     (RCC_CPU_CLOCK / 2)
#define RCC_APB1_CLOCK           (RCC_BUS_MATRIX_CLOCK / 2)
#define RCC_APB2_CLOCK           (RCC_BUS_MATRIX_CLOCK / 2)
#define RCC_APB4_CLOCK           (RCC_BUS_MATRIX_CLOCK / 2)
#define RCC_APB5_CLOCK           (RCC_BUS_MATRIX_CLOCK / 2)

/* Exported types ---------------------------------------------------------- */

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

void rcc_init(void);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RCC_H_ */
