//progress_timer也是一个计时器，它继承自timer，会在棉桃时自动输出时，省去了
// timer手动调用elapsed的工作，是一个用于自动计时相当方便的小工具
 
#include <boost/progress.hpp>
#include <iostream>
int main()
{
	// 如果要在一个程序中测量多个时间，可以用花括号以限定其生命周期
	{
		boost::progress_timer t;
	}
 
	{
		boost::progress_timer t;
	}
 
	return 0;
}

/////////////////////////////////////////////////////////////////
#include <boost/progress.hpp>
#include <iostream>
#include <fstream>
int main()
{
	// 如果要在一个程序中测量多个时间，可以用花括号以限定其生命周期
	std::ofstream out_file;
	out_file.open("test.txt",std::ios::out);
	
	for (int i=0;i<1000; ++i)
	{
		boost::progress_timer t(out_file);
	}
 
	out_file<<"boost::progress_timer 测试"<<std::endl;
 
	std::cout<<"boost::progress_timer 文件测试成功"<<std::endl;
 
	return 0;
}
