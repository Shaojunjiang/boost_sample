#include <iostream>
#include <string>
#include <functional>
#include <vector>
 
#include <boost/typeof/typeof.hpp>
 
#include <boost/assign.hpp>
#include <boost/bind.hpp>
 
 
using namespace boost::assign;
 
void print(int v)
{
	std::cout << v <<" ";
}
 
void print2(int v,int y)
{
	std::cout << v + y <<" ";
}
 
// binary_function 的三个参数为 第一个参数类型，第二个参数类型，函数的返回值类型
struct test2:public std::binary_function<int, std::string,void> 
{
	void operator()(int x,std::string y)const
	{
		std::cout << x << y << " ";
	}
};
 
 
struct test1:public std::binary_function<std::string,int, void> 
{
	void operator()(std::string y,int x)const
	{
		std::cout << x << y << " ";
	}
};
 
 
int main()
{
	std::vector<int> v;
 
	boost::assign::push_back(v),2,1,3,7,5,6;
 
	std::for_each(v.begin(),v.end(),print);
 
	std::cout << std::endl;
 
	std::for_each(v.begin(),v.end(),std::bind1st(test1(),"test"));
 
	std::cout << std::endl;
 
	std::for_each(v.begin(),v.end(),std::bind2nd(test2(),"test"));
 
	std::cout << std::endl;
 
	std::cout << std::count_if(v.begin(),v.end(),std::bind1st(std::greater<int>(),10)) << std::endl;
 
 
	std::for_each(v.begin(),v.end(),boost::bind(print2,10,_1));
 
	std::cout << std::endl;
 
	std::for_each(v.begin(),v.end(),boost::bind(print2,_1,11));
 
	std::cout << std::endl;
 
 
	return 0;
}
