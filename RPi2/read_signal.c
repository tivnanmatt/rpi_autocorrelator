#include "gpio.c"


int main(int argc, char **argv)
{
	const int n = atoi(argv[1]);
	int t;
	char s[n];
	int i;

	if(map_peripheral(&gpio) == -1)
	{
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}

	INP_GPIO(22);
	INP_GPIO(24);
	OUT_GPIO(23);
	OUT_GPIO(25);

	GPIO_SET(1<<23);
	usleep(100);
	GPIO_CLR(1<<23);
	usleep(2000000);



	for(i=0; i<32; i++)
	{
			usleep(50);
			while (!GPIO_READ(1<<24)){}
			if (GPIO_READ(1<<22))
				t = t | (1<<i);
			usleep(50);
			GPIO_SET(1<<23);
			while (GPIO_READ(1<<24)){}
			GPIO_CLR(1<<23);
	}

	for (i=0; i<n; i++)
	{
			usleep(50);
			while (!GPIO_READ(1<<24)){}
			s[i] = GPIO_READ(1<<22) ? 1 : 0;
			usleep(50);
			GPIO_SET(1<<23);
			while (GPIO_READ(1<<24)){}
			GPIO_CLR(1<<23);

	}

	GPIO_SET(1<<25);

	for(i=0;i<20; i++)
	{
			usleep(50);
			GPIO_SET(1<<23);
			usleep(50);
			GPIO_CLR(1<<23);
	}

	GPIO_CLR(1<<25);



	printf("%u ",t);

	for (i=0; i<n; i++)
	{
		printf("%u ",s[i]);
	}




/*
for(i=0;i<10000000; i++){
	printf("%d ",GPIO_READ(1<<24) ? 1 :0);
}
*/
	return 0;

}
