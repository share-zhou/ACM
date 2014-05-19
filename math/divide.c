#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000
char *minusNumber(char *, char *, char *);
void clearNull(char *);
void clearZeroLow(char num[])	//清除运算时产生的数组的低位的多余的0
{
    int i;
    char temp[MAX];
    int x;
    for (x = 0; x < MAX; x++)
	temp[x] = '\0';
    for (i = 0; num[i] == '0'; i++) ;
    int k;
    for (k = 0; i < MAX && num[i] != '\0'; i++, k++)
	temp[k] = num[i];
    for (x = 0; x < MAX; x++)
	num[x] = temp[x];
    if (num[0] == '\0')
	num[0] = '0';
}

void clearZero(char num[])	//清除运算时产生的数组的高位的多余的0
{
    int i;
    for (i = 0; num[i] != '\0'; i++)	//找到第一次出现‘\0’的位置
	;
    i--;
    if (num[i] == '-')		//如果这一位是负号
    {
	num[i] = '\0';
	i--;
	for (; num[i] == '0' && i > 0; i--)	//为0时循环清空
	    num[i] = '\0';
	i++;
	num[i] = '-';		//补上之前的负号
	if (num[0] == '0' && num[1] == '-')	//避免出现‘-0’的情况
	    num[1] = '\0';
    }

    else {
	for (; num[i] == '0' && i > 0; i--)	//没有负号的话，循环清空高位的0,最低位的0不清空
	    num[i] = '\0';
    }
}

//设置num成员的值
void setNumber(char num[], char numEnter[])
{
    int count = 0;
    for (; numEnter[count] != '\0'; count++) ;
    int i;
    for (i = 0; i <= count; i++)
	num[i] = numEnter[i];
}

//加减乘除运算部分
char *addNumber(char num1[], char num2[], char result[])
{
    if (num1[0] != '-' && num2[0] != '-')	//+ +
    {
	int i, j;		//i,j分别代表num1,num2数组中有效字符的长度,count代表需要的加法次数
	for (i = 0; num1[i] != '\0'; i++)	//确定num1,num2中参与运算的数字“个数”
	    ;
	for (j = 0; num2[j] != '\0'; j++) ;
	int c = 0;		//c代表进位
	if (i >= j) {
	    int calTimes;
	    for (calTimes = 0; calTimes < i + 1; calTimes++)	//执行加法运算i+1次
	    {
		if (j - calTimes - 1 >= 0)	//共有的位相加
		{
		    int addResult = (num1[i - calTimes - 1] - 48) + (num2[j - calTimes - 1] - 48) + c;	//运算结果的低位存在数组的低位
		    result[calTimes] = addResult % 10 + 48;
		    c = addResult / 10;
		}

		else if (j - calTimes - 1 < 0 && i - calTimes - 1 >= 0)	//较大的数独有的位与进位相加
		{
		    int addResult = (num1[i - calTimes - 1] - 48) + c;
		    result[calTimes] = addResult % 10 + 48;
		    c = addResult / 10;
		}

		else		//最后一次加法只有进位
		    result[calTimes] = c + 48;
	    }
	}

	else {
	    addNumber(num2, num1, result);

	    /*
	       for(int calTimes=0;calTimes<j+1;calTimes++)
	       {
	       if(i-calTimes-1>=0)
	       {
	       int addResult=(num1[i-calTimes-1]-48)+(num2[j-calTimes-1]-48)+c;                //运算结果的低位存在数组的低位
	       result[calTimes]=addResult%10+48;
	       c=addResult/10;
	       }
	       else if(i-calTimes-1<0 && j-calTimes-1>=0)
	       {
	       int addResult=(num2[j-calTimes-1]-48)+c;
	       result[calTimes]=addResult%10+48;
	       c=addResult/10;
	       }
	       else
	       result[calTimes]=c+48;
	       }
	     */
	}
    }

    else if (num1[0] != '-' && num2[0] == '-')	//+ -
    {
	int i, j, index;
	for (i = 0; num1[i] != '\0'; i++)	//确定num1,num2中参与运算的数字“个数”
	    ;
	for (j = 0; num2[j] != '\0'; j++) ;
	char tempNum2[MAX];
	for (index = 0; index < MAX; index++)	//两步for循环可以合成一个for循环
	    tempNum2[index] = '\0';
	for (index = 1; index < j; index++)
	    tempNum2[index - 1] = num2[index];
	minusNumber(num1, tempNum2, result);
    }

    else if (num1[0] == '-' && num2[0] != '-')	//- +
    {
	int i, j, index;
	for (i = 0; num1[i] != '\0'; i++)	//确定num1,num2中参与运算的数字“个数”
	    ;
	for (j = 0; num2[j] != '\0'; j++) ;
	char tempNum1[MAX];
	for (index = 0; index < MAX; index++)	//两步for循环可以合成一个for循环
	    tempNum1[index] = '\0';
	for (index = 1; index < i; index++)
	    tempNum1[index - 1] = num1[index];
	minusNumber(num2, tempNum1, result);
    }

    else			//- -
    {
	int i, j, index;
	for (i = 0; num1[i] != '\0'; i++)	//确定num1,num2中参与运算的数字“个数”
	    ;
	for (j = 0; num2[j] != '\0'; j++) ;
	char tempNum1[MAX];
	for (index = 0; index < MAX; index++)	//两步for循环可以合成一个for循环
	    tempNum1[index] = '\0';
	for (index = 1; index < i; index++)
	    tempNum1[index - 1] = num1[index];
	char tempNum2[MAX];
	for (index = 0; index < MAX; index++)	//两步for循环可以合成一个for循环
	    tempNum2[index] = '\0';
	for (index = 1; index < j; index++)
	    tempNum2[index - 1] = num2[index];
	addNumber(tempNum1, tempNum2, result);
	for (index = 0; result[index] != '\0'; index++) ;
	result[index] = '-';
    }

    //处理result数组高位为0的可能情况
    clearZero(result);
    return result;
}

