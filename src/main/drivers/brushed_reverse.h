#pragma once

#include <stdbool.h>

// Brushed reverse control (external H-bridge / dual NMOS direction pin).
//
// When enabled (USE_BRUSHED_FLIPOVERAFTERCRASH + BRUSHED_REVERSE_PIN), this module:
// - Configures the reverse GPIO early at boot and drives it to "normal" direction (safe state).
// - Allows switching between normal/reversed direction at runtime.
//
// Polarity:
// - If BRUSHED_FLIPOVERAFTERCRASH_LOW_ACTIVE is defined, "reversed" is active-low.
// - Otherwise, "reversed" is active-high.

void brushedReverseInit(void);
void brushedReverseSetReversed(bool reversed);
bool brushedReverseIsAvailable(void);

