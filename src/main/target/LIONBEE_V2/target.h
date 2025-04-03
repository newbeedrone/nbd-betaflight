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

#define TARGET_BOARD_IDENTIFIER         "LionBee V2"
#define USBD_PRODUCT_STRING             "AT32F435 LionBee V2"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PB1

#define LED0_PIN                        PA1
/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_VCP

#define USE_UART6
#define UART6_RX_PIN                    PA5
#define UART6_TX_PIN                    PA4

#define SERIAL_PORT_COUNT               2

/* ======== I2C ======== */
#define USE_I2C

#define USE_I2C_DEVICE_2
#define I2C2_SCL_PIN                    PB10
#define I2C2_SDA_PIN                    PB11

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_LATE

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDI_PIN                    PB14
#define SPI2_SDO_PIN                    PB15

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB12
#define SPI3_SDI_PIN                    PB4
#define SPI3_SDO_PIN                    PB0

#define USE_SPI_DEVICE_4
#define SPI4_SCK_PIN                    PB7
#define SPI4_SDI_PIN                    PB8
#define SPI4_SDO_PIN                    PB9

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_GYRO_EXTI
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P

#define GYRO_1_EXTI_PIN                 PC13
#define GYRO_1_CS_PIN                   PA14
#define GYRO_1_SPI_INSTANCE             SPI4

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PC14
#define MAX7456_SPI_INSTANCE            SPI4

/* ======== VTX ======== */
#define USE_VTX_RTC6705
#define SPI_SHARED_MAX7456_AND_RTC6705

#define RTC6705_CS_PIN                  PB2
#define RTC6705_SPI_INSTANCE            SPI4

#define RTC6705_EX_POWER_1_PIN          PB6   // External VTx Power LSB
#define RTC6705_EX_POWER_2_PIN          PB5   // External VTx Power MSB

#define RTC6705_DYNAMIC_POWER_CTRL // For External VTx Power Controller
#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== FLASH ======== */
#define USE_FLASH
#define USE_FLASH_SPI
#define USE_FLASH_M25P16
#define DEFAULT_BLACKBOX_DEVICE         BLACKBOX_DEVICE_FLASH

#define FLASH_CS_PIN                    PC15
#define FLASH_SPI_INSTANCE              SPI3

/* ======== RX ======== */
#define USE_RX_SPI
#define USE_RX_EXPRESSLRS
#define USE_RX_SX1280
#undef  USE_RX_SX127X

#define RX_SPI_CS_PIN                   PA8
#define RX_SPI_LED_PIN                  PA0
#define RX_SPI_EXTI_PIN                 PB3
#define RX_SPI_BIND_PIN                 PH2
#define RX_EXPRESSLRS_SPI_RESET_PIN     PH3
#define RX_EXPRESSLRS_SPI_BUSY_PIN      PA15

#define RX_SPI_INSTANCE                 SPI2
#define RX_EXPRESSLRS_TIMER_INSTANCE    TMR5

#define RX_SPI_LED_INVERTED

#define RX_SPI_PROTOCOL                 EXPRESSLRS
#define DEFAULT_RX_FEATURE              FEATURE_RX_SPI
#define RX_SPI_DEFAULT_PROTOCOL         RX_SPI_EXPRESSLRS

/* ======== BARO ======== */
#define USE_BARO

#undef USE_BARO_SPI_MS5611
#undef USE_BARO_SPI_BMP280
#undef USE_BARO_SPI_BMP388
#undef USE_BARO_SPI_LPS
#undef USE_BARO_SPI_QMP6988
#undef USE_BARO_SPI_DPS310
#undef USE_BARO_SPI_2SMBP_02B
#undef USE_BARO_SPI_LPS22DF

#define BARO_I2C_INSTANCE               (I2CDEV_2)
#define BARO_BUSTYPE                    BUS_TYPE_I2C

/* ======== MAG ======== */
#define USE_MAG

#define MAG_I2C_INSTANCE                (I2CDEV_2)
#define MAG_BUSTYPE                     BUS_TYPE_I2C

/* ======== ADC ======== */
#define USE_ADC

#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    12

#define ADC_VBAT_PIN                    PA2
#define ADC_CURR_PIN                    PA3

#define DEFAULT_VOLTAGE_METER_SCALE     107
#define DEFAULT_CURRENT_METER_SCALE     400

#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC

/* ======== ESC ======== */
#define MOTOR1_PIN                      PA6
#define MOTOR2_PIN                      PA7
#define MOTOR3_PIN                      PA9
#define MOTOR4_PIN                      PA10

#undef USE_DSHOT_DMAR
#define USE_DSHOT_BITBAND
#define USE_DSHOT_TELEMETRY

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, LED_STRIP_PIN , 1,  5)

/* ======== System ======== */
#define SYSTEM_HSE_MHZ                  8

#define USE_EXTI
#undef USE_TRANSPONDER
#undef USE_RX_PPM
#undef USE_RX_PWM
#undef USE_RX_CC2500
#undef USE_SERIAL_4WAY_SK_BOOTLOADER

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTH                 0xffff

#define FLASH_PAGE_SIZE                 ((uint32_t)0x0800) // 2K sectors

#define USE_TARGET_CONFIG