
#include <configs/platform-auto.h>


#define CONFIG_ZYNQ_I2C0
#define CONFIG_ZYNQ_I2C1
#define CONFIG_SYS_I2C_MAX_HOPS		1
#define CONFIG_SYS_NUM_I2C_BUSES	18
#define CONFIG_SYS_I2C_BUSES	{ \
				{0, {I2C_NULL_HOP} }, \
				{0, {{I2C_MUX_PCA9544, 0x75, 0} } }, \
				{0, {{I2C_MUX_PCA9544, 0x75, 1} } }, \
				{0, {{I2C_MUX_PCA9544, 0x75, 2} } }, \
				{1, {I2C_NULL_HOP} }, \
				{1, {{I2C_MUX_PCA9548, 0x74, 0} } }, \
				{1, {{I2C_MUX_PCA9548, 0x74, 1} } }, \
				{1, {{I2C_MUX_PCA9548, 0x74, 2} } }, \
				{1, {{I2C_MUX_PCA9548, 0x74, 3} } }, \
				{1, {{I2C_MUX_PCA9548, 0x74, 4} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 0} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 1} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 2} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 3} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 4} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 5} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 6} } }, \
				{1, {{I2C_MUX_PCA9548, 0x75, 7} } }, \
				}

#define CONFIG_SYS_I2C_ZYNQ

/* I2C */
#if defined(CONFIG_SYS_I2C_ZYNQ)
# define CONFIG_SYS_I2C
# define CONFIG_SYS_I2C_ZYNQ_SPEED		100000
# define CONFIG_SYS_I2C_ZYNQ_SLAVE		0
#endif

#define CONFIG_ZYNQMP_XHCI_LIST {ZYNQMP_USB0_XHCI_BASEADDR}

#if defined(CONFIG_ZYNQMP_USB)
#define CONFIG_USB_MAX_CONTROLLER_COUNT         1
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS      2
#define CONFIG_USB_XHCI_ZYNQMP

#define CONFIG_SYS_DFU_DATA_BUF_SIZE	0x1800000
#define DFU_DEFAULT_POLL_TIMEOUT	300
#define CONFIG_USB_FUNCTION_DFU
#define CONFIG_DFU_RAM
#define CONFIG_USB_CABLE_CHECK
#define CONFIG_CMD_THOR_DOWNLOAD
#define CONFIG_USB_FUNCTION_THOR
#define CONFIG_THOR_RESET_OFF
#define DFU_ALT_INFO_RAM \
		"dfu_ram_info=" \
	"setenv dfu_alt_info " \
	"Image ram $kernel_addr $kernel_size\\\\;" \
	"system.dtb ram $fdt_addr $fdt_size\0" \
	"dfu_ram=run dfu_ram_info && dfu 0 ram 0\0" \
	"thor_ram=run dfu_ram_info && thordown 0 ram 0\0"

#define DFU_ALT_INFO  \
		DFU_ALT_INFO_RAM
#endif

#if defined(CONFIG_ZYNQMP_USB)
#define BOOT_TARGET_DEVICES_USB(func)	func(USB, usb, 0) func(USB, usb, 1)
#else
#define BOOT_TARGET_DEVICES_USB(func)
#endif

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE

