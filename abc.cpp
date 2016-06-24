
#include "abc.h"




class A::Private
{
public:
	virtual ~Private()
	{
		std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	}

	int value;
};

DEFINE_PRIVATE(A)




A::A(const int value)
{
	Private & p = to_private();
	p.value = value;
	std::printf("%s class=%p private=%p\n", __PRETTY_FUNCTION__, this, &p);
}


A::~A()
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	std::fflush(stdout);
}


int A::value() const
{
	const Private & p = to_private();
	std::printf("%s class=%p private=%p addr(value)=%p\n", __PRETTY_FUNCTION__, this, &p, &p.value);
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
	~Private() override
	{
		std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	}

	int data;
	char foo[15];
};

DEFINE_PRIVATE(B)




B::B(const int data)
{
	Private & p = to_private();
	p.data = data;
	std::printf("%s class=%p private=%p\n", __PRETTY_FUNCTION__, this, &p);
}


B::~B()
{
	std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	std::fflush(stdout);
}


int B::data() const
{
	const Private & p = to_private();
	std::printf("%s class=%p private=%p addr(data)=%p addr(foo)=%p\n", __PRETTY_FUNCTION__, this, &p, &p.data, &p.foo);
	return p.data;
}


void B::event(const int what)
{
	std::printf("%s %p %d\n", __PRETTY_FUNCTION__, this, what);
	to_private().value = what + 100;
}
