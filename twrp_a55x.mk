# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/base.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)

# emulated storage
#$(call inherit-product, $(SRC_TARGET_DIR)/product/emulated_storage.mk)

# Inherit some common twrp stuff.
$(call inherit-product, vendor/twrp/config/common.mk)

# Inherit from essi device
$(call inherit-product, device/samsung/a55x/device.mk)

# Product Name
PRODUCT_RELEASE_NAME := a55x

PRODUCT_DEVICE := a55x
PRODUCT_NAME := twrp_a55x
PRODUCT_BRAND := samsung
PRODUCT_MODEL := SM-A556B
PRODUCT_MANUFACTURER := samsung

PRODUCT_GMS_CLIENTID_BASE := android-samsung-ss
