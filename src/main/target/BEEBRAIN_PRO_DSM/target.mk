F411_TARGETS += $(TARGET)
FEATURES     += VCP

TARGET_SRC = \
            drivers/max7456.c \
            drivers/vtx_rtc6705.c \

TARGET_SRC += \
            drivers/accgyro/accgyro_spi_bmi160.c \


CFLAGS += -DCLOUD_BUILD