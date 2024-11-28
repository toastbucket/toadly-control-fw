/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <app/drivers/blink.h>

#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#define GET_GPIO_FROM_LABEL(label) \
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(label), gpios, {0})

typedef enum {
	LOAD_FLOOD_LIGHT_DRIVER = 0,
	LOAD_FLOOD_LIGHT_REAR,
	LOAD_FLOOD_LIGHT_PASSENGER,
	LOAD_COMP_LIGHT_1,
	LOAD_COMP_LIGHT_2,
	LOAD_COMP_LIGHT_3,
	LOAD_COMP_LIGHT_4,
	LOAD_COMP_LIGHT_5,
	LOAD_MARKER_LIGHT,
	LOAD_BACKUP_CHIME,
	LOAD_FOG_LIGHT,
	LOAD_INTERSECT_DRIVER,
	LOAD_INTERSECT_PASSENGER,
	LOAD_AUX_1,
	LOAD_AUX_2,
	LOAD_AUX_3,
	LOAD_AUX_4,
	LOAD_AUX_5,
	LOAD_AUX_6,
	LOAD_AUX_7,
	LOAD_AUX_8,
	LOAD_AUX_9,
	LOAD_AUX_10,
	LOAD_AUX_11,
	LOAD_AUX_12,

	NUM_LOAD_DRIVERS
} load_driver_t;

typedef enum {
	SW_PARK_BRAKE = 0,
	SW_MARKER,
	SW_REVERSE,
	SW_STOP,
	SW_BATTERY_SWITCH,
	SW_HORN,
	SW_COMP_1,
	SW_COMP_2,
	SW_COMP_3,
	SW_COMP_4,
	SW_COMP_5,
	SW_CAB_1,
	SW_CAB_2,
	SW_CAB_3,
	SW_CAB_4,
	SW_CAB_5,
	SW_CAB_6,
	SW_CAB_7,
	SW_CAB_8,
	SW_AUX_1,
	SW_AUX_2,
	SW_AUX_3,

	NUM_INPUT_SWITCHES
} input_switch_t;

static const struct gpio_dt_spec ld_specs[NUM_LOAD_DRIVERS] = {
	[LOAD_FLOOD_LIGHT_DRIVER] = GET_GPIO_FROM_LABEL(ld_flood_d),
	[LOAD_FLOOD_LIGHT_REAR] = GET_GPIO_FROM_LABEL(ld_flood_r),
	[LOAD_FLOOD_LIGHT_PASSENGER] = GET_GPIO_FROM_LABEL(ld_flood_p),
	[LOAD_COMP_LIGHT_1] = GET_GPIO_FROM_LABEL(ld_comp_lgt_1),
	[LOAD_COMP_LIGHT_2] = GET_GPIO_FROM_LABEL(ld_comp_lgt_2),
	[LOAD_COMP_LIGHT_3] = GET_GPIO_FROM_LABEL(ld_comp_lgt_3),
	[LOAD_COMP_LIGHT_4] = GET_GPIO_FROM_LABEL(ld_comp_lgt_4),
	[LOAD_COMP_LIGHT_5] = GET_GPIO_FROM_LABEL(ld_comp_lgt_5),
	[LOAD_MARKER_LIGHT] = GET_GPIO_FROM_LABEL(ld_marker_lgt),
	[LOAD_BACKUP_CHIME] = GET_GPIO_FROM_LABEL(ld_backup_chime),
	[LOAD_FOG_LIGHT] = GET_GPIO_FROM_LABEL(ld_fog_lgt),
	[LOAD_INTERSECT_DRIVER] = GET_GPIO_FROM_LABEL(ld_isect_d),
	[LOAD_INTERSECT_PASSENGER] = GET_GPIO_FROM_LABEL(ld_isect_p),
	[LOAD_AUX_1] = GET_GPIO_FROM_LABEL(ld_aux_1),
	[LOAD_AUX_2] = GET_GPIO_FROM_LABEL(ld_aux_2),
	[LOAD_AUX_3] = GET_GPIO_FROM_LABEL(ld_aux_3),
	[LOAD_AUX_4] = GET_GPIO_FROM_LABEL(ld_aux_4),
	[LOAD_AUX_5] = GET_GPIO_FROM_LABEL(ld_aux_5),
	[LOAD_AUX_6] = GET_GPIO_FROM_LABEL(ld_aux_6),
	[LOAD_AUX_7] = GET_GPIO_FROM_LABEL(ld_aux_7),
	[LOAD_AUX_8] = GET_GPIO_FROM_LABEL(ld_aux_8),
	[LOAD_AUX_9] = GET_GPIO_FROM_LABEL(ld_aux_9),
	[LOAD_AUX_10] = GET_GPIO_FROM_LABEL(ld_aux_10),
	[LOAD_AUX_11] = GET_GPIO_FROM_LABEL(ld_aux_11),
	[LOAD_AUX_12] = GET_GPIO_FROM_LABEL(ld_aux_12),
};

