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

#ifndef MX25UW_H_
#define MX25UW_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ---------------------------------------------------------------- */

#include "main.h"

/* Exported macros --------------------------------------------------------- */

/* Exported constants ------------------------------------------------------ */

#define MX25UW_MANUFACTURER_ID                          0xC2

#define MX25UW_FLASH_SIZE                               0x2000000
#define MX25UW_BLOCK_SIZE                               0x10000
#define MX25UW_SECTOR_SIZE                              0x1000
#define MX25UW_PAGE_SIZE                                0x100

#define MX25UW_READ_CMD                                 0x03            /* Normal Read 3 Byte Address */
#define MX25UW_FAST_READ_CMD                            0x0B            /* Fast Read 3 Byte Address */
#define MX25UW_PAGE_PROG_CMD                            0x02            /* Page Program 3 Byte Address */
#define MX25UW_SECTOR_ERASE_CMD                         0x20            /* SubSector Erase 4KB 3 Byte Address*/
#define MX25UW_BLOCK_ERASE_CMD                          0xD8            /* Sector Erase 64KB 3 Byte Address*/
#define MX25UW_CHIP_ERASE_CMD                           0x60            /* Bulk Erase */

#define MX25UW_READ_4B_ADDR_CMD                         0x13            /* Normal Read 4 Byte address */
#define MX25UW_FAST_READ_4B_ADDR_CMD                    0x0C            /* Fast Read 4 Byte address */
#define MX25UW_PAGE_PROG_4B_ADDR_CMD                    0x12            /* Page Program 4 Byte Address */
#define MX25UW_SECTOR_ERASE_4B_ADDR_CMD                 0x21            /* SubSector Erase 4KB 4 Byte Address */
#define MX25UW_BLOCK_ERASE_4B_ADDR_CMD                  0xDC            /* Sector Erase 64KB 4 Byte Address */

#define MX25UW_WRITE_ENABLE_CMD                         0x06            /* Write Enable */
#define MX25UW_WRITE_DISABLE_CMD                        0x04            /* Write Disable */
#define MX25UW_PROG_ERASE_SUSPEND_CMD                   0xB0            /* Program/Erase suspend */
#define MX25UW_PROG_ERASE_RESUME_CMD                    0x30            /* Program/Erase resume */
#define MX25UW_ENTER_DEEP_POWER_DOWN_CMD                0xB9            /* Enter deep power down */
#define MX25UW_RELEASE_FROM_DEEP_POWER_DOWN_CMD         0xAB            /* Release from deep power down */
#define MX25UW_SET_BURST_LENGTH_CMD                     0xC0            /* Set burst length */
#define MX25UW_ENTER_SECURED_OTP_CMD                    0xB1            /* Enter secured OTP) */
#define MX25UW_EXIT_SECURED_OTP_CMD                     0xC1            /* Exit secured OTP) */

#define MX25UW_NOP_CMD                                  0x00            /* No operation */
#define MX25UW_RESET_ENABLE_CMD                         0x66            /* Reset Enable */
#define MX25UW_RESET_MEMORY_CMD                         0x99            /* Reset Memory */

#define MX25UW_READ_ID_CMD                              0x9F            /* Read IDentification */
#define MX25UW_READ_SERIAL_FLASH_DISCO_PARAM_CMD        0x5A            /* Read Serial Flash Discoverable Parameter */
#define MX25UW_READ_STATUS_REG_CMD                      0x05            /* Read Status Register */
#define MX25UW_READ_CFG_REG_CMD                         0x15            /* Read configuration Register */
#define MX25UW_WRITE_STATUS_REG_CMD                     0x01            /* Write Status Register */
#define MX25UW_READ_CFG_REG2_CMD                        0x71            /* Read configuration Register2 */
#define MX25UW_WRITE_CFG_REG2_CMD                       0x72            /* Write configuration Register2 */
#define MX25UW_READ_FAST_BOOT_REG_CMD                   0x16            /* Read fast boot Register */
#define MX25UW_WRITE_FAST_BOOT_REG_CMD                  0x17            /* Write fast boot Register */
#define MX25UW_ERASE_FAST_BOOT_REG_CMD                  0x18            /* Erase fast boot Register */
#define MX25UW_READ_SECURITY_REG_CMD                    0x2B            /* Read security Register */
#define MX25UW_WRITE_SECURITY_REG_CMD                   0x2F            /* Write security Register */
#define MX25UW_READ_LOCK_REG_CMD                        0x2D            /* Read lock Register */
#define MX25UW_WRITE_LOCK_REG_CMD                       0x2C            /* Write lock Register */

