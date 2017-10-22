#include <linux/init.h>           
#include <linux/module.h>         
#include <linux/device.h>         
#include <linux/kernel.h>         
#include <linux/fs.h>             
#include <asm/uaccess.h>          
#define  DEVICE_NAME "mytime"    
#define  CLASS_NAME  "mtime"        
 
MODULE_LICENSE("GPL");            
            
static int    majNumber;                  
static char   message[256] = {0};           
static struct class*  mytimeClass  = NULL; 
static struct device* mytimeDevice = NULL; 
 
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);

 
static struct file_operations fops =
{
 .read = dev_read,
   };

static int __init mytime_init(void)
{
   printk(KERN_INFO "mytime: Initializing the mytime LKM\n");
   majNumber = register_chrdev(0, DEVICE_NAME, &fops);
   if (majNumber<0){
      printk(KERN_ALERT "mytime failed to register a major number\n");
      return majNumber;
   }
   printk(KERN_INFO "mytime: registered correctly with major number %d\n", majNumber);
 
  
   mytimeClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(mytimeClass)){                
      unregister_chrdev(majNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to register device class\n");
      return PTR_ERR(mytimeClass);          
   }
   printk(KERN_INFO "mtime: device class registered correctly\n");
 
   
   mytimeDevice = device_create(mytimeClass, NULL, MKDEV(majNumber, 0), NULL, DEVICE_NAME);
   if (IS_ERR(mytimeDevice)){               
      class_destroy(mytimeClass);           
      unregister_chrdev(majNumber, DEVICE_NAME);
      printk(KERN_ALERT "Failed to create the device\n");
      return PTR_ERR(mytimeDevice);
   }
   printk(KERN_INFO "mytime: device class created correctly\n"); 
   return 0;
}
 

static void __exit mytime_exit(void){
   device_destroy(mytimeClass, MKDEV(majNumber, 0));     
   class_unregister(mytimeClass);                          
   class_destroy(mytimeClass);                             
   unregister_chrdev(majNumber, DEVICE_NAME);            
   printk(KERN_INFO "mytime: Goodbye from the LKM!\n");
}
 

 
static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    	struct timespec temp = current_kernel_time();
	struct timespec tp;
	getnstimeofday(&tp);
  if(!access_ok(VERIFY_WRITE, buffer, len))
 {
    return -EFAULT;
  }
	sprintf(message,"current_kernel_time:%ld %ld \n getnstimeofday: %ld %ld",temp.tv_sec,temp.tv_nsec,tp.tv_sec,tp.tv_nsec);

  copy_to_user(buffer,&message, len);
  printk(KERN_INFO "current time: %ld", temp.tv_sec);
  printk(KERN_INFO "current time: %ld", temp.tv_nsec);

  return 0;
}            
 
module_init(mytime_init);
module_exit(mytime_exit);
