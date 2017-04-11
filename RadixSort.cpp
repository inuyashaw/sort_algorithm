/*** Radix Sort 基本思想：
 * 基数排序是一种非比较型整数排序算法。原理是将整数按位数切割成不同的数字，
 * 然后按每个位数分别比较。基数排序的方式可以采用LSD（Least significant digital），
 * 或MSD（Most significant digital）。
 * LSD：先从低位开始进行排序，在每个关键字上，可采用桶排序
 * MSD：先从高位开始进行排序，在每个关键字上，可采用计数排序 ***/
/*** 实现逻辑：
 * 将所有待比较数值（正整数）统一为同样的数位长度，数位较短的数前面补零。
 * 从最低位开始，依次进行一次排序。
 * 这样从最低位排序一直到最高位排序完成以后, 数列就变成一个有序序列。 ***/
/*** 时间复杂度：O(k*n) 空间复杂度：O(k+n) 稳定性：稳定 ***/

/*** 基数排序与计数排序、桶排序都用了桶的概念，但是对桶的使用方法上有明显的差异：
 * 基数排序：根据键值的每位数字来分配桶；
 * 计数排序：每个桶只存储单一键值；
 * 桶排序：每个桶存储一定范围的数值 ***/


//基数排序radix sort只针对整形数
#include<iostream>
#include<stdlib.h>

using namespace std;

//求数据的最大位
int maxbit(int data[],int n)
{
	int maxData=data[0];
	int i;
	for(i=1;i<n;i++)
	{
		if(maxData<data[i])
			maxData = data[i];
	}
	int d=1;
	int p=10;
	while(maxData>=p)
	{
		maxData/=10;
		++d;
	}
	return d;
}

//基数排序
void RadixSort(int data[],int n)
{
	int d=maxbit(data,n);
	int *tmp=new int[n];//相当于桶，临时存放数组元素
	int *count=new int[10];//计数器，数组元素存放的是某位上与它下标相同的数的个数
	int i,j,k;
	int radix=1;
	for(i=1;i<=d;i++)//进行d次排序
	{
		for(j=0;j<10;j++)
			count[j]=0;//每次分配前清空计数器
		for(j=0;j<n;j++)
		{
			//统计每个桶中的记录数
			k=(data[j]/radix)%10;
			count[k]++;
		}
		for(j=1;j<10;j++)
		{
			count[j]+=count[j-1]; //分配tmp中的位置给每个桶
		}
		for(j=n-1;j>=0;j--)
		{
			k=(data[j]/radix)%10;
			tmp[count[k]-1]=data[j];
			count[k]--;
		}
		for(j=0;j<n;j++)//将临时数组的内容复制到data中
			data[j]=tmp[j];
		radix=radix*10;

	}
	delete [] tmp;
	delete [] count;
}


int main()
{
	srand(time(NULL));
	int arr[20];
	int i=0;
	cout<<"before:";
	for(;i<20;i++)
	{
		arr[i]=rand()%100;
		cout<<arr[i]<<' ';
	}
	cout<<endl;
        cout<<"after:";
        RadixSort(arr,20);
	for(i=0;i<20;i++)
	{
		cout<<arr[i]<<' ';
	}

        return 0;
}
