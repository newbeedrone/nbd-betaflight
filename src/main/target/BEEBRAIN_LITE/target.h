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

#ifdef BEEBRAIN_LITE_DSM
    #define TARGET_BOARD_IDENTIFIER     "BeeBrain Lite DSM Rev_C"
    #define USBD_PRODUCT_STRING         "BeeBrain Lite DSM"
#else
    #define TARGET_BOARD_IDENTIFIER     "BeeBrain Lite Rev_E"
    #define USBD_PRODUCT_STRING         "BeeBrain Lite"
#endif

#define TARGET_PREINIT

/* ======== LED ======== */
#define LED0_PIN                        PC13
#define LED1_PIN                        PC14

/* ======== UART ======== */
#define USE_UART

#define USE_VCP
#define USE_MSP_UART

#define USE_UART1
#define UART1_RX_PIN                    PA10
#define UART1_TX_PIN                    PA9

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define SERIAL_PORT_COUNT               3

/* ======== SPI ======== */
#define USE_SPI

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

#define GYRO_1_CS_PIN                   PA4
#define GYRO_1_SPI_INSTANCE             SPI3

#define GYRO_1_ALIGN                    CW90_DEG

/* ======== ACC ======== */
#define USE_ACC
#define USE_ACC_SPI_MPU6500

/* ======== BARO ======== */
#define USE_BARO
#define USE_BARO_SPI_BMP280

#define BARO_CS_PIN                     PA1
#define BARO_SPI_INSTANCE               SPI3

/* ======== OSD ======== */
#define USE_MAX7456
#define USE_NBD7456 // For NBD7456

#define MAX7456_SPI_CS_PIN              PA15
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== VTX ======== */
#define USE_VTX_RTC6705

#undef USE_VTX_SMARTAUDIO
#undef USE_VTX_TRAMP

#define RTC6705_CS_PIN                  PA14
#define RTC6705_SPI_INSTANCE            SPI3
#define RTC6705_POWER_PIN               PA6

#define VTX_POWER_PIN_INVERTED
#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== RX ======== */
#ifdef BEEBRAIN_LITE_DSM
    #define SERIALRX_UART               SERIAL_PORT_USART2
    #define DEFAULT_RX_FEATURE          FEATURE_RX_SERIAL
    #define SERIALRX_PROVIDER           SERIALRX_SPEKTRUM2048
#else
    #define USE_RX_SPI

    #define RX_SPI_INSTANCE             SPI2
    #define RX_NSS_PIN                  SPI2_NSS_PIN
    #define RX_SPI_LED_PIN              PA13
    #define RX_SPI_EXTI_PIN             PB2
    #define RX_SPI_BIND_PIN             PC15
    #define RX_CC2500_SPI_TX_EN_PIN     PB10
    #define RX_CC2500_SPI_ANT_SEL_PIN   PA7

    #define USE_RX_FRSKY_SPI_TELEMETRY
    #define USE_RX_CC2500_SPI_PA_LNA
    #define USE_RX_CC2500_SPI_DIVERSITY
    #define USE_RX_FRSKY_SPI_D
    #define USE_RX_FRSKY_SPI_X
    #define USE_RX_SFHSS_SPI
    #define USE_RX_REDPINE_SPI

    #define CC2500_BLINK_BIND
    #define DEFAULT_RX_FEATURE          FEATURE_RX_SPI
    #define RX_SPI_DEFAULT_PROTOCOL     RX_SPI_FRSKY_D
#endif

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define VBAT_ADC_PIN                    PB1
#define VBAT_SCALE_DEFAULT              110

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_NONE

/* ======== USB ======== */
#define USE_USB_DETECT
#define USB_DETECT_PIN                  PA5

/* ======== OTHER ======== */
#define DEFAULT_FEATURES                (FEATURE_LED_STRIP | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT      5
#define USED_TIMERS                     ( TIM_N(4) | TIM_N(5) )