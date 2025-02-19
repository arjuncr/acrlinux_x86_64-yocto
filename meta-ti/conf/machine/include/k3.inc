# TI K3 Aarch64 profile for Cortex-A53/A72 cores

require conf/machine/include/ti-soc.inc
SOC_FAMILY_append = ":k3"

require conf/machine/include/arm/arch-arm64.inc

BBMULTICONFIG += "k3r5"

# Increase this everytime you change something in the kernel
MACHINE_KERNEL_PR = "r0"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-ti-staging"
PREFERRED_PROVIDER_virtual/bootloader = "u-boot-ti-staging"
PREFERRED_PROVIDER_u-boot = "u-boot-ti-staging"

KERNEL_IMAGETYPE = "Image"
KERNEL_IMAGETYPES = "Image vmlinux.gz"

UBOOT_ARCH = "arm"
UBOOT_ENTRYPOINT = "0x80008000"
UBOOT_LOADADDRESS = "0x80008000"

SPL_BINARY = "tispl.bin"
UBOOT_SUFFIX = "img"

EXTRA_IMAGEDEPENDS += "virtual/bootloader"

TFA_PLATFORM = "k3"
TFA_BOARD = "generic"

MACHINE_GUI_CLASS = "smallscreen"

# Use the expected value of the ubifs filesystem's volume name in the kernel
# and u-boot.
UBI_VOLNAME = "rootfs"

# List common SoC features, may need to add touchscreen for specific machines
MACHINE_FEATURES = "kernel26 apm usbgadget usbhost vfat ext2 alsa ethernet pci"

IMAGE_FSTYPES += "tar.xz wic.xz wic.bmap"

IMAGE_BOOT_FILES_LEGACY = "${SPL_BINARY} u-boot.${UBOOT_SUFFIX} tiboot3.bin sysfw.itb"
IMAGE_BOOT_FILES_MULTI_CERT = "${SPL_BINARY} u-boot.${UBOOT_SUFFIX} tiboot3.bin"

IMAGE_BOOT_FILES ?= "${IMAGE_BOOT_FILES_LEGACY}"
IMAGE_EFI_BOOT_FILES ?= "${IMAGE_BOOT_FILES}"

EFI_PROVIDER ?= "grub-efi"
MACHINE_FEATURES += "efi"

WKS_FILE ?= "sdimage-2part-efi.wks"
do_image_wic[depends] += "virtual/bootloader:do_deploy"
do_image_wic[mcdepends] += "mc::k3r5:virtual/bootloader:do_deploy mc::k3r5:ti-sci-fw:do_deploy"
do_image_tar[mcdepends] += "mc::k3r5:virtual/bootloader:do_deploy mc::k3r5:ti-sci-fw:do_deploy"
