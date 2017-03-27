/*** 冒泡排序是一种交换排序 ***/
/*** 有两种方式进行冒泡，一种是先把小的冒泡到前边去，一种是把大元素冒泡到后面 ***/
/*** 通过两层循环来控制：外循环，负责把需要冒泡的那个数字排除在外；内循环，负责两两交换 ***/
/*** 性能分析：平均时间复杂度O(n^2)，最佳时间复杂度O(n),最差时间复杂度O(n^2),空间复杂度(1),排序方式：In-place,稳定性：稳定 ***/


//最基本的代码实现
#include<iostream>
using namespace std;
void BubbleSort(int arr[],int len)
{
	int i,j;
	for(i=0;i<len;i++)
	{
		for(j=1;j<len-i;j++)
		{
			if(arr[j-1]>arr[j])
				swap(arr[j-1],arr[j]);
		}
	}
}


//改进方法1：在某次遍历中如果没有数据交换，说明整个数组已经有序。若初始序列就是排序好的，如果用基础的冒泡排序方法，仍然还要比较O(N^2)次，但无交换次数。
//改进思路：通过设置标志位来记录此次遍历有无数据交换，进而可以判断是否要继续循环，设置一个flag标记，当在一趟序列中没有发生交换，则该序列已排序好，但优化后排序的时间复杂度没有发生量级的改变。
void BubbleSort_1(int arr[],int len)
{
	int i,j;
	for(i=0;i<len;i++)
	{		
		bool exchange=false;//改进，若在一趟中没有发生交互，则序列已经有序
		for(j=1;j<len-i;j++)
			if(arr[j-1]>arr[j])
			{
				swap(arr[j-1],arr[j]);
				exchange=true;
			}
		if(exchange==false)
			return;
	}
}


//改进方法2：如果有100个数的数组，仅前面10个无序，后面90个都已排好序且都大于前面10个数字，那么在第一趟遍历后，最后发生交换的位置必定小于10，且这个位置之后的数据必定已经有序了。
//改进思路：记录某次遍历时最后发生数据交换的位置pos，这个位置之后的数据显然已经有序了。因此通过记录最后发生数据交换的位置就可以确定下次循环的范围了。由于pos位置之后的记录均已交换到位,故在进行下一趟排序时只要扫描到pos位置即可。
void BubbleSort_2(int arr[],int len)
{
	int j,k;
	int pos;
	pos=len;
	while(pos>0)
	{
		k=pos;
		pos=0;
		for(j=1;j<k;j++)
			if(arr[j-1]>arr[j])
			{
				swap(arr[j-1],arr[j]);
				pos=j;
			}
	}
}


int main()
{
	int num[10]={88,0,9,3,2,1,4,5};
	BubbleSort_2(num,10);
	int i;
	for(i=0;i<10;i++)
		cout<<num[i]<<' ';
	return 0;
}
