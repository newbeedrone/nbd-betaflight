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

#if defined(HIVE16_DSM_BASE)
    #define TARGET_BOARD_IDENTIFIER     "Hive16 DSM"
    #define USBD_PRODUCT_STRING         "Hive16 DSM"
#else
    #define TARGET_BOARD_IDENTIFIER     "Hive16"
    #define USBD_PRODUCT_STRING         "Hive16"
#endif

/* ======== LED ======== */
#define LED0_PIN                        PC13
#define LED1_PIN                        PC14

/* ======== UART ======== */
#define USE_UART
#define USE_MSP_UART
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
#define SPI2_NSS_PIN                    PB12

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB3
#define SPI3_MISO_PIN                   PB4
#define SPI3_MOSI_PIN                   PB5

/* ======== GYRO ======== */
#define USE_GYRO
#define USE_GYRO_SPI_MPU6500

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PB0
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN                   SPI1_NSS_PIN
#define GYRO_1_SPI_INSTANCE             SPI1

#define GYRO_1_ALIGN                    ALIGN_CUSTOM
#define GYRO_1_CUSTOM_ALIGN             SENSOR_ALIGNMENT(0, 0, 45)

/* ======== ACC ======== */
#define USE_ACC
#define USE_ACC_SPI_MPU6500

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              PA15
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== VTX ======== */
#define USE_VTX_RTC6705

#undef USE_VTX_SMARTAUDIO
#undef USE_VTX_TRAMP

#define RTC6705_CS_PIN                  PA14
#define RTC6705_SPI_INSTANCE            SPI3
#define RTC6705_POWER_PIN               PC15

#define VTX_POWER_PIN_INVERTED
#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== RX ======== */
#if defined(HIVE16_BASE)
    #define DJTS
    #define USE_RX_SPI
    #define RX_SPI_INSTANCE             SPI2
    #define RX_NSS_PIN                  SPI2_NSS_PIN
    #define RX_SPI_LED_PIN              PA13
    #define RX_SPI_EXTI_PIN             PB2
    #define RX_CC2500_SPI_TX_EN_PIN     PB10
    #define RX_CC2500_SPI_ANT_SEL_PIN   PA8
    #define RX_CC2500_SPI_LNA_EN_PIN    NONE

    #define USE_RX_FRSKY_SPI_TELEMETRY
    #define USE_RX_CC2500_SPI_PA_LNA
    #define USE_RX_CC2500_SPI_DIVERSITY
    #define USE_RX_FRSKY_SPI_D
    #define USE_RX_FRSKY_SPI_X
    #define USE_RX_SFHSS_SPI

    #define CC2500_BLINK_BIND
    #define DEFAULT_RX_FEATURE          FEATURE_RX_SPI
    #define RX_SPI_DEFAULT_PROTOCOL     RX_SPI_FRSKY_D
#elif defined(HIVE16_DSM_BASE)
    #define SERIALRX_PROVIDER           SERIALRX_SPEKTRUM2048
    #define DEFAULT_RX_FEATURE          FEATURE_RX_SERIAL
    #define SERIALRX_UART               SERIAL_PORT_USART2
#endif

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define VBAT_ADC_PIN                    PB1

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_NONE

/* ======== ESC ======== */
#define ENABLE_DSHOT_DMAR               DSHOT_DMAR_AUTO
#define DSHOT_BITBANG_DEFAULT           DSHOT_BITBANG_OFF

/* ======== OTHER ======== */
#define DEFAULT_FEATURES                (FEATURE_LED_STRIP | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT      6
#define USED_TIMERS                     ( TIM_N(4) | TIM_N(5) )

#define USE_TARGET_CONFIG