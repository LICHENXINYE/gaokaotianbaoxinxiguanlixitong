#include<stdio.h>
int main(void)
{
	int year,flag;
	printf("Enter year");
	scanf("%d",&year);
	if((year%4==0&&year%100!=0)||year%400==0)
	flag=1;
	else
	flag = 0;
	if(flag==1)
	printf("%d is a leap year!\n",year);
	if(flag==0)
	printf("%d is not a leap year!\n",year);
	return 0;
}
