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
#include "sensors/barometer.h"
#include "sensors/gyro.h"


void targetConfiguration(void) {

    /* Configuration -> Other Features */
    featureConfigMutable()->enabledFeatures |= (FEATURE_TELEMETRY | FEATURE_LED_STRIP | FEATURE_OSD);

    /* Configuration -> Dshot Beacon Configuration */
    beeperConfigMutable()->dshotBeaconOffFlags = BEEPER_RX_LOST;
    beeperConfigMutable()->dshotBeaconOffFlags = BEEPER_RX_SET;

    /* Configuration -> LED Strip */
    ledStripStatusModeConfigMutable()->ledConfigs[0] = DEFINE_LED( 7,  7,  8, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE));
    ledStripStatusModeConfigMutable()->ledConfigs[1] = DEFINE_LED( 8,  7, 13, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE));
    ledStripStatusModeConfigMutable()->ledConfigs[2] = DEFINE_LED( 9,  7, 11, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE));
    ledStripStatusModeConfigMutable()->ledConfigs[3] = DEFINE_LED( 10, 7, 12, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE));

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

    /* Video Transmitter -> VTX Table */
#define _USER_VTX_TABLE_MAX_BANDS           5
#define _USER_VTX_TABLE_MAX_CHANNELS        8
#define _USER_VTX_TABLE_MAX_POWER_LEVELS    3

    uint16_t vtxTableFrequency[_USER_VTX_TABLE_MAX_BANDS][_USER_VTX_TABLE_MAX_CHANNELS] = {
        { 5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725 }, // Boscam A
        { 5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866 }, // Boscam B
        { 5705, 5685, 5665,    0, 5885, 5905,    0,    0 }, // Boscam E
        { 5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880 }, // FatShark
        { 5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917 }, // RaceBand
    };

    const char *vtxTableBandNames[_USER_VTX_TABLE_MAX_BANDS + 1] = {
        "BOSCAM A",
        "BOSCAM B",
        "BOSCAM E",
        "FATSHARK",
        "RACEBAND",
    };

    char vtxTableBandLetters[_USER_VTX_TABLE_MAX_BANDS + 1] = {
        "ABEFR",
    };

    const char *vtxTableChannelNames[_USER_VTX_TABLE_MAX_CHANNELS + 1] = {
        "1", "2", "3", "4", "5", "6", "7", "8",
    };

    const char *rtc6705PowerNames[_USER_VTX_TABLE_MAX_POWER_LEVELS + 1] = {
        "25 ", "100", "MAX",
    };

    vtxTableConfigMutable()->bands = _USER_VTX_TABLE_MAX_BANDS;
    vtxTableConfigMutable()->channels = _USER_VTX_TABLE_MAX_CHANNELS;
    vtxTableConfigMutable()->powerLevels = _USER_VTX_TABLE_MAX_POWER_LEVELS;

    for (uint8_t i = 0; i < _USER_VTX_TABLE_MAX_BANDS; i++) {
        for (uint8_t j = 0; j < _USER_VTX_TABLE_MAX_CHANNELS; j++) {
            vtxTableConfigMutable()->frequency[i][j] = vtxTableFrequency[i][j];
        }
    }
    for (uint8_t i = 0; i < _USER_VTX_TABLE_MAX_BANDS; i++) {
        strcpy(vtxTableConfigMutable()->bandNames[i], vtxTableBandNames[i]);
        vtxTableConfigMutable()->bandLetters[i] = vtxTableBandLetters[i];
    }
    for (uint8_t i = 0; i < _USER_VTX_TABLE_MAX_CHANNELS; i++) {
        strcpy(vtxTableConfigMutable()->channelNames[i], vtxTableChannelNames[i]);
    }
    for (uint8_t i = 0; i < _USER_VTX_TABLE_MAX_POWER_LEVELS; i++) {
        vtxTableConfigMutable()->powerValues[i] = i;
        strcpy(vtxTableConfigMutable()->powerLabels[i], rtc6705PowerNames[i]);
    }

