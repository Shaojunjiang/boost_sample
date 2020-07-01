//注释中的Page是指：Boost程序库完全开发指南(第三版)
#include <iostream>
//Page542: 在头文件<boost/asio.hpp>前定义此宏，它就会向标准流cerr输出运行日志。
//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/asio.hpp>
 
#include <boost/thread.hpp>  
long boost_thread_id_to_long(boost::thread::id id)
{
    std::stringstream ss; ss << id;
    return strtol(std::string(ss.str()).c_str(), (char**)NULL, 16);
}
 
#include <boost/date_time/posix_time/posix_time.hpp>
std::string local_time_to_simple_string()
{
    boost::posix_time::ptime ptm = boost::posix_time::microsec_clock::local_time();
    return boost::posix_time::to_simple_string(ptm);
}
 
#include <boost/format.hpp>
std::string completion_handler_fun(float f, std::string str)
{
    str = (boost::format("%|s|, thread_id=%|ld|, f=%|.3f|, str=%|s|")
        % local_time_to_simple_string()
        % boost_thread_id_to_long(boost::this_thread::get_id())
        % f % str.c_str()).str();
    std::cout << str << std::endl;
    return str;
}
 
int main1()
{
    boost::asio::io_service io;
    io.post(boost::bind(completion_handler_fun, 3.141592653f, "111"));
    io.post(boost::bind(completion_handler_fun, 3.141592653f, "222"));
    std::cout << "sleep some seconds before run" << std::endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    io.run();
    std::cout << "sleep some seconds after  run" << std::endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    return 0;
    //在这个程序中，主线程提供了io_service::run的上下文。也可以创建一个线程，然后在这个线程里执行run函数。
    //当run开始后，就执行所有的handler，如果io_service里面没有可执行的handler了，就退出run函数了。
}
 
int main2()
{
    boost::asio::io_service io;
    //请阅读Page540的io_service::work的描述。
    //io_service::work会让io_service::run始终有事可做，所以不会退出run函数。
    boost::asio::io_service::work wk(io);
    io.post(boost::bind(completion_handler_fun, 3.141592653f, "111"));
    io.post(boost::bind(completion_handler_fun, 3.141592653f, "222"));
    std::cout << "sleep some seconds before run" << std::endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    io.run();
    //有io_service::work的存在，所以，即时没有可执行的handler了，也不会退出run函数。
    std::cout << "io_service::run is end and will exit." << std::endl;
    return 0;
}
 
int main3()
{
    boost::asio::io_service io;
    //事先在io_service里面放了100个要执行的handler。
    for (int i = 0; i < 100; ++i)
    {
        std::stringstream ss; ss << i;
        io.post(boost::bind(completion_handler_fun, 3.141592653f, std::string(ss.str())));
    }
    boost::thread_group th_gp;
    //线程组创建3个线程，同时处理这100个handler。
    for (int i = 0; i < 3; ++i)
    {
        boost::thread* th_ptr = th_gp.create_thread(boost::bind(&boost::asio::io_service::run, boost::ref(io)));
        std::cout << "thread_group, thread_id=" << boost_thread_id_to_long(th_ptr->get_id()) << std::endl;
    }
    //这3个线程可能同时往屏幕上输出，所以屏幕可能会乱。
    //执行完handler后，run函数退出，线程退出，thread_group的join_all会执行完毕。
    th_gp.join_all();
    std::cout << "will exit" << std::endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    return 0;
}
 
int main()
{
    boost::asio::io_service io;
    //io_service::work阻止了io_service的run函数退出，所以thread_group的join_all函数会一直阻塞在那里。
    boost::asio::io_service::work wk(io);
    boost::thread_group th_gp;
    for (int i = 0; i < 3; ++i)
    {
        boost::system::error_code error;
        boost::thread* th_ptr = th_gp.create_thread(boost::bind(&boost::asio::io_service::run, boost::ref(io), error));
        std::cout << "thread_group, thread_id=" << boost_thread_id_to_long(th_ptr->get_id()) << std::endl;
    }
    io.post(boost::bind(completion_handler_fun, 3.141592653f, "xxx"));
    th_gp.join_all();
    std::cout << "will exit" << std::endl;
    boost::this_thread::sleep_for(boost::chrono::seconds(3));
    return 0;
}
