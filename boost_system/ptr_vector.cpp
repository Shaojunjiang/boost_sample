#include <iostream>
#include <string>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/noncopyable.hpp>
 
class c_test:boost::noncopyable
{
	public:
		c_test(std::string str_name)
		:m_str_name(str_name)
		{
			std::cout << "---- 构造 -> " << m_str_name << std::endl;
		}
		
		~c_test()
		{
			std::cout << "---- 销毁 -> " << m_str_name << std::endl;
		}
		void print()
		{
			std::cout << m_str_name << std::endl; 
		}
	private:
		std::string m_str_name;
};
 
int main()
{
 
	boost::ptr_vector<c_test> m_vect_ptr;
 
	m_vect_ptr.push_back(new c_test("name test 1"));
	m_vect_ptr.push_back(new c_test("name test 2"));
 
	m_vect_ptr.push_back(new c_test("name test 3"));
	m_vect_ptr.push_back(new c_test("name test 4"));
 
	m_vect_ptr.push_back(new c_test("name test 5"));
	m_vect_ptr.push_back(new c_test("name test 6"));
 
	m_vect_ptr.push_back(new c_test("name test 7"));
	m_vect_ptr.push_back(new c_test("name test 8"));
 
 
	boost::ptr_vector<c_test>::iterator const_pos; 
	for(const_pos = m_vect_ptr.begin(); const_pos != m_vect_ptr.end();++ const_pos)
	{
	//	(*const_pos).print();
		const_pos->print();
	}
 
	return 0;
}
