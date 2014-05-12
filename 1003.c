/*calculate a*b in which a and b are big integers less 10^500*/
#include <stdio.h>
#include <string.h>
#define MAX 1000

void add(char *num1, char *num2, char *result);
void multiplay(char *num1, char *num2, char *result);

int main(void)
{
	char num1[MAX];
	char num2[MAX];
	char num3[MAX*MAX];

	memset(num1, 0, MAX);
	memset(num2, 0, MAX);
	memset(num3, 0, MAX);
	
	while(scanf("%s%s",num1,num2)==2) 
	{
		multiplay(num1, num2, num3);
		printf("%s\n",num3);	

		memset(num1, 0, MAX);
		memset(num2, 0, MAX);
		memset(num3, 0, MAX);
	}
	
	return 0;
}

void multiplay(char *num1, char *num2, char *result) 
{
	//将num2中每一位与num1中进行乘法运算	
	int len1 = strlen(num1);
	int len2 = strlen(num2);

	int carry = 0;
	int current = 0;
		
	int i=0, j=0;
	for(; i<len2; i++)
	{
		carry = 0;
		current = 0;

		int digit2 = num2[len2-1-i]-48;
		char tmp[MAX+1];
		memset(tmp, 0, MAX+1);

		for(j = 0; j<len1; j++)
		{
			int digit1 = num1[len1-1-j]-48;
			int calc = digit1*digit2+carry;
			carry = calc/10;
			current = calc%10;
			
			tmp[j] = current+48;
		}
		if(carry>0)
			tmp[j] = carry+48;
		int len_tmp = strlen(tmp);
		char tmp2[MAX*MAX];
		memset(tmp2, 0, MAX+1);
		for(j=0; j<len_tmp; j++)
			tmp2[j] = tmp[len_tmp-1-j];
		for(j=0; j<i; j++)	
			tmp2[len_tmp+j] = '0';
		char result_tmp[MAX*MAX];
		strcpy(result_tmp, result);
		add(tmp2, result_tmp, result);
	}
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
