#include<stdio.h>
#include<unistd.h>
#include<linux/unistd.h>
#include<linux/time.h>
int main(){
int y;
struct timespec abc ;
y = syscall(327,&abc);
if(y==0)
{
printf("%ld\n",abc.tv_sec);
printf("%ld\n",abc.tv_nsec);
}
else
{
printf("Error\n");
}
return 0;
}
