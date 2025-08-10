# Archlinux Installation Guide
The arch install process is very manual, so you get the joy of knowing exactly what's going on. There are these general steps:
* **pre-installation** - Setting up install media
* **disk formatting** - Getting the disk set up
* **pacstrap** - Installing needed packages on the system first from the installation environment
* **chroot** - Going into the system from the installation environment and doing some more setup
* **first boot** - Booting for first time, it wil be pretty barebones at this stage
* **more setup** - More. Setup.

## 0. Pre-installation
- Make arch install USB (e.g. can use Rufus on windows or UUSB etc.)
- Recommend connecting LAN cable
- Normally I would do BIOS mode if possible but sometimes youre locked into UEFI :(

## 1. Disk Partitioning
**choose the correct disk**
```bash
lsblk
fdisk -l
fdisk /dev/sdX
```
### fdisk steps
#### BIOS/MBR
* need to use gpt as well - g
* delete all partitions (d, d, d)
* (if doing UEFI need to make ESP - 300mb or something i.e +300M, t ef)
* add new partition (for swap, size = to your RAM size) (n, p, 1 ( /enter enter enter, first sector default, last sector +32G or however many G of ram you have, yes remove signature)
* t to change type of last one to linux swap - 82
* create new partition with rest of space for your system - n, enter enter enter use all space
* t and then 83 (probably the default anyway)
* w - write **(no going back)**

#### UEFI/GPT
* esp - 1
* linux swap - 19
* linux filesystem - default
* etc

### Set up newly created partitions
```bash
mkfs.fat -F 32 /dev/sdX1
mkfs.ext4 /dev/sdX2
mkswap /dev/sdX1
swapon /dev/sdX1
mount /dev/sdX2 /mnt
```

## 2. Base Installation
Install the base system. Can be worth grabbing other packages you'll need here too, espeically if needed during the coming steps, e.g. a text editor.
If you were trying to install on wifi you would need some wifi utilities here.

```bash
pacstrap -K /mnt base linux linux-firmware base-devel nvim git
```

## Initial Config
```bash
# pretty sure this is how it knows what disks to automatically mount
genfstab -U /mnt >> /mnt/etc/fstab
# chroot! (change root)
arch-chroot /mnt
```
Congratulations, you are now inside the system. Be sure to set up these other things:
```bash
# Timezone - tab to autocomplete
ln -sf /usr/share/zoneinfo/Australia/Sydney /etc/localtime
# idk what this does or if its important
hwclock --systohc
# locales or something. does it just say en-us in /etc/locale. Not sure its right, might need more steps. but i dont think its used much anyway.
locale-gen
# Root passwd
passwd
# Add your user
useradd username
passwd username
```

Sudoers config also needed.
```bash
export EDITOR=nvim && visudo
```
go down to the line root ALL=(ALL:ALL) ALL
put your user, recommend NOPASSWD option like it says there
wq

### Bootloader Setup
This assumes BIOS mode was used. If you used EFI, all I can say is, have fun. LMAO
```bash
pacman -S grub
grub-install /dev/sdX
grub-mkconfig -o /boot/grub/grub.cfg
```

UEFI mode:
```bash
mkdir -p /efi
mount /dev/sdb1 /efi
bootctl install
```

**WARNING: May need to disable secure boot in bios if it won't boot**

uefi sucks
ok always choose /boot
maybe make it bigger

**Reboot the system.**
```bash
exit
reboot
```

## Post-installation


### Second Reboot - Internet & repo folder

#### NetworkManager Setup
```bash
sudo systemctl enable NetworkManager
sudo systemctl start NetworkManager
nmcli device wifi list
nmcli con show
nmcli device wifi connect "SSID" password "yourpassword"
```

> Ok well i have internet now

> Can u use tmux as your window manager? lol

> (arch linux speedrun any%)

### Gpt script

### Installing X
```bash
sudo pacman -S xorg-xinit xorg-server
```

### Sound
User must be added to the sound group. Probably was enough to get stuff working with ALSA but also theresmore stuff you can do for pipewire

### AUR Manager
This is needed. Paru in rust
```bash
git clone https://aur.archlinux.org/paru.git
cd paru
makepkg -si
```


## Appendix 1: Repository Manager

- `Repman add kennoath gnomes`
  - Clones to appropriate folder and locates to there
- `Repman status`
  - Clean
  - Behind (yellow)
  - Ahead (red)
- `Repman sync name commitmsg`
  - `cd`, `git add *`, `git commit -m "commitmsg"`, `git push`

> Support for adding shit to your path etc.

## Appendix 2: Question / Agent
> Just like, ? how do I set up networkmanager? If thats possible

- `.agent` file stores per directory context
- Agent does a pass to determine what the strategy is to get all the info it needs, then gathers the info, then answers info (or thinks)
	
> ?? finish the function at relic.rs:256
> Makes a commit or a patch that u review and approve etc
> Does vim have a patch viewer? Surely. Or maybe it just makes a commit that u can remove. Or commit at current point. Commit msg of prompt
