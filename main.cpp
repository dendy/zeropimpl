
#include <cstdio>
#include <memory>

#include "lib.h"




int main(int argc, char ** argv)
{
	std::printf("start\n");
	std::fflush(stdout);
	std::unique_ptr<A> a(A::make(33));
	std::printf("a->value=%d\n", a->value());
	std::fflush(stdout);
	a->setValue(55);
	std::printf("a->value=%d\n", a->value());
	std::fflush(stdout);

	std::unique_ptr<B> b(B::make(87));
	std::printf("b->value=%d b->data=%d\n", b->value(), b->data());
	std::fflush(stdout);
	b->setValue(45);
	std::printf("b->value=%d b->data=%d\n", b->value(), b->data());
	std::fflush(stdout);

	return 0;
}
