#include "stdio.h"
#include <iostream>
#include <tlist.hpp>



class MyClass {
public:
	MyClass() {
		printf_s("地址：%p 构造: %s\n" , this , __FUNCSIG__);
	}
	MyClass(int i) :m_value(i) {
		printf_s("地址：%p 构造: %s\n" , this , __FUNCSIG__);
	}

	~MyClass() {
		printf_s("地址：%p 析构：%s\n" , this , __FUNCSIG__);
	}
	void _destory() {
	// 析构函数
		printf_s("地址：%p 析构：%s\n" , this , __FUNCSIG__);
	}

	MyClass(const MyClass &t) {
		printf_s("地址：%p 拷贝构造: %s\n" , this , __FUNCSIG__);

		if (&t == this) {
			return;
		}
		this->m_value = t.m_value;
		return;
	}

	MyClass(MyClass&& t) {
		printf_s("地址：%p 拷贝构造: %s\n" , this , __FUNCSIG__);
		if (&t == this) {
			return;
		}
		this->m_value = t.m_value;
		t.m_value = 0;
		return;
	}


	MyClass& operator=(const MyClass& t) {
		printf_s("地址：%p 赋值构造: %s\n" , this , __FUNCSIG__);
		if (&t == this) {
			return *this;
		}
		this->m_value = t.m_value;
		return *this;
	}


	MyClass& operator=(MyClass&& t) {
		printf_s("地址：%p 赋值构造: %s\n" , this , __FUNCSIG__);
		if (&t == this) {
			return *this;
		}
		this->m_value = t.m_value;
		t.m_value = 0;
		return *this;
	}


	bool operator==(const MyClass &t) {
		if (&t == this) {
			return true;
		}
		return this->m_value == t.m_value ? false : true;
	}
private:
	int m_value;
};





Tstl::TList<int>* gtest;
Tstl::TList<MyClass>* gmyclass;
Tstl::TList<MyClass>* gmyclass1;



void test() {

	Tstl::init_global_vars(gmyclass , gtest , gmyclass1);


	//Tstl::Constructor<MyClass> t3 , t4;
	//t3.init_args(1);
	//t4.init_args(2);

	//t3.get().m_str = "t1";
	//t4.get().m_str = "t2";
	//gmyclass->add(t3);
	//gmyclass->add(t4);

	MyClass t3(1) , t4(2) , t5(6);
	MyClass ttt1 = t3;
	auto ttt2 = t3;
	ttt2 = t3;



	gmyclass->add(t3);
	gmyclass->add(t4);
	gmyclass->add(Tstl::move(t5));
	gmyclass->clear();


	auto fun = [](int a , int b) {
		return a + b;
	};
	auto testff = fun(1 , 2);



	Tstl::destory_global_vars(gmyclass , gtest , gmyclass1);







}


int main() {
	test();
	return 1;
}