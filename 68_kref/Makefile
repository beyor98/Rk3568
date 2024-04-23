export ARCH=arm64
KERN_DIR = /home/huangsheng/Rk3566_code/kernel-4.19

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= kref.o
