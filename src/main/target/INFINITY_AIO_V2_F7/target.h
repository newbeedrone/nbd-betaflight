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

#define TARGET_BOARD_IDENTIFIER         "Infinity AIO F7"
#define USBD_PRODUCT_STRING             "Infinity AIO F7"

/* ======== LED ======== */
#define LED0_PIN                        PC0

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PD13
#define BEEPER_PWM_HZ                   5400
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_UART

#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PB7

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define USE_UART3
#define UART3_RX_PIN                    PB11
#define UART3_TX_PIN                    PB10

#define USE_UART5
#define UART5_RX_PIN                    PD2

#define USE_UART7
#define UART7_TX_PIN                    PE8

#define USE_UART8
#define UART8_RX_PIN                    PE0
#define UART8_TX_PIN                    PE1

#define SERIAL_PORT_COUNT               7

/* ======== SPI ======== */
#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PA5
#define SPI1_MISO_PIN                   PA6
#define SPI1_MOSI_PIN                   PA7
#define SPI1_NSS_PIN                    PB0

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB3
#define SPI3_MISO_PIN                   PB4
#define SPI3_MOSI_PIN                   PD6
#define SPI3_NSS_PIN                    PA15

#define USE_SPI_DEVICE_4
#define SPI4_SCK_PIN                    PE12
#define SPI4_MISO_PIN                   PE13
#define SPI4_MOSI_PIN                   PE14
#define SPI4_NSS_PIN                    PE11

/* ======== I2C ======== */
#define USE_I2C
#define USE_I2C_DEVICE_3
#define I2C_DEVICE_3                    (I2CDEV_3)
#define I2C3_SCL                        PA8
#define I2C3_SDA                        PC9

/* ======== GYRO ======== */
#define USE_GYRO
#define USE_GYRO_SPI_MPU6000

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PB1
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN                   SPI4_NSS_PIN
#define GYRO_1_SPI_INSTANCE             SPI4

#define GYRO_1_ALIGN                    CW180_DEG

/* ======== ACC ======== */
#define USE_ACC
#define USE_ACC_SPI_MPU6000

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              SPI3_NSS_PIN
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
#define FLASH_CS_PIN                    SPI1_NSS_PIN
#define FLASH_SPI_INSTANCE              SPI1

/* ======== ADC ======== */
#define USE_ADC
#define ADC1_INSTANCE                   ADC1

#define VBAT_ADC_PIN                    PC1
#define CURRENT_METER_ADC_PIN           PC2

#define VBAT_SCALE_DEFAULT              110
#define CURRENT_METER_SCALE_DEFAULT     230
#define CURRENT_METER_OFFSET_DEFAULT    10

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define ENABLE_DSHOT_DMAR               DSHOT_DMAR_ON

/* ======== OTHER ======== */
#define DEFAULT_FEATURES                (FEATURE_LED_STRIP | FEATURE_ESC_SENSOR | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTE                 0xffff

#define USABLE_TIMER_CHANNEL_COUNT      6
#define USED_TIMERS                     ( TIM_N(1) | TIM_N(3) | TIM_N(4) )