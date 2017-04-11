/*** Bucket Sort基本思想：
 * 桶排序的思想近乎彻底的分治思想。桶排序假设排序的一组数均匀独立的分布在一个范围中，
 * 并将这一范围划分为几个子范围（桶）。
 * 然后基于某种映射函数f，将待排序列的关键字k映射到第i个桶中，那么该关键字k就作为该桶
 * 序列中的一个元素。
 * 接着将各个桶中的数据有序的合并起来，对每个桶中的所有元素进行比较排序（可使用快排）。
 * 然后依次枚举输出中的全部内容即是一个有序序列 ***/
/*** 为了使桶排序更加高效，在额外空间充足的情况下，尽量增大桶的数量。使用的映射函数能
 * 将输入的N个数据均匀的分配到k个桶中去。同时，对于桶中的元素的排序，选择何种比较排序
 * 算法对于性能的影响至关重要 ***/
/*** 一般映射关系 桶的下标=(元素-min)/[(max-min)/桶个数] ***/
/*** 平均时间复杂度：O(n+k) 空间复杂度：O(n*k) 稳定性:稳定 ***/




//假设数据分布在[0,100)之间，每个桶内部用链表表示，在数据入桶的同时插入排序。然后把各个桶
//中的数据合并。
#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

const int BUCKET_NUM = 10;

struct ListNode
{
	explicit ListNode(int i=0):mData(i),mNext(NULL){}
	ListNode* mNext;
	int mData;
};

//插入到相应的桶对应的链表中，插入的同时排序已经进行
ListNode* insert(ListNode*head,int val)
{
      //dummyNode是指向第一个节点的头节点(空节点)
	ListNode dummyNode;
       //待插入的新节点
	ListNode* newNode=new ListNode(val);
	ListNode*pre,*curr;
	dummyNode.mNext=head;
	pre=&dummyNode;
	curr=head;
	while(NULL!=curr && curr->mData<=val)
	{
		pre=curr;
		curr=curr->mNext;
	}
	newNode->mNext=curr;
	pre->mNext=newNode;
	return dummyNode.mNext;
}

ListNode* Merge(ListNode* head1,ListNode* head2)
{
       //dummyNode是头节点
	ListNode dummyNode;
       //dummy是指针,最开始指向头节点
	ListNode* dummy=&dummyNode;
	while(NULL!=head1 && NULL!=head2)
	{
		if(head1->mData <= head2->mData)
		{
                      //第一轮到进行到此的时候，把dummyNode的mNext指向了head1，
                      //相当于给head1的链表加了个头结点(mData为空的节点)
			dummy->mNext=head1;
			head1=head1->mNext;
		}
		else
		{
			dummy->mNext=head2;
			head2=head2->mNext;
		}
                //和head不管是1、2的指向相同
		dummy=dummy->mNext;
	}
        //把剩下的一个链表链到之前比较过得到的链表的后面，即合并为一条
	if(NULL!=head1) dummy->mNext=head1;
	if(NULL!=head2) dummy->mNext=head2;
       //返回的是比较后有顺序链表的第一个节点
	return dummyNode.mNext;
}
void BucketSort(int n,int arr[])
{
      //初始化一个容器，容器中存的是节点的指针
	vector<ListNode*> buckets(BUCKET_NUM,(ListNode*)(0));
	int i;
	for( i=0;i<n;++i)
	{
               //0-100,桶个数10,index=(arr[i]-0)/[(100-0)/10]=arr[i]/10
		int index=arr[i]/BUCKET_NUM;
               //head和vector中index中的指针指向同一个地方
		ListNode* head=buckets.at(index);
		buckets.at(index)=insert(head,arr[i]);
	}
	ListNode* head=buckets.at(0);
	for(i=1;i<BUCKET_NUM;i++)
	{
		head=Merge(head,buckets.at(i));
	}
	for(int i=0;i<n;i++)
	{
		arr[i]=head->mData;
		head=head->mNext;
	}
}


int main()
{
	srand(time(NULL));
	int arr[10];
	int i=0;
	for(;i<10;i++)
		arr[i]=rand()%100;
	cout<<"before:";
	for(i=0;i<10;i++)
		cout<<arr[i]<<' ';
	cout<<endl;
	BucketSort(10,arr);
	cout<<"after:";
	for(i=0;i<10;i++)
		cout<<arr[i]<<' ';
	cout<<endl;

	return 0;
}
