#ifndef _CREATINTNUM_H_
#define _CREATINTNUM_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>

class CreatIntNum
{
public:
	CreatIntNum(){};
	/*num是产生的数字个数，file是写入的文件名*/
	CreatIntNum(long num, char *file)
	{
		this->num = num;
		this->file = file;
	};
	~CreatIntNum(){};
	int genrand();
	void writeNum(long num, int arr[], char *outFile);

private:
	char * file;
	long num;
};


int CreatIntNum::genrand()
{
	std::ofstream output;
	int *dat, *p, i;

    dat = (int *)malloc(num * sizeof(int));
    p = dat;
    
    if (dat == NULL)
	{
		std::cout << "malloc error, memory not enough!\n" << std::endl;
        exit(1);
    }
    
    srand( (unsigned int)time(0) );
    for (i = 0; i < num; i++)
	{
        dat[i] = rand();
    }
    
    /* 保存到文件中 */
	output.open(file);
	if(!output.is_open())
	{
		std::cout << "can't open file " << file << "!\n" << std::endl;
		exit(2);
	}
    long j=0;
	for (long j = 0; j < num; j++)
	{
		output << dat[j] << std::endl;
	}

    free(dat);
    output.close();

    return 0;    
};
void CreatIntNum::writeNum(long num, int arr[], char *outFile)
{
	std::ofstream output;
	output.open(outFile);

	for (long i = 0; i < num; i++)
	{
		output << arr[i] << " ";
	}
	output.close();
};

#endif