static const struct gpio_dt_spec sw_specs[NUM_LOAD_DRIVERS] = {
	[SW_PARK_BRAKE] = GET_GPIO_FROM_LABEL(sw_park_brake),
	[SW_MARKER] = GET_GPIO_FROM_LABEL(sw_marker_light),
	[SW_REVERSE] = GET_GPIO_FROM_LABEL(sw_reverse_light),
	[SW_STOP] = GET_GPIO_FROM_LABEL(sw_stop_light),
	[SW_BATTERY_SWITCH] = GET_GPIO_FROM_LABEL(sw_batt),
	[SW_HORN] = GET_GPIO_FROM_LABEL(sw_horn),
	[SW_COMP_1] = GET_GPIO_FROM_LABEL(sw_comp_1),
	[SW_COMP_2] = GET_GPIO_FROM_LABEL(sw_comp_2),
	[SW_COMP_3] = GET_GPIO_FROM_LABEL(sw_comp_3),
	[SW_COMP_4] = GET_GPIO_FROM_LABEL(sw_comp_4),
	[SW_COMP_5] = GET_GPIO_FROM_LABEL(sw_comp_5),
	[SW_CAB_1] = GET_GPIO_FROM_LABEL(sw_cab_1),
	[SW_CAB_2] = GET_GPIO_FROM_LABEL(sw_cab_2),
	[SW_CAB_3] = GET_GPIO_FROM_LABEL(sw_cab_3),
	[SW_CAB_4] = GET_GPIO_FROM_LABEL(sw_cab_4),
	[SW_CAB_5] = GET_GPIO_FROM_LABEL(sw_cab_5),
	[SW_CAB_6] = GET_GPIO_FROM_LABEL(sw_cab_6),
	[SW_CAB_7] = GET_GPIO_FROM_LABEL(sw_cab_7),
	[SW_CAB_8] = GET_GPIO_FROM_LABEL(sw_cab_8),
	[SW_AUX_1] = GET_GPIO_FROM_LABEL(sw_aux_1),
	[SW_AUX_2] = GET_GPIO_FROM_LABEL(sw_aux_2),
	[SW_AUX_3] = GET_GPIO_FROM_LABEL(sw_aux_3),
};

static int initialize() {
	int i, ret;

	// initialize load drivers
	for (i=0; i < sizeof(ld_specs)/sizeof(ld_specs[0]); i++) {
		if (!gpio_is_ready_dt(&ld_specs[i]))
			return -EAGAIN;

		ret = gpio_pin_configure_dt(&ld_specs[i], GPIO_OUTPUT_INACTIVE);
		if (ret < 0)
			return ret;
	}

	// initialize inputs
	for (i=0; i < sizeof(sw_specs)/sizeof(sw_specs[0]); i++) {
		if (!gpio_is_ready_dt(&sw_specs[i]))
			return -EAGAIN;

		ret = gpio_pin_configure_dt(&sw_specs[i], GPIO_INPUT);
		if (ret < 0)
			return ret;
	}

	return 0;
}

int main(void)
{
	int ret;

	printk("Toadly Control %s\n", APP_VERSION_STRING);

	ret = initialize();
	if (ret < 0) {
		printk("failed to initialize: %d\n", ret);
		return ret;
	}

	while (1);

	return 0;
}

