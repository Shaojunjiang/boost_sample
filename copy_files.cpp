#include <iostream>
 
#include <boost/filesystem.hpp>
#include <boost/progress.hpp>
#include <boost/foreach.hpp>
 
 
void find_files(const boost::filesystem::path& dir,const std::string& filename,std::vector<boost::filesystem::path>& v)
{
 
	if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir)) return;
 
	boost::filesystem::recursive_directory_iterator end;
 
	for (boost::filesystem::recursive_directory_iterator pos(dir);pos!=end;++pos)
	{
		if (!boost::filesystem::is_directory(*pos)/* && pos->path().filename().string() == filename*/)
		{
			v.push_back(pos->path());
		}
	}
 
}
 
size_t copy_files(const boost::filesystem::path& from_dir,const boost::filesystem::path& to_dir,const std::string& filename = "*")
{
	if (!boost::filesystem::is_directory(from_dir))
	{
		std::cout <<"args is not a dir." << std::endl;
		return 0;
	}
 
	std::cout << "prepare for copy,please wait..."<< std::endl;
 
	std::vector<boost::filesystem::path> v;
 
	find_files(from_dir,filename,v);
 
	if (v.empty())
	{
		std::cout << "0 file copied." << std::endl;
 
		return 0;
	}
 
	std::cout << "now begin copy files ..." << std::endl;
 
	boost::filesystem::path tmp;
 
	boost::progress_display pd(v.size());
 
	BOOST_FOREACH(boost::filesystem::path &p,v)
	{
		tmp = to_dir / p.string().substr(from_dir.string().length());
 
		if (!boost::filesystem::exists(tmp.parent_path()))
		{
			boost::filesystem::create_directories(tmp.parent_path());
		}
 
		boost::filesystem::copy_file(p,tmp);
 
		++pd;
	}
 
	std::cout << v.size() << "file copied." << std::endl;
 
	return v.size();
}
 
int main(int argc, char **argv)
{
	copy_files("I:\\QT","I:\\TQ");
}
