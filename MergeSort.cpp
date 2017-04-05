/*** 归并排序merge-sort，采用分治法，且各层分治递归可以同时进行，归并排序思路简单，速度仅次于快速排序，是稳定的排序算法，一般用于总体无序，但是各个子项相对有序的数列 ***/
/*** 平均时间复杂度：O(nlogn),空间复杂度O(n),排序方式：In-place，稳定性：稳定 ***/


#include<iostream>
#include<unistd.h>

using namespace std;

//归并排序-迭代法
	template<typename T>
void MergeSort(T arr[],int len)
{
	T* a=arr;
	T* b=new T[len];
	for(int seg=1;seg<len;seg+=seg)
	{
		for(int start=0;start<len;start+=seg+seg)
		{
			//在将要进行比较的相邻子序列中，left_min是第一组的起始元素位置，
			//left_max是第一组的最后一个元素的下一个元素位置(第一组不能超过的边界)，即为第二组起始元素的位置right_min
			//right_max为第二组元素最后一个元素的下一个元素（第二组不能超过的边界）
			int left_min=start,left_max=min(start+seg,len),right_min=left_max,right_max=min(start+seg+seg,len);
			int k=left_min;
			int start1=left_min,end1=left_max;
			int start2=right_min,end2=right_max;
			while(start1<end1 && start2<end2)
				b[k++]=a[start1]<a[start2]?a[start1++]:a[start2++];
			while(start1<end1)
				b[k++]=a[start1++];
			while(start2<end2)
				b[k++]=a[start2++];
		}
		//每间隔seg比较一次后，需要继续用得到的结果去继续进行下一轮的比较
		//每次一轮得到的结果在指针b所指向的空间，所以需要进行指针交换
		T* temp=a;
		a=b;
		b=temp;
	}
	//在最后一轮的交换后，a指向的是最终的结果，如果a指针和arr不一致时
	//说明a指向的是最开始new出来的空间
	if(a!=arr)
	{
		for(int i=0;i<len;i++)
			b[i]=a[i];
		//此时为什么把a的指向赋给b，在下面delete b，而不是直接在下delete a
		//是因为有a==arr的这种情况存在
		b=a;
	}
	delete [] b;

}



//归并排序-递归法
	template<class T>
void Merge_sort_recursive(T arr[],T reg[],int start,int end)
{
	if(start>=end)
		return ;
	int len=end-start,mid=(len>>1)+start;
	int start1=start,end1=mid;
	int start2=mid+1,end2=end;
	Merge_sort_recursive(arr,reg,start1,end1);
	Merge_sort_recursive(arr,reg,start2,end2);
	int k=start;
	while(start1<=end1 && start2<=end2)
		reg[k++]=arr[start1]<arr[start2]?arr[start1++]:arr[start2++];
	while(start1<=end1)
		reg[k++]=arr[start1++];
	while(start2<=end2)
		reg[k++]=arr[start2++];
	for(k=start;k<=end;k++)
		arr[k]=reg[k];
}

template<class T>
void MergeSort_1(T arr[],const int len)
{
   T reg[len];
   Merge_sort_recursive(arr,reg,0,len-1);
}

int main()
{
	int arr[10]={2,33,5,22,676,354,4,6,57,67};
	MergeSort_1<int>(arr,10);
	int i;
	for(i=0;i<10;i++)
		cout<<arr[i]<<' ';

	return 0;    
}
