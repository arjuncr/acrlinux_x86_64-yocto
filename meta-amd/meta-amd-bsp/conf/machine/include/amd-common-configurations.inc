require conf/machine/include/amd-features.inc

POKY_DEFAULT_DISTRO_FEATURES_remove = "wayland"

PREFERRED_VERSION_grub-efi ?= "2.02"
PREFERRED_VERSION_grub ?= "2.02"
PREFERRED_PROVIDER_jpeg ?= "jpeg"
PREFERRED_PROVIDER_jpeg-native ?= "jpeg-native"
PREFERRED_VERSION_linux-yocto ?= "5.4%"

MULTILIBS ?= ""
require conf/multilib.conf

MACHINE_FEATURES += "wifi efi alsa"

# QEMU does not support some of the enhanced instructions available
# on the AMD chips which causes some build time failures.
MACHINE_FEATURES_remove = "qemu-usermode"

MACHINE_EXTRA_RRECOMMENDS += "kernel-modules alsa-utils"
MACHINE_EXTRA_RRECOMMENDS += "grub parted util-linux-blkid"
MACHINE_EXTRA_RRECOMMENDS += "rtc-test watchdog-test spi-test smbus-test gpio-test"
MACHINE_EXTRA_RRECOMMENDS += "amd-spi"

# Add serial consoles to kernel commandline, these should occur before the tty0
KERNEL_SERIAL_CONSOLE ??= ""
APPEND += "${KERNEL_SERIAL_CONSOLE}"

# Make sure the kernel messages go to the VGA console
APPEND += "console=tty0"

# Set a generic video mode, use gfxpayload=wxh for grub2
GRUB_OPTS_append = ";set gfxpayload=1024x768"

# We use ext4 rootfs normally so give it priority rather than trying other FS first
APPEND += "rootfstype=ext4,ext3,ext2"

APPEND_ADDITIONAL ??= ""
APPEND += "${APPEND_ADDITIONAL}"

EXTRA_OECONF_append_pn-matchbox-panel-2 = " --with-battery=acpi"

# Add common feartures to be supported for all machines here
EXTRA_IMAGE_FEATURES += "amd-misc-pkgs"
