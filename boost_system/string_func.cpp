#include <vector>
#include <string>
#include <iostream>
 
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
 
 
int main()
{
	std::string str("readme.txt");
 
	if (boost::ends_with(str,"txt"))
	{
		std::cout<< boost::to_upper_copy(str) + " UPPER" << std::endl;
 
		std::cout<< boost::ends_with(str,"txt") << std::endl;
	}
 
	boost::replace_first(str,"readme","followme");
 
	std::cout<< str <<std::endl;
 
	std::vector<char> v(str.begin(),str.end());
 
	//1> 返回一个删除后copy的区间
	//2> 返回一个upper后的copy区间
	//3> copy 赋值操作符 
	std::vector<char> v2 = boost::to_upper_copy(boost::erase_first_copy(v,"txt"));
 
	for (unsigned int i = 0;i< v2.size(); ++i)
	{
		std::cout<< v2[i];
	}
 
	//////////////////////////////////////////////////////////////////////////
	// 大小写转换
	std::string str1 = "I Don't Know.\n";
 
	std::cout<< str1 <<std::endl;
 
	std::cout<<"to_upper_copy -> " << boost::to_upper_copy(str1) << std::endl;
	
	std::cout<<"str1 -> " << str1 << std::endl; 
 
	std::cout<<"to_lower_copy -> " << boost::to_lower_copy(str1) << std::endl;
 
	std::cout<<"str1 -> " << str1 << std::endl; 
 
	boost::to_upper(str1);
 
	std::cout<<"str1 -> " << str1 << std::endl; 
 
	boost::to_lower(str1);
 
	std::cout<<"str1 -> " << str1 << std::endl; 
 
	//////////////////////////////////////////////////////////////////////////
	// 判断式（算法）
	std::string str2("Power Bomb");
 
	std::cout << boost::iends_with(str2,"bomb") << std::endl;
 
	std::cout << !boost::ends_with(str2,"bomb") << std::endl;
 
	std::cout << boost::starts_with(str2,"Pow") << std::endl;
 
	std::cout << boost::contains(str2,"er") << std::endl;
 
	std::string str3 = boost::to_lower_copy(str2);
 
	// 无大小写的 == 判断
	std::cout << boost::iequals(str2,str3) << std::endl;
 
	std::string str4("power suit");
 
	// 参数1 是否小于 参数2  -> 无符号比较
	std::cout << boost::ilexicographical_compare(str2,str4) << std::endl;
 
	// 判断0 -- 5 五个字符是否全为小写
	std::cout << boost::all(str3.substr(0,5),boost::is_lower()) << std::endl;
	
	//////////////////////////////////////////////////////////////////////////
	// 判断式（函数对象）
	std::string str5 = "Samus";
	std::string str6 = "samus";
 
 	std::cout<< boost::is_equal()(str5,str6) << std::endl;
 
	std::cout<< boost::is_less()(str5,str6) << std::endl;
 
	std::cout<< boost::is_not_greater()(str5,str6) << std::endl;
 
	//////////////////////////////////////////////////////////////////////////
	// 分类
	// 用于检测一个字符是否符合某种特性，主要用于搭配其他算法
	
	std::cout << boost::is_space()(' ') << std::endl;
	
	std::cout << boost::is_alnum()('l') << std::endl;
 
	std::cout << boost::is_alpha()('l') << std::endl;
 
	std::cout << boost::is_cntrl()('\n') << std::endl;
 
	std::cout << boost::is_digit()('1') << std::endl;
 
	std::cout << boost::is_graph()(' ') << std::endl;
 
	std::cout << boost::is_lower()('W') << std::endl;
 
	std::cout << boost::is_print()(250) << std::endl;
 
	std::cout << boost::is_punct()(',') << std::endl;
 
	//////////////////////////////////////////////////////////////////////////
	// 修剪算法
	boost::format fmt("|%s|\n");
 
	std::string str7 = "  samus aran  ";
	std::cout<< fmt % boost::trim_copy(str7) << std::endl;
	std::cout<< fmt % boost::trim_left_copy(str7) << std::endl;
 
	boost::trim_right(str7);
	std::cout << fmt % str7 << std::endl;
 
	std::string str8 = "2010 Hapy new Year!!!";
	std::cout << fmt % boost::trim_left_copy_if(str8,boost::is_digit())<<std::endl;
	std::cout << fmt % boost::trim_right_copy_if(str8,boost::is_punct())<<std::endl;
	std::cout << fmt % boost::trim_copy_if(str8,boost::is_digit() || boost::is_punct() || boost::is_space())<<std::endl;
 
	//////////////////////////////////////////////////////////////////////////
	// 查找
	boost::format fmt9("|%s|.pos = %d\n");
 
	std::string str9 = "Long long ago, there was a king.";
 
 	boost::iterator_range<std::string::iterator> rge;
 
 	rge = boost::find_first(str9,"long");
 
 	std::cout<< fmt9 % rge % (rge.begin()- str9.begin());
 
 	rge = boost::ifind_first(str9,"long");
 
 	std::cout<< fmt9 % rge % (rge.begin() - str9.begin());
 
	// 找第三次出现
 	rge = boost::find_nth(str9,"ng",2);
 
	std::cout<< fmt9 % rge % (rge.begin() - str9.begin());
 
 	rge = boost::find_head(str9,4);
 
	std::cout<< fmt9 % rge % (rge.begin() - str9.begin());
 
 	rge = boost::find_tail(str9,5);
 
	std::cout<< fmt9 % rge % (rge.begin() - str9.begin());
 
 	rge = boost::find_first(str9,"samus");
 
 	std::cout<< (rge.empty() && ! rge) <<std::endl;
 
	//////////////////////////////////////////////////////////////////////////
	// 替换和删除
	
 
 
	return 0;
}