#undef _USER_VTX_TABLE_MAX_BANDS
#undef _USER_VTX_TABLE_MAX_CHANNELS
#undef _USER_VTX_TABLE_MAX_POWER_LEVELS

    /* Motors */
    motorConfigMutable()->digitalIdleOffsetValue = 550;
    motorConfigMutable()->dev.useDshotTelemetry = DSHOT_TELEMETRY_ON;
    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT600;
    motorConfigMutable()->motorPoleCount = 12;

    /* Power & Battery */
    batteryConfigMutable()->vbatmincellvoltage = 330;
    batteryConfigMutable()->vbatwarningcellvoltage = 340;
    batteryConfigMutable()->vbatmaxcellvoltage  = 440;

    /* Configuration -> Arming */
    imuConfigMutable()->small_angle = 180;

    /* Configuration -> Dshot Beacon Configuration */
    beeperConfigMutable()->dshotBeaconTone = DSHOT_CMD_BEACON2;

    /* Motors -> Mixer */
    mixerConfigMutable()->yaw_motors_reversed = true;

    /* Mag */
    compassConfigMutable()->mag_hardware = MAG_NONE;
    
    /* BARO */
    barometerConfigMutable()->baro_hardware = BARO_NONE;

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

    osdConfigMutable()->core_temp_alarm   = 85;
    osdConfigMutable()->displayPortDevice = OSD_DISPLAYPORT_DEVICE_MAX7456;

    /* Video Transmitter -> Select Mode */
    vtxSettingsConfigMutable()->band = 4;
    vtxSettingsConfigMutable()->channel = 4;
    vtxSettingsConfigMutable()->power = 1;

    /* OSD -> Video Format */
    vcdProfileMutable()->video_system = VIDEO_SYSTEM_NTSC;

    /* Unknow -> CPU */
    schedulerConfigMutable()->cpuLatePercentageLimit = 35;

    /* Configuration -> Personalization */
    strcpy(pilotConfigMutable()->craftName, USBD_PRODUCT_STRING);

    /* Gyro */
    gyroConfigMutable()->gyro_lpf1_static_hz = 0;
    gyroConfigMutable()->gyro_lpf2_static_hz = 500;
    gyroConfigMutable()->gyro_lpf1_dyn_min_hz = 0;
    gyroConfigMutable()->gyro_lpf1_dyn_max_hz = 0;
    dynNotchConfigMutable()->dyn_notch_count = 1;
    dynNotchConfigMutable()->dyn_notch_q = 600;
    dynNotchConfigMutable()->dyn_notch_max_hz  = 750;
    rxConfigMutable()->rc_smoothing_auto_factor_rpy = 25;
    rxConfigMutable()->rc_smoothing_auto_factor_throttle = 25;
    rpmFilterConfigMutable()->rpm_filter_weights[0] = 100;
    rpmFilterConfigMutable()->rpm_filter_weights[1] = 20;
    rpmFilterConfigMutable()->rpm_filter_weights[2] = 100;
    rpmFilterConfigMutable()->rpm_filter_fade_range_hz = 100;
    rpmFilterConfigMutable()->rpm_filter_harmonics = 1;
    rpmFilterConfigMutable()->rpm_filter_fade_range_hz = 120;

    /* PID Tuning -> PID Profile Setting */
    pidProfilesMutable(0)->dterm_lpf1_dyn_min_hz = 67;
    pidProfilesMutable(0)->dterm_lpf1_dyn_max_hz = 135;
    pidProfilesMutable(0)->dterm_lpf1_dyn_expo = 7;
    pidProfilesMutable(0)->dterm_lpf1_static_hz = 67;
    pidProfilesMutable(0)->dterm_lpf2_static_hz = 135;
    pidProfilesMutable(0)->iterm_relax_cutoff = 45;
    pidProfilesMutable(0)->itermLimit = 500;
    pidProfilesMutable(0)->pidSumLimitYaw = 1000;
    pidProfilesMutable(0)->pid[PID_PITCH].P = 44;
    pidProfilesMutable(0)->pid[PID_PITCH].I = 87;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 37;
    pidProfilesMutable(0)->pid[PID_PITCH].F = 143;
    pidProfilesMutable(0)->pid[PID_ROLL].P = 42;
    pidProfilesMutable(0)->pid[PID_ROLL].I = 83;
    pidProfilesMutable(0)->pid[PID_ROLL].D = 31;
    pidProfilesMutable(0)->pid[PID_ROLL].F = 138;
    pidProfilesMutable(0)->d_min[FD_ROLL] = 25;
    pidProfilesMutable(0)->d_min[FD_PITCH] = 30;
    pidProfilesMutable(0)->dyn_idle_min_rpm = 180;
    pidProfilesMutable(0)->dyn_idle_p_gain  = 35;
    pidProfilesMutable(0)->thrustLinearization = 20;
    pidProfilesMutable(0)->simplified_pids_mode = PID_SIMPLIFIED_TUNING_RP;
    pidProfilesMutable(0)->feedforward_averaging = FEEDFORWARD_AVERAGING_2_POINT;
    pidProfilesMutable(0)->feedforward_smooth_factor = 65;
    pidProfilesMutable(0)->feedforward_jitter_factor = 5;
    pidProfilesMutable(0)->feedforward_boost = 18;
    pidProfilesMutable(0)->feedforward_max_rate_limit = 100; 
    pidProfilesMutable(0)->simplified_master_multiplier = 100;
    pidProfilesMutable(0)->simplified_i_gain = 110;
    pidProfilesMutable(0)->simplified_d_gain = 85;
    pidProfilesMutable(0)->simplified_pi_gain = 95;
    pidProfilesMutable(0)->simplified_dmin_ratio = 70;
    pidProfilesMutable(0)->simplified_feedforward_gain = 115;
    pidProfilesMutable(0)->simplified_roll_pitch_ratio = 105;
    pidProfilesMutable(0)->simplified_dterm_filter_multiplier = 90;
    pidProfilesMutable(0)->simplified_pitch_pi_gain = 100;
    pidProfilesMutable(0)->ez_landing_limit = 5;

    /* PID Tuning -> Rateprofile Settings */
    controlRateProfilesMutable(0)->thrMid8 = 45;
    controlRateProfilesMutable(0)->thrExpo8 = 60;
    controlRateProfilesMutable(0)->rcExpo[FD_ROLL] = 54;
    controlRateProfilesMutable(0)->rcExpo[FD_PITCH] = 54;
    controlRateProfilesMutable(0)->rcExpo[FD_YAW] = 54;
    controlRateProfilesMutable(0)->rates[FD_ROLL] = 52;
    controlRateProfilesMutable(0)->rates[FD_PITCH] = 52;
    controlRateProfilesMutable(0)->rates[FD_YAW] = 57;
    controlRateProfilesMutable(0)->rcRates[FD_ROLL] = 8;
    controlRateProfilesMutable(0)->rcRates[FD_PITCH] = 8;
    controlRateProfilesMutable(0)->rcRates[FD_YAW] = 8;
    controlRateProfilesMutable(0)->throttle_limit_type = THROTTLE_LIMIT_TYPE_SCALE;
    controlRateProfilesMutable(0)->throttle_limit_percent = 98;
}
#endif