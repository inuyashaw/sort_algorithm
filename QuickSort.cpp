/*** 快速排序：又称为划分交换排序。基本思想是：通过一趟排序将待排序记录分隔成独立的两部分，其中一部分记录的关键字均比另一部分记录的关键字小，则可以继续对这两部分记录继续进行排序，以达到整个序列有序 ***/
/*** 快速排序使用分治法(divide and conquer)策略来把一个序列分为两个子序列(sub-lists) ***/
/*** 从数列找中挑选出一个元素，称为“基准”，重新排序数列，所有元素比基准值小的摆放在基准的前面，所有元素比基准大的摆放在基准的后面（相同的可以放在任何一边）。在这个分区退出后，该基准就处于数列的中间位置。这个称为分区操作。递归地（recursive）把小于基准值元素的子数列和大于基准值的子数列排序。递归到最底部，数列的大小是零或者一，也就是排好序了 ***/
/*** 平均时间复杂度：O(nlogn) 空间复杂度：根据实现方式的不同而不同 ***/


#include<iostream>

using namespace std;

	template<typename T>
void quick_sort_recursive(T arr[],int start,int end)
{
	if(start >= end)
		return ;
	T mid=arr[end];
	int left=start;
	int right=end-1;
	while(left<right)
	{
		while(arr[left]<mid && left<right) 
			left++;
		while(arr[right]>=mid && left<right)// >=
			right--;
		swap(arr[left],arr[right]);
	}
	if(arr[left]>=arr[end])
		swap(arr[left],arr[end]);
	else
		left++;
	quick_sort_recursive(arr,start,left-1);
	quick_sort_recursive(arr,left+1,end);

}

//这个算法一定会结束，因为在每次的迭代（iteration）中，它至少会把一个元素摆到它最后的位置去。
	template<typename T>
void QuickSort(T arr[],int len)
{
	quick_sort_recursive(arr,0,len-1);
}


int main()
{
	int arr[10]={3,7,4,23,435,546,32,2,42,32};
	QuickSort<int>(arr,10);
	int i;
	for(i=0;i<10;i++)
		cout<<arr[i]<<' ';

	return 0;
}
