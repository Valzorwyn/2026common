# Born2beroot — Eval Cheatsheet

Replace `bajankov` / `bajankov42` / paths if yours differ.

## 0. Signature (on host, before booting)
```bash
shasum *.vdi                  # Mac (Linux: sha1sum) — must match signature.txt
```

## 1. OS / basics
```bash
cat /etc/os-release
uname -a
ls /usr/bin/*session          # no GUI
sudo aa-status                # AppArmor loaded + profiles in enforce mode
sudo systemctl status apparmor
sudo systemctl status ufw
sudo systemctl status ssh
```

## 2. User & groups
```bash
groups bajankov               # sudo, user42
getent group sudo user42
sudo adduser newuser          # password must follow policy
sudo groupadd evaluating
sudo usermod -aG evaluating newuser
getent group evaluating
groups newuser
```

## 3. Password policy
```bash
sudo chage -l bajankov        # max 30 / min 2 / warn 7
grep "^PASS_" /etc/login.defs
grep pwquality /etc/pam.d/common-password
# minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3
# reject_username difok=7 enforce_for_root
```

## 4. Hostname
```bash
hostname                      # bajankov42
sudo hostnamectl set-hostname newname
sudo nano /etc/hosts          # update 127.0.1.1 line
sudo reboot
hostname                      # verify, then revert the same way
```

## 5. Partitions / LVM
```bash
lsblk
sudo lvdisplay
```

## 6. sudo
```bash
dpkg -l | grep sudo
sudo visudo                   # or: sudo cat /etc/sudoers.d/*
# passwd_tries=3, badpass_message, logfile, log_input/log_output,
# requiretty, secure_path
sudo ls /var/log/sudo/
sudo cat /var/log/sudo/sudo.log   # whatever logfile= points to
```

## 7. UFW
```bash
dpkg -l | grep ufw
sudo ufw status numbered      # only 4242
sudo ufw allow 8080
sudo ufw status numbered
sudo ufw delete <num>         # delete both v4 and v6 rules
sudo ufw status numbered
```

## 8. SSH
```bash
dpkg -l | grep openssh-server
sudo grep -E "^Port|^PermitRootLogin" /etc/ssh/sshd_config   # 4242 / no
ssh bajankov@localhost -p 4242     # from host: ssh bajankov@127.0.0.1 -p 4242
ssh root@localhost -p 4242         # must FAIL
```

## 9. Cron / monitoring.sh
```bash
cat /usr/local/bin/monitoring.sh
sudo crontab -l               # */10 * * * * bash /usr/local/bin/monitoring.sh
sudo crontab -e               # change to */1 to demo, revert after
sudo systemctl stop cron      # stop script without editing it
sudo systemctl start cron
```

### CPU load shows 0.0%?
Idle VM → `vmstat` id = 100 → 100 - 100 = 0. Demo load:
```bash
yes > /dev/null &
bash /usr/local/bin/monitoring.sh
kill %1
```

## 10. Concept questions (be ready)
- What a VM is, why use one
- Debian vs Rocky; why you picked Debian
- Password policy pros/cons
**apt vs aptitude** — both front-ends to dpkg. `apt` is lower-level, CLI only.
`aptitude` is higher-level: interactive ncurses UI, proposes alternative
solutions on dependency conflicts, tracks auto-installed packages and removes
unused ones more aggressively.
 
**AppArmor** — Linux security module (mandatory access control). Per-program
profiles restrict files, capabilities and network access, even for root.
Modes: *enforce* (blocks) / *complain* (logs only). Path-based, vs SELinux
which is label-based and more complex. Default on Debian; SELinux on Rocky.
 
**LVM** — Logical Volume Manager. Abstraction layer over disks:
PV (physical volume) → VG (volume group) → LV (logical volume).
Resize/add/snapshot partitions without repartitioning; can span multiple
disks. In B2BR it sits inside an encrypted LUKS partition.
 
**UFW** — Uncomplicated Firewall. Simple front-end for iptables/nftables.
Default deny incoming; only 4242 allowed.
 
**SSH** — Secure Shell. Encrypted protocol for remote login/commands
(password or key auth). Here: port 4242, root login disabled.
 
**cron** — daemon that runs scheduled commands from a crontab.
Format: `min hour day month weekday command`. `*/10 * * * *` = every 10 min.
Root's crontab runs `monitoring.sh`, which broadcasts to all terminals via `wall`.

