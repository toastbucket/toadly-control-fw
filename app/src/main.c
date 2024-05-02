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

int main(void)
{
	int ret;

	printk("Toadly Control %s\n", APP_VERSION_STRING);

	load_driver_init();

#if 0
	if (!device_is_ready(led.port)) {
		printk("led not ready\n");
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		printk("unable to configure led\n");
		return;
	}

	while (1) {
		gpio_pin_toggle_dt(&led);
		k_sleep(K_MSEC(200));
	}
#endif

	return 0;
}