char *minusNumber(char num1[], char num2[], char result[])
{
    int i, j;			//i,j分别代表num1，num2中要参与运算的数字的个数（包括负号和首位为0的情况）
    for (i = 0; num1[i] != '\0'; i++) ;
    for (j = 0; num2[j] != '\0'; j++) ;
    if (num1[0] != '-' && num2[0] != '-')	//+ +
    {
	if (i > j)		//num1的长度大,>num2
	{
	    int minusTimes;
	    for (minusTimes = 0; minusTimes < i; minusTimes++) {
		int minusResult;
		if (j - minusTimes - 1 >= 0)	//共有的位相减
		{
		    minusResult =
			(num1[i - minusTimes - 1] - 48) -
			(num2[j - minusTimes - 1] - 48);
		}

		else if (j - minusTimes - 1 < 0 && i - minusTimes - 1 >= 0)	//num1独有的位减去借位
		{
		    minusResult = num1[i - minusTimes - 1] - 48;
		}
		if (minusResult < 0) {
		    minusResult += 10;
		    int k;
		    for (k = i - minusTimes - 2; num1[k] == '0'; k--)	//向高位借位
		    {
			num1[k] = '9';
		    }
		    num1[k] = (num1[k] - 48) - 1 + 48;	//便于理解，可以简化
		}
		result[minusTimes] = minusResult + 48;
	    }
	}

	else if (i == j)	//num1与num2等长(不含符号位)，谁更大需判断
	{
	    int index;
	    for (index = 0; num1[index] == num2[index] && index < i; index++)	//找到num1，num2不相等的那一位
		;
	    if (index == i)	//num1==num2
	    {
		result[0] = '0';
	    }

	    else {
		if (num1[index] > num2[index])	//num1>num2
		{
		    int minusTimes;
		    for (minusTimes = 0; minusTimes < i; minusTimes++) {
			int minusResult;
			if (i - minusTimes - 1 >= 0)	//共有的位相减
			{
			    minusResult =
				(num1[i - minusTimes - 1] -
				 48) - (num2[i - minusTimes - 1] - 48);
			}
			if (minusResult < 0) {
			    minusResult += 10;
			    int k;
			    for (k = i - minusTimes - 2; num1[k] == '0'; k--)	//向高位借位
			    {
				num1[k] = '9';
			    }
			    num1[k] = (num1[k] - 48) - 1 + 48;	//便于理解，可以简化
			}
			result[minusTimes] = minusResult + 48;
		    }
		}

		else		//num1<num2
		{
		    int minusTimes;
		    for (minusTimes = 0; minusTimes < j; minusTimes++) {
			int minusResult;
			if (j - minusTimes - 1 >= 0)	//共有的位相减
			{
			    minusResult =
				(num2[j - minusTimes - 1] -
				 48) - (num1[j - minusTimes - 1] - 48);
			}
			if (minusResult < 0) {
			    minusResult += 10;
			    int k;
			    for (k = j - minusTimes - 2; num2[k] == '0'; k--)	//向高位借位
			    {
				num2[k] = '9';
			    }
			    num2[k] = (num2[k] - 48) - 1 + 48;	//便于理解，可以简化
			}
			result[minusTimes] = minusResult + 48;
		    }
		    result[minusTimes] = '-';
		}
	    }
	}

	else			//num1的长度小,num1<num2
	{
	    int index;
	    minusNumber(num2, num1, result);
	    for (index = 0; result[index] != '\0'; index++) ;
	    result[index] = '-';
	}
    }

    else if (num1[0] != '-' && num2[0] == '-')	//+ -
    {
	int index;
	char tempNum2[MAX];
	for (index = 0; index < MAX; index++)
	    tempNum2[index] = '\0';
	for (index = 1; index < j; index++)
	    tempNum2[index - 1] = num2[index];
	addNumber(num1, tempNum2, result);
    }

    else if (num1[0] == '-' && num2[0] != '-')	//- +
    {
	int index;
	char tempNum1[MAX];
	for (index = 0; index < MAX; index++)
	    tempNum1[index] = '\0';
	for (index = 1; index < i; index++)
	    tempNum1[index - 1] = num1[index];
	addNumber(tempNum1, num2, result);
	for (index = 0; result[index] != '\0'; index++) ;
	result[index] = '-';
    }

    else			//- -
    {
	int index;
	char tempNum1[MAX];
	char tempNum2[MAX];
	for (index = 0; index < MAX; index++) {
	    tempNum1[index] = '\0';
	    tempNum2[index] = '\0';
	}
	for (index = 1; index < i; index++)
	    tempNum1[index - 1] = num1[index];
	for (index = 1; index < j; index++)
	    tempNum2[index - 1] = num2[index];
	minusNumber(tempNum2, tempNum1, result);
    }
    clearZero(result);
    return result;
}

