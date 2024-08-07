F411_TARGETS += $(TARGET)
FEATURES     += VCP

TARGET_SRC = \
            drivers/max7456.c \
            drivers/vtx_rtc6705.c \
            drivers/accgyro/accgyro_spi_icm426xx.c \
            drivers/rx/expresslrs_driver.c \
            drivers/rx/rx_sx127x.c \
            drivers/rx/rx_sx1280.c \
            rx/expresslrs_telemetry.c \
            rx/expresslrs_common.c \
            rx/expresslrs.c
CFLAGS += -DCLOUD_BUILD