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

#define TARGET_BOARD_IDENTIFIER         "HummingBird F4 V3"
#define USBD_PRODUCT_STRING             "HummingBird F4 V3"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
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
#define SPI3_SCK_PIN                    PB3
#define SPI3_MISO_PIN                   PB4
#define SPI3_MOSI_PIN                   PB5

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

#define GYRO_1_ALIGN                    CW180_DEG

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

#define MAX7456_SPI_CS_PIN              PB12
#define MAX7456_SPI_INSTANCE            SPI2

/* ======== VTX ======== */
#define USE_VTX
#define USE_VTX_COMMON
#define USE_VTX_CONTROL
#define USE_VTX_MSP
#define USE_VTX_TABLE
#define USE_VTX_RTC6705
#define SPI_SHARED_MAX7456_AND_RTC6705

#define RTC6705_CS_PIN                  PA14
#define RTC6705_SPI_INSTANCE            SPI2

#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

// #define USE_BEESIGN
// #define USE_VTX_BEESIGN

// #define BEESIGN_UART                    SERIAL_PORT_USART1

// #define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== RX ======== */
#define USE_RX_SPI
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

#define RX_SPI_INSTANCE                 SPI3
#define RX_SPI_LED_INVERTED
#define RX_NSS_PIN                      PA15
#define RX_SPI_LED_PIN                  PC15
#define RX_SPI_EXTI_PIN                 PC13
#define RX_SPI_BIND_PIN                 PB2
#define RX_EXPRESSLRS_SPI_RESET_PIN     PB9
#define RX_EXPRESSLRS_SPI_BUSY_PIN      PA13
#define RX_EXPRESSLRS_TIMER_INSTANCE    TIM5

#define USE_TELEMETRY
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
#define CURRENT_METER_SCALE_DEFAULT     510
#define CURRENT_METER_OFFSET_DEFAULT    0

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

/* ======== OTHER ======== */
#define USE_OVERCLOCK
#define USE_BLACKBOX
#define USE_SERVOS
#define USE_PINIO
#define USE_PINIOBOX
#define DEFAULT_FEATURES                (FEATURE_INFLIGHT_ACC_CAL | FEATURE_LED_STRIP | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 (BIT(2))

#define USE_BEEPER

#define USABLE_TIMER_CHANNEL_COUNT      5
#define USED_TIMERS                     ( TIM_N(2) | TIM_N(3) | TIM_N(4) )

#define USE_TARGET_CONFIG