#include  <linux/linkage.h>
#include  <linux/export.h>
#include  <linux/time.h>
#include  <asm/uaccess.h>
#include  <linux/printk.h>
#include  <linux/slab.h>
asmlinkage int sys_my_xtime(struct timespec *current_time)
{
  struct timespec temp = current_kernel_time();

  if(!access_ok(VERIFY_WRITE, current_time, sizeof(current_time))) {
    return -EFAULT;
  }

  copy_to_user(current_time, &temp, sizeof(temp));
  printk(KERN_INFO "current time: %ld", temp.tv_sec);
  printk(KERN_INFO "current time: %ld", temp.tv_nsec);

  return 0;
}
