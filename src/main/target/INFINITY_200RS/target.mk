F7X5XG_TARGETS += $(TARGET)
FEATURES       += VCP ONBOARDFLASH

TARGET_SRC = \
            drivers/max7456.c \
            $(ROOT)/lib/main/BoschSensortec/BMI270-Sensor-API/bmi270_maximum_fifo.c \
            drivers/accgyro/accgyro_spi_bmi270.c \
            drivers/accgyro/accgyro_spi_mpu6000.c \
