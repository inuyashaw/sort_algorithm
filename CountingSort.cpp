/*** Counting-Sort  基本思想：
 * 计数排序使用一个额外的数组C，其中第i个元素是待排序数组A中值等于i的元素的个数。
 * 计数排序的核心在于将输入的数据值转化为键存储在额外开辟的数组空间中。
 * 作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。
 * 用来计数的数组C的长度取决于待排序数组中数据的范围（最大-最小+1），
 * 然后分配处理 ***/
/*** 实现逻辑：找出待排序的数组中最大和最小的元素
 *             统计数组中每个值为i的元素出现的次数，存入数组C的第i项
 *             对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加）
 *             反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)-1 ***/
/*** 平均时间复杂度：O(n+k) 空间复杂度：O(n+k) 稳定性：稳定 ***/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


using namespace std;

void CountingSort(int *ini_arr,int *sorted_arr,int n)
{
	int *count_arr=new int [100];
	int i,j,k;
	for(i=0;i<n;i++)
		count_arr[i]=0;
	//数组中第i个元素是ini_arr数组中值等于i的元素的个数
	for(i=0;i<n;i++)
		count_arr[ini_arr[i]]++;
	//数组中元素的个数累计慢慢增加，为下一个for循环赋值做准备。具体来说，例如数组为
	//{4,3,2,1,1,2,4,4},统计后得到数组{2,2,1,3}累计增加后为{2,4,5,8},
	//其中排序时值为1的下标范围[0,2),值为2下标范围[2,4),3[4,5),4[5,8)
	//具体的作用参考本函数的第三个for循环
	for(k=1;k<100;k++)
		count_arr[k]+=count_arr[k-1];
	for(j=n;j>0;j--)
		sorted_arr[--count_arr[ini_arr[j-1]]]=ini_arr[j-1];
	delete [] count_arr;
}



//极端的例子：如果排序的数组有200W个元素，但是这200W个数的值都在1000000-1000100，也就说有100个数，这时候n的值为200W，用计数排序，如果按原来的算法，k的值10001000，但是此时c中真正用到的地方只有100个，这样对空间造成了极大的浪费。
//改进C数组大小，优化计数排序，优化后：
void CountingSort_1(int* a,int* b,int n)
{
	int max=a[0],min=a[0];
	int i;
	for(i=1;i<n;i++)
	{
	if(a[i]>max)
			max=a[i];
		if(a[i]<min)
			min=a[i];
	}
    
	int k=max-min+1;
	int*c=new int[k];
	for(i=0;i<n;i++)
		c[a[i]-min]+=1;//优化，减小了数组c的大小
	for(i=1;i<k;i++)
		c[i]=c[i]+c[i-1];
	for(i=n-1;i>=0;i--)
		b[--c[a[i]-min]]=a[i];
}

int main()
{
	int n=10;
	int i;
	int* arr=new int[n];
	int* sorted_arr=new int[n];
	srand(time(0));
	cout<<"ini_arr:";
	for(i=0;i<n;i++)
	{
		arr[i]=rand()%100;
		cout<<arr[i]<<' ';
	}
	cout<<endl;

	//CountingSort(arr,sorted_arr,n);
	CountingSort_1(arr,sorted_arr,n);

	cout<<"sorted_arr:";
	for(i=0;i<n;i++)
		cout<<sorted_arr[i]<<' ';
	cout<<endl;
	delete []arr;
	delete [] sorted_arr;

	return 0;

}
