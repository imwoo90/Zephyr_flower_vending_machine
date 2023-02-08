/*
 * Copyright (c) 2022 Lukasz Majewski, DENX Software Engineering GmbH
 * Copyright (c) 2019 Peter Bigot Consulting, LLC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Sample which uses the filesystem API with littlefs */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

#include <Controller.h>

LOG_MODULE_REGISTER(main);

int main(void)
{
	Controller* ctrl = Controller::getInstance();
	ctrl->setup();

	while(1) {
		ctrl->loop();
	}

	return 0;
}
