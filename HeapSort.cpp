/*** 堆一般指的是二叉堆，二叉堆是完全二叉树或者近似完全二叉树。 ***/
/*** 每个节点的值都大于或等于其子节点的值，为最大堆；反之为最小堆 ***/
/*** 一般用数组来表示堆，下标为i的节点的父节点下标为(i-1)/2；其左右子节点分别为(2i+1)和(2i+2) ***/
/*** 堆中定义的几种操作：最大堆调整：将堆的末端子节点作调整，使得子节点永远小于父节点。
 *                       创建最大堆：将堆所有数据重新排序
 *                       堆排序：移除位在第一个数据的根节点，并做最大堆排序调整的递归运算 ***/
/*** 堆排序heapsort是指利用堆这种数据结构所设计的一种排序算法。堆积是一个近似完全二叉树的结构，并同时满足堆积的性质：即子节点的键值总是小于或者大于它的父节点 ***/
/*** 堆排序的基本思想：利用大顶堆（小顶堆）堆顶记录的是最大关键字（最小关键字）这一特点，使得每次从无序中选择最大记录（最小记录）变得简单
 * 将待排序的序列构造成一个最大堆，此时序列的最大值为根节点
 * 依次将根节点与待排序序列的最后一个元素交换
 * 再维护从根节点到该元素的前一个节点为最大对，如此往复，最终得到一个递增序列 ***/
/*** 平均时间复杂度：O(nlogn) 稳定性：不稳定 ***/

#include<iostream>

using namespace std;

void max_heapify(int arr[],int start,int end)
{
	//建立父节点指标和子节点指标
	int dad=start;
	int son=dad*2+1;//左子节点
	while(son<=end)//子节点指标在范围内才做比较
	{
		if(son+1<=end && arr[son]<arr[son+1])//比较两个子节点的大小
			son++;
		if(arr[dad]>arr[son])//若父节点大于子节点则跳出循环
			return;
		else//否则交换内容后，再继续子节点和孙节点比较
		{
			swap(arr[dad],arr[son]);
			dad=son;
			son=dad*2+1;
		}
	}
}

void HeapSort(int arr[],int len)
{
	//初始化，i从最后一个父节点开始调整
	for(int i=(len-1-1)/2;i>=0;i--)
		max_heapify(arr,i,len-1);
	//先将第一个元素与已经排好的元素前一位做交换，再从新调正（刚调整的元素之前的元素），知道排序完成
	for(int i=len-1;i>0;i--)
	{
		swap(arr[0],arr[i]);
		max_heapify(arr,0,i-1);
	}
}


int main(int argc,char* argv[])
{
	int arr[]={0,8,6,4,6,2,5,11,23,53,434,44,21,65,654,865};
	int len=sizeof(arr)/sizeof(int);
	cout<<"len:"<<len<<endl;
	HeapSort(arr,len);
	for(int i=0;i<len;i++)
		cout<<arr[i]<<' ';
	cout<<endl;
	return 0;
}
