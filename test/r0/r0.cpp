#include <ntddk.h>
#define _KERNEL_TSTL
#include <tlist.hpp>

#define printf_s DbgPrint

class MyClass {
public:
	MyClass() {
		printf_s("��ַ��%p ����: %s\n" , this , __FUNCSIG__);
	}
	MyClass(int i) :m_value(i) {
		printf_s("��ַ��%p ����: %s\n" , this , __FUNCSIG__);
	}

	~MyClass() {
		printf_s("��ַ��%p ������%s\n" , this , __FUNCSIG__);
	}

	// �������
	void _destory() {
		// ��������
		printf_s("��ַ��%p ������%s\n" , this , __FUNCSIG__);
	}


	MyClass(const MyClass &t) {
		printf_s("��ַ��%p ��������: %s\n" , this , __FUNCSIG__);

		if (&t == this) {
			return;
		}
		this->m_value = t.m_value;
		return;
	}

	MyClass(MyClass&& t) {
		printf_s("��ַ��%p ��������: %s\n" , this , __FUNCSIG__);
		if (&t == this) {
			return;
		}
		this->m_value = t.m_value;
		t.m_value = 0;
		return;
	}


	MyClass& operator=(const MyClass& t) {
		printf_s("��ַ��%p ��ֵ����: %s\n" , this , __FUNCSIG__);
		if (&t == this) {
			return *this;
		}
		this->m_value = t.m_value;
		return *this;
	}


	MyClass& operator=(MyClass&& t) {
		printf_s("��ַ��%p ��ֵ����: %s\n" , this , __FUNCSIG__);
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
		printf_s("��ַ��%p ��ֵ����: %s\n" , this , __FUNCSIG__);
	}
private:
	int m_value;
};
Tstl::TList<int>* gtest;
Tstl::TList<MyClass>* gmyclass;
Tstl::TList<MyClass>* gmyclass1;

EXTERN_C
void DriverUnload(
	_DRIVER_OBJECT *DriverObject
) {
	UNREFERENCED_PARAMETER(DriverObject);
	Tstl::destory_global_vars(gmyclass1 , gtest , gmyclass);

}


EXTERN_C
NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject ,
	_In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);
	DriverObject->DriverUnload = DriverUnload;

	 //ȫ�ֱ���
	Tstl::init_global_vars(gtest , gmyclass1 , gmyclass);




	// �ֲ�����
	Tstl::TList<int> test;
	Tstl::TList<MyClass> testcc;
	MyClass tT1 , tT2;

	// ʹ��
	testcc.add(tT1);
	testcc.add(Tstl::move(tT2));
	testcc.remove(tT1);
	testcc.clear();
	Tstl::Constructor<MyClass> t1 , t2;

	//����lambda
	auto fun1 = [](MyClass& t , int a , int b) {
		t.test1();
		return a + b;
	};
	auto testff = fun1(tT1 , 1 , 2);

	UNREFERENCED_PARAMETER(testff);



	


	return STATUS_SUCCESS;
}