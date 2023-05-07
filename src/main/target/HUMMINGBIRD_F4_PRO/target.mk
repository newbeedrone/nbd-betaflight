F411_TARGETS += $(TARGET)
FEATURES     += VCP

TARGET_SRC = \
            drivers/max7456.c \
            drivers/accgyro/accgyro_spi_bmi160.c \
            drivers/rx/rx_cc2500.c \
            rx/cc2500_common.c \
            rx/cc2500_frsky_shared.c \
            rx/cc2500_frsky_d.c \
            rx/cc2500_frsky_x.c \
            rx/cc2500_sfhss.c \
            rx/cc2500_redpine.c

CFLAGS += -DCLOUD_BUILD