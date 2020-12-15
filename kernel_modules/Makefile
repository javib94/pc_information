
ifneq ($(KERNELRELEASE),) 
	obj-m := cpu_201213619.o
	obj-m := memo_201213619.o
else 

	KERNELDIR ?= /lib/modules/$(shell uname -r)/build 

	PWD := $(shell pwd)

default: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean


