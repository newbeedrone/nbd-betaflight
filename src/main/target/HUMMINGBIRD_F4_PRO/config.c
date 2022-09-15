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

#include "common/axis.h"
#include "common/maths.h"

#include "config/config.h"
#include "config/feature.h"

#include "drivers/barometer/barometer.h"
#include "drivers/light_led.h"
#include "drivers/pwm_esc_detect.h"
#include "drivers/pwm_output.h"

#include "fc/controlrate_profile.h"
#include "fc/core.h"
#include "fc/rc_adjustments.h"
#include "fc/rc_modes.h"
#include "fc/rc_controls.h"

#include "flight/mixer.h"
#include "flight/pid.h"
#include "flight/imu.h"
#include "flight/failsafe.h"

#include "pg/vcd.h"
#include "pg/rx.h"
#include "pg/motor.h"
#include "pg/vtx_table.h"

#include "rx/rx.h"
#include "rx/cc2500_frsky_common.h"

#include "pg/rx.h"
#include "pg/rx_spi.h"
#include "pg/rx_spi_cc2500.h"
#include "pg/vcd.h"

#include "osd/osd.h"

#include "io/serial.h"
#include "io/vtx.h"
#include "io/ledstrip.h"

#include "sensors/battery.h"
#include "sensors/gyro.h"
#include "sensors/barometer.h"

#include "telemetry/telemetry.h"

void targetConfiguration(void)
{

// BASE Defaults

    // OSD
    osdElementConfigMutable()->item_pos[OSD_CRAFT_NAME]        = OSD_POS(9, 10) | OSD_PROFILE_1_FLAG;
    osdElementConfigMutable()->item_pos[OSD_MAIN_BATT_VOLTAGE] = OSD_POS(23, 9) | OSD_PROFILE_1_FLAG;
    osdElementConfigMutable()->item_pos[OSD_ITEM_TIMER_2]      = OSD_POS(2,  9) | OSD_PROFILE_1_FLAG;
    osdElementConfigMutable()->item_pos[OSD_FLYMODE]           = OSD_POS(17, 9) | OSD_PROFILE_1_FLAG;
    osdElementConfigMutable()->item_pos[OSD_VTX_CHANNEL]       = OSD_POS(9,  9) | OSD_PROFILE_1_FLAG;
    osdElementConfigMutable()->item_pos[OSD_WARNINGS]          = OSD_POS(9, 10);
    osdElementConfigMutable()->item_pos[OSD_CURRENT_DRAW]      = OSD_POS(22,10) | OSD_PROFILE_1_FLAG;
    osdElementConfigMutable()->item_pos[OSD_RSSI_VALUE]        = OSD_POS(2, 10) | OSD_PROFILE_1_FLAG;

    osdConfigMutable()->enabledWarnings &= ~(1 << OSD_WARNING_CORE_TEMPERATURE);
    //osdConfigMutable()->cap_alarm = 2200;
    
    // RX
    rxConfigMutable()->rc_smoothing_mode = 1;
    rxConfigMutable()->fpvCamAngleDegrees = 0;

    // VTX, US Regulations
#if !defined(HUMMINGBIRD_F4_PRO_BASE_NOBEESIGN) && !defined(HUMMINGBIRD_F4_PRO_65_NOBEESIGN)
    vtxSettingsConfigMutable()->band = 5;
    vtxSettingsConfigMutable()->channel = 8;
    vtxSettingsConfigMutable()->power = 1;

    uint16_t vtxTableFrequency[6][8] = {
        { 5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725 }, // Boscam A
        { 5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866 }, // Boscam B
        { 5705, 5685, 5665,    0, 5885, 5905,    0,    0 }, // Boscam E
        { 5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880 }, // FatShark
        { 5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917 }, // RaceBand
        { 5732, 5765, 5828, 5840, 5866, 5740,    0,    0 }, // IMD6
    };

    const char * vtxTableBandNames[6] = {
            "BOSCAM A",
            "BOSCAM B",
            "BOSCAM E",
            "FATSHARK",
            "RACEBAND",
            "IMD6"
    };
    char vtxTableBandLetters[7] = "ABEFRI";
    vtxTableConfigMutable()->bands = 6;
    vtxTableConfigMutable()->channels = 8;
    for (uint8_t i = 0; i < 6; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            vtxTableConfigMutable()->frequency[i][j] = vtxTableFrequency[i][j];
        }
    }
    for (uint8_t i = 0; i < 6; i++) {
        strcpy(vtxTableConfigMutable()->bandNames[i], vtxTableBandNames[i]);
        vtxTableConfigMutable()->bandLetters[i] = vtxTableBandLetters[i];
    }
    strcpy(vtxTableConfigMutable()->channelNames[0], "1");
    strcpy(vtxTableConfigMutable()->channelNames[1], "2");
    strcpy(vtxTableConfigMutable()->channelNames[2], "3");
    strcpy(vtxTableConfigMutable()->channelNames[3], "4");
    strcpy(vtxTableConfigMutable()->channelNames[4], "5");
    strcpy(vtxTableConfigMutable()->channelNames[5], "6");
    strcpy(vtxTableConfigMutable()->channelNames[6], "7");
    strcpy(vtxTableConfigMutable()->channelNames[7], "8");
    vtxTableConfigMutable()->powerLevels = 2;
    vtxTableConfigMutable()->powerValues[0] = 0;
    vtxTableConfigMutable()->powerValues[1] = 1;
    strcpy(vtxTableConfigMutable()->powerLabels[0], "25 ");
