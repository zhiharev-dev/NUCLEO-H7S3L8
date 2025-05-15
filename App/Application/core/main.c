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

#include "main.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define VTOR_ADDRESS        0x70000000

#define HSI_CLOCK           64000000

#define CPU_CLOCK           600000000

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* Системный таймер */
volatile uint32_t systick;

/* FreeRTOS */
static uint32_t appl_idle_hook_counter;
static size_t free_heap_size;
static size_t minimum_ever_free_heap_size;

/* Private function prototypes --------------------------------------------- */

static void setup_hardware(void);

static void setup_vector_table(void);

static void setup_fpu(void);

static void app_main(void *argv);

static void systick_init(const uint32_t frequency);

/* Private user code ------------------------------------------------------- */

int main(void)
{
    setup_hardware();

    xTaskCreate(app_main,
                "app_main",
                configMINIMAL_STACK_SIZE * 4,
                NULL,
                tskIDLE_PRIORITY + 1,
                NULL);

    vTaskStartScheduler();
}
/* ------------------------------------------------------------------------- */

void error(void)
{
    __disable_irq();

    while (true)
        ;
}
/* ------------------------------------------------------------------------- */

static void app_main(void *argv)
{
    static const TickType_t frequency = pdMS_TO_TICKS(1000);

    TickType_t last_wake_time = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&last_wake_time, frequency);
    }

    vTaskDelete(NULL);
}
/* ------------------------------------------------------------------------- */

void vApplicationIdleHook(void)
{
    /* Отслеживание свободного времени FreeRTOS */
    appl_idle_hook_counter++;
    /* Обновить информацию об используемой памяти FreeRTOS */
    free_heap_size = xPortGetFreeHeapSize();
    minimum_ever_free_heap_size = xPortGetMinimumEverFreeHeapSize();
}
/* ------------------------------------------------------------------------- */

static void setup_hardware(void)
{
    setup_vector_table();
    setup_fpu();

    systick_init(CPU_CLOCK);
}
/* ------------------------------------------------------------------------- */

static void setup_vector_table(void)
{
    __disable_irq();
    __set_PRIMASK(1);

    WRITE_REG(SCB->VTOR, VTOR_ADDRESS);

    __set_PRIMASK(0);
    __enable_irq();
}
/* ------------------------------------------------------------------------- */

static void setup_fpu(void)
{
    SET_BIT(SCB->CPACR, (0x03 << 20) | (0x03 << 22));
}
/* ------------------------------------------------------------------------- */

/**
 * @brief           Инициализировать SysTick
 */
static void systick_init(const uint32_t frequency)
{
    /* Сбросить настройки */
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
