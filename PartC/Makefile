obj-m+=mytime.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) umtime.c -o umtime
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm umtime
 
