cp fusionos.bin isodir/boot/fusionos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o fusionos.iso isodir
