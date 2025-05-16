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
#include "systick.h"
#include "pwr.h"
#include "rcc.h"
#include "led.h"

/* Private macros ---------------------------------------------------------- */

/* Private constants ------------------------------------------------------- */

#define VTOR_ADDRESS        0x70000000

#define HSI_CLOCK           64000000

#define CPU_CLOCK           600000000

/* Private types ----------------------------------------------------------- */

/* Private variables ------------------------------------------------------- */

/* FreeRTOS */
static uint32_t appl_idle_hook_counter;
static size_t free_heap_size;
static size_t minimum_ever_free_heap_size;

/* Private function prototypes --------------------------------------------- */

static void setup_hardware(void);

static void setup_vector_table(void);

static void setup_fpu(void);

static void app_main(void *argv);

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

    /* Выключить светодиоды */
    led_off(LED_GREEN);
    led_off(LED_YELLOW);
    led_off(LED_RED);

    while (true) {
        /* Включить красный светодиод - Ошибка */
        led_on(LED_RED);
    }
}
/* ------------------------------------------------------------------------- */

static void app_main(void *argv)
{
    static const TickType_t frequency = pdMS_TO_TICKS(1000);

    TickType_t last_wake_time = xTaskGetTickCount();

    while (true) {
        vTaskDelayUntil(&last_wake_time, frequency);

        /* Включить зеленый светодиод - Индикация перехода в приложение */
        led_on(LED_GREEN);
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
    pwr_init();
    rcc_init();
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
