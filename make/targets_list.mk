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

UNIFIED_TARGETS := STM32F405 \
	STM32F411 \
	STM32F7X2 \
	STM32F745

# Legacy targets are targets that have been replaced by Unified Target configurations
LEGACY_TARGETS := \

CI_TARGETS := $(filter-out $(LEGACY_TARGETS) $(UNSUPPORTED_TARGETS), $(VALID_TARGETS))

TARGETS_TOTAL := $(words $(CI_TARGETS))
TARGET_GROUPS := 3
TARGETS_PER_GROUP := $(shell expr $(TARGETS_TOTAL) / $(TARGET_GROUPS) )

ST := 1
ET := $(shell expr $(ST) + $(TARGETS_PER_GROUP))
GROUP_1_TARGETS := $(wordlist  $(ST), $(ET), $(CI_TARGETS))

ST := $(shell expr $(ET) + 1)
ET := $(shell expr $(ST) + $(TARGETS_PER_GROUP))
GROUP_2_TARGETS := $(wordlist $(ST), $(ET), $(CI_TARGETS))

GROUP_OTHER_TARGETS := $(filter-out $(GROUP_1_TARGETS) $(GROUP_2_TARGETS), $(CI_TARGETS))

GROUP_BB_LITE_TARGETS := BEEBRAIN_LITE_BASE

GROUP_BB_PRO_TARGETS := BEEBRAIN_PRO_BASE \
BEEBRAIN_PRO_DSM_BASE

GROUP_BBBL_V1_TARGETS := BEEBRAIN_BL_V1_BASE \
BEEBRAIN_BL_V1_75 \
BEEBRAIN_BL_V1_75_CRSF \
BEEBRAIN_BL_V1_SVB \
BEEBRAIN_BL_V1_SVB_CRSF

GROUP_BBBL_V2_TARGETS := BEEBRAIN_BL_V2_BASE

GROUP_BBBL_V3_TARGETS := BEEBRAIN_BL_V3_BASE \
BEEBRAIN_BL_V3_65 \
BEEBRAIN_BL_V3_MQT

GROUP_HUMMINGBIRD_F4_PRO_TARGETS := HUMMINGBIRD_F4_PRO_BASE \
HUMMINGBIRD_F4_PRO_BASE_NOBEESIGN

GROUP_RELEASE := BEEBRAIN_LITE_BASE \
BEEBRAIN_PRO_BASE \
BEEBRAIN_PRO_DSM_BASE \
BEEBRAIN_BL_V1_BASE \
BEEBRAIN_BL_V1_75 \
BEEBRAIN_BL_V1_SVB \
BEEBRAIN_BL_V2_BASE \
BEEBRAIN_BL_V3_BASE \
BEEBRAIN_BL_V3_65 \
BEEBRAIN_BL_V3_MQT \
HUMMINGBIRD_F4_PRO_BASE \
HUMMINGBIRD_F4_PRO_BASE_NOBEESIGN