#define CONFIG_EXTRA_ENV_SETTINGS \
	SERIAL_MULTI \
	CONSOLE_ARG \
	PSSERIAL0 \
    "bitstream_image=system.bit \0"\
    "loadbootenv_addr=0x2000000\0" \
    "bootenv=/uEnv.txt\0" \
    "bootEnv_ext=/uEnv_ext.txt\0" \
    "bootEnv_network=/uEnv_network.txt\0" \
    "loadbootenv=fatload mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv}\0" \
    "bootarrgsGenerate=setenv bootargs mem=1024MB@0 vmalloc=1024MB console=ttyPS0,115200n8 consoleblank=0 rootfstype=ext4 root=/dev/mmcblk0p2 ro rootwait fsck.mode=force earlyprintk ip=${ipaddr}\0" \
    "preboot=echo U-BOOT for xilinx-zcu102-2017_2 preboot; run reloadbootenv; saveenv; printenv bootdelay; printenv preboot\0" \
    "prebootcmd=run reloadbootenv ; saveenv ; printenv envver ; printenv bootdelay ; run loadFpga;  run bootarrgsGenerate\0" \
	"nc=setenv stdout nc;setenv stdin nc;\0" \
	"ethaddr=00:0a:35:00:22:01\0" \
	"importbootenv=echo \"Importing environment from SD ...\"; " \
		"env import -t ${loadbootenv_addr} $filesize\0" \
	"loadbootenv=load mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv}\0" \
	"sd_uEnvtxt_existence_test=test -e mmc $sdbootdev:$partid ${bootenv}\0" \
	"uenvboot=" \
    "run bootarrgsGenerate;"\
	"if run sd_uEnvtxt_existence_test; then" \
		"run loadbootenv; " \
		"echo Loaded environment from ${bootenv};" \
		"run importbootenv; \0" \
    "fi\0" \
	"sdboot=echo boot Petalinux; run uenvboot ; mmcinfo && fatload mmc $sdbootdev:$partid ${netstart} ${kernel_img} && bootm \0" \
	"autoload=no\0" \
	"clobstart=0x10000000\0" \
	"netstart=0x10000000\0" \
	"dtbnetstart=0x11800000\0" \
	"loadaddr=0x10000000\0" \
	"boot_img=BOOT.BIN\0" \
	"load_boot=tftpboot ${clobstart} ${boot_img}\0" \
	"update_boot=setenv img boot; setenv psize ${bootsize}; setenv installcmd \"install_boot\"; run load_boot ${installcmd}; setenv img; setenv psize; setenv installcmd\0" \
	"install_boot=mmcinfo && fatwrite mmc $sdbootdev:$partid ${clobstart} ${boot_img} ${filesize}\0" \
	"bootenvsize=0x40000\0" \
	"bootenvstart=0x1e00000\0" \
	"eraseenv=sf probe 0 && sf erase ${bootenvstart} ${bootenvsize}\0" \
	"jffs2_img=rootfs.jffs2\0" \
	"load_jffs2=tftpboot ${clobstart} ${jffs2_img}\0" \
	"update_jffs2=setenv img jffs2; setenv psize ${jffs2size}; setenv installcmd \"install_jffs2\"; run load_jffs2 test_img; setenv img; setenv psize; setenv installcmd\0" \
	"sd_update_jffs2=echo Updating jffs2 from SD; mmcinfo && fatload mmc $sdbootdev:$partid ${clobstart} ${jffs2_img} && run install_jffs2\0" \
	"install_jffs2=sf probe 0 && sf erase ${jffs2start} ${jffs2size} && " \
		"sf write ${clobstart} ${jffs2start} ${filesize}\0" \
	"kernel_img=image.ub\0" \
	"load_kernel=tftpboot ${clobstart} ${kernel_img}\0" \
	"update_kernel=setenv img kernel; setenv psize ${kernelsize}; setenv installcmd \"install_kernel\"; run load_kernel ${installcmd}; setenv img; setenv psize; setenv installcmd\0" \
	"install_kernel=mmcinfo && fatwrite mmc $sdbootdev:$partid ${clobstart} ${kernel_img} ${filesize}\0" \
	"cp_kernel2ram=mmcinfo && fatload mmc $sdbootdev:$partid ${netstart} ${kernel_img}\0" \
	"dtb_img=system.dtb\0" \
	"load_dtb=tftpboot ${clobstart} ${dtb_img}\0" \
	"update_dtb=setenv img dtb; setenv psize ${dtbsize}; setenv installcmd \"install_dtb\"; run load_dtb test_img; setenv img; setenv psize; setenv installcmd\0" \
	"sd_update_dtb=echo Updating dtb from SD; mmcinfo && fatload mmc $sdbootdev:$partid ${clobstart} ${dtb_img} && run install_dtb\0" \
	"fault=echo ${img} image size is greater than allocated place - partition ${img} is NOT UPDATED\0" \
	"test_crc=if imi ${clobstart}; then run test_img; else echo ${img} Bad CRC - ${img} is NOT UPDATED; fi\0" \
	"test_img=setenv var \"if test ${filesize} -gt ${psize}\\; then run fault\\; else run ${installcmd}\\; fi\"; run var; setenv var\0" \
	"netboot=tftpboot ${netstart} ${kernel_img} && bootm\0" \
	"default_bootcmd=run cp_kernel2ram && bootm ${netstart}\0" \
    "reloadbootenv=run loadbootenv ;  run importbootenv ; saveenv ; run loadbootenv_ext ;  run importbootenv ; saveenv ; printenv envver\0" \
    "loadFpga=mmc rescan; fatload mmc $sdbootdev:$partid 0x100000 ${bitstream_image} && fpga loadb 0:1 0x100000 ${filesize};\0" \
    "emmcboot=mmc rescan;  run bootarrgsGenerate ; echo Copying Linux from SD to RAM... && fatload mmc $sdbootdev:$partid 0x3000000 ${kernel_img} && fatload mmc $sdbootdev:$partid 0x2A00000 ${dtb_img} && bootm 0x3000000 - 0x2A00000 \0" \
    "bootcmd=run prebootcmd ; run emmcboot \0" \
    "bootenvdw=tftpboot ${loadbootenv_addr} ${bootenv} && run  importbootenv && saveenv\0" \
    "bootenvfatwrite=fatwrite mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv} ${filesize}\0" \
    "tftpbootenv=run bootenvdw; run bootenvfatwrite\0" \
    "ipaddr=192.168.1.8\0" \
    "serverip=192.168.1.9\0" \
    "loadbootenv_ext=load mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv_ext}\0" \
    "loadbootenv_network=load mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv_network}\0" \

