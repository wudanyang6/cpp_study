#include <iostream>

#define max 100//定义最大值

using namespace std;

//全局变量
int fastTime[2][max];
int line[2][max];
int lastLine;
int time;


void FastestWay(int a[][max], int t[][max], int* e, int* x, int n)
{
    fastTime[0][0] = e[0] + a[0][0];
    fastTime[1][0] = e[1] + a[1][0];

    for (int i = 1; i < n; ++i)
    {
        if (fastTime[0][i-1] <= fastTime[1][i-1] + t[1][i-1])
        {
            fastTime[0][i] = fastTime[0][i-1] + a[0][i];
            line[0][i] =  0;
        }
        else
        {
            fastTime[0][i] = fastTime[1][i-1] + t[1][i-1] + a[0][i];
            line[0][i] = 1;
        }

        if (fastTime[1][i-1] < fastTime[0][i-1] + t[0][i-1])
        {
            fastTime[1][i] = fastTime[1][i-1] + a[1][i];
            line[1][i] = 1;
        }
        else
        {
            fastTime[1][i] = fastTime[0][i-1] + t[0][i-1] + a[1][i];
            line[1][i] = 0;
        }
    }
    if (fastTime[0][n-1] + x[0] < fastTime[1][n-1] + x[1])
    {
        time = fastTime[0][n-1] + x[0];
        lastLine = 0;
    }
    else
    {
        time = fastTime[1][n-1] + x[1];
        lastLine = 1;
    }
}
//打印站点，参数为：线路，站点数，出站位置
void PrintStation(int line[][max], int stations, int lastline)
{
    int i = lastline;
	cout << "line " << i + 1 << ",station " << stations << endl;
    for (int j = stations - 1; j >= 1; j--)
    {
        i = line[i][j];
        cout << "line " << i + 1 << ",station " << j << endl;
    }
}


int main()
{
    int n;
    int a[2][max];
    int t[2][max];
    int e[2];
    int x[2];
	

	cout << "请输入站的数目: ";
	cin >> n;
	if (0 == n)
	{
		exit(1);
	}
		
	cout << "请输入1上每个站花费的时间: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[0][i];
    }

	cout << "请输入2上每个站花费的时间: " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[1][i];
    }
		
	cout << "请输入1转2时花费的时间（站数-1）: " << endl;
    for (int i = 0; i + 1 < n; i++)
    {
        cin >> t[0][i];
    }

	cout << "请输入2转1时花费的时间（站数-1）: " << endl;
    for (int i = 0; i + 1 < n; i++)
    {
        cin >> t[1][i];
    }
		
	cout << "进站时间e1,e2: " << endl;
    cin >> e[0] >> e[1];
	cout << "出站时间x1,x2: " << endl;
	cin >> x[0] >> x[1];

    FastestWay(a, t, e, x, n);
    cout << "最小时间： " << time << endl;
	PrintStation(line,n,lastLine);
	cout << endl;
}


