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

#define TARGET_BOARD_IDENTIFIER         "HummingBird V4.1"
#define USBD_PRODUCT_STRING             "HMB V4.1 RS"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PH2
#define LED0_PIN                        PA9

/* ======== UART ======== */
#define USE_VCP

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define USE_UART4
#define UART4_RX_PIN                    PA1
#define UART4_TX_PIN                    PA0

#define USE_UART5
#define UART5_RX_PIN                    PB8
#define UART5_TX_PIN                    PB9

#define SERIAL_PORT_COUNT               4

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_LATE

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PA5
#define SPI1_SDI_PIN                    PA6
#define SPI1_SDO_PIN                    PA7

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

/* ======== VTX ======== */
#define USE_VTX_RTC6705

#define RTC6705_CS_PIN                  PC15
#define RTC6705_SPI_INSTANCE            SPI1

#define RTC6705_EX_POWER_1_PIN          PC13 // External VTx Power LSB
#define RTC6705_EX_POWER_2_PIN          PC14  // External VTx Power MSB

#define RTC6705_DYNAMIC_POWER_CTRL // For External VTx Power Controller
#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PA4
#define MAX7456_SPI_INSTANCE            SPI1

/* ======== RX ======== */
#define SERIALRX_UART                   SERIAL_PORT_UART4
#define DEFAULT_RX_FEATURE              FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER               SERIALRX_CRSF

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define ADC_VBAT_PIN                    PB0
#define ADC_CURR_PIN                    PB1

#define VBAT_SCALE_DEFAULT              110
#define DEFAULT_CURRENT_METER_SCALE     680
#define DEFAULT_CURRENT_METER_OFFSET    120
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC

/* ======== ESC ======== */
#define MOTOR1_PIN                      PB10
#define MOTOR2_PIN                      PB11
#define MOTOR3_PIN                      PB5
#define MOTOR4_PIN                      PB4

#undef USE_DSHOT_DMAR
#define USE_DSHOT_BITBAND
#define USE_DSHOT_TELEMETRY

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, LED_STRIP_PIN , 1,  5) 
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

#define USE_TARGET_CONFIG