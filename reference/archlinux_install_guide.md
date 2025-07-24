Installation
Arch
Rufus
(connect internet via lan cable)
fdisk -l
fdisk /dev/sda
Mkfs.ext4 /dev/sda2
Mkswap /dev/sda1
Swapon /dev/sda1
mount  /dev/sda2 /mnt
pacstrap -K /mnt base linux linux-firmware <other packages here>
	Git
	Shit for wifi
Rust
intel-ucode



genfstab -U /mnt >> /mnt/etc/fstab
arch-chroot /mnt
Ln -sf /usr/share/zoneinfo/Aus/Syd
Hwclock --systohc
Locale-gen
Passwd

grub-mkconfig -o /boot/grub/grub.cfg   # Arch and others
grub-install /dev/sdX

exit
sudo reboot



First Reboot - Adding user
useradd s
passwd s
chown s /home/s

sudo visudo /etc/sudoers
(sudo EDITOR=nvim visudo)

S all all all

Let them ignore password:
s ALL=(ALL) NOPASSWD: ALL

Second Reboot - Internet & repo folder
sudo systemctl enable NetworkManager
sudo systemctl start NetworkManager
Nmcli device wifi list
Nmcli con show
nmcli device wifi connect "SSID" password "yourpassword"




Ok well i have internet now



Can u use tmux as your window manager? lol



(arch linux speedrun any%)


Gpt script


Installing X
Sudo pacman -S xorg-xinit xorg-xserver



Cooking Appendix 1: Repository Manager

Repman add kennoath gnomes
	Clones to appropriate folder and locates to there
Repman status
	Clean
	Behind (yellow)
	Ahead (red)
Repman sync name commitmsg
	Cd, git add*, git commit -m commitmsg, git push

Support for adding shit to your path etc



Cooking Appendix 2: Question / Agent
Just like, ? how do I set up networkmanager? If thats possible

.agent file stores per directory context
Agent does a pass to determine what the strategy is to get all the info it needs, then gathers the info, then answers info (or thinks)
	
?? finish the function at relic.rs:256
Makes a commit or a patch that u review and approve etc
Does vim have a patch viewer? Surely. Or maybe it just makes a commit that u can remove. Or commit at current point. Commit msg of prompt