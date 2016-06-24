
#include <cstdio>
#include <memory>

#include "lib.h"




int main(int argc, char ** argv)
{
	std::unique_ptr<A> a(new A(33));
	std::printf("a->value=%d\n", a->value());
	a->setValue(55);
	std::printf("a->value=%d\n", a->value());

//	A a2;

	std::unique_ptr<B> b(new B(87));
	std::printf("b->value=%d b->data=%d\n", b->value(), b->data());
	b->setValue(45);
	std::printf("b->value=%d b->data=%d\n", b->value(), b->data());

	return 0;
}