char *multiNumber(char num1[], char num2[], char result[])
{
    int i, j;			//记录要运算的数字个数(包括符号)
    int c;			//低位向高位的进位
    for (i = 0; num1[i] != '\0'; i++) ;
    for (j = 0; num2[j] != '\0'; j++) ;
    int multiResult;
    int iLoop, jLoop;
    if (num1[0] != '-' && num2[0] != '-')	//+ +
    {
	for (jLoop = 0; j - jLoop - 1 >= 0; jLoop++) {
	    for (c = 0, iLoop = 0; i - iLoop - 1 >= 0; iLoop++)	//需要优化，为0的就不用乘了
	    {
		multiResult = (num2[j - jLoop - 1] - 48) * (num1[i - iLoop - 1] - 48) + c;	//对应位相乘加上低位来的进位
		if (result[jLoop + iLoop] == '\0')
		    result[jLoop + iLoop] = '0';
		c = ((result[jLoop + iLoop] - 48) + multiResult) / 10;	//这样写考虑了乘完后对应位相加后的进位
		result[jLoop + iLoop] = ((result[jLoop + iLoop] - 48) + multiResult) % 10 + 48;	//本位数字
	    }
	    if (c > 0) {
		if (result[jLoop + iLoop] == '\0')
		    result[jLoop + iLoop] = '0';
		result[jLoop + iLoop] = (result[jLoop + iLoop] - 48) + c + 48;
	    }
	}
    }

    else if (num1[0] != '-' && num2[0] == '-')	//+ -
    {
	int index;
	char tempNum2[MAX];
	for (index = 0; index < MAX; index++)
	    tempNum2[index] = '\0';
	for (index = 1; index < j; index++)
	    tempNum2[index - 1] = num2[index];
	multiNumber(num1, tempNum2, result);
	for (index = 0; result[index] != '\0'; index++) ;
	result[index] = '-';
    }

    else if (num1[0] == '-' && num2[0] != '-')	//- +
    {
	int index;
	char tempNum1[MAX];
	for (index = 0; index < MAX; index++)
	    tempNum1[index] = '\0';
	for (index = 1; index < i; index++)
	    tempNum1[index - 1] = num1[index];
	multiNumber(tempNum1, num2, result);
	for (index = 0; result[index] != '\0'; index++) ;
	result[index] = '-';
    }

    else			//- -
    {
	int index;
	char tempNum1[MAX];
	char tempNum2[MAX];
	for (index = 0; index < MAX; index++) {
	    tempNum1[index] = '\0';
	    tempNum2[index] = '\0';
	}
	for (index = 1; index < i; index++)
	    tempNum1[index - 1] = num1[index];
	for (index = 1; index < j; index++)
	    tempNum2[index - 1] = num2[index];
	multiNumber(tempNum1, tempNum2, result);
    }
    clearZero(result);
    return result;
}

