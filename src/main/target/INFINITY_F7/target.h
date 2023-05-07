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

#define TARGET_BOARD_IDENTIFIER         "Infinity F7"
#define USBD_PRODUCT_STRING             "Infinity F7"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED0_PIN                        PA15

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PC15
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

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PC10
#define SPI3_MISO_PIN                   PC11
#define SPI3_MOSI_PIN                   PC12
#define SPI3_NSS_PIN                    PC13

/* ======== I2C ======== */
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C_DEVICE                      (I2CDEV_1)
#define I2C1_SCL                        PB6
#define I2C1_SDA                        PB7

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_SPI_GYRO
#define USE_MULTI_GYRO
#define USE_ACCGYRO_BMI160

#define BMI160_SPI_DIVISOR              16

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PC4
#define GYRO_2_EXTI_PIN                 PC3
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN                   PB12
#define GYRO_1_SPI_INSTANCE             SPI2
#define GYRO_2_CS_PIN                   PC2
#define GYRO_2_SPI_INSTANCE             SPI2

#define GYRO_1_ALIGN                    CW90_DEG
#define GYRO_2_ALIGN                    ALIGN_CUSTOM
#define GYRO_2_CUSTOM_ALIGN             SENSOR_ALIGNMENT(  0,   0,  45)

#define GYRO_CONFIG_USE_GYRO_DEFAULT    GYRO_CONFIG_USE_GYRO_BOTH

/* ======== OSD ======== */
#define USE_OSD
#define USE_CANVAS
#define USE_CMS
#define USE_CMS_FAILSAFE_MENU
#define USE_EXTENDED_CMS_MENUS
#define USE_MSP_DISPLAYPORT
#define USE_OSD_OVER_MSP_DISPLAYPORT
#define USE_OSD_ADJUSTMENTS
#define USE_OSD_PROFILES
#define USE_OSD_STICK_OVERLAY
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              SPI3_NSS_PIN
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== RX ======== */
#define USE_RX_PPM
#define USE_RX_PWM
#define USE_SERIALRX
#define USE_SERIALRX_CRSF               // Team Black Sheep Crossfire protocol
#define USE_SERIALRX_GHST               // ImmersionRC Ghost Protocol
#define USE_SERIALRX_IBUS               // FlySky and Turnigy receivers
#define USE_SERIALRX_SBUS               // Frsky and Futaba receivers
#define USE_SERIALRX_SPEKTRUM           // SRXL, DSM2 and DSMX protocol
#define USE_SERIALRX_FPORT              // FrSky FPort
#define USE_SERIALRX_XBUS               // JR
#define USE_SERIALRX_SRXL2              // Spektrum SRXL2 protocol
#define USE_SERIALRX_JETIEXBUS
#define USE_SERIALRX_SUMD               // Graupner Hott protocol
#define USE_SERIALRX_SUMH               // Graupner legacy protocol

#define USE_CRSF_V3
#define USE_CRSF_CMS_TELEMETRY
#define USE_CRSF_LINK_STATISTICS
#define USE_TELEMETRY
#define USE_TELEMETRY_FRSKY_HUB
#define USE_TELEMETRY_SMARTPORT
#define USE_TELEMETRY_CRSF
#define USE_TELEMETRY_GHST
#define USE_TELEMETRY_SRXL
#define USE_TELEMETRY_IBUS
#define USE_TELEMETRY_IBUS_EXTENDED
#define USE_TELEMETRY_JETIEXBUS
#define USE_TELEMETRY_MAVLINK
#define USE_TELEMETRY_HOTT
#define USE_TELEMETRY_LTM

#define USE_SPEKTRUM_BIND
#define USE_SPEKTRUM_BIND_PLUG
#define USE_SPEKTRUM_REAL_RSSI
#define USE_SPEKTRUM_FAKE_RSSI
#define USE_SPEKTRUM_RSSI_PERCENT_CONVERSION
#define USE_SPEKTRUM_VTX_CONTROL
#define USE_SPEKTRUM_VTX_TELEMETRY
#define USE_SPEKTRUM_CMS_TELEMETRY
#define SERIALRX_UART                   SERIAL_PORT_USART1
#define DEFAULT_RX_FEATURE              FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER               SERIALRX_SBUS

/* ======== FLASH ======== */
#define USE_BLACKBOX
#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT
#define USE_FLASHFS
#define USE_FLASH_M25P16
#define USE_FLASH_W25M
#define USE_FLASH_W25N01G
#define FLASH_CS_PIN                    SPI1_NSS_PIN
#define FLASH_SPI_INSTANCE              SPI1

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define VBAT_ADC_PIN                    PC0
#define CURRENT_METER_ADC_PIN           PC1

#define VBAT_SCALE_DEFAULT              110

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define USE_DSHOT
#define USE_DSHOT_DMAR
#define USE_DSHOT_BITBANG
#define USE_DSHOT_TELEMETRY
#define USE_DSHOT_TELEMETRY_STATS
#define USE_BRUSHED_ESC_AUTODETECT  // Detect if brushed motors are connected and set defaults appropriately to avoid motors spinning on boot
#define ENABLE_DSHOT_DMAR               DSHOT_DMAR_ON
#define DSHOT_BITBANG_DEFAULT           DSHOT_BITBANG_AUTO

/* ======== PINIO ======== */
#define PINIO1_PIN                      PB2

/* ======== OTHER ======== */
#define USE_SERVOS
#define DEFAULT_FEATURES                (FEATURE_LED_STRIP | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT      5
#define USED_TIMERS                     ( TIM_N(1) | TIM_N(2) | TIM_N(3) )