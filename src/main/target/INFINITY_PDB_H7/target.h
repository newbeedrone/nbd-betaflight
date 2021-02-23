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

#define TARGET_BOARD_IDENTIFIER         "Infinity PDB H7 Rev_B"
#define USBD_PRODUCT_STRING             "Infinity PDB H7"

/* ======== LED ======== */
#define LED0_PIN                        PB0

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PC9
#define BEEPER_PWM_HZ                   5400
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_UART

#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PB15

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define USE_UART3
#define UART3_RX_PIN                    PD9
#define UART3_TX_PIN                    PD8

#define USE_UART4
#define UART4_RX_PIN                    PA1
#define UART4_TX_PIN                    PA0

#define USE_UART5
#define UART5_RX_PIN                    PB12
#define UART5_TX_PIN                    PB13

#define USE_UART6
#define UART6_RX_PIN                    PC7
#define UART6_TX_PIN                    PC6

#define USE_UART7
#define UART7_RX_PIN                    PE7

#define SERIAL_PORT_COUNT               8

/* ======== SPI ======== */
#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PB3
#define SPI1_MISO_PIN                   PB4
#define SPI1_MOSI_PIN                   PB5
#define SPI1_NSS_PIN                    PA15

#define USE_SPI_DEVICE_4
#define SPI4_SCK_PIN                    PE2
#define SPI4_MISO_PIN                   PE5
#define SPI4_MOSI_PIN                   PE6
#define SPI4_NSS_PIN                    PE4

#define USE_SPI_DEVICE_6
#define SPI6_SCK_PIN                    PA5
#define SPI6_MISO_PIN                   PA6
#define SPI6_MOSI_PIN                   PA7
#define SPI6_NSS_PIN                    PA4

/* ======== I2C ======== */
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C_DEVICE                      (I2CDEV_1)
#define I2C1_SCL                        PB6
#define I2C1_SDA                        PB7

/* ======== GYRO ======== */
#define USE_GYRO
#define USE_GYRO_SPI_MPU6000

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PC4
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN                   SPI6_NSS_PIN
#define GYRO_1_SPI_INSTANCE             SPI6

#define GYRO_1_ALIGN                    CW180_DEG

/* ======== ACC ======== */
#define USE_ACC
#define USE_ACC_SPI_MPU6000

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              SPI1_NSS_PIN
#define MAX7456_SPI_INSTANCE            SPI1

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
#define FLASH_CS_PIN                    SPI4_NSS_PIN
#define FLASH_SPI_INSTANCE              SPI4

/* ======== ADC ======== */
#define USE_ADC
#define ADC1_INSTANCE                   ADC1
#define ADC2_INSTANCE                   ADC2
#define ADC3_INSTANCE                   ADC3
#define ADC1_DMA_OPT                    8
#define ADC2_DMA_OPT                    9
#define ADC3_DMA_OPT                    10

#define VBAT_ADC_PIN                    PC0
#define CURRENT_METER_ADC_PIN           PC1

#define VBAT_SCALE_DEFAULT              110
#define CURRENT_METER_SCALE_DEFAULT     510
#define CURRENT_METER_OFFSET_DEFAULT    0

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define ENABLE_DSHOT_DMAR               DSHOT_DMAR_ON

/* ======== OTHER ======== */
#define DEFAULT_FEATURES                (FEATURE_LED_STRIP | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTE                 0xffff

#define USABLE_TIMER_CHANNEL_COUNT      6
#define USED_TIMERS                     ( TIM_N(1) | TIM_N(3) | TIM_N(16) )