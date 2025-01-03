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
#include <math.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "blackbox/blackbox.h"

#include "build/debug.h"

#include "cli/cli.h"

#include "common/sensor_alignment.h"

#include "config/config_eeprom.h"
#include "config/feature.h"
#include "config/simplified_tuning.h"

#include "drivers/dshot_command.h"
#include "drivers/motor.h"
#include "drivers/osd.h"
#include "drivers/system.h"

#include "fc/controlrate_profile.h"
#include "fc/core.h"
#include "fc/rc.h"
#include "fc/rc_adjustments.h"
#include "fc/rc_controls.h"
#include "fc/runtime_config.h"

#include "flight/failsafe.h"
#include "flight/imu.h"
#include "flight/mixer.h"
#include "flight/pid.h"
#include "flight/pid_init.h"
#include "flight/rpm_filter.h"
#include "flight/servos.h"
#include "flight/position.h"

#include "io/beeper.h"
#include "io/displayport_msp.h"
#include "io/gps.h"
#include "io/ledstrip.h"
#include "io/serial.h"
#include "io/vtx.h"

#include "msp/msp_box.h"

#include "osd/osd.h"

#include "pg/adc.h"
#include "pg/beeper.h"
#include "pg/beeper_dev.h"
#include "pg/displayport_profiles.h"
#include "pg/dyn_notch.h"
#include "pg/gyrodev.h"
#include "pg/motor.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"
#include "pg/rx.h"
#include "pg/rx_spi.h"
#include "pg/sdcard.h"
#include "pg/vcd.h"
#include "pg/vtx_table.h"

#include "rx/rx.h"
#include "rx/rx_spi.h"

#include "scheduler/scheduler.h"

#include "sensors/acceleration.h"
#include "sensors/battery.h"
#include "sensors/compass.h"
#include "sensors/gyro.h"

void targetConfiguration(void) {

    /* Configuration -> Other Features */
    featureConfigMutable()->enabledFeatures |= ( FEATURE_SERVO_TILT | FEATURE_TELEMETRY | FEATURE_OSD | FEATURE_CHANNEL_FORWARDING );

    /* PID Frequency */
    pidConfigMutable()->pid_process_denom=2;

    /* Modes */
    modeActivationConditionsMutable(0)->modeId          = BOXARM;
    modeActivationConditionsMutable(0)->auxChannelIndex = AUX1 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(0)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(0)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    modeActivationConditionsMutable(1)->modeId          = BOXANGLE;
    modeActivationConditionsMutable(1)->auxChannelIndex = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(1)->range.startStep = CHANNEL_VALUE_TO_STEP(900);
    modeActivationConditionsMutable(1)->range.endStep   = CHANNEL_VALUE_TO_STEP(1300);

    modeActivationConditionsMutable(2)->modeId          = BOXHORIZON;
    modeActivationConditionsMutable(2)->auxChannelIndex = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(2)->range.startStep = CHANNEL_VALUE_TO_STEP(1300);
    modeActivationConditionsMutable(2)->range.endStep   = CHANNEL_VALUE_TO_STEP(1700);

    modeActivationConditionsMutable(3)->modeId          = BOXFLIPOVERAFTERCRASH;
    modeActivationConditionsMutable(3)->auxChannelIndex = AUX3 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(3)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(3)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    /* Motors */
    motorConfigMutable()->minthrottle = 1030;

    /* OSD */
    osdWarnSetState(OSD_WARNING_BATTERY_NOT_FULL, false);
    osdWarnSetState(OSD_WARNING_VISUAL_BEEPER, false);

    osdElementConfigMutable()->item_pos[OSD_MAIN_BATT_VOLTAGE]  = OSD_PROFILE_1_FLAG | OSD_POS(24,10);
    osdElementConfigMutable()->item_pos[OSD_RSSI_VALUE]         = OSD_PROFILE_1_FLAG | OSD_POS(1, 11);
    osdElementConfigMutable()->item_pos[OSD_ITEM_TIMER_2]       = OSD_PROFILE_1_FLAG | OSD_POS(1, 10);
    osdElementConfigMutable()->item_pos[OSD_FLYMODE]            = OSD_PROFILE_1_FLAG | OSD_POS(18,10);
    osdElementConfigMutable()->item_pos[OSD_VTX_CHANNEL]        = OSD_PROFILE_1_FLAG | OSD_POS(8, 10);
    osdElementConfigMutable()->item_pos[OSD_CURRENT_DRAW]       = OSD_PROFILE_1_FLAG | OSD_POS(23,11);
    osdElementConfigMutable()->item_pos[OSD_CRAFT_NAME]         = OSD_PROFILE_1_FLAG | OSD_POS(8 ,11);
    osdElementConfigMutable()->item_pos[OSD_WARNINGS]           = OSD_PROFILE_1_FLAG | OSD_PROFILE_FLAG(2) | OSD_PROFILE_FLAG(3) | OSD_POS(9, 6);

    osdConfigMutable()->displayPortDevice = OSD_DISPLAYPORT_DEVICE_AUTO;

    /* OSD -> Video Format */
    vcdProfileMutable()->video_system = VIDEO_SYSTEM_AUTO;

    /* Configuration -> Personalization */
    strcpy(pilotConfigMutable()->craftName, USBD_PRODUCT_STRING);

    /* Configuration -> LED Strip */
    ledStripStatusModeConfigMutable()->ledConfigs[0] = DEFINE_LED( 7, 7,  8, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE));
    ledStripStatusModeConfigMutable()->ledConfigs[1] = DEFINE_LED( 8, 7, 13, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE));
    ledStripStatusModeConfigMutable()->ledConfigs[2] = DEFINE_LED( 9, 7, 11, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE));
}

#endif /* USE_TARGET_CONFIG */