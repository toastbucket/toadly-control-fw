/*
 * Copyright (c) 2024 Nick Elsmore
 * SPDX-License-Identifier: Apache-2.0
 */

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

void load_driver_init(void);
int load_driver_set(load_driver_t load, bool value);
bool load_driver_get(load_driver_t load);
