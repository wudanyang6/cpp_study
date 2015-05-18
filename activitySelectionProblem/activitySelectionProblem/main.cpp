#include <iostream>

using namespace std;

#define maxValue 30000

struct activityTime  //结构体类型的说明与定义分开。 声明
{
int sTime;	
int fTime;   
};

int resultNum = 0;

	/*
		参数为：activityTime times[]活动时间 activityTime result[]结果 int arrNum总活动数 int i开始, int j结束
	*/
void recursive_activity_selector(activityTime times[], activityTime result[], int arrNum, int i, int j);//递归地求解
int greedy_activity_selector(activityTime times[], activityTime result[], int arrNum);//贪婪算法

int main()
{
	int numNum;
	//输入活动的个数
	cout << "请输入活动的数量(为实际数量)：" << endl;
	cin >> numNum;
	numNum += 2;
	activityTime *arr = NULL;
	try
	{
		arr = new activityTime[numNum];//使用new创建数组
		for (int i = 0; i < numNum; i++)
		{
			arr[i].sTime = -1;
			arr[i].fTime = -1;
		}
	}
	catch (exception e)
	{
		cout << "创建数组失败。" << endl;
	}

	activityTime *result = NULL;
	try
	{
		result = new activityTime[numNum];//使用new创建数组
		for (int i = 0; i < numNum; i++)
		{
			result[i].sTime = -1;
			result[i].fTime = -1;
		}
	}
	catch (exception e)
	{
		cout << "创建数组失败。" << endl;
	}

	//输入活动详情
	cout << "请输入每个活动的开始和结束时间：" << endl;
	for (int i = 0; i < numNum; i++)
	{
		if (i == 0)
		{
			arr[i].sTime = 0;
			arr[i].fTime = 0;
		}
		else if (i == numNum-1)
		{
			arr[i].sTime = maxValue;
			arr[i].fTime = maxValue;
			cout << "输入结束。" << endl;
		}
		else
		{
			cout << "开始与结束时间：";
			cin >> arr[i].sTime >> arr[i].fTime;
		}
		
	}

	//贪婪算法求解

	/*for (int i = 0; i < greedy_activity_selector(arr, result, numNum); i++)
	{
		cout << "s:" << result[i].sTime << "f:" << result[i].fTime << endl;
	}*/

	//递归求解
	recursive_activity_selector(arr, result, numNum, 0, numNum+1);

	for (int i = numNum-1; i >= 0; i--)
	{//&& result[i].sTime != maxValue
		if (result[i].sTime != -1 && result[i].sTime != maxValue)
		{
			cout << "s:" << result[i].sTime << "f:" << result[i].fTime << endl;
		}
	}

	delete []result;
	delete []arr;
}


void recursive_activity_selector(activityTime times[],activityTime result[], int arrNum, int i, int j)
{
	int m = i + 1;
	while (m < j && times[m].sTime < times[i].fTime)
	{
		m = m + 1;
	}
	if (m < j)
	{
		recursive_activity_selector(times, result, arrNum-1, m, j);
		for (int i = 0; i < arrNum; i++)
		{
			if (result[i].sTime == -1)
			{
				result[i].sTime = times[m].sTime;
				result[i].fTime = times[m].fTime;
			}
		}	
	}
}

int greedy_activity_selector(activityTime times[], activityTime result[], int arrNum)
{
	int m, i = 1;
	int resultNum = 0;
	result[resultNum].sTime = times[1].sTime;
	result[resultNum].fTime = times[1].fTime;
	for (m = 2; m < arrNum; m++)
	{
		if (times[m].sTime >= times[i].fTime)
		{
			resultNum++;
			result[resultNum].sTime = times[m].sTime;
			result[resultNum].fTime = times[m].fTime;
			i = m;
		}
	}
	return resultNum;
}
