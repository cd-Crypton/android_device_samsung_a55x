#
# Copyright (C) 2024 The Android Open Source Project
# Copyright (C) 2024 SebaUbuntu's TWRP device tree generator
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := device/samsung/a55x

# Enable virtual A/B OTA
$(call inherit-product, $(SRC_TARGET_DIR)/product/virtual_ab_ota.mk) 

# A/B
AB_OTA_UPDATER := true
TARGET_ENFORCE_AB_OTA_PARTITION_LIST := true

PRODUCT_PACKAGES += \
android.hardware.boot@1.2-impl \
android.hardware.boot@1.2-impl.recovery \
android.hardware.boot@1.2-service

AB_OTA_POSTINSTALL_CONFIG += \
RUN_POSTINSTALL_system=true \
POSTINSTALL_PATH_system=bin/checkpoint_gc \
FILESYSTEM_TYPE_system=erofs \
POSTINSTALL_OPTIONAL_system=true

AB_OTA_POSTINSTALL_CONFIG += \
RUN_POSTINSTALL_vendor=true \
POSTINSTALL_PATH_vendor=bin/checkpoint_gc \
FILESYSTEM_TYPE_vendor=erofs \
POSTINSTALL_OPTIONAL_vendor=true

PRODUCT_PACKAGES += \
android.hardware.fastboot@1.1-impl-mock \
fastbootd 

PRODUCT_PACKAGES += \
    bootctrl.erd8845

#PRODUCT_STATIC_BOOT_CONTROL_HAL := \
    bootctrl.erd8845 \
    libgptutils \
    libz \
    libcutils

PRODUCT_PACKAGES += \
    otapreopt_script \
    cppreopts.sh \
    update_engine \
    update_verifier \
    update_engine_sideload \
    checkpoint_gc

# Partitions
PRODUCT_USE_DYNAMIC_PARTITIONS := true

# Shipping level
PRODUCT_SHIPPING_API_LEVEL := 32
PRODUCT_TARGET_VNDK_VERSION := 32

# Soong namespaces
PRODUCT_SOONG_NAMESPACES += \
    $(LOCAL_PATH)
