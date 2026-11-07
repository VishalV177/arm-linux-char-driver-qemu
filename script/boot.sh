#!/bin/bash
cd "$(dirname "$0")/.."
qemu-system-arm -M versatilepb \
  -kernel kernel/output/zImage \
  -dtb kernel/output/versatile-pb.dtb \
  -initrd rootfs/rootfs.img.gz \
  -append "console=ttyAMA0 rdinit=/init" \
  -nographic
