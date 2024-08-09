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

#define TARGET_BOARD_IDENTIFIER         "Infinity AIO"
#define USBD_PRODUCT_STRING             "Infinity AIO"

/* ======== LED ======== */
#define USE_LED_STRIP
#define USE_LED_STRIP_STATUS_MODE
#define LED_STRIP_PIN                   PA9

#define LED0_PIN                        PC0

/* ======== BUZZER ======== */
#define USE_BEEPER
#define BEEPER_PIN                      PD13
#define BEEPER_INVERTED

/* ======== UART ======== */
#define USE_UART

#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN                    PB7

#define USE_UART2
#define UART2_RX_PIN                    PA3
#define UART2_TX_PIN                    PA2

#define USE_UART3
#define UART3_RX_PIN                    PB11
#define UART3_TX_PIN                    PB10

#define USE_UART5
#define UART5_RX_PIN                    PD2

#define USE_UART7
#define UART7_TX_PIN                    PE8

#define USE_UART8
#define UART8_RX_PIN                    PE0
#define UART8_TX_PIN                    PE1

#define SERIAL_PORT_COUNT               7

/* ======== SPI ======== */
#define USE_SPI
#define USE_SPI_DMA_ENABLE_EARLY

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PA5
#define SPI1_SDI_PIN                    PA6
#define SPI1_SDO_PIN                    PA7

#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PB3
#define SPI3_SDI_PIN                    PB4
#define SPI3_SDO_PIN                    PD6
#define SPI3_NSS_PIN                    PA15

#define USE_SPI_DEVICE_4
#define SPI4_SCK_PIN                    PE12
#define SPI4_SDI_PIN                    PE13
#define SPI4_SDO_PIN                    PE14
#define SPI4_NSS_PIN                    PE11

/* ======== I2C ======== */
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C1_SCL_PIN                    PB8
#define I2C1_SDA_PIN                    PB9

/* ======== GYRO ======== */
#define USE_GYRO
#define USE_GYRO_SPI_MPU6000

#define GYRO_1_EXTI_PIN                 PB1
#define GYRO_1_CS_PIN                   SPI4_NSS_PIN
#define GYRO_1_SPI_INSTANCE             SPI4

#define GYRO_1_ALIGN                    CW180_DEG

/* ======== ACC ======== */
#define USE_ACC
#define USE_ACC_SPI_MPU6000

/* ======== OSD ======== */
#define USE_MAX7456

#define MAX7456_SPI_CS_PIN              SPI3_NSS_PIN
#define MAX7456_SPI_INSTANCE            SPI3

/* ======== FLASH ======== */
#define USE_FLASH_W25Q128FV

#define FLASH_CS_PIN                    PB0
#define FLASH_SPI_INSTANCE              SPI1

/* ======== ADC ======== */
#define USE_ADC
#define ADC_INSTANCE                    ADC1
#define ADC1_DMA_OPT                    0

#define ADC_VBAT_PIN                    PC1
#define ADC_CURR_PIN                    PC2

#define VBAT_SCALE_DEFAULT              100
#define CURRENT_METER_SCALE_DEFAULT     410

#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

/* ======== ESC ======== */
#define MOTOR1_PIN                      PC9
#define MOTOR2_PIN                      PC8
#define MOTOR3_PIN                      PC7
#define MOTOR4_PIN                      PC6

#define USE_ESCSERIAL

/* ======== OTHER ======== */
#define USE_EXTI

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, MOTOR1_PIN ,    1, 0) \
    TIMER_PIN_MAP( 1, MOTOR2_PIN ,    1, 0) \
    TIMER_PIN_MAP( 2, MOTOR3_PIN ,    1, 0) \
    TIMER_PIN_MAP( 3, MOTOR4_PIN ,    1, 0) \
    TIMER_PIN_MAP( 4, LED_STRIP_PIN , 1, 0) \
    TIMER_PIN_MAP( 5, BEEPER_PIN ,    1, 0) 

#define TARGET_IO_PORTA                 0xffff
#define TARGET_IO_PORTB                 0xffff
#define TARGET_IO_PORTC                 0xffff
#define TARGET_IO_PORTD                 0xffff
#define TARGET_IO_PORTE                 0xffff
#define TARGET_IO_PORTF                 0xffff

#define FLASH_PAGE_SIZE                 ((uint32_t)0x8000) // 32K sectors