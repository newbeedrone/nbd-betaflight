OFFICIAL_TARGETS  = \
    BEEBRAIN_BL \
    BEEBRAIN_BL_V2 \
    BEEBRAIN_BL_V3 \
    BEEBRAIN_LITE \
    BEEBRAIN_LITE_DSM \
    BEEBRAIN_PRO \
    BEEBRAIN_PRO_DSM \
    CRICKET_F7 \
    GALAXY_AIO \
    HUMMINGBIRDF4_PRO \
    INFINITY_AIO \
    INFINITY_F4 \
    INFINITY_F7 \
    INFINITY_PDB_F7 \
    INFINITY_PDB_H7 \
    INFINITY_AIO_V2_F7 \
    INFINITY_AIO_V2_H7

ALT_TARGET_PATHS  = $(filter-out %/target,$(basename $(wildcard $(ROOT)/src/main/target/*/*.mk)))
ALT_TARGET_NAMES  = $(notdir $(ALT_TARGET_PATHS))
BASE_TARGET_NAMES = $(notdir $(patsubst %/,%,$(dir $(ALT_TARGET_PATHS))))
BASE_ALT_PAIRS    = $(join $(BASE_TARGET_NAMES:=/),$(ALT_TARGET_NAMES))

ALT_TARGETS       = $(sort $(notdir $(BASE_ALT_PAIRS)))
BASE_TARGETS      = $(sort $(notdir $(patsubst %/,%,$(dir $(wildcard $(ROOT)/src/main/target/*/target.mk)))))
NOBUILD_TARGETS   = $(sort $(filter-out target,$(basename $(notdir $(wildcard $(ROOT)/src/main/target/*/*.nomk)))))
OPBL_TARGETS      = $(sort $(filter %_OPBL,$(ALT_TARGETS)))
VALID_TARGETS     = $(sort $(filter-out $(NOBUILD_TARGETS),$(BASE_TARGETS) $(ALT_TARGETS)))

# For alt targets, returns their base target name.
# For base targets, returns the (same) target name.
# param $1 = target name
find_target_pair  = $(filter %/$(1),$(BASE_ALT_PAIRS))
get_base_target   = $(if $(call find_target_pair,$(1)),$(patsubst %/,%,$(dir $(call find_target_pair,$(1)))),$(1))

UNSUPPORTED_TARGETS := \

SUPPORTED_TARGETS := $(filter-out $(UNSUPPORTED_TARGETS), $(VALID_TARGETS))

TARGETS_TOTAL := $(words $(SUPPORTED_TARGETS))
TARGET_GROUPS := 5
TARGETS_PER_GROUP := $(shell expr $(TARGETS_TOTAL) / $(TARGET_GROUPS) )

ST := 1
ET := $(shell expr $(ST) + $(TARGETS_PER_GROUP))
GROUP_1_TARGETS := $(wordlist  $(ST), $(ET), $(SUPPORTED_TARGETS))

ST := $(shell expr $(ET) + 1)
ET := $(shell expr $(ST) + $(TARGETS_PER_GROUP))
GROUP_2_TARGETS := $(wordlist $(ST), $(ET), $(SUPPORTED_TARGETS))

ST := $(shell expr $(ET) + 1)
ET := $(shell expr $(ST) + $(TARGETS_PER_GROUP))
GROUP_3_TARGETS := $(wordlist $(ST), $(ET), $(SUPPORTED_TARGETS))

ST := $(shell expr $(ET) + 1)
ET := $(shell expr $(ST) + $(TARGETS_PER_GROUP))
GROUP_4_TARGETS := $(wordlist $(ST), $(ET), $(SUPPORTED_TARGETS))

GROUP_OTHER_TARGETS := $(filter-out $(GROUP_1_TARGETS) $(GROUP_2_TARGETS) $(GROUP_3_TARGETS) $(GROUP_4_TARGETS), $(SUPPORTED_TARGETS))
