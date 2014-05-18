/*calculate a-b in which a and b are big integers less than 10^500*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

void minus(char *num1, char *num2, char *result);
void divide(char *num1, char *num2, char *result);
void trimZeroAtTheEnd(char *data);
void reverse(char *data);
void processMinus(char *result, char *flag);
void trimZeroAtTheStart(char *data);

int main(int argc, char *argv[])
{
	char num1[MAX];	
	char num2[MAX];
	char num3[MAX];

	memset(num1, 0, MAX);
	memset(num2, 0, MAX);
	memset(num3, 0, MAX);

	while(scanf("%s%s", num1, num2)==2)
	{
		int len1 = strlen(num1);
		int len2 = strlen(num2);

		minus(num1, num2, num3);	
		printf("%s\n", num3);

		memset(num1, 0, MAX);
		memset(num2, 0, MAX);
		memset(num3, 0, MAX);
	}
	return 0;
}

/**
 * num1>=num2
 */
void minus(char *num1, char *num2, char *result) 
{
	/*num1=num2*/
	if(strcmp(num1, num2)==0) 
	{
		result[0] = '0';
		return;
	}
	
	/*num1>num2*/
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	int len_min = len1<len2?len1:len2;
	int len_max = len1<len2?len2:len1;

	/*标识对应位的结果是否为负*/
	char flag[MAX];
	memset(flag, 0, MAX);

	/*逐位相减*/
	int index = 0;
	/*对应位相减*/
	for(; index<len_min; index++)
	{
		int digit1 = num1[len1-1-index]-48;
		int digit2 = num2[len2-1-index]-48;
		int minus = digit1-digit2;
		result[index] = abs(minus)+48;	
		if(minus<0)
			flag[index] = '-';
		else if(minus>0)
			flag[index] = '+';
		else
			flag[index] = '0';
	}
	/*非对应位相减(num1>num2)*/
	char *remain = num1;
	for(; index<len_max; index++)
	{
		result[index] = num1[len1-1-index];
		if(result[index]=='0')
			flag[index] = '0';
		else
			flag[index] = '+';
	}
	/*去掉尾部多余的0*/
	trimZeroAtTheEnd(result);	
	int len_res = strlen(result);
	memset(flag+len_res, 0, strlen(flag)-len_res);
	/*逆序排列，得到结果*/
	reverse(result);
	reverse(flag);
	/*扫描flag中的符号-，借位*/
	processMinus(result, flag);
	/*去掉头部多余的0*/
	trimZeroAtTheStart(result);
}

void trimZeroAtTheEnd(char *data)
{
	int len = strlen(data);
	int hasNextZero = 1;
	int i = len-1;
	for(; i>=0 && hasNextZero==1; i--)
	{
		if(data[i]=='0')
			data[i] = '\0';
		else
			hasNextZero = 0;
	}
}

void trimZeroAtTheStart(char *data)
{
	char tmp[MAX];
	memset(tmp, 0, MAX);

	int i = 0;
	for(; data[i]=='0'; i++)	
		;
	strcpy(tmp, data+i);
	strcpy(data, tmp);
}

void reverse(char *data)
{
	int len = strlen(data);
	char tmp[MAX];
	memset(tmp, 0, MAX);
	int i = 0;
	for(; i<len; i++)	
	{
		tmp[i] = data[len-1-i];
	}
	strcpy(data, tmp);
}

void processMinus(char *result, char *flag)
{
	int len = strlen(flag);	
	int i = len-1;
	for(; i>=0; i--)
	{
		/*需要处理借位*/
		if(flag[i]=='-')
		{
			/**
			 * flag从i-1所在的位开始向前扫描，直到找到一个元素为+的位，
			 * 因为num1>num2，结果大于等于0，所以一定可以找到符合条件的位
			 */
			int j = i-1;
			for(; j>=0 && flag[j]!='+'; j--)
				;
			/*从第j位-1，后续的j+1到i-1位加9，第i位10*/
			result[j] = result[j]-1;
			if(result[j]!='0')
				flag[j] = '+';
			else
				flag[j] = '0';
			/*j+1到i-1位要么为负，要么为0*/
			for(j++; j<i; j++) {
				result[j] = -1*(result[j]-48)+9+48;
				if(result[j]!='0')
					flag[j] = '+';
				else
					flag[j] = '0';
			}
			result[j] = -1*(result[j]-48)+10+48;
			if(result[j]!='0')
				flag[j] = '+';
			else
				flag[j] = '0';
		}
	}
}
