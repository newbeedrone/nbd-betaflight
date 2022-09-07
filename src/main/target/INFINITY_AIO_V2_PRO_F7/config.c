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
#include "flight/rpm_filter.h"

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
#include "pg/pinio.h"
#include "pg/piniobox.h"

#include "osd/osd.h"

#include "io/serial.h"
#include "io/vtx.h"
#include "io/ledstrip.h"

#include "sensors/battery.h"
#include "sensors/gyro.h"
#include "sensors/barometer.h"
#include "sensors/acceleration.h"
#include "sensors/compass.h"

#include "telemetry/telemetry.h"

#include "config_helper.h"

void targetConfiguration(void)
{

// BASE Defaults

    //compass
    compassConfigMutable()->mag_busType = BUS_TYPE_I2C;
    compassConfigMutable()->mag_i2c_device = 1;

    //Barometer
    barometerConfigMutable()->baro_hardware = BARO_NONE;

    //Motor
    mixerConfigMutable()->yaw_motors_reversed = true;

    //Others
    imuConfigMutable()->small_angle = 180;

    //Dusking's dual BMI270 filter settings
    {
        //Gyro
        gyroConfigMutable()->gyro_hardware_lpf = GYRO_HARDWARE_LPF_NORMAL;

        gyroConfigMutable()->gyro_lpf1_type = FILTER_PT1;
        gyroConfigMutable()->gyro_lpf1_dyn_min_hz = 0;
        gyroConfigMutable()->gyro_lpf1_dyn_max_hz = 0;
        gyroConfigMutable()->gyro_lpf1_dyn_expo = 5;
        gyroConfigMutable()->gyro_lpf1_static_hz = 0;

        gyroConfigMutable()->gyro_lpf2_type = FILTER_PT2;
        gyroConfigMutable()->gyro_lpf2_static_hz = 145;

        gyroConfigMutable()->simplified_gyro_filter = false;
        gyroConfigMutable()->simplified_gyro_filter_multiplier = 100;

        gyroConfigMutable()->gyro_soft_notch_hz_1 = 0;
        gyroConfigMutable()->gyro_soft_notch_cutoff_1 = 0;
        gyroConfigMutable()->gyro_soft_notch_hz_2 = 0;
        gyroConfigMutable()->gyro_soft_notch_cutoff_2 = 0;
        gyroConfigMutable()->gyro_filter_debug_axis = FD_ROLL;
        
        gyroConfigMutable()->gyro_hardware_lpf = GYRO_HARDWARE_LPF_OPTION_2;

        //ACC
        accelerometerConfigMutable()->acc_lpf_hz = 10;

        //DYN
        dynNotchConfigMutable()->dyn_notch_count = 1;
        dynNotchConfigMutable()->dyn_notch_q = 500;
        dynNotchConfigMutable()->dyn_notch_min_hz = 150;
        dynNotchConfigMutable()->dyn_notch_max_hz = 600;

        //RPM
        rpmFilterConfigMutable()->rpm_filter_harmonics = 3;
        rpmFilterConfigMutable()->rpm_filter_q = 500;
        rpmFilterConfigMutable()->rpm_filter_min_hz = 100;
        rpmFilterConfigMutable()->rpm_filter_fade_range_hz = 50;
        rpmFilterConfigMutable()->rpm_filter_lpf_hz = 150;

        //Motor
        motorConfigMutable()->dev.useDshotTelemetry = true;
        motorConfigMutable()->dev.motorPwmProtocol = PWM_TYPE_DSHOT600;

        //Pid
        pidConfigMutable()->pid_process_denom = 1;

        pidProfilesMutable(0)->dterm_lpf1_type = FILTER_PT1;
        pidProfilesMutable(0)->dterm_lpf1_dyn_min_hz = 75;
        pidProfilesMutable(0)->dterm_lpf1_dyn_max_hz = 150;
        pidProfilesMutable(0)->dterm_lpf1_dyn_expo = 5;
        pidProfilesMutable(0)->dterm_lpf1_static_hz = 75;

        pidProfilesMutable(0)->dterm_lpf2_type = FILTER_PT1;
        pidProfilesMutable(0)->dterm_lpf2_static_hz = 150;

        pidProfilesMutable(0)->dterm_notch_hz = 0;
        pidProfilesMutable(0)->dterm_notch_cutoff = 0;

        pidProfilesMutable(0)->simplified_dterm_filter = true;
        pidProfilesMutable(0)->simplified_dterm_filter_multiplier = 100;

        pidProfilesMutable(0)->yaw_lowpass_hz = 100;
    }

#if defined INFINITY_AIO_V2_PRO_BASE
    strcpy(pilotConfigMutable()->name, "InfinityAIOv2Pro");
#endif
}
#endif
