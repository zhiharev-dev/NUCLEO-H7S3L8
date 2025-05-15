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

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>

    void xPortSysTickHandler( void );
#endif

#define configUSE_PREEMPTION                                1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION             0
#define configUSE_TICKLESS_IDLE                             0
#define configCPU_CLOCK_HZ                                  600000000
#define configTICK_RATE_HZ                                  1000
#define configMAX_PRIORITIES                                7
#define configMINIMAL_STACK_SIZE                            128
#define configMAX_TASK_NAME_LEN                             16
#define configTICK_TYPE_WIDTH_IN_BITS                       TICK_TYPE_WIDTH_32_BITS
#define configIDLE_SHOULD_YIELD                             0
#define configUSE_MUTEXES                                   1
#define configUSE_RECURSIVE_MUTEXES                         1
#define configUSE_COUNTING_SEMAPHORES                       1
#define configUSE_TIME_SLICING                              0

/* Memory allocation related definitions. */
#define configSUPPORT_STATIC_ALLOCATION                     0
#define configSUPPORT_DYNAMIC_ALLOCATION                    1
#define configTOTAL_HEAP_SIZE                               65536
#define configAPPLICATION_ALLOCATED_HEAP                    0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP           0

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                                 1
#define configUSE_TICK_HOOK                                 0
#define configCHECK_FOR_STACK_OVERFLOW                      0
#define configUSE_MALLOC_FAILED_HOOK                        0
#define configUSE_DAEMON_TASK_STARTUP_HOOK                  0
#define configUSE_SB_COMPLETED_CALLBACK                     0

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS                       0
#define configUSE_TRACE_FACILITY                            0
#define configUSE_STATS_FORMATTING_FUNCTIONS                0

/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES                               0
#define configMAX_CO_ROUTINE_PRIORITIES                     1

/* Software timer related definitions. */
#define configUSE_TIMERS                                    1
#define configTIMER_TASK_PRIORITY                           3
#define configTIMER_QUEUE_LENGTH                            10
#define configTIMER_TASK_STACK_DEPTH                        configMINIMAL_STACK_SIZE

/* Interrupt nesting behaviour configuration. */

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
    /* __NVIC_PRIO_BITS will be specified when CMSIS is being used. */
    #define configPRIO_BITS         __NVIC_PRIO_BITS
#else
     #define configPRIO_BITS        4       /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority" function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY     15

/* The highest interrupt priority that can be used by any interrupt service
   routine that makes calls to interrupt safe FreeRTOS API functions. DO NOT CALL
   INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
   PRIORITY THAN THIS! higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY        5

#define configKERNEL_INTERRUPT_PRIORITY     ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY        ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

/* Define to trap errors during development. */
#define configASSERT( x )       if ( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ) {} }

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_xTaskResumeFromISR              1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_xEventGroupSetBitFromISR        1
#define INCLUDE_xTimerPendFunctionCall          1

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS standard names. */
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler      PendSV_Handler

#endif /* FREERTOS_CONFIG_H */
