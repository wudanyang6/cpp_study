#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "CreatIntNum.h"
using namespace std;

int randomized_select(int arr[], int p, int r, int i);//第i小数

void quicksort(int arr[], int p,   int r);//快速排序
int partition(int arr[], int p, int r);//对数组划分

void randomized_quicksort(int arr[], int p, int r);//快速排序的随机版本
int randomized_partition(int arr[], int p, int r);//对数组随机划分

void exchange(int arr[], int i, int j);//交换数组中的两个元素
int random(int i, int j);//生成i--j中的一个随机数

int main()
{
	long numNum;
	int numTh = -1;//第几小数
	//输入数字的个数
	cout << "请输入要生成数字的数量：" << endl;
	cin >> numNum;

	do
	{
		cout << "请输入要取第几小的数：" << endl;
		cin >> numTh;
	} while (numTh <= 0 && numTh > numNum);



	//生成数组并保存到文件中
	CreatIntNum creatNum(numNum, "num.txt");
	creatNum.genrand(); 

	int *arr = NULL;
	try
	{
		arr = new int[numNum];//使用new创建数组
	}
	catch (exception e)
	{
		cout << "创建数组失败。" << endl;
	}
	

	//读取文件中的数字并保存到数组中
	fstream f;
	f.open("num.txt");
	for (long i = 0; i < numNum; i++)
	{
		f >> arr[i];
	}
	f.close();//关闭f

	//排序并计算所用时间
	clock_t startQuick, endQuick;

	startQuick = clock();
	//快速排序
	//quicksort(arr, 0, 9);
	//randomized_quicksort(arr, 0, 9);
	int selectNum = randomized_select(arr, 0, numNum-1, numTh);
	endQuick = clock();
	cout << "第" << numTh << "小数是：" << selectNum << endl;

	cout << "The search time is:"<< (double)(endQuick - startQuick)/CLK_TCK << endl;

	
	//使用快速排序并且写入到“sortedNum.txt”中
	randomized_quicksort(arr, 0, numNum-1);
	creatNum.writeNum(numNum, arr, "sortedNum.txt");

	delete []arr;
	return 0;
}

void quicksort(int arr[], int p,   int r)
{
	int q = 0;
	if (p < r)
	{
		q = partition(arr, p, r);
		quicksort(arr, p, q-1);
		quicksort(arr, q+1, r);
	}
}
int partition(int arr[], int p, int r)
{
	int x = arr[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			exchange(arr, i, j);
		}
	}
	exchange(arr, i+1, r);
	return i+1;
}

void exchange(int arr[], int i, int j)
{
	int temp;
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}


void randomized_quicksort(int arr[], int p, int r)
{
	int q = 0;

	if (p < r)
	{
		q = randomized_partition(arr, p, r);
		randomized_quicksort(arr, p, q-1);
		randomized_quicksort(arr, q+1, r);
	}
}

int randomized_partition(int arr[], int p, int r)
{
	int i = random(p, r);
	exchange(arr, r, i);
	return partition(arr, p, r);
}

int random(int i, int j)
{
	srand( (unsigned int)time(0) );

	int randIntNum = 0;

	randIntNum = rand()%(j-i+1) + i;
	return randIntNum;
}


int randomized_select(int arr[], int p, int r, int i)
{
	int q, k;
	if (p == r)
	{
		return arr[p];
	}
	q = randomized_partition(arr, p, r);
	k = q - p + 1;
	if (i == k)
	{
		return arr[q];
	}
	else if(i < k)
	{
		return randomized_select(arr, p, q-1, i);
	}
	else
	{
		return randomized_select(arr, q+1, r, i-k);
	}
}