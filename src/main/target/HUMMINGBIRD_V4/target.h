/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define TARGET_BOARD_IDENTIFIER         "HummingBird AT FC 200"
#define USBD_PRODUCT_STRING             "HummingBird AT FC 200"

/* ======== LED ======== */

#define LED0_PIN                        PA9
/* ======== UART ======== */
#define USE_VCP

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define SERIAL_PORT_COUNT               2

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_LATE

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDI_PIN                    PB14
#define SPI2_SDO_PIN                    PB15

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_GYRO_EXTI
#define USE_GYRO_SPI_ICM42688P

#define GYRO_1_EXTI_PIN                 PA8
#define GYRO_1_CS_PIN                   PB12
#define GYRO_1_SPI_INSTANCE             SPI2

#define GYRO_1_ALIGN                    CW90_DEG

/* ======== PINBOX ======== */
// #define USE_BRUSHED_FLIPOVERAFTERCRASH
// #define BRUSHED_REVERSE_PIN             PC15

/* ======== ESC ======== */
#define MOTOR1_PIN                      PB10
#define MOTOR2_PIN                      PB11
#define MOTOR3_PIN                      PB5
#define MOTOR4_PIN                      PB4

#undef USE_DSHOT_DMAR
#define USE_DSHOT_BITBAND
#define USE_DSHOT_TELEMETRY
// #define USE_ESCSERIAL

// #define DEFAULT_MOTOR_DSHOT_SPEED       PWM_TYPE_DSHOT300
/* ======== System ======== */
#undef USE_TRANSPONDER
#undef USE_RX_PPM
#undef USE_RX_PWM
#undef USE_RX_SPI
#undef USE_RX_CC2500
#undef USE_RX_EXPRESSLRS
// #undef USE_SERIAL_4WAY_BLHELI_BOOTLOADER
#undef USE_SERIAL_4WAY_SK_BOOTLOADER
#define USE_EXTI
// #define USE_PID_DENOM_CHECK

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTH                 0xffff

#define FLASH_PAGE_SIZE                 ((uint32_t)0x0800) // 2K sectors