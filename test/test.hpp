#ifndef _TEST_HPP_
#define _TEST_HPP_

#ifndef _KERNEL_TSTL
#include "stdio.h"
#else
#define printf_s DbgPrint
#endif





namespace Test {

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

	public:
		void test1() {
			printf_s("地址：%p 成员函数: %s\n" , this , __FUNCSIG__);
		}

		virtual void test2() {
			// 不支持
			printf_s("地址：%p 虚函数: %s\n" , this , __FUNCSIG__);
		}
	private:
		int m_value;
	};




	Tstl::TList<int>* gtest;
	Tstl::TList<MyClass>* g_listMyclass1;
	Tstl::TList<MyClass>* g_listMyclass2;
	MyClass* g_MyClass;


	void __init() {
		Tstl::init_global_vars(g_listMyclass1 , gtest , g_listMyclass2 , g_MyClass);
	}

	void __destory() {
		Tstl::destory_global_vars(g_listMyclass1 , gtest , g_listMyclass2 , g_MyClass);
	}

	// 测试全局变量
	void test_g_class() {
		//Tstl::Constructor<MyClass> t3 , t4;
		//t3.init_args(1);
		//t4.init_args(2);

		//t3.get().m_str = "t1";
		//t4.get().m_str = "t2";
		//gmyclass->add(t3);
		//gmyclass->add(t4);

		MyClass t1(1) , t2(2) , t3(6);
		MyClass ttt1 = t1;
		auto ttt2 = t1;
		ttt2 = t1;

		g_listMyclass1->add(t1);
		g_listMyclass1->add(t2);
		g_listMyclass1->add(Tstl::move(t3));

		g_listMyclass1->remove(t1);
		g_listMyclass1->clear();

		auto fun = [](MyClass& my , int a , int b) {
			g_MyClass->test1();
			my.test1();
			//my.test2();
			return a + b;
		};
		auto testff = fun(t1 , 1 , 2);

	}

	// 测试局部变量
	void test_l_class() {
		Tstl::TList<MyClass> listMyclass;
		MyClass t1(1) , t2(2) , t3(6);
		MyClass ttt1 = t1;
		auto ttt2 = t1;
		ttt2 = t1;

		listMyclass.add(t1);
		listMyclass.add(t2);
		listMyclass.add(Tstl::move(t3));
		listMyclass.remove(t1);
		listMyclass.clear();

		auto fun = [](MyClass& my , int a , int b) {
			g_MyClass->test1();
			my.test1();
			//my.test2();
			return a + b;
		};
		auto testff = fun(t1 , 1 , 2);

	}

}

















#endif // !_TEST_HPP_
