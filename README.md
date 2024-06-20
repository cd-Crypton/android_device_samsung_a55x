# Android device tree for samsung SM-A556B (a55x)
# Clone
    git clone https://github.com/TheNoobDevs/android_device_samsung_a55x.git -b twrp-12.1 device/samsung/a55x
# Build
    export ALLOW_MISSING_DEPENDENCIES=true; . build/envsetup.sh; lunch twrp_a55x-eng; mka vendorbootimage
