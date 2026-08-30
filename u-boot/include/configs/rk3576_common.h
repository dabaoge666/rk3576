/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2023 Rockchip Electronics Co., Ltd
 *
 */

#ifndef __CONFIG_RK3576_COMMON_H
#define __CONFIG_RK3576_COMMON_H

#define CFG_CPUID_OFFSET                0xa

#include "rockchip-common.h"

#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_TEXT_BASE		0x40000000
#define CONFIG_SPL_MAX_SIZE		0x00040000
#define CONFIG_SPL_BSS_START_ADDR	0x43fe0000
#define CONFIG_SPL_BSS_MAX_SIZE		0x00010000
#define CONFIG_SPL_STACK		0x43fe0000
#ifdef CONFIG_SPL_LOAD_FIT_ADDRESS
#undef CONFIG_SPL_LOAD_FIT_ADDRESS
#endif
#define CONFIG_SPL_LOAD_FIT_ADDRESS	0x42000000

#define CONFIG_SYS_MALLOC_LEN		(32 << 20)
#define CONFIG_SYS_CBSIZE		1024

#ifdef CONFIG_SUPPORT_USBPLUG
#define CONFIG_SYS_TEXT_BASE		0x40000000
#else
#define CONFIG_SYS_TEXT_BASE		0x40200000
#endif

#define CONFIG_SYS_INIT_SP_ADDR		0x40400000
#define CONFIG_SYS_LOAD_ADDR		0x40700800
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)	/* 64M */
#undef COUNTER_FREQUENCY

#define GICD_BASE			0x2a701000
#define GICC_BASE			0x2a702000

/* secure otp */
#define OTP_UBOOT_ROLLBACK_OFFSET	0x610
#define OTP_UBOOT_ROLLBACK_WORDS	2	/* 64 bits, 2 words */
#define OTP_ALL_ONES_NUM_BITS		32
#define OTP_SECURE_BOOT_ENABLE_ADDR	0x20
#define OTP_SECURE_BOOT_ENABLE_SIZE	1
#define OTP_RSA4096_ENABLE_ADDR		0x21
#define OTP_RSA4096_ENABLE_SIZE		1
#define OTP_RSA_HASH_ADDR		0x200
#define OTP_RSA_HASH_SIZE		32

#define CONFIG_BOUNCE_BUFFER
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define SDRAM_MAX_SIZE			(0x100000000 - CONFIG_SYS_SDRAM_BASE)	/* max 4G */
#define CONFIG_SYS_NONCACHED_MEMORY	(1 << 20)	/* 1M */

/* env used only in U-Boot */
#ifndef CONFIG_SPL_BUILD
/* usb mass storage */
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_ROCKUSB_G_DNL_PID	0x350e

#define BOOTTEST_BOOTENV_SETTINGS \
	"bootcount=0\0" \
	"boottest=0\0" \
	"boottestcount=if test $boottest = 1;" \
	"then setexpr bootcount ${bootcount} + 1;" \
	"saveenv;" \
	"echo boottest=1 bootcount: ${bootcount};" \
	"fi\0"

#define NET_BOOTENV_SETTINGS \
	"bootname=boot.img\0" \
	"netmask=255.255.255.0\0" \
	"tftpaddr=0x50000000\0" \
	"nfsargs=setenv bootargs root=/dev/nfs "\
	"nfsroot=${serverip}:${nfspath},vers=3 rw " \
	"ip=${ipaddr}:${serverip}:${netmask}:${gatewayip};\0" \
	"tftp_load=tftp ${tftpaddr} ${bootname}\0" \
	"net_boot=setenv devtype nfs; " \
	"run nfsargs; " \
	"if run tftp_load; then " \
	"boot_fit ${tftpaddr}; fi;\0"

/*
 * DDR layout mainly follow rk3588 Soc
 */
#define ENV_MEM_LAYOUT_SETTINGS \
	"scriptaddr=0x40500000\0" \
	"pxefile_addr_r=0x40600000\0" \
	"fdt_addr_r=0x48300000\0" \
	"kernel_addr_r=0x40400000\0" \
	"kernel_addr_c=0x45480000\0" \
	"ramdisk_addr_r=0x4a200000\0"

#include <config_distro_bootcmd.h>

#define CONFIG_EXTRA_ENV_SETTINGS \
	NET_BOOTENV_SETTINGS \
	ENV_MEM_LAYOUT_SETTINGS \
	"partitions=" PARTS_RKIMG \
	BOOTTEST_BOOTENV_SETTINGS \
	ROCKCHIP_DEVICE_SETTINGS \
	RKIMG_DET_BOOTDEV \
	BOOTENV
#endif /* !CONFIG_SPL_BUILD */

/* rockchip ohci host driver */
#define CONFIG_USB_OHCI_NEW
#define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	1

#define CONFIG_PREBOOT
#define CONFIG_LIB_HW_RAND

#endif /* __CONFIG_RK3576_COMMON_H */
