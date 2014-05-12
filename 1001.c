/*input integers a and b, output the result of a+b*/
#include <stdio.h>
int main(int argc, char *argv[])
{
	int a,b;
	while(scanf("%d%d",&a,&b)==2) {
		printf("%d\n",a+b);
	}
	
	return 0;
}
