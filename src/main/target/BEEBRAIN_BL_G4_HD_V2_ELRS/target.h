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

#define TARGET_BOARD_IDENTIFIER         "Beebrain G4 HD V2 ELRS"
#define USBD_PRODUCT_STRING             "AcroBee75 HD O4"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PB9

#define LED0_PIN                        PB2
#define LED1_PIN                        PA3

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
#define UART2_RX_PIN                    PA15
#define UART2_TX_PIN                    PA14

#define USE_UART3
#define UART3_RX_PIN                    PB11
#define UART3_TX_PIN                    PB10

#define USE_UART4
#define UART4_RX_PIN                    PC11
#define UART4_TX_PIN                    PC10

#define SERIAL_PORT_COUNT               5

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_LATE

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PB3
#define SPI1_SDI_PIN                    PB4
#define SPI1_SDO_PIN                    PB5

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDI_PIN                    PB14
#define SPI2_SDO_PIN                    PB15

/* ======== I2C ======== */
#define USE_I2C
#define USE_I2C_PULLUP
#define I2C_FULL_RECONFIGURABILITY

#define USE_I2C_DEVICE_2
#define I2C2_SCL_PIN                    PC4
#define I2C2_SDA_PIN                    PA8

#define I2C2_CLOCKSPEED                 400

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO

#define USE_ACC_SPI_MPU6000
#define USE_GYRO_SPI_MPU6000

#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P
#define ICM426XX_CLOCK                  6000000

#define GYRO_1_EXTI_PIN                 PC14
#define GYRO_1_CS_PIN                   PB12
#define GYRO_1_SPI_INSTANCE             SPI2

#define GYRO_1_ALIGN                    CW90_DEG_FLIP

/* ======== FLASH ======== */
#define USE_FLASH
#define USE_FLASH_M25P16

#define DEFAULT_BLACKBOX_DEVICE         BLACKBOX_DEVICE_FLASH

#define FLASH_CS_PIN                    PB6
#define FLASH_SPI_INSTANCE              SPI1

/* ======== VTX ======== */
#define MSP_DISPLAYPORT_UART            SERIAL_PORT_USART1

/* ======== RX ======== */
#define SERIALRX_UART                   SERIAL_PORT_USART2
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

#define BARO_I2C_INSTANCE               (I2CDEV_2)
#define BARO_BUSTYPE                    BUS_TYPE_I2C

/* ======== MAG ======== */
#define USE_MAG

#define MAG_I2C_INSTANCE                (I2CDEV_2)
#define MAG_BUSTYPE                     BUS_TYPE_I2C

/* ======== GPS ======== */
#define USE_GPS
#define USE_GPS_NMEA
#define USE_GPS_UBLOX
#define USE_GPS_RESCUE

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define ADC_VBAT_PIN                    PA0
#define ADC_CURR_PIN                    PA1

#define DEFAULT_VOLTAGE_METER_SCALE     110
#define DEFAULT_CURRENT_METER_SCALE     410

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define MOTOR1_PIN                      PB0
#define MOTOR2_PIN                      PB1
#define MOTOR3_PIN                      PA6
#define MOTOR4_PIN                      PA7

#define USE_ESCSERIAL

/* ======== System ======== */
#define SYSTEM_HSE_MHZ                  8

#undef USE_SDCARD
#define USE_EXTI
#define USE_PID_DENOM_CHECK
#define USE_TIMER_UP_CONFIG

#define SPI1_TX_DMA_OPT                 14
#define SPI2_TX_DMA_OPT                 10

#define SPI1_RX_DMA_OPT                 13
#define SPI2_RX_DMA_OPT                 11

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