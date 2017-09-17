echo "Will be running VNC on port 5905"
qemu-system-i386 -cdrom fusionos.iso -L /usr/share/qemu/ -vnc :5
