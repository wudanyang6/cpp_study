/*
	1.生成30000个整型数
	2.存到num.txt中
	3.读取num.txt中的读取数字
	4.进行排序
	5.输出数组(显示运行时间)
*/
#include <iostream>
#include <fstream>
#include <time.h>
#include "CreatIntNum.h"
#include "outputArray.h"


using namespace std;
//插入排序
void InsertSort(int arr[], int numNum);
//合并排序 参数为：数组，开始点，结束点
void MergeSort(int arr[], int startPoint, int endPoint);
//合并 参数为： 数组，开始点，中间点，结束点
void Merge(int arr[], int startPoint, int middlePoint, int endPoint);

int main()
{
	long numNum;
	//输入数字的个数
	cout << "请输入要生成数字的数量：" << endl;
	cin >> numNum;

	//生成数组并保存到文件中
	CreatIntNum creatNum(numNum, "num.txt");
	creatNum.genrand();

	int *arr;
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

	//outputSortedArray.outArray(arr, numNum);




	/************************************************************************/
	/* 插入排序                                                                     
	/************************************************************************/
	//排序并计算所用时间
	clock_t startInsert, endInsert;

	startInsert = clock();

	//排序
	InsertSort(arr, numNum);

	endInsert = clock();
	creatNum.writeNum(numNum, arr, "insert.txt");
	cout << "The insert sort time is:"<< (double)(endInsert - startInsert)/CLK_TCK << endl;


	/************************************************************************/
	/* 归并排序                                                                     
	/************************************************************************/
	int *arrMerge;
	try
	{
		arrMerge = new int[numNum];//使用new创建数组
	}
	catch (exception e)
	{
		cout << "创建数组失败。" << endl;
	}

	fstream fin;
	fin.open("num.txt");

	//读取文件中的数字并保存到数组中
	for (long i = 0; i < numNum; i++)
	{
		fin >> arrMerge[i];
	}
	fin.close();//关闭fin

	//排序并计算所用时间
	clock_t startMerge, endMerge;

	startMerge = clock();

	//排序
	MergeSort(arrMerge, 0, numNum-1);

	endMerge = clock();

	creatNum.writeNum(numNum, arrMerge, "merge.txt");
	cout << "The merge sort time is:"<< (double)(endMerge - startMerge)/CLK_TCK << endl;

	
	//释放空间
	delete [] arr;
	delete [] arrMerge;
	return 0;
}

void InsertSort(int arr[], int numNum)   
{
	int key, i;
	for (int j = 1; j < numNum; j++)
	{
		key = arr[j];
		i = j - 1;
		while (i >= 0 && arr[i] > key)
		{
			arr[i+1] = arr[i];
			i--;
		}
		arr[i+1] = key;
	}
}

void MergeSort(int arrMerge[], int startPoint, int endPoint)
{
	int middle;//中间点
	if (startPoint < endPoint)
	{
		middle = (startPoint+endPoint) / 2;
		MergeSort(arrMerge, startPoint, middle);
		MergeSort(arrMerge, middle+1, endPoint);
		Merge(arrMerge, startPoint, middle, endPoint);
	}
}

void Merge(int arrMerge[], int startPoint, int middlePoint, int endPoint)
{
	int n1, n2;//要合并的左、右数量
	int *L, *R;//要合并的两个数组

	n1 = middlePoint - startPoint + 1;
	n2 = endPoint - middlePoint;

	try{
		//创建两个动态数组
		L = new int[n1+1];
		R = new int[n2+1];
	}catch(exception e){
		cout << "创建数组失败" << endl;
	}

	for (int i = 0; i < n1; i++)
	{
		//（startPoint + i）
		L[i] = arrMerge[startPoint + i];
	}

	for (int i = 0; i < n2; i++)
	{
		R[i] = arrMerge[middlePoint + i + 1];
	}

	L[n1] = 2147483647;
	R[n2] = 2147483647;

	int i,j;
	i = j = 0;
	for (int k = startPoint; k <= endPoint; k++)//从startPoint开始到endPoint结束，总共经过了(endPoint-endPoint+1)个循环
	{
		if (L[i] <= R[j])
		{
			arrMerge[k] = L[i];
			i++;
		}
		else
		{
			arrMerge[k] = R[j];
			j++;
		}
	}

	//释放空间
	delete[] L;
	delete[] R;
}