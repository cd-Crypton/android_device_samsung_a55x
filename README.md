## Samsung Galaxy A55 5G SM-A556B (a55x)
For unofficial TWRP build release, go to [release - version A55X-TND_B004](https://github.com/cd-Crypton/custom_recovery_tree_samsung_a55x/releases/tag/A55X-TND_B004).

## Flash Steps
Assuming you know the basic of flashing...
* Via ODIN
    * Download `twrp-vendor_boot.tar` file in the release.
    * In ODIN, in AP section, flash the file you downloaded in release section.
    * Reboot now to Recovery.
* Via FastbootD
    * Download `recovery.cpio.lz4` file in the release.
    * Reboot your device to fastbootd, and in command line, type: `fastboot flash vendor_boot:recovery recovery.cpio.lz4`
    * Run: `fastboot reboot recovery`
 
## Build Steps
Assuming you know the basic of preparing build environment...
* TWRP Source:
```
repo init --depth=1 -u https://github.com/minimal-manifest-twrp/platform_manifest_twrp_aosp.git -b twrp-12.1
```
```
sed -i '/<remove-project name="platform\/external\/gflags"  \/>/d' .repo/manifests/remove-minimal.xml
```
```
repo sync -j$(nproc --all) --force-sync
```
* Device Tree (Make sure you are in root directory of TWRP source.):
```
git clone https://github.com/cd-Crypton/custom_recovery_tree_samsung_a55x -b twrp-12.1 ./device/samsung/a55x
```
* Build (Make sure you are in root directory of TWRP source.)
```
source build/envsetup.sh; export ALLOW_MISSING_DEPENDENCIES=true; lunch twrp_a55x-eng; mka vendorbootimage
```
* Check `vendor_boot.img` in $OUT directory.