#define MX25UW_READ_DPB_REG_CMD                         0xE0            /* Read DPB register */
#define MX25UW_WRITE_DPB_REG_CMD                        0xE1            /* Write DPB register */
#define MX25UW_READ_SPB_STATUS_CMD                      0xE2            /* Read SPB status */
#define MX25UW_WRITE_SPB_BIT_CMD                        0xE3            /* SPB bit program */
#define MX25UW_ERASE_ALL_SPB_CMD                        0xE4            /* Erase all SPB bit */
#define MX25UW_WRITE_PROTECT_SEL_CMD                    0x68            /* Write Protect selection */
#define MX25UW_GANG_BLOCK_LOCK_CMD                      0x7E            /* Gang block lock: whole chip write protect */
#define MX25UW_GANG_BLOCK_UNLOCK_CMD                    0x98            /* Gang block unlock: whole chip write unprotect */
#define MX25UW_READ_PASSWORD_REGISTER_CMD               0x27            /* Read Password */
#define MX25UW_WRITE_PASSWORD_REGISTER_CMD              0x28            /* Write Password */
#define MX25UW_PASSWORD_UNLOCK_CMD                      0x29            /* Unlock Password */
#define MX25UW_PAGE_BUFFER_READ                         0x25            /* Page Buffer Read */
#define MX25UW_WRITE_BUFFER_INITIAL                     0x22            /* Write Buffer Initial */
#define MX25UW_WRITE_BUFFER_CONTINUE                    0x24            /* Write Buffer Continue */
#define MX25UW_WRITE_BUFFER_CONFIRM                     0x31            /* Write Buffer Confirm */

#define MX25UW_OPI_READ_CMD                             0xEC13          /* OPI IO Read */
#define MX25UW_OPI_READ_DTR_CMD                         0xEE11          /* OPI IO Read DTR */
#define MX25UW_OPI_PAGE_PROG_CMD                        0x12ED          /* OPI Page Program */
#define MX25UW_OPI_SECTOR_ERASE_CMD                     0x21DE          /* OPI SubSector Erase 4KB */
#define MX25UW_OPI_BLOCK_ERASE_CMD                      0xDC23          /* OPI Sector Erase 64KB */
#define MX25UW_OPI_CHIP_ERASE_CMD                       0x609F          /* OPI Bulk Erase */

#define MX25UW_OPI_WRITE_ENABLE_CMD                     0x06F9          /* OPI Write Enable */
#define MX25UW_OPI_WRITE_DISABLE_CMD                    0x04FB          /* OPI Write Disable */
#define MX25UW_OPI_PROG_ERASE_SUSPEND_CMD               0xB04F          /* OPI Program/Erase suspend */
#define MX25UW_OPI_PROG_ERASE_RESUME_CMD                0x30CF          /* OPI Program/Erase resume */
#define MX25UW_OPI_ENTER_DEEP_POWER_DOWN_CMD            0xB946          /* OPI Enter deep power down */
#define MX25UW_OPI_RELEASE_FROM_DEEP_POWER_DOWN_CMD     0xAB54          /* OPI Release from deep power down */
#define MX25UW_OPI_SET_BURST_LENGTH_CMD                 0xC03F          /* OPI Set burst length */
#define MX25UW_OPI_ENTER_SECURED_OTP_CMD                0xB14E          /* OPI Enter secured OTP) */
#define MX25UW_OPI_EXIT_SECURED_OTP_CMD                 0xC13E          /* OPI Exit secured OTP) */

#define MX25UW_OPI_NOP_CMD                              0x00FF          /* OPI No operation */
#define MX25UW_OPI_RESET_ENABLE_CMD                     0x6699          /* OPI Reset Enable */
#define MX25UW_OPI_RESET_MEMORY_CMD                     0x9966          /* OPI Reset Memory */

