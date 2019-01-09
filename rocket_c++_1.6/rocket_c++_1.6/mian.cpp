#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;

class String
{
public:
	typedef char*  iterator;

public:
	String(const char *str = "")
	{
		if (nullptr == str)
			str = "";

		_size = strlen(str);
		_capacity = 15;//����ŵ���15���ֽ�
		_str = new char[_capacity + 1];//ע�����￪�ٵ���������С�ռ䣬������Ч�ַ��ռ�
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(nullptr)
		, _size(s._size)
		, _capacity(s._capacity)
	{
		String StrTmp(s._str);
		swap(_str, StrTmp._str);
	}

	String& operator=(String s)
	{
		swap(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}

	~String()
	{
		if (_str){
			delete[] _str;
			_str = nullptr;
		}
	}

	///////////////////////////////////////////////////////////////////
	// iterator ������
	iterator Begin()//�����ַ���ָ��
	{
		return _str;
	}

	iterator End()//�����ַ���ָ��
	{
		return _str + _size;
	}

	///////////////////////////////////////////////////////////////////
	// modify �޸�

	void PushBack(char c)
	{
		//�Ƿ�����
		if (_size == _capacity)
			Reserve(_capacity * 2);//

		_str[_size++] = c;
		_str[_size] = '\0';//
	}

	String& operator+=(char c)
	{
		PushBack(c);
		return *this;
	}

	String& Append(size_t n, char c)
	{
		for (size_t i = 0; i < n; ++i)
			PushBack(c);

		return *this;
	}


	///////////////////////////////////////////////////////////////////
	// capacity ����
	void Reserve(size_t newCapacity)//������Ҫ�ڿռ俪���¿ռ�
	{
		//�¿ռ���ھɿռ����Ҫ����
		if (newCapacity > _capacity){
			char *str = new char[newCapacity + 1];
			strcpy(str, _str);

			delete[] _str;//�ͷžɿռ�
			_str = str;
			_capacity = newCapacity;//�¿ռ������[����+1]
		}
	}

	void Resize(size_t newsize, char c = '\0')
	{
		if (newsize > _size){
			//newsize����ԭ�ռ���������Ҫ�����¿ռ�
			if (newsize > _capacity)
				Reserve(newsize);

			memset(_str + _size, c, newsize - _size);
		}

		_size = newsize;
		_str[_size] = '\0';
	}

	size_t Capacity()const
	{
		return _capacity;
	}

	size_t Size()const
	{
		return _size;
	}

	size_t Length()const
	{
		return _size;
	}

	bool Empty()const
	{
		if (0 == _size)
			return 1;
		else
			return 0;
	}

	void Clear()
	{
		_size = 0;
	}


	///////////////////////////////////////
	//����
	char& operator[](size_t pos)
	{
		assert(pos < _size);//С��Խ�����
		return _str[pos];
	}

private:
	char *_str;
	size_t _size;
	size_t _capacity;
};

void TestString1()
{
	String s1("hello");
	s1.Append(100, '!');
}

int main()
{
	TestString1();
	return 0;
}
