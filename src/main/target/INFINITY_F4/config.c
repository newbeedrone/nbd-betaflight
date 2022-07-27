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
#include "pg/motor.h"
#if defined(INFINITY305_BASE)
#include "pg/pinio.h"
#include "pg/piniobox.h"
#endif

#include "osd/osd.h"

#include "io/serial.h"
#include "io/vtx.h"
#include "io/ledstrip.h"
#if defined(INFINITY200_WHIRLYGIG)
#include "io/gps.h"
#endif

#include "sensors/battery.h"
#include "sensors/gyro.h"
#include "sensors/barometer.h"

#include "telemetry/telemetry.h"

#include "config_helper.h"

static targetSerialPortFunction_t targetSerialPortFunction[] = {
#if defined(INFINITY200_WHIRLYGIG)
    { SERIAL_PORT_UART4,        FUNCTION_GPS},
#endif

    { SERIAL_PORT_UART5,        FUNCTION_ESC_SENSOR},

#if defined(INFINITY200_WHIRLYGIG) || defined(INFINITY200_CINEMAH) || defined(INFINITY200_INVISI360)
    { SERIAL_PORT_USART6,       FUNCTION_MSP}
#endif
};

void targetConfiguration(void)
{

// BASE Defaults

    // Serial
    targetSerialPortFunctionConfig(targetSerialPortFunction, ARRAYLEN(targetSerialPortFunction));

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
    
    // RX
    rxConfigMutable()->rc_smoothing_type = RC_SMOOTHING_TYPE_FILTER;
    rxConfigMutable()->fpvCamAngleDegrees = 0;

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

    // Motor & ESC
    motorConfigMutable()->digitalIdleOffsetValue = 550;
    motorConfigMutable()->dev.useBurstDshot = true;
    motorConfigMutable()->dev.useDshotTelemetry = false;
    motorConfigMutable()->motorPoleCount = 12;
    motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT600;

    mixerConfigMutable()->yaw_motors_reversed = true;
    mixerConfigMutable()->crashflip_motor_percent = 0;

    // Voltage & Current
    batteryConfigMutable()->vbatmaxcellvoltage = 450;
    batteryConfigMutable()->vbatfullcellvoltage = 400;
    batteryConfigMutable()->vbatmincellvoltage = 290;
    batteryConfigMutable()->vbatwarningcellvoltage = 320;

    // Others
    pidConfigMutable()->pid_process_denom = 1;
    pidConfigMutable()->runaway_takeoff_prevention = true;
    imuConfigMutable()->small_angle = 25;

    //BNF Configurations

#if defined(INFINITY200_BASE)
    strcpy(pilotConfigMutable()->name, "INFINITY200");

#elif defined(INFINITY305_BASE)
    strcpy(pilotConfigMutable()->name, "INFINITY305");

#elif defined(INFINITY200_WHIRLYGIG)
    strcpy(pilotConfigMutable()->name, "WHIRLYGIG");

    gpsConfigMutable()->provider = GPS_UBLOX;
    gpsConfigMutable()->autoBaud = true;

    pidConfigMutable()->pid_process_denom = 2;

    gyroConfigMutable()->gyro_lowpass2_hz = 350;
    gyroConfigMutable()->dyn_notch_width_percent = 0;
    gyroConfigMutable()->dyn_notch_q = 250;
    gyroConfigMutable()->dyn_notch_max_hz = 350;
    gyroConfigMutable()->dyn_lpf_gyro_min_hz = 280;
    gyroConfigMutable()->dyn_lpf_gyro_max_hz = 700;

    motorConfigMutable()->dev.useDshotTelemetry = true;

    pidProfilesMutable(0)->dyn_lpf_dterm_min_hz = 98;
    pidProfilesMutable(0)->dyn_lpf_dterm_max_hz = 238;
    pidProfilesMutable(0)->dterm_lowpass2_hz = 210;
    pidProfilesMutable(0)->itermAcceleratorGain = 4800;
    pidProfilesMutable(0)->pid[PID_PITCH].P = 74;
    pidProfilesMutable(0)->pid[PID_PITCH].I = 72;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 72;
    pidProfilesMutable(0)->pid[PID_PITCH].F = 130;
    pidProfilesMutable(0)->pid[PID_ROLL].P  = 67;
    pidProfilesMutable(0)->pid[PID_ROLL].I  = 68;
    pidProfilesMutable(0)->pid[PID_ROLL].D  = 66;
    pidProfilesMutable(0)->pid[PID_ROLL].F  = 122;
    pidProfilesMutable(0)->pid[PID_YAW].P   = 72;
    pidProfilesMutable(0)->pid[PID_YAW].I   = 72;
    pidProfilesMutable(0)->pid[PID_YAW].D   = 0;
    pidProfilesMutable(0)->pid[PID_YAW].F   = 122;
    pidProfilesMutable(0)->d_min[FD_ROLL]   = 0;
    pidProfilesMutable(0)->d_min[FD_PITCH]  = 0;

#elif defined(INFINITY200_CINEMAH)
    strcpy(pilotConfigMutable()->name, "CINEMAH");

    motorConfigMutable()->minthrottle = 1070;
    motorConfigMutable()->digitalIdleOffsetValue = 300;
    motorConfigMutable()->dev.useDshotTelemetry = true;

    mixerConfigMutable()->yaw_motors_reversed = false;

    pidProfilesMutable(0)->pid[PID_PITCH].P = 69;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 51;
    pidProfilesMutable(0)->pid[PID_PITCH].F = 76;
    pidProfilesMutable(0)->pid[PID_ROLL].P  = 63;
    pidProfilesMutable(0)->pid[PID_ROLL].D  = 47;
    pidProfilesMutable(0)->pid[PID_ROLL].F  = 72;
    pidProfilesMutable(0)->pid[PID_YAW].P   = 68;
    pidProfilesMutable(0)->pid[PID_YAW].F   = 72;
    pidProfilesMutable(0)->d_min[FD_ROLL]   = 31;
    pidProfilesMutable(0)->d_min[FD_PITCH]  = 34;

#elif defined(INFINITY200_INVISI360)
    strcpy(pilotConfigMutable()->name, "INVISI360");

    gyroConfigMutable()->gyro_lowpass2_hz = 225;
    gyroConfigMutable()->dyn_lpf_gyro_min_hz = 180;
    gyroConfigMutable()->dyn_lpf_gyro_max_hz = 450;

    motorConfigMutable()->dev.useDshotTelemetry = true;

    pidProfilesMutable(0)->dyn_lpf_dterm_min_hz = 60;
    pidProfilesMutable(0)->dyn_lpf_dterm_max_hz = 145;
    pidProfilesMutable(0)->dterm_lowpass2_hz = 128;
    pidProfilesMutable(0)->pid[PID_PITCH].P = 79;
    pidProfilesMutable(0)->pid[PID_PITCH].D = 53;
    pidProfilesMutable(0)->pid[PID_ROLL].P  = 73;
    pidProfilesMutable(0)->pid[PID_ROLL].D  = 50;
    pidProfilesMutable(0)->d_min[FD_ROLL]   = 0;
    pidProfilesMutable(0)->d_min[FD_PITCH]  = 0;
#endif
}
#endif
