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

/* Created by jflyper */

#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "platform.h"

#if defined(USE_VTX_BEESIGN) && defined(USE_VTX_CONTROL)

#include "build/debug.h"

#include "common/maths.h"
#include "common/utils.h"

#include "cms/cms_menu_vtx_tramp.h"

#include "drivers/beesign.h"
#include "drivers/vtx_common.h"

#include "io/serial.h"
#include "io/vtx_tramp.h"
#include "io/vtx_control.h"
#include "io/vtx.h"
#include "io/vtx_beesign.h"

#if (defined(USE_CMS) || defined(USE_VTX_COMMON)) && !defined(USE_VTX_TABLE)
const uint16_t bsPowerTable[(uint8_t)BEESIGN_POWER_COUNT - BEESIGN_DEFAULT_POWER] = {
    25, 100, 200, 400, 600
};
const char *const bsPowerNames[] = {
    "OFF", "25", "100", "200", "400", "600", "PIT MODE"
};
const char *const bsModeNames[] = {
    "RACE", "MANUAL", "POR"
};
#endif

#ifdef USE_VTX_COMMON
static const vtxVTable_t bsVTable; // Forward
static vtxDevice_t vtxBeesign = {
    .vTable = &bsVTable,
};
#endif

bool vtxBeesignInit(void)
{
    if (!checkBeesignSerialPort()) {
        return false;
    }

    vtxCommonSetDevice(&vtxBeesign);
    bsSetVTxUnlock();

    return true;
}

void vtxBSProcess(vtxDevice_t *vtxDevice, timeUs_t currentTimeUs)
{
    UNUSED(vtxDevice);
    UNUSED(currentTimeUs);
}

#ifdef USE_VTX_COMMON
// Interface to common VTX API

vtxDevType_e vtxBSGetDeviceType(const vtxDevice_t *vtxDevice)
{
    UNUSED(vtxDevice);
    return VTXDEV_BEESIGN;
}

static bool vtxBSIsReady(const vtxDevice_t *vtxDevice)
{
    return (bool)((vtxDevice != NULL) && (!(bsDevice.version == 0)));
}

static void vtxBSSetBandAndChannel(vtxDevice_t *vtxDevice, uint8_t band, uint8_t channel)
{
    UNUSED(vtxDevice);
    if (bsValidateBandAndChannel(band, channel)) {
        bsSetBandAndChannel(band - 1, channel - 1);
    }
}

static void vtxBSSetPitMode(vtxDevice_t *vtxDevice, uint8_t onoff)
{
    UNUSED(vtxDevice);
    if (onoff) {
        bsDevice.lastPower = bsDevice.power;
        vtxSettingsConfigMutable()->power = ((uint8_t)BEESIGN_VTX_PWR_PIT + BEESIGN_MIN_POWER); // pit mode
    } else {
        vtxSettingsConfigMutable()->power = bsDevice.lastPower;
    }
}

static void vtxBSSetPowerIndex(vtxDevice_t *vtxDevice, uint8_t index)
{
    UNUSED(vtxDevice);
    if (index == 0) {
        // beesign doesn't support power off.
        return;
    }
    bsSetPower(index);
}

static void vtxBSSetFreq(vtxDevice_t *vtxDevice, uint16_t freq)
{
    UNUSED(vtxDevice);
    if (bsValidateFreq(freq) && freq != bsDevice.freq) {
        bsSetFreq(freq);
    }
}

static bool vtxBSGetBandAndChannel(const vtxDevice_t *vtxDevice, uint8_t *pBand, uint8_t *pChannel)
{
    if (!vtxBSIsReady(vtxDevice)) {
        return false;
    }

    // if in user-freq mode then report band as zero
    *pBand = (bsDevice.mode == BEESIGN_VTX_MODE_RACE) ? (BS_DEVICE_CHVAL_TO_BAND(bsDevice.channel) + 1) : 0;
    *pChannel = BS_DEVICE_CHVAL_TO_CHANNEL(bsDevice.channel) + 1;

    return true;
}

static bool vtxBSGetPowerIndex(const vtxDevice_t *vtxDevice, uint8_t *pIndex)
{
    if (!vtxBSIsReady(vtxDevice)) {
        return false;
    }

    *pIndex = bsDevice.power;

    return true;
}

static bool vtxBSGetPitMode(const vtxDevice_t *vtxDevice, unsigned *status)
{
    if (!vtxBSIsReady(vtxDevice)) {
        return false;
    }

    if (bsDevice.power == ((uint8_t)BEESIGN_VTX_PWR_PIT + BEESIGN_MIN_POWER)) {
        *status = 1;
    } else {
        *status = 0;
    }

    return true;
}

static bool vtxBSGetFreq(const vtxDevice_t *vtxDevice, uint16_t *pFreq)
{
    if (!vtxBSIsReady(vtxDevice)) {
        return false;
    }

    // if not in user-freq mode then convert band/chan to frequency
    *pFreq = bsDevice.freq;

    return true;
}

static uint8_t vtxBsGetPowerLevels(const vtxDevice_t *vtxDevice, uint16_t *levels, uint16_t *powers)
{
    UNUSED(vtxDevice);
    UNUSED(levels);
    UNUSED(powers);

    return 0;
}

static const vtxVTable_t bsVTable = {
    .process = vtxBSProcess,
    .getDeviceType = vtxBSGetDeviceType,
    .isReady = vtxBSIsReady,
    .setBandAndChannel = vtxBSSetBandAndChannel,
    .setPowerByIndex = vtxBSSetPowerIndex,
    .setPitMode = vtxBSSetPitMode,
    .setFrequency = vtxBSSetFreq,
    .getBandAndChannel = vtxBSGetBandAndChannel,
    .getPowerIndex = vtxBSGetPowerIndex,
    .getStatus = vtxBSGetPitMode,
    .getFrequency = vtxBSGetFreq,
    .getPowerLevels = vtxBsGetPowerLevels,
};
#endif // USE_VTX_COMMON

#endif // USE_VTX_BEESIGN
