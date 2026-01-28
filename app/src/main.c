#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/app_version.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define APP_GIT_VERSION STR(APP_BUILD_VERSION)

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   200

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

const struct device *flash_dev = DEVICE_DT_GET(DT_NODELABEL(w25q16));

int main(void)
{
	int ret;
	bool led_state = true;

	printf("Project version: %s\n", APP_GIT_VERSION);

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led_1, GPIO_OUTPUT_INACTIVE);
	if (ret < 0) {
		return 0;
	}

	if (!device_is_ready(flash_dev)) {
		printk("Flash not ready!\n");
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}

		ret = gpio_pin_toggle_dt(&led_1);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
