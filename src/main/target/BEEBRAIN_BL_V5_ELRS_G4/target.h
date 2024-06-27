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

#define TARGET_BOARD_IDENTIFIER         "Beebrain BL V5 ELRS Rev_A"
#define USBD_PRODUCT_STRING             "Beebrain BL V5 ELRS G4"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PB9

#define LED0_PIN                        PB2
#define LED1_PIN                        PC13

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PB7
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PA10
#define UART1_TX_PIN                    PA9

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define USE_UART3
#define UART3_RX_PIN                    PB8
#define UART3_TX_PIN                    PB9

#define USE_UART4
#define UART4_RX_PIN                    PC11
#define UART4_TX_PIN                    PC10

#define SERIAL_PORT_COUNT               5

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_LATE

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                   PB3
#define SPI1_SDI_PIN                   PB4
#define SPI1_SDO_PIN                   PB5

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_ACCGYRO_BMI270

#define GYRO_1_EXTI_PIN                 PC14
#define GYRO_1_CS_PIN                   PA4
#define GYRO_1_SPI_INSTANCE             SPI1

#define GYRO_1_ALIGN                    CW90_DEG

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PA15
#define MAX7456_SPI_INSTANCE            SPI1

/* ======== VTX ======== */
#define USE_VTX_RTC6705

#define RTC6705_CS_PIN                  PA14
#define RTC6705_SPI_INSTANCE            SPI1

#define RTC6705_EX_POWER_1_PIN          PC6  // External VTx Power LSB
#define RTC6705_EX_POWER_2_PIN          PB15 // External VTx Power MSB

#define RTC6705_DYNAMIC_POWER_CTRL // For External VTx Power Controller
#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== RX ======== */
#define SERIALRX_UART                   SERIAL_PORT_USART2
#define DEFAULT_RX_FEATURE              FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER               SERIALRX_CRSF

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define ADC_VBAT_PIN                    PA0
#define ADC_CURR_PIN                    PA1

#define VBAT_SCALE_DEFAULT              110
#define CURRENT_METER_SCALE_DEFAULT     500
#define CURRENT_METER_OFFSET_DEFAULT    791

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define MOTOR1_PIN                      PB0
#define MOTOR2_PIN                      PB1
#define MOTOR3_PIN                      PA6
#define MOTOR4_PIN                      PA7

#define USE_ESCSERIAL

/* ======== OTHER ======== */
#define PINIO1_BOX                      40
#define PINIO1_PIN                      PB8

/* ======== System ======== */
#undef USE_SDCARD
#define USE_EXTI
#define USE_PID_DENOM_CHECK
#define USE_TIMER_UP_CONFIG

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, MOTOR1_PIN   ,    2, 6) \
    TIMER_PIN_MAP( 1, MOTOR2_PIN   ,    2, 1) \
    TIMER_PIN_MAP( 2, MOTOR3_PIN   ,    2, 2) \
    TIMER_PIN_MAP( 3, MOTOR4_PIN   ,    3, 3) \
    TIMER_PIN_MAP( 4, LED_STRIP_PIN,    3, 4) \
    TIMER_PIN_MAP( 5, BEEPER_PIN   ,    3, 5)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTE                 0xffff
#define TARGET_IO_PORTF                 0xffff

#define USE_TARGET_CONFIG