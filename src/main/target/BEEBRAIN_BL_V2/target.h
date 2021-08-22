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

#define TARGET_BOARD_IDENTIFIER         "BeeBrain BL V2"
#define USBD_PRODUCT_STRING             "BeeBrain BL V2"

/* ======== LED ======== */
#define LED0_PIN                        PC13
#define LED1_PIN                        PC14

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PB10
#define BEEPER_PWM_HZ                   5400
#define BEEPER_INVERTED

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

/* ======== GYRO & ACC ======== */
#define USE_ACC
#define USE_GYRO
#define USE_SPI_GYRO
#define USE_ACCGYRO_BMI160

#define BMI160_SPI_DIVISOR              16

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN                 PB0
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN                   PA4
#define GYRO_1_SPI_INSTANCE             SPI3

#define GYRO_1_ALIGN                    CW0_DEG

/* ======== OSD ======== */
#define USE_MAX7456
#define USE_NBD7456

#define MAX7456_SPI_CS_PIN              PA15
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== VTX ======== */
#define USE_VTX_RTC6705

#undef USE_VTX_SMARTAUDIO
#undef USE_VTX_TRAMP

#define RTC6705_CS_PIN                  PA14
#define RTC6705_SPI_INSTANCE            SPI3

#define CMS_SKIP_EMPTY_VTX_TABLE_ENTRIES

/* ======== RX ======== */
#define USE_RX_SPI

#define RX_SPI_INSTANCE                 SPI2
#define RX_NSS_PIN                      SPI2_NSS_PIN
#define RX_SPI_LED_PIN                  PA13
#define RX_SPI_EXTI_PIN                 PB2
#define RX_SPI_BIND_PIN                 PC15
#define RX_CC2500_SPI_ANT_SEL_PIN       PA7

#define USE_RX_FRSKY_SPI_TELEMETRY
#define USE_RX_CC2500_SPI_PA_LNA
#define USE_RX_CC2500_SPI_DIVERSITY
#define USE_RX_FRSKY_SPI_D
#define USE_RX_FRSKY_SPI_X
#define USE_RX_SFHSS_SPI

#define CC2500_BLINK_BIND
#define DEFAULT_RX_FEATURE              FEATURE_RX_SPI
#define RX_SPI_DEFAULT_PROTOCOL         RX_SPI_FRSKY_D

/* ======== ADC ======== */
#define USE_ADC
#define ADC1_INSTANCE                   ADC1

#define VBAT_ADC_PIN                    PB1
#define CURRENT_METER_ADC_PIN           PA5

#define VBAT_SCALE_DEFAULT              110
#define CURRENT_METER_SCALE_DEFAULT     510
#define CURRENT_METER_OFFSET_DEFAULT    0

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define ENABLE_DSHOT_DMAR               DSHOT_DMAR_ON

/* ======== OTHER ======== */
#define DEFAULT_FEATURES                (FEATURE_LED_STRIP | FEATURE_OSD)

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT      6
#define USED_TIMERS                     ( TIM_N(2) | TIM_N(4) | TIM_N(5) )

#define USE_TARGET_CONFIG