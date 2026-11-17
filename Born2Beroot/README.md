*This project has been created as part of the 42 curriculum by bajankov.*
 
# Born2beroot
 
## Description
 
Born2beroot is a system administration project: set up a hardened Debian
server inside a virtual machine, with no graphical interface, following strict
rules.
 
**Goal:** learn the basics of virtualization, partitioning, user and permission
management, and securing a Linux server.
 
**Overview:**
- Debian (stable) in VirtualBox, no GUI
- Encrypted partitions with LVM (LUKS → volume group → logical volumes)
- AppArmor enabled at boot
- SSH only on port 4242, root login disabled
- UFW firewall: only port 4242 open
- Strict password policy (expiry, complexity) through `login.defs` and `pam_pwquality`
- Hardened `sudo` (3 tries, custom error message, full I/O logging, TTY required, restricted path)
- User `bajankov` in the `sudo` and `user42` groups, hostname `bajankov42`
- `monitoring.sh`, run by cron every 10 minutes, broadcasts system info to all terminals with `wall`
## Instructions
 
**Requirements:** VirtualBox and the project's `.vdi` disk image.
 
1. Check the disk image against the submitted signature:
```bash
   shasum born2beroot.vdi        # Linux: sha1sum — must match signature.txt
```
2. Attach the `.vdi` to a new VirtualBox VM (Debian 64-bit) and boot it.
3. Enter the disk encryption passphrase, then log in as `bajankov`.
4. SSH from the host. This needs a NAT port-forwarding rule from host 4242 to guest 4242:
```bash
   ssh bajankov@127.0.0.1 -p 4242
```
5. Run the monitoring script manually:
```bash
   sudo bash /usr/local/bin/monitoring.sh
```
 
## Technical choices
 
| Topic | Choice | Why |
|---|---|---|
| OS | Debian | Stable, beginner-friendly, large documentation base. Rocky (RHEL-based) is more enterprise-oriented and its SELinux setup is more complex. |
| MAC | AppArmor | Default on Debian. Path-based profiles are simpler than SELinux's label-based policies. |
| Firewall | UFW | Simple front-end to iptables/nftables. firewalld (Rocky's default) is zone-based and more complex. |
| Hypervisor | VirtualBox | Free and cross-platform. UTM is the usual choice on Apple Silicon Macs. |
| Partitioning | LVM on LUKS | Encrypted at rest. Volumes can be resized or added without repartitioning. |
 
**apt vs aptitude:** both are front-ends to dpkg. `apt` is lower-level and command-line only. `aptitude` is higher-level: it has an interactive ncurses UI, suggests alternative solutions when dependencies conflict, and is more aggressive about removing unused auto-installed packages.
 
**AppArmor:** a Linux security module that does mandatory access control. Each program gets a profile that limits its files, capabilities and network access, even when it runs as root. It has two modes: *enforce* (blocks violations) and *complain* (only logs them).
 
**LVM:** physical volume (PV) → volume group (VG) → logical volume (LV). Volumes can be resized and snapshotted, and can span several disks.
 
**SSH:** an encrypted protocol for remote login and commands. Here it uses port 4242 with root login disabled.
 
**cron:** a daemon that runs scheduled commands from a crontab (`min hour day month weekday command`). `*/10 * * * *` means every 10 minutes.
 
## Evaluation checklist
 
Replace the username, hostname and paths if yours differ.
 
### OS / services
```bash
cat /etc/os-release
uname -a
ls /usr/bin/*session          # no GUI
sudo aa-status                # AppArmor loaded, profiles in enforce mode
sudo systemctl status apparmor ufw ssh
```
 
### User & groups
```bash
groups bajankov               # sudo, user42
getent group sudo user42
sudo adduser newuser          # password must follow the policy
sudo groupadd evaluating
sudo usermod -aG evaluating newuser
getent group evaluating
```
 
### Password policy
```bash
sudo chage -l bajankov        # max 30 / min 2 / warn 7
grep "^PASS_" /etc/login.defs
grep pwquality /etc/pam.d/common-password
# minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3
# reject_username difok=7 enforce_for_root
```
 
### Hostname
```bash
hostname                      # bajankov42
sudo hostnamectl set-hostname newname
sudo nano /etc/hosts          # update the 127.0.1.1 line
sudo reboot                   # verify, then revert the same way
```
 
### Partitions
```bash
lsblk
sudo lvdisplay
```
 
### sudo
```bash
dpkg -l | grep sudo
sudo visudo                   # or: sudo cat /etc/sudoers.d/*
sudo ls /var/log/sudo/
```
 
### UFW
```bash
sudo ufw status numbered      # only 4242
sudo ufw allow 8080
sudo ufw status numbered
sudo ufw delete <num>         # remove both the v4 and v6 rules
```
 
### SSH
```bash
sudo grep -E "^Port|^PermitRootLogin" /etc/ssh/sshd_config   # 4242 / no
ssh bajankov@localhost -p 4242
ssh root@localhost -p 4242    # must fail
```
 
### Cron / monitoring.sh
```bash
sudo crontab -l               # */10 * * * * bash /usr/local/bin/monitoring.sh
sudo crontab -e               # change to */1 for the demo, revert after
sudo systemctl stop cron      # stops the script without editing it
sudo systemctl start cron
```
 
**CPU load shows 0.0%?** An idle VM reports `vmstat` id = 100, so 100 − 100 = 0. To show it working:
```bash
yes > /dev/null & sudo bash /usr/local/bin/monitoring.sh; kill %1
```
 
## Resources
 
- [Debian Administrator's Handbook](https://debian-handbook.info/)
- [Debian Wiki: AppArmor](https://wiki.debian.org/AppArmor)
- [Debian Wiki: LVM](https://wiki.debian.org/LVM)
- [Ubuntu UFW documentation](https://help.ubuntu.com/community/UFW)
- [OpenSSH manual: sshd_config](https://man.openbsd.org/sshd_config)
- [sudoers(5) man page](https://www.sudo.ws/docs/man/sudoers.man/)
- [pam_pwquality(8) man page](https://man7.org/linux/man-pages/man8/pam_pwquality.8.html)
- [crontab(5) man page](https://man7.org/linux/man-pages/man5/crontab.5.html)
### AI usage
 
AI (Claude) was used to:
- debug the CPU load metric in `monitoring.sh` and explain why it reads 0.0% on an idle VM
- compile the evaluation command checklist and the short concept explanations
- draft and structure this README

 

