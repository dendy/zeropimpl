
#include "lib.h"

#include <cstdio>
#include <stdexcept>




#define DEFINE_PRIVATE(T) \
	void * T::operator new(const std::size_t) \
	{ \
		Private * p = new Private; \
		std::printf("%s %p\n", __PRETTY_FUNCTION__, p); \
		std::fflush(stdout); \
		return p; \
	} \
	\
	void T::operator delete(void * const ptr) \
	{ \
		std::printf("%s %p\n", __PRETTY_FUNCTION__, ptr); \
		std::fflush(stdout); \
		delete static_cast<Private*>(ptr); \
	}




class A::Private
{
public:
	int value;
};

DEFINE_PRIVATE(A)




A::A(const int value)
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	Private & p = to_private();
	p.value = value;
}


A::~A()
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	std::fflush(stdout);
}


int A::value() const
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	const Private & p = to_private();
	return p.value;
}


void A::setValue(const int value)
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	Private & p = to_private();
	p.value = value;
}




class B::Private : public A::Private
{
public:
	int data;
};

DEFINE_PRIVATE(B)




B::B(const int data)
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	Private & p = to_private();
	p.data = data;
}


B::~B()
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	std::fflush(stdout);
}


int B::data() const
{
	const Private & p = to_private();
	return p.data;
}
