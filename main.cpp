#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <psmoveapi/psmove.h>

void getCurrent(int *r,int *g, int *b)
{
	*r=rand()%256;
	*g=rand()%256;
	*b=rand()%256;
}
int main()
{
	PSMove *move;
	move=psmove_connect();
	double r=0,g=0,b=0; 
	double kr=0,kg=0,kb=0;
	int step=100;
	int celr,celg,celb;
	while(!(psmove_get_buttons(move)&Btn_PS))
	{
		getCurrent(&celr,&celg,&celb);	
		kr=(celr-r)/step;
		kg=(celg-g)/step;
		kb=(celb-b)/step;
		for (int i = 0; i < step; i++) {
			r+=kr;
			g+=kg;
			b+=kb;
			psmove_set_leds(move,int(r),int(g),int(b));
			psmove_update_leds(move);
			usleep(50000);
		}
	}
	psmove_disconnect(move);
	return 0;
}
