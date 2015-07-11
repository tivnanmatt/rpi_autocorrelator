#include "gpio.h"

struct bcm2835_peripheral gpio = {GPIO_BASE};

// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int map_peripheral(struct bcm2835_peripheral *p)
{
   // Open /dev/mem
   if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   }

   p->map = mmap(
      NULL,
      BLOCK_SIZE,
      PROT_READ|PROT_WRITE,
      MAP_SHARED,
      p->mem_fd,      // File descriptor to physical memory virtual file '/dev/mem'
      p->addr_p       // Address in physical map that we want this memory block to expose
   );

   if (p->map == MAP_FAILED) {
        perror("mmap");
        return -1;
   }

   p->addr = (volatile unsigned int *)p->map;

   return 0;
}

void unmap_peripheral(struct bcm2835_peripheral *p) {

    munmap(p->map, BLOCK_SIZE);
    close(p->mem_fd);
}


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x)
// NOTE: lower case "g" indicates a numerical pin number whereas an upper case "G" indicates a binary series where the Gth bit is a one


#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   INP_GPIO(g); \
                      *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))

#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET(G)  *(gpio.addr+7) = (G)

#define GPIO_CLR(G)  *(gpio.addr+10) = (G)

#define GPIO_READ(G)  (*(gpio.addr+13) & (G) ) == (G)

