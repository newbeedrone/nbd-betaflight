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

#define TARGET_BOARD_IDENTIFIER         "Galaxy AIO Rev_B"
#define USBD_PRODUCT_STRING             "Galaxy AIO"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PA0

#define LED0_PIN                        PC13
#define LED1_PIN                        PC14

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PB10
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_UART

#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PA10
#define UART1_TX_PIN                    PA9

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define USE_SOFTSERIAL1
#define SOFTSERIAL1_RX_PIN              PA8

#define SERIAL_PORT_COUNT               4

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_EARLY
#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDO_PIN                   PB14
#define SPI2_SDI_PIN                   PB15
#define SPI2_NSS_PIN                    PB12

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB3
#define SPI3_SDO_PIN                   PB4
#define SPI3_SDI_PIN                   PB5

/* ======== GYRO ======== */
#define USE_GYRO
#define USE_GYRO_SPI_MPU6000

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PB0

#define GYRO_1_CS_PIN                   PA4
#define GYRO_1_SPI_INSTANCE             SPI3

#define GYRO_1_ALIGN                    CW0_DEG_FLIP

/* ======== ACC ======== */
#define USE_ACC
#define USE_ACC_SPI_MPU6000

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PA15
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== RX ======== */
#define SERIALRX_UART                   SERIAL_PORT_USART1
#define DEFAULT_RX_FEATURE              FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER               SERIALRX_SBUS

/* ======== FLASH ======== */
#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT
#define USE_FLASHFS
#define USE_FLASH_M25P16
#define USE_FLASH_W25M
#define USE_FLASH_W25N01G
#define FLASH_CS_PIN                    SPI2_NSS_PIN
#define FLASH_SPI_INSTANCE              SPI2

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define ADC_VBAT_PIN                    PB1
#define ADC_CURR_PIN                    PA5

#define VBAT_SCALE_DEFAULT              110
#define CURRENT_METER_SCALE_DEFAULT     510
#define CURRENT_METER_OFFSET_DEFAULT    0

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define ENABLE_DSHOT_DMAR               DSHOT_DMAR_ON
#define DSHOT_BITBANG_DEFAULT           DSHOT_BITBANG_OFF

#define MOTOR1_PIN                      PB6
#define MOTOR2_PIN                      PB8
#define MOTOR3_PIN                      PB9
#define MOTOR4_PIN                      PB7

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PB6 , 1,  0) \
    TIMER_PIN_MAP( 1, PB8 , 2,  1) \
    TIMER_PIN_MAP( 2, PB9 , 1,  2) \
    TIMER_PIN_MAP( 3, PB7 , 1,  3) \
    TIMER_PIN_MAP( 4, PA0 , 1,  4) \
    TIMER_PIN_MAP( 5, PB10, 1,  5)

/* ======== OTHER ======== */

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTE                 0xffff
#define TARGET_IO_PORTF                 0xffff
#define FLASH_PAGE_SIZE ((uint32_t)0x8000) // 32K sectors