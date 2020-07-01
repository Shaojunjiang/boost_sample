#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
 
using namespace std ;
 
boost::mutex iomutex ;
void runchild(const int n)
{
    {
        boost::mutex::scoped_lock lock(iomutex) ;
        cout<<"我是第"<<n<<"个子线程"<<endl ;
    }
 
    {
        boost::mutex::scoped_lock lock(iomutex) ;
        cout<<"进程"<<n<<" 退出 "<<endl ;
    }
}
 
void dummy(int n)
{
    boost::mutex::scoped_lock lock(iomutex) ;
    for (int i = 0 ; i < n ; ++i)
    {
        cout<<i<<"\t" ;
    }
 
    cout<<endl ;
}
 
int main()
{
    boost::thread_group group ;
    for (int num = 0 ; num < 10 ; ++num)
    {
    //create_thread()是一个工厂函数，可以创建thead对象并运行线程，同时加入内部的list
//      group.create_thread(boost::bind(&runchild , num)) ;
        group.create_thread(boost::bind(dummy , num)) ;
    }
    group.join_all() ; //等待所有线程执行结束
    system("pause") ;
    return 1 ;
}