#define MX25UW_OPI_READ_ID_CMD                          0x9F60          /* OPI Read IDentification */
#define MX25UW_OPI_READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5AA5          /* OPI Read Serial Flash Discoverable Parameter */
#define MX25UW_OPI_READ_STATUS_REG_CMD                  0x05FA          /* OPI Read Status Register */
#define MX25UW_OPI_READ_CFG_REG_CMD                     0x15EA          /* OPI Read configuration Register */
#define MX25UW_OPI_WRITE_STATUS_REG_CMD                 0x01FE          /* OPI Write Status Register */
#define MX25UW_OPI_READ_CFG_REG2_CMD                    0x718E          /* OPI Read configuration Register2 */
#define MX25UW_OPI_WRITE_CFG_REG2_CMD                   0x728D          /* OPI Write configuration Register2 */
#define MX25UW_OPI_READ_FAST_BOOT_REG_CMD               0x16E9          /* OPI Read fast boot Register */
#define MX25UW_OPI_WRITE_FAST_BOOT_REG_CMD              0x17E8          /* OPI Write fast boot Register */
#define MX25UW_OPI_ERASE_FAST_BOOT_REG_CMD              0x18E7          /* OPI Erase fast boot Register */
#define MX25UW_OPI_READ_SECURITY_REG_CMD                0x2BD4          /* OPI Read security Register */
#define MX25UW_OPI_WRITE_SECURITY_REG_CMD               0x2FD0          /* OPI Write security Register */
#define MX25UW_OPI_READ_LOCK_REG_CMD                    0x2DD2          /* OPI Read lock Register */
#define MX25UW_OPI_WRITE_LOCK_REG_CMD                   0x2CD3          /* OPI Write lock Register */
#define MX25UW_OPI_READ_DPB_REG_CMD                     0xE01F          /* OPI Read DPB register */
#define MX25UW_OPI_WRITE_DPB_REG_CMD                    0xE11E          /* OPI Write DPB register */
#define MX25UW_OPI_READ_SPB_STATUS_CMD                  0xE21D          /* OPI Read SPB status */
#define MX25UW_OPI_WRITE_SPB_BIT_CMD                    0xE31C          /* OPI SPB bit program */
#define MX25UW_OPI_ERASE_ALL_SPB_CMD                    0xE41B          /* OPI Erase all SPB bit */
#define MX25UW_OPI_WRITE_PROTECT_SEL_CMD                0x6897          /* OPI Write Protect selection */
#define MX25UW_OPI_GANG_BLOCK_LOCK_CMD                  0x7E81          /* OPI Gang block lock: whole chip write protect */
#define MX25UW_OPI_GANG_BLOCK_UNLOCK_CMD                0x9867          /* OPI Gang block unlock: whole chip write unprote */
#define MX25UW_OPI_READ_PASSWORD_REGISTER_CMD           0x27D8          /* OPI Read Password */
#define MX25UW_OPI_WRITE_PASSWORD_REGISTER_CMD          0x28D7          /* OPI Write Password */
#define MX25UW_OPI_PASSWORD_UNLOCK_CMD                  0x29D6          /* OPI Unlock Password */
#define MX25UW_OPI_PAGE_BUFFER_READ                     0x25DA          /* OPI Page Buffer Read */
#define MX25UW_OPI_WRITE_BUFFER_INITIAL                 0x22DD          /* OPI Write Buffer Initial */
#define MX25UW_OPI_WRITE_BUFFER_CONTINUE                0x24DB          /* OPI Write Buffer Continue */

#define MX25UW_OK            0
#define MX25UW_ERROR        -1

/* Exported types ---------------------------------------------------------- */

/**
 * @brief           Определение перечисления интерфейсов MX25UW
 */
enum mx25uw_interface {
    MX25UW_SPI,
    MX25UW_OPI_STR,
    MX25UW_OPI_DTR,
};


/**
 * @brief           Определение структуры данных MX25UW
 */
struct mx25uw {
    XSPI_TypeDef *xspi;                         /*!< Указатель на структуру данных XSPI */

    uint8_t interface;                          /*!< Интерфейс @ref enum mx25uw_interface */

    uint8_t id[3];                              /*!< Идентификатор */
};

/* Exported variables ------------------------------------------------------ */

/* Exported function prototypes -------------------------------------------- */

int32_t mx25uw_init(void);

int32_t mx25uw_setup_opi_dtr(void);

int32_t mx25uw_setup_memory_mapped_mode(void);

/* Exported callback function prototypes ----------------------------------- */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX25UW_H_ */
