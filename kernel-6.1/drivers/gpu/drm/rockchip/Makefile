# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the drm device driver.  This driver provides support for the
# Direct Rendering Infrastructure (DRI) in XFree86 4.1.0 and higher.

rockchipdrm-y := rockchip_drm_drv.o rockchip_drm_fb.o \
		 rockchip_drm_gem.o rockchip_drm_logo.o rockchip_drm_clk.o\

rockchipdrm-$(CONFIG_DRM_FBDEV_EMULATION) += rockchip_drm_fbdev.o
rockchipdrm-$(CONFIG_ROCKCHIP_DRM_DEBUG) += rockchip_drm_debugfs.o

rockchipdrm-$(CONFIG_ROCKCHIP_VOP2) += rockchip_drm_vop2.o rockchip_vop2_reg.o rockchip_post_csc.o
rockchipdrm-$(CONFIG_ROCKCHIP_DW_HDMI) += dw_hdmi-rockchip.o
rockchipdrm-$(CONFIG_ROCKCHIP_DW_MIPI_DSI2) += dw-mipi-dsi2-rockchip.o

obj-$(CONFIG_ROCKCHIP_DW_HDCP2) += dw_hdcp2.o
obj-$(CONFIG_DRM_ROCKCHIP) += rockchipdrm.o
