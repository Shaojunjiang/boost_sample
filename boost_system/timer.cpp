// timer类可以测量时间的流逝，是一个小型的计时器，提供毫秒级别的计时精度和操作
// 函数，代程序员手工控制使用，就像是个方便的秒表
// timer位于名字空间boost，为了使用timer组件，需要包含头文件<boost/timer.hpp>
// 
#include <boost/timer.hpp>
#include <iostream>
int main()
{
	boost::timer t;						//声明一个计时器对象，开始计时
	std::cout<<"max timespan:"<<t.elapsed_max() / 3600 << "h" << std::endl;//可度量的最大时间，以小时为单位 
	std::cout<<"min timespan:"<<t.elapsed_min()<<"s"<<std::endl;//可度量的最小时间，以秒为单位
 
	//输出已经流逝的时间
	std::cout<<"now time elapsed:"<< t.elapsed()<<"s"<<std::endl;
}
