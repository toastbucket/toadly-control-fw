/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <app/load_driver.h>
#include <app_version.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static int initialize() {
	int ret;

	if (!gpio_is_ready_dt(&led))
		return -EAGAIN;

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
		return ret;

	gpio_pin_set_dt(&led, 1);

	load_driver_init();

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

