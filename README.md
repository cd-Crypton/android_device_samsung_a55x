## Samsung Galaxy A55 5G SM-A556B (a55x)
For unofficial TWRP build release, go to [custom-recovery-releases](https://github.com/cdpcrp/custom-recovery-releases).

## Flash Steps
You can find the guide in the download area.
 
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
