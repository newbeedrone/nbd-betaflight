F7X2RE_TARGETS += $(TARGET)
FEATURES       += VCP ONBOARDFLASH

TARGET_SRC = \
            drivers/max7456.c \
            drivers/accgyro/accgyro_spi_bmi160.c \
