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
#include "pg/gps_rescue.h"

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
    featureConfigMutable()->enabledFeatures |= ( FEATURE_GPS | FEATURE_SERVO_TILT | FEATURE_TELEMETRY | FEATURE_LED_STRIP | FEATURE_OSD | FEATURE_CHANNEL_FORWARDING );

    /* Configuration -> Dshot Beacon Configuration */
    beeperConfigMutable()->dshotBeaconOffFlags = BEEPER_RX_SET;

    /* Modes */
    modeActivationConditionsMutable(0)->modeId          = BOXARM;
    modeActivationConditionsMutable(0)->auxChannelIndex = AUX1 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(0)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(0)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    modeActivationConditionsMutable(1)->modeId          = BOXANGLE;
    modeActivationConditionsMutable(1)->auxChannelIndex = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(1)->range.startStep = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(1)->range.endStep   = CHANNEL_VALUE_TO_STEP(2100);

    modeActivationConditionsMutable(2)->modeId          = BOXHORIZON;
    modeActivationConditionsMutable(2)->auxChannelIndex = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(2)->range.startStep = CHANNEL_VALUE_TO_STEP(1300);
    modeActivationConditionsMutable(2)->range.endStep   = CHANNEL_VALUE_TO_STEP(1700);

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
    motorConfigMutable()->digitalIdleOffsetValue = 550;
    motorConfigMutable()->dev.useDshotTelemetry = DSHOT_TELEMETRY_ON;
    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT600;
    motorConfigMutable()->motorPoleCount = 12;

    /* Motors -> Mixer */
    mixerConfigMutable()->yaw_motors_reversed = true;
    
    /* Compass */
    compassConfigMutable()->mag_alignment = CW180_DEG;
    compassConfigMutable()->mag_customAlignment.yaw = 1800;
    compassConfigMutable()->mag_customAlignment.pitch = 0;

    /* GPS */
    gpsConfigMutable()->gps_ublox_use_galileo = true;

    /* Failsafe -> Stage 2 - Setting */
    failsafeConfigMutable()->failsafe_procedure = FAILSAFE_PROCEDURE_GPS_RESCUE;
    gpsRescueConfigMutable()->initialClimbM = 30;
    gpsRescueConfigMutable()->maxRescueAngle = 60;
    gpsRescueConfigMutable()->minSats = 6;
    gpsRescueConfigMutable()->allowArmingWithoutFix = true;
    gpsRescueConfigMutable()->minStartDistM = 10;
    gpsRescueConfigMutable()->ascendRate = 500;
    gpsRescueConfigMutable()->groundSpeedCmS = 500;
    gpsRescueConfigMutable()->descentDistanceM = 30;
    gpsRescueConfigMutable()->descendRate = 100;

    /* RxFail */
    rxFailsafeChannelConfigsMutable(3)->mode = RX_FAILSAFE_MODE_SET;
    rxFailsafeChannelConfigsMutable(3)->step = CHANNEL_VALUE_TO_RXFAIL_STEP(1500);

    rxFailsafeChannelConfigsMutable(5)->mode = RX_FAILSAFE_MODE_SET;
    rxFailsafeChannelConfigsMutable(5)->step = CHANNEL_VALUE_TO_RXFAIL_STEP(1100);

    /* Power & Battery */
    batteryConfigMutable()->vbatmincellvoltage = 330;
    batteryConfigMutable()->vbatwarningcellvoltage = 350;
    batteryConfigMutable()->vbatmaxcellvoltage  = 440;

    /* Configuration -> Dshot Beacon Configuration */
    beeperConfigMutable()->dshotBeaconTone = DSHOT_CMD_BEACON2;
    beeperConfigMutable()->dshotBeaconOffFlags = BEEPER_SILENCE;

    /* Configuration -> Arming */
    imuConfigMutable()->small_angle = 180;

    /* OSD */ 
    osdElementConfigMutable()->item_pos[OSD_MAIN_BATT_VOLTAGE]             = OSD_PROFILE_1_FLAG | OSD_POS(43,16);
    osdElementConfigMutable()->item_pos[OSD_WARNINGS]                      = OSD_PROFILE_1_FLAG | OSD_POS(21,9);
    osdElementConfigMutable()->item_pos[OSD_RSSI_VALUE]                    = OSD_PROFILE_1_FLAG | OSD_POS(3,17);
    osdElementConfigMutable()->item_pos[OSD_ITEM_TIMER_1]                  = OSD_PROFILE_1_FLAG | OSD_POS(3,16);
    osdElementConfigMutable()->item_pos[OSD_FLYMODE]                       = OSD_PROFILE_1_FLAG | OSD_POS(19,17);
    osdElementConfigMutable()->item_pos[OSD_CURRENT_DRAW]                  = OSD_PROFILE_1_FLAG | OSD_POS(26,17);
    osdElementConfigMutable()->item_pos[OSD_CRAFT_NAME]                    = OSD_PROFILE_1_FLAG | OSD_POS(19,16);
    osdElementConfigMutable()->item_pos[OSD_GPS_SATS]                      = OSD_PROFILE_1_FLAG | OSD_POS(2,2);
    osdElementConfigMutable()->item_pos[OSD_AVG_CELL_VOLTAGE]              = OSD_PROFILE_1_FLAG | OSD_POS(43,17);

    osdConfigMutable()->displayPortDevice = OSD_DISPLAYPORT_DEVICE_MSP;

    /* OSD -> Video Format */
    vcdProfileMutable()->video_system = VIDEO_SYSTEM_HD;

    /* Configuration -> Personalization */
    strcpy(pilotConfigMutable()->craftName, USBD_PRODUCT_STRING);

    /* PID Tuning */
    gyroConfigMutable()->gyro_lpf1_static_hz = 0;
    gyroConfigMutable()->gyro_lpf1_dyn_min_hz = 0;
    rxConfigMutable()->rc_smoothing_auto_factor_rpy = 60;
    rpmFilterConfigMutable()->rpm_filter_weights[0] = 100;
    rpmFilterConfigMutable()->rpm_filter_weights[1] = 20;
    rpmFilterConfigMutable()->rpm_filter_weights[2] = 100;
    rpmFilterConfigMutable()->rpm_filter_fade_range_hz = 150;
    pidProfilesMutable(0)->vbat_sag_compensation = 100;
    pidProfilesMutable(0)->iterm_relax_cutoff  = 45;
    pidProfilesMutable(0)->pid[PID_PITCH].P = 42;
    pidProfilesMutable(0)->pid[PID_PITCH].I = 98;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 42;
    pidProfilesMutable(0)->pid[PID_PITCH].F = 137;
    pidProfilesMutable(0)->pid[PID_ROLL].P = 40;
    pidProfilesMutable(0)->pid[PID_ROLL].I = 93;
    pidProfilesMutable(0)->pid[PID_ROLL].D = 37;
    pidProfilesMutable(0)->pid[PID_ROLL].F = 132;
    pidProfilesMutable(0)->pid[PID_YAW].P = 45;
    pidProfilesMutable(0)->pid[PID_YAW].I = 80;
    pidProfilesMutable(0)->pid[PID_YAW].F = 120;
    pidProfilesMutable(0)->d_min[FD_ROLL] = 28;
    pidProfilesMutable(0)->d_min[FD_PITCH] = 32;
    pidProfilesMutable(0)->thrustLinearization = 20;
    pidProfilesMutable(0)->feedforward_averaging = FEEDFORWARD_AVERAGING_2_POINT;
    pidProfilesMutable(0)->feedforward_smooth_factor = 65;
    pidProfilesMutable(0)->feedforward_jitter_factor = 10;
    pidProfilesMutable(0)->dyn_idle_min_rpm = 60;
    pidProfilesMutable(0)->simplified_pids_mode = PID_SIMPLIFIED_TUNING_RP;
    pidProfilesMutable(0)->simplified_master_multiplier = 100;
    pidProfilesMutable(0)->simplified_i_gain = 130;
    pidProfilesMutable(0)->simplified_d_gain = 95;
    pidProfilesMutable(0)->simplified_pi_gain = 90;
    pidProfilesMutable(0)->simplified_dmin_ratio = 90;
    pidProfilesMutable(0)->simplified_feedforward_gain = 110;
    pidProfilesMutable(0)->simplified_pitch_pi_gain = 100;
}

#endif /* USE_TARGET_CONFIG */