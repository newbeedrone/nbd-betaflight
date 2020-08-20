F411_TARGETS += $(TARGET)
FEATURES	 += VCP

TARGET_SRC = \
            drivers/max7456.c \
            drivers/vtx_rtc6705.c \
            drivers/accgyro/accgyro_spi_mpu6000.c \
