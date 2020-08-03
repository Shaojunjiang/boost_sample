#include <iostream>
#include <fstream>
 
#include <boost/filesystem.hpp>
#include <boost/io/ios_state.hpp>
#include <boost/progress.hpp>
 
int main(int argc, char **argv)
{
	//////////////////////////////////////////////////////////////////////////
	// 遍历当前路径下的中的目录，只能迭代本层目录
	{
		boost::progress_timer t;
		{
 
			std::ofstream of("path.log");
 
			// 保存流的所有状态,以便恢复
			boost::io::ios_all_saver ifs(std::cout);
 
			std::cout.rdbuf(of.rdbuf());
 
			boost::filesystem::directory_iterator end;
 
 
			for (boost::filesystem::directory_iterator pos("J:");pos != end;++pos)
			{
				std::cout << *pos << std::endl;
 
				// 返回path类型，继而返回文件名
//				pos->path().filename();
			}
 
		}
	}
 
	//////////////////////////////////////////////////////////////////////////
	// 指定深度的目录遍历
	{
		boost::progress_timer t;
		{
 
			std::ofstream of("file1.log");
 
			// 保存流的所有状态,以便恢复
			boost::io::ios_all_saver ifs(std::cout);
 
			std::cout.rdbuf(of.rdbuf());
 
			boost::filesystem::recursive_directory_iterator end;
 
 
			for (boost::filesystem::recursive_directory_iterator pos("J:");pos != end;++pos)
			{
				if (boost::filesystem::is_directory(*pos) && (pos.level() > 5) )
				{
					pos.no_push();
				}else
					std::cout << "level -- " << pos.level() << ":" << *pos << std::endl;
 
			}
 
		}
	}
 
 
 
	//////////////////////////////////////////////////////////////////////////
	// 深度迭代所有目录和文件
	{
		boost::progress_timer t;
		{
 
			std::ofstream of("file.log");
 
			// 保存流的所有状态,以便恢复
			boost::io::ios_all_saver ifs(std::cout);
 
			std::cout.rdbuf(of.rdbuf());
 
			boost::filesystem::recursive_directory_iterator end;
 
 
			for (boost::filesystem::recursive_directory_iterator pos("J:");pos != end;++pos)
			{
				std::cout << "level -- " << pos.level() << ":" << *pos << std::endl;
 
			}
 
		}
	}
 
 
 
	return 0;
}
