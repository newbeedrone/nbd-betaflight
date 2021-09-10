F7X5XG_TARGETS += $(TARGET)
FEATURES       += VCP ONBOARDFLASH

TARGET_SRC = \
            drivers/max7456.c \
            drivers/accgyro/accgyro_spi_mpu6000.c \
            drivers/compass/compass_qmc5883l.c
