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

#define TARGET_BOARD_IDENTIFIER         "HummingBird F4 Pro ELRS"
#define USBD_PRODUCT_STRING             "HummingBird F4 Pro"

/* ======== LED ======== */
#define LED0_PIN                        PC14

/* ======== UART ======== */
#define USE_UART

#define USE_VCP

#define USE_UART1
#define UART1_TX_PIN                    PA9
#define UART1_RX_PIN                    PA10

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define SERIAL_PORT_COUNT               3

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

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB3
#define SPI3_MISO_PIN                   PB4
#define SPI3_MOSI_PIN                   PB5
#define SPI3_NSS_PIN                    PA15

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_SPI_GYRO
#define USE_ACCGYRO_BMI270

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PB6
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN                   SPI1_NSS_PIN
#define GYRO_1_SPI_INSTANCE             SPI1

#define GYRO_1_ALIGN                    CW0_DEG

/* ======== OSD ======== */
#define USE_MAX7456
#define USE_NBD7456_NEW

#define MAX7456_SPI_CS_PIN              SPI2_NSS_PIN
#define MAX7456_SPI_INSTANCE            SPI2

/* ======== VTX ======== */
#define USE_BEESIGN
#define USE_VTX_BEESIGN

#undef USE_VTX_SMARTAUDIO
#undef USE_VTX_TRAMP

#define BEESIGN_UART                    SERIAL_PORT_USART1

#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== RX ======== */
#define USE_RX_SPI

#define RX_SPI_INSTANCE                 SPI3
#define RX_SPI_LED_INVERTED
#define RX_NSS_PIN                      SPI3_NSS_PIN
#define RX_SPI_LED_PIN                  PC15
#define RX_SPI_EXTI_PIN                 PC13
#define RX_SPI_BIND_PIN                 PB2
#define RX_EXPRESSLRS_SPI_RESET_PIN     PB9
#define RX_EXPRESSLRS_SPI_BUSY_PIN      PA13
#define RX_EXPRESSLRS_TIMER_INSTANCE    TIM5

#define USE_RX_EXPRESSLRS
#define USE_RX_SX1280

#define DEFAULT_RX_FEATURE              FEATURE_RX_SPI
#define RX_SPI_DEFAULT_PROTOCOL         RX_SPI_EXPRESSLRS

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define VBAT_ADC_PIN                    PA1
#define CURRENT_METER_ADC_PIN           PB0

#define VBAT_SCALE_DEFAULT              110
#define CURRENT_METER_SCALE_DEFAULT     600
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
#define TARGET_IO_PORTD                 (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT      5
#define USED_TIMERS                     ( TIM_N(2) | TIM_N(3) | TIM_N(4) )