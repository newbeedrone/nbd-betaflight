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
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PB1
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, LED_STRIP_PIN , 1,  5) 

#define LED0_PIN                        PC14

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PB0
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
#define UART3_RX_PIN                    PB11
#define UART3_TX_PIN                    PB10

#define USE_UART6
#define UART6_RX_PIN                    PA5
#define UART6_TX_PIN                    PA4

#define SERIAL_PORT_COUNT               5

/* ======== I2C ======== */
#define USE_I2C
#define USE_I2C_DEVICE_2

#define I2C2_SCL_PIN         PH3
#define I2C2_SDA_PIN         PB11

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_LATE

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PB3
#define SPI1_SDI_PIN                    PB4
#define SPI1_SDO_PIN                    PB5
#define SPI1_NSS_PIN                    PA15

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDI_PIN                    PB14
#define SPI2_SDO_PIN                    PB15

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB7
#define SPI3_SDI_PIN                    PB8
#define SPI3_SDO_PIN                    PB9

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_GYRO_EXTI
#define USE_GYRO_SPI_ICM42688P

#define GYRO_1_EXTI_PIN                 PC13
#define GYRO_1_CS_PIN                   PB12
#define GYRO_1_SPI_INSTANCE             SPI2

#define GYRO_1_ALIGN                    CW90_DEG

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PB6
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== FLASH ======== */
#define USE_FLASH_W25Q128FV

#define FLASH_CS_PIN                    SPI1_NSS_PIN
#define FLASH_SPI_INSTANCE              SPI1

/* ======== VTX ======== */
// #define USE_VTX_RTC6705

// #define RTC6705_CS_PIN                  PA14
// #define RTC6705_SPI_INSTANCE            SPI2

// #define RTC6705_EX_POWER_1_PIN          PC15 // External VTx Power LSB
// #define RTC6705_EX_POWER_2_PIN          PA5  // External VTx Power MSB

// #define RTC6705_DYNAMIC_POWER_CTRL // For External VTx Power Controller
// #define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== RX ======== */
#define SERIALRX_UART                   SERIAL_PORT_USART2
#define DEFAULT_RX_FEATURE              FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER               SERIALRX_CRSF

// #define USE_TELEMETRY
// #define USE_RX_EXPRESSLRS
// #define USE_RX_SX1280

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define ADC_VBAT_PIN                    PA6
#define ADC_CURR_PIN                    PA7

#define VBAT_SCALE_DEFAULT              110
#define CURRENT_METER_SCALE_DEFAULT     410

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== GPIO ======== */
#define USE_BRUSHED_FLIPOVERAFTERCRASH
#define BRUSHED_REVERSE_PIN             PC15

/* ======== ESC ======== */
#define MOTOR1_PIN                      PA8
#define MOTOR2_PIN                      PB2
#define MOTOR3_PIN                      PA0
#define MOTOR4_PIN                      PA1

#undef USE_DSHOT_DMAR
#define USE_DSHOT_BITBAND
// #define USE_ESCSERIAL

#define DEFAULT_MOTOR_DSHOT_SPEED       PWM_TYPE_DSHOT300

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
#define USE_PID_DENOM_CHECK

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTH                 0xffff

#define FLASH_PAGE_SIZE                 ((uint32_t)0x0800) // 2K sectors