char *divNumber(char num1[], char num2[], char result[], char cResult[])
{
    int i, j;
    char c[MAX];
    char cTemp[MAX];
    char resultTemp[MAX];
    char tempNum[MAX];		//将被用于运算的数组参数
    for (i = 0; num1[i] != '\0'; i++)	//确定num1,num2的有效长度，包括符号位
	;
    for (j = 0; num2[j] != '\0'; j++) ;
    if (num1[0] != '-' && num2[0] != '-')	//+ +
    {
	int divResult;		//保存商
	int x;
	for (x = 0; x < MAX; x++) {
	    c[x] = '\0';
	    cTemp[x] = '\0';
	    resultTemp[x] = '\0';
	}
	int jPosition;		//定位被除数中的当前位
	for (jPosition = 0; jPosition < i; jPosition++) {
	    int cLength;	//保存c中的有效长度
	    for (cLength = 0; c[cLength] != '\0'; cLength++) ;
	    c[cLength] = num1[jPosition];
	    cLength++;

	    //cLength>=j的时候才能进行求商运算，否则，直接赋商值为0
	    if (cLength == j)	//c[]和num2[]长度相等
	    {
		int m;		//保存不相等的那一位的位置
		for (m = 0; c[m] == num2[m] && m < j; m++) ;
		if (m == j)	//当前余数c[]和num2[]相等
		{
		    divResult = 1;	//商为1
		    result[jPosition] = divResult + 48;
		    clearNull(c);

		    //无需对c[]进行操作,c[]现在为空
		}

		else		//c[]和num2[]不相等，在m位不相等，m从0取到j-1
		{
		    if (c[m] > num2[m])	//c[]>num2[]
		    {
 label:		divResult = -1;
			//divResult==-1表示还没有求出合适的商值
			int x;
			for (x = 0; x < MAX; x++)
			    tempNum[x] = '\0';
			char copyResult[MAX];	//存储result中商值的临时数组
			int i;
			for (i = 0; i < MAX; i++)
			    copyResult[i] = result[i];	//暂存result到copyResult
			int tempResult;
			for (tempResult = 1;
			     tempResult < 10 && divResult == -1; tempResult++) {
			    clearNull(resultTemp);	//清空
			    tempNum[0] = tempResult + 48;	//
			    multiNumber(num2, tempNum, resultTemp);	//resultTemp=num2*tempNum
			    int highPosition;
			    for (highPosition = 0;
				 resultTemp[highPosition] !=
				 '\0'; highPosition++) ;
			    highPosition--;
			    char resultTempTemp[MAX];
			    int i;
			    for (i = 0; i < MAX; i++)
				resultTempTemp[i] = '\0';
			    for (i = 0; i < MAX; i++, highPosition--)
				resultTempTemp[i] = resultTemp[highPosition];
			    clearNull(result);	//清空result备用
			    int x;
			    for (x = 0; x < MAX; x++)	//减法函数的定义中对参数进行了修改，先保留一个副本
				cTemp[x] = c[x];
			    minusNumber(c, resultTempTemp, result);	//result=c-resultTemp
			    for (x = 0; x < MAX; x++)	//还原c
				c[x] = cTemp[x];

			    //result中的结果是倒序存储的，再次利用result中的值时，需将其倒置
			    clearNull(resultTemp);
			    for (highPosition = 0;
				 result[highPosition] != '\0'; highPosition++) ;
			    highPosition--;
			    if (result[highPosition] == '0')	//tempNum[0]即为合适的商，highPosition一定为0
			    {
				clearNull(c);	//余数为0
				clearNull(cTemp);
				divResult = tempNum[0];
				int x;
				for (x = 0; x < MAX; x++)
				    result[x] = copyResult[x];	//将copyResult中的值赋回result
				result[jPosition] = tempNum[0];	//赋给result当前位新的商值
			    }

			    else if (result[highPosition] == '-') {
				divResult = tempResult - 1;	//合适的商值
				tempNum[0] = divResult + 48;	//
				clearNull(resultTemp);
				multiNumber(num2, tempNum, resultTemp);	//resultTemp=num2*tempNum
				int i;
				for (i = 0; i < MAX; i++)
				    resultTempTemp[i] = '\0';
				for (highPosition = 0; resultTemp[highPosition]
				     != '\0'; highPosition++) ;
				highPosition--;
				for (i = 0;
				     highPosition >= 0; i++, highPosition--)
				    resultTempTemp[i] =
					resultTemp[highPosition];
				clearNull(result);	//清空result备用
				minusNumber(c, resultTempTemp, result);	//result=c-resultTemp
				for (highPosition = 0;
				     result[highPosition] !=
				     '\0'; highPosition++) ;
				highPosition--;
				clearNull(c);
				clearNull(cTemp);
				int x;
				for (x = 0;
				     highPosition >= 0; x++, highPosition--) {
				    c[x] = result[highPosition];	//将c更新为当前的余数
				    cTemp[x] = result[highPosition];
				}
				for (x = 0; x < MAX; x++)
				    result[x] = copyResult[x];	//将copyResult中的值赋回result
				result[jPosition] = tempNum[0];	//赋给result当前位新的商值
			    }
			}
		    }

		    else {
			result[jPosition] = '0';	//赋值为0的时候不能清空c,除非c[0]为0
			if (c[0] == '0') {
			    clearNull(c);
			    clearNull(cTemp);
			}
			continue;
		    }
		}
	    }

	    else if (cLength < j) {
		result[jPosition] = '0';
		if (c[0] == '0') {
		    clearNull(c);
		    clearNull(cTemp);
		}
		continue;
	    }

	    else {
		goto label;
	    }
	}
    }

    else if (num1[0] != '-' && num2[0] == '-')	//+ -
    {
    }

    else if (num1[0] == '-' && num2[0] != '-')	//- +
    {
    }

    else			//- -
    {
    }
    int x;
    for (x = 0; x < MAX; x++)
	cResult[x] = c[x];
    clearZeroLow(result);
    return result;
}

void clearNull(char num[])
{
    int i;
    for (i = 0; num[i] != '\0'; i++)
	num[i] = '\0';
}

int main(int argc, char *argv[])
{
    char number1[MAX];
    memset(number1, 0, MAX);
    memset(number2, 0, MAX);
    while (scanf("%s%s", number1, number2) == 2) {
	char result[MAX];
	char cresult[MAX];
	memset(result, 0, MAX);
	memset(result, 0, MAX);
	divNumber(number1, number2, result, cresult);
	printf("%s\n", result);
    } return 0;
}
