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

#define TARGET_BOARD_IDENTIFIER         "HummingBird 300 RS"
#define USBD_PRODUCT_STRING             "HummingBird 300 RS"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PA8

#define LED0_PIN                        PA15

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PC15
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PB7

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

#define USE_UART6
#define UART6_RX_PIN                    PC7
#define UART6_TX_PIN                    PC6

#define SERIAL_PORT_COUNT               7

/* ======== I2C ======== */
#define USE_I2C

#define USE_I2C_DEVICE_1
#define I2C1_SCL_PIN                    PB8
#define I2C1_SDA_PIN                    PB9

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_LATE
#define SPI_FULL_RECONFIGURABILITY

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PA5
#define SPI1_SDI_PIN                    PA6
#define SPI1_SDO_PIN                    PA7

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDI_PIN                    PB14
#define SPI2_SDO_PIN                    PB15

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PC10
#define SPI3_SDI_PIN                    PC11
#define SPI3_SDO_PIN                    PB2

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_GYRO_EXTI
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
#define GYRO_1_EXTI_PIN                 PC4
#define GYRO_1_CS_PIN                   PB12
#define GYRO_1_SPI_INSTANCE             SPI2

#define GYRO_1_ALIGN                    CW90_DEG

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PC13
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== SDCARD ======== */
#define USE_SDCARD
#define USE_SDCARD_SPI
#define SDCARD_SPI_CS_PIN               PA4
#define SDCARD_SPI_INSTANCE             SPI1
#define DEFAULT_BLACKBOX_DEVICE         BLACKBOX_DEVICE_SDCARD

/* ======== RX ======== */
#define SERIALRX_UART                   SERIAL_PORT_USART6
#define DEFAULT_RX_FEATURE              FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER               SERIALRX_CRSF

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

#define BARO_I2C_INSTANCE               (I2CDEV_1)
#define BARO_BUSTYPE                    BUS_TYPE_I2C

/* ======== MAG ======== */
#define USE_MAG

#define MAG_I2C_INSTANCE                (I2CDEV_1)
#define MAG_BUSTYPE                     BUS_TYPE_I2C

/* ======== ADC ======== */
#define USE_ADC

#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    12

#define ADC_VBAT_PIN                    PC0
#define ADC_CURR_PIN                    PC1

#define DEFAULT_VOLTAGE_METER_SCALE     110
#define DEFAULT_CURRENT_METER_SCALE     800

#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC

/* ======== PINBOX ======== */
#define PINIO1_BOX                      40
#define PINIO1_PIN                      PC14
#define PINIO1_CONFIG                   (PINIO_CONFIG_MODE_OUT_PP | PINIO_CONFIG_OUT_INVERTED)

/* ======== ESC ======== */
#define MOTOR1_PIN                      PB0
#define MOTOR2_PIN                      PB5
#define MOTOR3_PIN                      PB4
#define MOTOR4_PIN                      PB1
#define MOTOR5_PIN                      PC8
#define MOTOR6_PIN                      PC9
#define MOTOR7_PIN                      PB3
#define MOTOR8_PIN                      PB6

#define USE_ESCSERIAL

/* ======== OTHER ======== */
#define USE_EXTI

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, MOTOR1_PIN , 1,  0)\
    TIMER_PIN_MAP( 1, MOTOR2_PIN , 1,  0)\
    TIMER_PIN_MAP( 2, MOTOR3_PIN , 1,  0)\
    TIMER_PIN_MAP( 3, MOTOR4_PIN , 1,  0)\
    TIMER_PIN_MAP( 4, MOTOR5_PIN , 1,  0)\
    TIMER_PIN_MAP( 5, MOTOR6_PIN , 1,  0)\
    TIMER_PIN_MAP( 6, MOTOR7_PIN , 1,  0)\
    TIMER_PIN_MAP( 7, MOTOR8_PIN , 1,  0)\
    TIMER_PIN_MAP( 8, LED_STRIP_PIN , 1,  0)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTE                 0xffff
#define TARGET_IO_PORTF                 0xffff

#define FLASH_PAGE_SIZE                 ((uint32_t)0x4000) // 16K sectors
#define USE_TARGET_CONFIG