## Samsung Galaxy A55 5G SM-A556B (a55x)
For unofficial TWRP build release, go to [release section](https://github.com/cd-Crypton/custom_recovery_tree_samsung_a55x/releases).

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