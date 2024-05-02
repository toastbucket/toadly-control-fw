/*
 * Copyright (c) 2024 Nick Elsmore
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include <app/load_driver.h>

#define GET_GPIO_FROM_LABEL(label) \
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(label), gpios, {0})

static const struct gpio_dt_spec specs[NUM_LOAD_DRIVERS] = {
	[LOAD_FLOOD_LIGHT_DRIVER] = GET_GPIO_FROM_LABEL(flood_d),
	[LOAD_FLOOD_LIGHT_REAR] = GET_GPIO_FROM_LABEL(flood_r),
	[LOAD_FLOOD_LIGHT_PASSENGER] = GET_GPIO_FROM_LABEL(flood_p),
	[LOAD_COMP_LIGHT_1] = GET_GPIO_FROM_LABEL(comp_lgt_1),
	[LOAD_COMP_LIGHT_2] = GET_GPIO_FROM_LABEL(comp_lgt_2),
	[LOAD_COMP_LIGHT_3] = GET_GPIO_FROM_LABEL(comp_lgt_3),
	[LOAD_COMP_LIGHT_4] = GET_GPIO_FROM_LABEL(comp_lgt_4),
	[LOAD_COMP_LIGHT_5] = GET_GPIO_FROM_LABEL(comp_lgt_5),
	[LOAD_MARKER_LIGHT] = GET_GPIO_FROM_LABEL(marker_lgt),
	[LOAD_BACKUP_CHIME] = GET_GPIO_FROM_LABEL(backup_chime),
	[LOAD_FOG_LIGHT] = GET_GPIO_FROM_LABEL(fog_lgt),
	[LOAD_INTERSECT_DRIVER] = GET_GPIO_FROM_LABEL(isect_d),
	[LOAD_INTERSECT_PASSENGER] = GET_GPIO_FROM_LABEL(isect_p),
	[LOAD_AUX_1] = GET_GPIO_FROM_LABEL(aux_1),
	[LOAD_AUX_2] = GET_GPIO_FROM_LABEL(aux_2),
	[LOAD_AUX_3] = GET_GPIO_FROM_LABEL(aux_3),
	[LOAD_AUX_4] = GET_GPIO_FROM_LABEL(aux_4),
	[LOAD_AUX_5] = GET_GPIO_FROM_LABEL(aux_5),
	[LOAD_AUX_6] = GET_GPIO_FROM_LABEL(aux_6),
	[LOAD_AUX_7] = GET_GPIO_FROM_LABEL(aux_7),
	[LOAD_AUX_8] = GET_GPIO_FROM_LABEL(aux_8),
	[LOAD_AUX_9] = GET_GPIO_FROM_LABEL(aux_9),
	[LOAD_AUX_10] = GET_GPIO_FROM_LABEL(aux_10),
	[LOAD_AUX_11] = GET_GPIO_FROM_LABEL(aux_11),
	[LOAD_AUX_12] = GET_GPIO_FROM_LABEL(aux_12),
};

void load_driver_init(void) {
	int i, err;

	for (i=0; i < sizeof(specs)/sizeof(specs[0]); i++) {
		if (!gpio_is_ready_dt(&specs[i]))
			return;

		err = gpio_pin_configure_dt(&specs[i], GPIO_OUTPUT_INACTIVE);
		if (err != 0)
			return;
	}
}

int load_driver_set(load_driver_t load, bool value) {
	return gpio_pin_set_dt(&specs[load], (int) value); 
}

bool load_driver_get(load_driver_t load) {
	return gpio_pin_get_dt(&specs[load]);
}
