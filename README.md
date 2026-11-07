# Linux character device driver on emulated ARM (QEMU)

A minimal Linux character device driver (`/dev/mysensor`) built as an
out-of-tree kernel module and tested on an emulated ARM Versatile PB board.

## What is built
- Linux 6.6 kernel cross-compiled for ARM (`versatile_defconfig`)
- BusyBox root filesystem (static, packed as initramfs)
- `chardriver.ko`: registers a char device and returns a placeholder value
- Everything runs inside an Ubuntu ARM64 VM (UTM) on an Apple Silicon Mac

## Layout
- `driver/`  driver source and Makefile
- `scripts/` `boot.sh` (QEMU launch), `init` (board startup script)
- `kernel/kernel.config` kernel configuration used

## Run
1. Build the kernel and BusyBox (see config files), pack `rootfs.img.gz`
2. `cd driver && make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-`
3. Copy `chardriver.ko` into the rootfs, repack, run `scripts/boot.sh`
4. On the board: `insmod /mnt/driver/chardriver.ko`, then create the node
   with `mknod` and `cat /dev/mysensor`
