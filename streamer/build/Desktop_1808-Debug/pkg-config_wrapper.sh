#!/bin/sh
PKG_CONFIG_SYSROOT_DIR=/media/grdl/09e50ce8-257c-4792-ac70-fd7cc9951e99/toolchain-05072021/host/aarch64-buildroot-linux-gnu/sysroot
export PKG_CONFIG_SYSROOT_DIR
PKG_CONFIG_LIBDIR=/media/grdl/09e50ce8-257c-4792-ac70-fd7cc9951e99/toolchain-05072021/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/pkgconfig:/media/grdl/09e50ce8-257c-4792-ac70-fd7cc9951e99/toolchain-05072021/host/aarch64-buildroot-linux-gnu/sysroot/usr/share/pkgconfig:/media/grdl/09e50ce8-257c-4792-ac70-fd7cc9951e99/toolchain-05072021/host/aarch64-buildroot-linux-gnu/sysroot/usr/lib/aarch64-buildroot-linux-gnu/pkgconfig
export PKG_CONFIG_LIBDIR
exec pkg-config "$@"
