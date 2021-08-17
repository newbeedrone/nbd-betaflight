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

#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {

    DEF_TIM(TIM1, CH1, PE9,  TIM_USE_MOTOR,         0, 1, 0), // M1
    DEF_TIM(TIM3, CH2, PC7,  TIM_USE_MOTOR,         0, 2, 0), // M2
    DEF_TIM(TIM4, CH3, PB8,  TIM_USE_MOTOR,         0, 3, 0), // M3
    DEF_TIM(TIM1, CH3, PA10, TIM_USE_MOTOR,         0, 4, 0), // M4

    DEF_TIM(TIM1, CH2, PA9,  TIM_USE_LED,           0, 11, 0), // LED Strip
    DEF_TIM(TIM4, CH2, PD13, TIM_USE_BEEPER,        0, 12, 0)  // Beeper
};
