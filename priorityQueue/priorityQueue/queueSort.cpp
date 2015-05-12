#include <iostream>
#include <fstream>
#include <time.h>
#include "MPriorityQueue.h"

using namespace std;


int menu();//选项菜单

bool genrand(int num);//随机生成

int main()
{
	int num;//生成的元素个数
	cout << "请输入生成的元素个数(int)：" << endl;
	cin >> num;
	if ( !genrand(++num) )
	{
		exit(1);
	}

	MPNode<int> *arr = NULL;
	try
	{
		arr = new MPNode<int>[num];//使用new创建数组
	}
	catch (exception e)
	{
		cout << "创建数组失败。" << endl;
	}

	int temp;
	//读取文件中的数字并保存到数组中
	fstream f;
	f.open("MPNode.txt");
	for (int i = 1; i < num; i++)
	{
		f >> temp;
		arr[i].setKey(temp);
		f >> temp;
		arr[i].setValue(temp);
	}
	f.close();//关闭




	//建立
	MPQueue<int> priorityQueue(num);

	for (int i = 1; i < num; i++)
	{
		priorityQueue.Insert(arr[i]);
	}

	MPNode<int> a;

	bool exit = false;
	for (;;) {
		int choice = menu();
		switch (choice) {
		case (1):
			a = priorityQueue.MaxValue();
			cout << "key:" << a.getKey() << "\tvalue:" << a.getValue() << endl;
			break;
		case (2):
			a = priorityQueue.ExtractMax();
			cout << "key:" << a.getKey() << "\tvalue:" << a.getValue() << endl;
			break;
		case (3):
			int x,key;
			cout << "想要增加第几位：" << endl;
			cout << "增加到多少？" << endl;
			cin >> x >> key;
			priorityQueue.IncreaseKey(x, key);
			break;
		case (4):
			priorityQueue.Output();
			cout << "重新读入MPNode.txt" << endl;
			for (int i = 1; i < num; i++)
			{
				priorityQueue.Insert(arr[i]);
			}
			break;
		case (5):
			continue;
			break;
		case (6):
			exit = true;
			break;
		default:
			cout << "请重新选择 " << endl;
			break;
		} // end switch

		if (exit == true)
			break;
	} // end forever



	delete [] arr;

	return 0;
}




int menu() {
	int choice;
	cout << "********************" << endl << endl;
	cout << " **** 选项列表 **** " << endl << endl;
	cout << "(1) 显示队列首元素 " << endl;
	cout << "(2) 显示队列首元素并去除 " << endl;
	cout << "(3) 增加key值 " << endl;
	cout << "(4) 导出到文件 " << endl;
	cout << "(5) 重新显示列表 " << endl;
	cout << "(6) 退出: "<< endl << endl;
	cin >> choice;
	return choice;
}


bool genrand(int num)
{
	ofstream output;
	MPNode<int> *dat, *p;


	dat = (MPNode<int> *)malloc(num * sizeof(MPNode<int>));
	p = dat;

	if (dat == NULL)
	{
		cout << "malloc error, memory not enough!\n" << endl;
		exit(1);
	}

	srand( (unsigned int)time(0) );
	for (int i = 1; i < num; i++)
	{
		dat[i].setKey(rand());	// = rand();
	}
	for (int i = 1; i < num; i++)
	{
		dat[i].setValue(rand());	//此处不知道会不会和key重叠
	}

	/* 保存到文件中 */
	output.open("MPNode.txt");
	if(!output.is_open())
	{
		std::cout << "can't open file " << "MPNode.txt" << "!\n" << std::endl;
		exit(2);
	}

	for (int j = 1; j < num; j++)
	{
		output << dat[j].getKey() << "\t" << dat[j].getValue() << endl;
	}

	free(dat);
	output.close();

	return true;
}