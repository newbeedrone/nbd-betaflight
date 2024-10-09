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
#include "pg/gps_rescue.h"
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

#include "drivers/dshot.h"

void targetConfiguration(void) {

    /* Configuration -> Other Features */
    featureConfigMutable()->enabledFeatures |= (FEATURE_LED_STRIP | FEATURE_OSD | FEATURE_GPS);

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

    modeActivationConditionsMutable(3)->modeId          = BOXBEEPERON;
    modeActivationConditionsMutable(3)->auxChannelIndex = AUX3 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(3)->range.startStep = CHANNEL_VALUE_TO_STEP(1300);
    modeActivationConditionsMutable(3)->range.endStep   = CHANNEL_VALUE_TO_STEP(1700);

    modeActivationConditionsMutable(4)->modeId          = BOXGPSRESCUE;
    modeActivationConditionsMutable(4)->auxChannelIndex = AUX4 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(4)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(4)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    modeActivationConditionsMutable(5)->modeId          = BOXFLIPOVERAFTERCRASH;
    modeActivationConditionsMutable(5)->auxChannelIndex = AUX3 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(5)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(5)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    /* PID Tuning -> Filter Setting */
    dynNotchConfigMutable()->dyn_notch_count = 1;
    dynNotchConfigMutable()->dyn_notch_q = 500;

    /* Motors */
    motorConfigMutable()->digitalIdleOffsetValue = 800;
    motorConfigMutable()->dev.useBurstDshot = DSHOT_DMAR_ON;
    motorConfigMutable()->dev.useDshotTelemetry = DSHOT_TELEMETRY_ON;
    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT300;
    motorConfigMutable()->motorPoleCount = 12;

    /* Failsafe -> Stage 2 - Setting */
    gpsRescueConfigMutable()->allowArmingWithoutFix = true;

    /* Motors -> Mixer */
    mixerConfigMutable()->yaw_motors_reversed = true;

    /* Configuration -> System configuration */
    pidConfigMutable()->pid_process_denom = 2;

    /* Configuration -> Arming */
    imuConfigMutable()->small_angle = 90;

    /* OSD */
    osdElementConfigMutable()->item_pos[OSD_MAIN_BATT_VOLTAGE]  = OSD_PROFILE_1_FLAG | OSD_POS(47,16);
    osdElementConfigMutable()->item_pos[OSD_RSSI_VALUE]         = OSD_PROFILE_1_FLAG | OSD_POS(1, 16);
    osdElementConfigMutable()->item_pos[OSD_ITEM_TIMER_2]       = OSD_PROFILE_1_FLAG | OSD_POS(1, 17);
    osdElementConfigMutable()->item_pos[OSD_FLYMODE]            = OSD_PROFILE_1_FLAG | OSD_POS(25,16);
    osdElementConfigMutable()->item_pos[OSD_CURRENT_DRAW]       = OSD_PROFILE_1_FLAG | OSD_POS(46,17);
    osdElementConfigMutable()->item_pos[OSD_CRAFT_NAME]         = OSD_PROFILE_1_FLAG | OSD_POS(18,17);
    osdElementConfigMutable()->item_pos[OSD_GPS_SATS]           = OSD_PROFILE_1_FLAG | OSD_POS(1, 15);
    osdElementConfigMutable()->item_pos[OSD_WARNINGS]           = OSD_PROFILE_1_FLAG | OSD_POS(21, 9);

    /* CPU Frequency */
    systemConfigMutable()->cpu_overclock = 1;

    /* PID Tuning -> Filter Settings -> Gyro RPM Filter */
    rpmFilterConfigMutable()->rpm_filter_harmonics = 2;

    /* Configuration -> Personalization */
    strcpy(pilotConfigMutable()->craftName, USBD_PRODUCT_STRING);

    /* PID Tuning */
    pidProfilesMutable(0)->pid[PID_PITCH].P = 111;
    pidProfilesMutable(0)->pid[PID_PITCH].I = 169;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 159;
    pidProfilesMutable(0)->pid[PID_PITCH].F = 74;
    pidProfilesMutable(0)->pid[PID_ROLL].P = 76;
    pidProfilesMutable(0)->pid[PID_ROLL].I = 115;
    pidProfilesMutable(0)->pid[PID_ROLL].D = 116;
    pidProfilesMutable(0)->pid[PID_ROLL].F = 50;
    pidProfilesMutable(0)->pid[PID_YAW].P = 130;
    pidProfilesMutable(0)->pid[PID_YAW].I = 60;
    pidProfilesMutable(0)->pid[PID_YAW].F = 0;
    pidProfilesMutable(0)->pid[PID_LEVEL].I = 50;
    pidProfilesMutable(0)->d_min[FD_ROLL] = 96;
    pidProfilesMutable(0)->d_min[FD_PITCH] = 131;
    pidProfilesMutable(0)->simplified_pids_mode = PID_SIMPLIFIED_TUNING_RP;
    pidProfilesMutable(0)->simplified_master_multiplier = 170;
    pidProfilesMutable(0)->simplified_i_gain = 85;
    pidProfilesMutable(0)->simplified_d_gain = 190;
    pidProfilesMutable(0)->simplified_dmin_ratio = 60;
    pidProfilesMutable(0)->simplified_feedforward_gain = 25;
    pidProfilesMutable(0)->simplified_roll_pitch_ratio = 120;
    pidProfilesMutable(0)->simplified_pitch_pi_gain = 140;
}

#endif /* USE_TARGET_CONFIG */