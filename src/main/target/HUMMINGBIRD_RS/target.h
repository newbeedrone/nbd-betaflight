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

#define TARGET_BOARD_IDENTIFIER         "HummingBird F4 V3 Rev_D"
#define USBD_PRODUCT_STRING             "HummingBird F4 V3"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PB1

#define LED0_PIN                        PC14

/* ======== UART ======== */
#define USE_UART

#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PA10
#define UART1_TX_PIN                    PA9

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define SERIAL_PORT_COUNT               3

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_EARLY

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PA5
#define SPI1_SDI_PIN                    PA6
#define SPI1_SDO_PIN                    PA7
#define SPI1_NSS_PIN                    PA4

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDI_PIN                    PB14
#define SPI2_SDO_PIN                    PB15

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB3
#define SPI3_SDI_PIN                    PB4
#define SPI3_SDO_PIN                    PB5
#define SPI3_NSS_PIN                    PA15

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_ACCGYRO_BMI270

#define GYRO_1_CS_PIN                   SPI1_NSS_PIN
#define GYRO_1_EXTI_PIN                 PB6
#define GYRO_1_SPI_INSTANCE             SPI1

#define GYRO_1_ALIGN                    CW180_DEG

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PB12
#define MAX7456_SPI_INSTANCE            SPI2

/* ======== VTX ======== */
#define USE_VTX_RTC6705

#define RTC6705_CS_PIN                  PA14
#define RTC6705_SPI_INSTANCE            SPI2

/* ======== RX ======== */
#define USE_RX_SPI
#define USE_RX_EXPRESSLRS
#define USE_RX_SX1280
#undef  USE_RX_SX127X

#define RX_SPI_CS_PIN                   SPI3_NSS_PIN
#define RX_SPI_LED_PIN                  PC15
#define RX_SPI_EXTI_PIN                 PC13
#define RX_SPI_BIND_PIN                 PB2
#define RX_EXPRESSLRS_SPI_RESET_PIN     PB9
#define RX_EXPRESSLRS_SPI_BUSY_PIN      PA13

#define RX_SPI_INSTANCE                 SPI3
#define RX_EXPRESSLRS_TIMER_INSTANCE    TIM9

#define RX_SPI_LED_INVERTED

#define DEFAULT_RX_FEATURE              FEATURE_RX_SPI
#define RX_SPI_DEFAULT_PROTOCOL         RX_SPI_EXPRESSLRS

/* ======== ADC ======== */
#define USE_ADC

#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define ADC_VBAT_PIN                    PA1
#define ADC_CURR_PIN                    PB0

#define DEFAULT_VOLTAGE_METER_SCALE     110
#define DEFAULT_CURRENT_METER_SCALE     510
#define DEFAULT_CURRENT_METER_OFFSET    0

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define MOTOR1_PIN                      PB8
#define MOTOR2_PIN                      PA0
#define MOTOR3_PIN                      PB10
#define MOTOR4_PIN                      PB7

#define USE_DSHOT_BITBAND
#define USE_ESCSERIAL
/* ======== System ======== */
#define USE_EXTI
#define USE_PID_DENOM_CHECK

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, MOTOR1_PIN   , 2,  0) \
    TIMER_PIN_MAP( 1, MOTOR2_PIN   , 1,  0) \
    TIMER_PIN_MAP( 2, MOTOR3_PIN   , 1,  0) \
    TIMER_PIN_MAP( 3, MOTOR4_PIN   , 1,  0) \
    TIMER_PIN_MAP( 4, LED_STRIP_PIN, 2,  0) 

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTE                 0xffff

#define FLASH_PAGE_SIZE                 ((uint32_t)0x4000) // 16K sectors

#define USE_TARGET_CONFIG