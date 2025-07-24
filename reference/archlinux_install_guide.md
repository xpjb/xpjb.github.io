# Archlinux Installation Guide

## Pre-installation

- **Tooling**: Arch, Rufus
- **Connectivity**: Connect internet via LAN cable.

### Disk Partitioning
```bash
fdisk -l
fdisk /dev/sda
```

### Filesystem Creation
```bash
Mkfs.ext4 /dev/sda2
Mkswap /dev/sda1
Swapon /dev/sda1
mount /dev/sda2 /mnt
```

### Base System Installation
```bash
# Add other packages like git, wifi utilities, rust, intel-ucode
pacstrap -K /mnt base linux linux-firmware
```

## System Configuration

```bash
genfstab -U /mnt >> /mnt/etc/fstab
arch-chroot /mnt
```

- **Timezone**: `ln -sf /usr/share/zoneinfo/Aus/Syd`
- **Hardware Clock**: `hwclock --systohc`
- **Localization**: `locale-gen`
- **Root Password**: `passwd`

### Bootloader Setup
```bash
grub-install /dev/sdX
grub-mkconfig -o /boot/grub/grub.cfg
```

**Reboot the system.**
```bash
exit
reboot
```

## Post-installation

### First Reboot - Adding user
```bash
useradd -m s
passwd s
```

#### Sudoers Configuration
For editing the sudoers file, run `visudo` or `EDITOR=nvim visudo`.

Add the following line to allow user 's' to use sudo:
```
s ALL=(ALL) ALL
```
To allow user 's' to run commands without a password:
```
s ALL=(ALL) NOPASSWD: ALL
```

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

---

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