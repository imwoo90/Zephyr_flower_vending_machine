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

LOG_MODULE_REGISTER(main);

#define PARTITION_NODE DT_NODELABEL(lfs1)

#if DT_NODE_EXISTS(PARTITION_NODE)
FS_FSTAB_DECLARE_ENTRY(PARTITION_NODE);
#else /* PARTITION_NODE */
FS_LITTLEFS_DECLARE_DEFAULT_CONFIG(storage);
static struct fs_mount_t lfs_storage_mnt = {
	.type = FS_LITTLEFS,
	.fs_data = &storage,
	.storage_dev = (void *)FIXED_PARTITION_ID(storage_partition),
	.mnt_point = "/lfs",
};
#endif /* PARTITION_NODE */

	struct fs_mount_t *mp =
#if DT_NODE_EXISTS(PARTITION_NODE)
		&FS_FSTAB_ENTRY(PARTITION_NODE)
#else
		&lfs_storage_mnt
#endif
		;

static char test_buf[40*1024] = "wrtie sucess";

void main(void)
{
	int fd;
	k_msleep(5000);


	LOG_INF("test start");
	k_msleep(1000);
	while(1) {
		fd = open("/root/test.txt", O_CREAT|O_WRONLY);
		if (fd < 0){
			LOG_INF("file open fail %d", fd);
			break;
		}

		write(fd, test_buf, sizeof(test_buf));
		close(fd);

		char buf[30] = {0,};
		fd = open("/root/test.txt", O_RDONLY);
		read(fd, buf, 12);
		LOG_INF("%s", buf);
		close(fd);
		k_msleep(1);
	}
}
