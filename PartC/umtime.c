#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<linux/unistd.h>
#include<sys/time.h>
#define N 4
#define BUFFER_LENGTH 256               
struct timeval gtodTimes[N];
char *procClockTimes[N];
static char receive[BUFFER_LENGTH];
int fd,i;
int bytes_read;
int main() 
{
for( i=0; i < N; i++)
{
procClockTimes[i] = (char *) malloc(1024);
}
fd = open("/dev/mytime", O_RDONLY);
if (fd < 0){
      perror("Failed to open the device...");
      return errno;
}
for( i=0; i < N; i++)
{
	gettimeofday(&gtodTimes[i], 0);
	bytes_read = read(fd, procClockTimes[i], BUFFER_LENGTH);
	if (bytes_read < 0){
      perror("Failed to read the message from the device.");
      return errno;
}
}
close(fd);

for(i=0; i < N; i++) {
	printf("Time is:  %ld %ld\n%s\n", gtodTimes[i].tv_sec,gtodTimes[i].tv_usec, procClockTimes[i]);
	
}

}

