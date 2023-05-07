H743xI_TARGETS += $(TARGET)
FEATURES     += VCP SDCARD_SDIO

TARGET_SRC = \
            drivers/max7456.c \
            drivers/accgyro/accgyro_mpu.c \
            $(ROOT)/lib/main/BoschSensortec/BMI270-Sensor-API/bmi270_maximum_fifo.c \
            drivers/accgyro/accgyro_spi_bmi270.c \
            drivers/barometer/barometer_dps310.c \
            drivers/compass/compass_hmc5883l.c \
            $(addprefix drivers/compass/,$(notdir $(wildcard $(SRC_DIR)/drivers/compass/*.c))) \

CFLAGS += -DCLOUD_BUILD