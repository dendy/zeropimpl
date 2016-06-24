
#pragma once

#include <cstddef>




#define DECLARE_PRIVATE(T) \
public: \
	void * operator new(std::size_t size); \
	void operator delete(void * ptr); \
	class Private; \
private: \
	static T * from_private(Private * p) { return reinterpret_cast<T*>(p); } \
	const Private * to_private() const { return reinterpret_cast<const Private*>(this); } \
	Private * to_private() { return reinterpret_cast<Private*>(this); }




class A
{
public:
	A(int value = 42);
	~A();

	int value() const;
	void setValue(int value);

	DECLARE_PRIVATE(A)
};





class B : public A
{
public:
	B(int data);
	~B();

	int data() const;

	DECLARE_PRIVATE(B)
};
