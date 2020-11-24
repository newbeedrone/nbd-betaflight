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
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "common/maths.h"

#include "target/config_helper.h"

#include "fc/config.h"
#include "fc/rc_modes.h"
#include "fc/rc_controls.h"

#include "flight/mixer.h"

#include "pg/motor.h"

#include "drivers/motor.h"

#include "rx/rx.h"

#include "osd/osd.h"

#include "io/ledstrip.h"

static targetSerialPortFunction_t targetSerialPortFunction[] = {
    { SERIAL_PORT_SOFTSERIAL1,  FUNCTION_ESC_SENSOR },
};

void targetConfiguration(void)
{
    strcpy(pilotConfigMutable()->name, "Galaxy AIO");

    mixerConfigMutable()->yaw_motors_reversed = true;

    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT600;

    modeActivationConditionsMutable(0)->modeId          = BOXARM;
    modeActivationConditionsMutable(0)->auxChannelIndex = AUX1 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(0)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(0)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    osdConfigMutable()->item_pos[OSD_ITEM_TIMER_2]      = OSD_POS( 1, 10) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_RSSI_VALUE]        = OSD_POS( 1, 11) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_VTX_CHANNEL]       = OSD_POS(10, 10) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_WARNINGS]          = OSD_POS(10, 11) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_CRAFT_NAME]        = OSD_POS(10, 11) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_FLYMODE]           = OSD_POS(18, 10) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_MAIN_BATT_VOLTAGE] = OSD_POS(24, 10) | OSD_PROFILE_1_FLAG;
    osdConfigMutable()->item_pos[OSD_CURRENT_DRAW]      = OSD_POS(23, 11) | OSD_PROFILE_1_FLAG;

    ledStripStatusModeConfigMutable()->ledConfigs[0] = DEFINE_LED( 7, 7,  8, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[1] = DEFINE_LED( 8, 7, 13, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[2] = DEFINE_LED( 9, 7, 11, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[3] = DEFINE_LED(10, 7,  4, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);

    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));
}

#endif /* USE_TARGET_CONFIG */
