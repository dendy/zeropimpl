
#pragma once

#include "lib.h"




class A
{
public:
	virtual ~A();

	int value() const;
	void setValue(int value);

	virtual void event(int) {}

protected:
	A(int value = 42);

	DECLARE_PRIVATE(A)
};





class B : public A
{
public:
	~B();

	int data() const;

	void event(int what) override;

protected:
	B(int data = 73);

	DECLARE_PRIVATE(B)
};




class C : public B
{
public:
	C(int value) :
		value(value)
	{
		std::printf("C()\n");
	}

	~C() override
	{
		std::printf("~C()\n");
	}

	void event(int what) override
	{
		std::printf("C::event() %d\n", what);
		B::event(what);
	}

	int value;
};
