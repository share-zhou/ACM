/*calculate a+b in which a and b are large non-negative numbers*/
#include <stdio.h>
#include <string.h>

void add(char *, char *, char *);

/* 10^500 */
#define MAX 10000
int main(int argc, char *argv[])
{
	char num1[MAX];
	char num2[MAX];
	char num3[MAX];

	memset(num1, '\0', MAX);
	memset(num2, '\0', MAX);
	memset(num3, '\0', MAX);

	while(scanf("%s%s", num1, num2)==2) 
	{
		add(num1, num2, num3);
		printf("%s\n", num3);

		memset(num1, '\0', MAX);
		memset(num2, '\0', MAX);
		memset(num3, '\0', MAX);
	}
		
	return 0;
}

void add(char *num1, char *num2, char *result) 
{
	int len1 = strlen(num1);
	int len2 = strlen(num2);

	int len_min = len1<len2?len1:len2;
	int len_max = len1<len2?len2:len1;
	//将低位的运算放置在临时数组result的高位
	int index = 0;
	int carry = 0;
	// add
	for(; index<len_min; index++)
	{
		int digit1 = num1[len1-1-index]-48;	
		int digit2 = num2[len2-1-index]-48;

		int sum = digit1+digit2+carry;
		carry = sum/10;
		sum = sum%10;
		result[index] = sum+48;
	}
	char *remain = len1>len2?num1:num2;
	if(carry==1)
	{
		if(len1==len2) {
			result[index] = '1';
		}
		else 
		{
			for(; index<len_max; index++)
			{
				int digit = remain[len_max-1-index]-48;
				int sum = digit+carry;
				carry = sum/10;
				sum = sum%10;
				result[index] = sum+48;
			}
			if(carry==1)
				result[index] = '1';
		}
	}
	else
	{
		for(; index<len_max; index++)
			result[index] = remain[len_max-1-index];
	}

	//将result中的数字逆序排列一次
	char tmp[MAX];	
	memset(tmp, '\0', MAX);
	int len_res = strlen(result);
	for(index=0; index<len_res; index++)
		tmp[index]=result[len_res-1-index];
	strcpy(result, tmp);
}