#endif

    // Switches / Modes
    modeActivationConditionsMutable(0)->modeId           = BOXARM;
    modeActivationConditionsMutable(0)->auxChannelIndex  = AUX1 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(0)->range.startStep  = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(0)->range.endStep    = CHANNEL_VALUE_TO_STEP(2100);

    modeActivationConditionsMutable(1)->modeId           = BOXANGLE;
    modeActivationConditionsMutable(1)->auxChannelIndex  = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(1)->range.startStep  = CHANNEL_VALUE_TO_STEP(900);
    modeActivationConditionsMutable(1)->range.endStep    = CHANNEL_VALUE_TO_STEP(1300);

    modeActivationConditionsMutable(2)->modeId           = BOXHORIZON;
    modeActivationConditionsMutable(2)->auxChannelIndex  = AUX2 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(2)->range.startStep  = CHANNEL_VALUE_TO_STEP(1300);
    modeActivationConditionsMutable(2)->range.endStep    = CHANNEL_VALUE_TO_STEP(1700);

    modeActivationConditionsMutable(3)->modeId           = BOXFLIPOVERAFTERCRASH;
    modeActivationConditionsMutable(3)->auxChannelIndex  = AUX3 - NON_AUX_CHANNEL_COUNT;
    modeActivationConditionsMutable(3)->range.startStep  = CHANNEL_VALUE_TO_STEP(1700);
    modeActivationConditionsMutable(3)->range.endStep    = CHANNEL_VALUE_TO_STEP(2100);

    // LEDS
    ledStripStatusModeConfigMutable()->ledConfigs[0] = DEFINE_LED( 7, 7,  8, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[1] = DEFINE_LED( 8, 7, 13, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[2] = DEFINE_LED( 9, 7, 11, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);
    ledStripStatusModeConfigMutable()->ledConfigs[3] = DEFINE_LED(10, 7,  4, 0, LF(COLOR), LO(LARSON_SCANNER) | LO(THROTTLE), 0);

     // Motor & ESC
    motorConfigMutable()->digitalIdleOffsetValue = 1000;
    motorConfigMutable()->dev.useBurstDshot = true;
    motorConfigMutable()->dev.useDshotTelemetry = true;
    motorConfigMutable()->motorPoleCount = 12;
    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT300;

    mixerConfigMutable()->yaw_motors_reversed = false;
    mixerConfigMutable()->crashflip_motor_percent = 0;

    // Voltage & Current
    batteryConfigMutable()->forceBatteryCellCount = 1;
    batteryConfigMutable()->batteryCapacity = 300;
    batteryConfigMutable()->vbatmaxcellvoltage = 450;
    batteryConfigMutable()->vbatmincellvoltage = 290;
    batteryConfigMutable()->vbatwarningcellvoltage = 320;

    // Others
    pidConfigMutable()->pid_process_denom = 1;
    pidConfigMutable()->runaway_takeoff_prevention = true;
    imuConfigMutable()->small_angle = 180;

    //BNF Configurations

#if defined HUMMINGBIRD_F4_PRO_BASE || HUMMINGBIRD_F4_PRO_BASE_NOBEESIGN
    strcpy(pilotConfigMutable()->name, "HMB F4 PRO");

#elif defined(HUMMINGBIRD_F4_PRO_65) || defined(HUMMINGBIRD_F4_PRO_65_NOBEESIGN)
    strcpy(pilotConfigMutable()->name, "HMB F4 PRO 65");

    gyroConfigMutable()->gyro_lpf1_static_hz = 375;
    gyroConfigMutable()->gyro_lpf2_static_hz = 750;
    gyroConfigMutable()->gyro_lpf1_dyn_min_hz = 375;
    gyroConfigMutable()->gyro_lpf1_dyn_max_hz = 750;
    gyroConfigMutable()->simplified_gyro_filter_multiplier = 150;

    dynNotchConfigMutable()->dyn_notch_min_hz = 100;
    dynNotchConfigMutable()->dyn_notch_max_hz = 1000;

    rxConfigMutable()->rc_smoothing_auto_factor_rpy = 52;

    motorConfigMutable()->digitalIdleOffsetValue = 550;

    failsafeConfigMutable()->failsafe_delay = 10;

  //Pid Profile 1
    pidProfilesMutable(0)->vbat_sag_compensation = 100;
    pidProfilesMutable(0)->itermAcceleratorGain = 10000;
    pidProfilesMutable(0)->iterm_relax_cutoff = 10;
    pidProfilesMutable(0)->pid[PID_PITCH].P = 75;
    pidProfilesMutable(0)->pid[PID_PITCH].I = 134;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 76;
    pidProfilesMutable(0)->pid[PID_PITCH].F = 199;
    pidProfilesMutable(0)->pid[PID_ROLL].P  = 71;
    pidProfilesMutable(0)->pid[PID_ROLL].I  = 127;
    pidProfilesMutable(0)->pid[PID_ROLL].D  = 67;
    pidProfilesMutable(0)->pid[PID_ROLL].F  = 191;
    pidProfilesMutable(0)->pid[PID_YAW].P   = 71;
    pidProfilesMutable(0)->pid[PID_YAW].I   = 127;
    pidProfilesMutable(0)->pid[PID_YAW].F   = 191;
    pidProfilesMutable(0)->d_min[FD_ROLL]   = 67;
    pidProfilesMutable(0)->d_min[FD_PITCH]  = 76;
    pidProfilesMutable(0)->thrustLinearization  = 20;
    pidProfilesMutable(0)->feedforward_averaging  = FEEDFORWARD_AVERAGING_2_POINT;
    pidProfilesMutable(0)->feedforward_smooth_factor  = 45;
    pidProfilesMutable(0)->feedforward_jitter_factor  = 8;
    pidProfilesMutable(0)->simplified_master_multiplier = 160;
    pidProfilesMutable(0)->simplified_d_gain = 140;
    pidProfilesMutable(0)->simplified_dmin_ratio = 0;

//   //Pid Profile 2
    pidProfilesMutable(1)->pid[PID_PITCH].P = 77;
    pidProfilesMutable(1)->pid[PID_PITCH].I = 55;
    pidProfilesMutable(1)->pid[PID_PITCH].D = 142;
    pidProfilesMutable(1)->pid[PID_PITCH].F = 72;
    pidProfilesMutable(1)->pid[PID_ROLL].P  = 67;
    pidProfilesMutable(1)->pid[PID_ROLL].I  = 47;
    pidProfilesMutable(1)->pid[PID_ROLL].D  = 112;
    pidProfilesMutable(1)->pid[PID_ROLL].F  = 62;
    pidProfilesMutable(1)->pid[PID_YAW].P   = 67;
    pidProfilesMutable(1)->pid[PID_YAW].I   = 47;
    pidProfilesMutable(1)->pid[PID_YAW].F   = 62;
    pidProfilesMutable(1)->d_min[FD_ROLL]   = 85;
    pidProfilesMutable(1)->d_min[FD_PITCH]  = 106;
    pidProfilesMutable(1)->simplified_master_multiplier = 150;
    pidProfilesMutable(1)->simplified_i_gain = 40;
    pidProfilesMutable(1)->simplified_d_gain = 190;
    pidProfilesMutable(1)->simplified_dmin_ratio = 95;
    pidProfilesMutable(1)->simplified_feedforward_gain = 35;
    pidProfilesMutable(1)->simplified_roll_pitch_ratio = 110;
    pidProfilesMutable(1)->simplified_pitch_pi_gain = 110;

  //Rate Profile 1
    controlRateProfilesMutable(0)->rcExpo[FD_ROLL] = 30;
    controlRateProfilesMutable(0)->rcExpo[FD_PITCH] = 30;
    controlRateProfilesMutable(0)->rates[FD_ROLL] = 100;
    controlRateProfilesMutable(0)->rates[FD_PITCH] = 100;

#endif
}
#endif
