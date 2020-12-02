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

#define TARGET_BOARD_IDENTIFIER         "Infinity F4 Rev_E"
#define USBD_PRODUCT_STRING             "Infinity F4"

#define USE_TARGET_CONFIG

/* ======== LED ======== */
#define LED0_PIN                        PC0

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PB6
#define BEEPER_PWM_HZ                   5400
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_UART

#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PA10

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define USE_UART3
#define UART3_RX_PIN                    PB11
#define UART3_TX_PIN                    PB10

#define USE_UART4
#define UART4_RX_PIN                    PA1
#define UART4_TX_PIN                    PA0

#define USE_UART5
#define UART5_RX_PIN                    PD2
#define UART5_TX_PIN                    PC12

#define USE_UART6
#define UART6_RX_PIN                    PC7
#define UART6_TX_PIN                    PC6

#define SERIAL_PORT_COUNT               7

/* ======== SPI ======== */
#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PA5
#define SPI1_MISO_PIN                   PA6
#define SPI1_MOSI_PIN                   PA7
#define SPI1_NSS_PIN                    PA4

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_MISO_PIN                   PB14
#define SPI2_MOSI_PIN                   PB15
#define SPI2_NSS_PIN                    PB12

/* ======== I2C ======== */
/*!< UART3 pin (for speedybee module) on [FC305 Rev_F] conflicts with I2C2 >!*/
// #define USE_I2C
// #define USE_I2C_DEVICE_2
// #define I2C_DEVICE                      (I2CDEV_2)
// #define I2C2_SCL                        PB10
// #define I2C2_SDA                        PB11

/* ======== GYRO ======== */
#define USE_GYRO
#define USE_GYRO_SPI_MPU6000

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PC13
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN                   SPI2_NSS_PIN
#define GYRO_1_SPI_INSTANCE             SPI2

#define GYRO_1_ALIGN                    CW90_DEG

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

/* ======== ADC ======== */
#define USE_ADC
#define ADC1_INSTANCE                   ADC1

#define VBAT_ADC_PIN                    PC4
#define CURRENT_METER_ADC_PIN           PC3

#define VBAT_SCALE_DEFAULT              110

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define ENABLE_DSHOT_DMAR               DSHOT_DMAR_ON

/* ======== PINIO ======== */
#define PINIO1_PIN                      PC1

/* ======== OTHER ======== */
#define DEFAULT_FEATURES                (FEATURE_LED_STRIP | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT      6
#define USED_TIMERS                     ( TIM_N(1) | TIM_N(3) | TIM_N(4) | TIM_N(8) )
