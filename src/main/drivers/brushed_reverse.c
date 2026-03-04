/*
 * Brushed motor direction control via a dedicated GPIO.
 *
 * This is commonly used on brushed FCs with an H-bridge / dual NMOS stage where
 * a single direction pin selects forward/backward.
 */

#include "platform.h"

#include "drivers/brushed_reverse.h"

#include "drivers/io.h"
#include "drivers/resource.h"

#if defined(USE_BRUSHED_FLIPOVERAFTERCRASH) && defined(BRUSHED_REVERSE_PIN)

static IO_t brushedReverseIO = IO_NONE;

bool brushedReverseIsAvailable(void)
{
    return brushedReverseIO != IO_NONE;
}

static void brushedReverseWrite(bool reversed)
{
    if (brushedReverseIO == IO_NONE) {
        return;
    }

#if defined(BRUSHED_FLIPOVERAFTERCRASH_LOW_ACTIVE)
    // Active-low: reversed -> LOW, normal -> HIGH
    if (reversed) {
        IOLo(brushedReverseIO);
    } else {
        IOHi(brushedReverseIO);
    }
#else
    // Active-high: reversed -> HIGH, normal -> LOW
    if (reversed) {
        IOHi(brushedReverseIO);
    } else {
        IOLo(brushedReverseIO);
    }
#endif
}

void brushedReverseInit(void)
{
    brushedReverseIO = IOGetByTag(IO_TAG(BRUSHED_REVERSE_PIN));
    if (brushedReverseIO == IO_NONE) {
        return;
    }

    // Configure early and drive to a known-safe default (normal direction).
    IOInit(brushedReverseIO, OWNER_SYSTEM, 0);
    IOConfigGPIO(brushedReverseIO, IOCFG_OUT_PP);
    brushedReverseWrite(false);
}

void brushedReverseSetReversed(bool reversed)
{
    brushedReverseWrite(reversed);
}

#else

bool brushedReverseIsAvailable(void)
{
    return false;
}

void brushedReverseInit(void)
{
}

void brushedReverseSetReversed(bool reversed)
{
    UNUSED(reversed);
}

#endif

