/*** 插入排序是通过构建有序的序列，对于未排序数据，在已经排序序列中从后向前扫描，找到相应位置并插入。插入法排在从后向前扫描的过程中，需要反复把已经排序元素组不向后挪位，为最新的元素提供插入的空间 ***/
/*** 插入排序对几乎已经排好序的数据操作时，效率很高，它不适合对于数量比较大的排序应用 ***/
/*** 平均时间复杂度：O(n^2),空间复杂度：O(1),排序方式(In-place)，稳定性：稳定 ***/
/*** In-place:占用常数内存，不占用额外内存;Out-place:占用额外内存 ***/

#include<iostream>

using namespace std;

//代码实现
void Insertion_Sort(int arr[],int len)
{
	int i,j,temp;
	for(i=1;i<len;i++)
	{
		temp=arr[i];
		for(j=i-1;j>=0;j--)
		{
			if(arr[j]>temp)
				arr[j+1]=arr[j];
			else
				break;//注意如果小于就跳出循环
		}
		arr[j+1]=temp;
	}
}


//优化改进1：
//改进思路：在向前找合适的插入位置时采用二分法查找的方式，即折半插入
//二分插入排序相对于直接插入排序而言，平均性能更快，时间复杂度将至O(nlogn)???,排序是稳定的
//逻辑a、从第一个元素开始，该元素可以认为已经被排序；b、取下一个元素，在已经排序的元素序列中二分查找到一个比它大的数（该数的前一位数小于等于它）的位置；c、将新的元素插入到该位置；d、重复上述两步
void Binary_Insertion_Sort(int arr[],int len)
{
	int key,left,right,middle;
	int i,j;
	for(i=1;i<len;i++)
	{
		key=arr[i];
		left=0;
		right=i-1;
		while(left<=right)
		{
			middle=(left+right)/2;
			if(arr[i]<arr[middle])//if(key < arr[middle]);
				right=middle-1;
			else
				left=middle+1;
		}
		for(j=i-1;j>=left;j--)
			arr[j+1]=arr[j];
		arr[j+1]=key;//arr[left] = key;
	}
}


//优化改进2：
//改进思路：先将整个待排序的序列分为若干个子序列（由相隔某个“增量”的元素组成的）分别进行直接插入排序，然后依次缩减增量再进行排序，待整个序列中的元素基本有序（增量足够小）时，再对全体元素进行一次直接插入排序。其实也就是“希尔排序”


int main()
{
	int arr[10]={77,5,34,7,44,9,0,66,54,3};
	Binary_Insertion_Sort(arr,10);

	int i=0;
	for(;i<10;i++)
		cout<<arr[i]<<endl;
	return 0;
}
