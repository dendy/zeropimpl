
#include <cstdio>
#include <memory>
#include <string>
#include <ctime>
#include <iostream>
#include <chrono>

#include "abc.h"

#include "test_pimpl.h"
#include "test_zeropimpl.h"




static const int kNumAllocs = 100000000;




void runPimpl()
{
	for ( int i = 0; i < kNumAllocs; ++i ) {
		const int r = std::rand();
		std::unique_ptr<PObject> o(r%2 ? new PObject(r) : new PWidget(r, r));
	}
}


void runZeropimpl()
{
	for ( int i = 0; i < kNumAllocs; ++i ) {
		const int r = std::rand();
		std::unique_ptr<ZObject> o(r%2 ? new ZObject(r) : new ZWidget(r, r));
	}
}




int main(int argc, char ** argv)
{
	if ( argc > 1 ) {
		std::srand(42);

		const std::string arg = argv[1];
		std::cout << arg << std::endl;

		const auto begin = std::chrono::system_clock::now();

		if ( arg == "pimpl" ) {
			runPimpl();
		} else if ( arg == "zeropimpl" ) {
			runZeropimpl();
		}

		std::chrono::duration<double> time = std::chrono::system_clock::now() - begin;
		std::cout << "time: " << time.count() << std::endl;

		return 0;
	}

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

	std::unique_ptr<A> b2(B::make(44));
	const B * const b2reader = static_cast<const B*>(b2.get());
	std::printf("b2->value=%d b2->data=%d\n", b2reader->value(), b2reader->data());
	b2->event(48);
	std::printf("b2->value=%d b2->data=%d\n", b2reader->value(), b2reader->data());

	std::unique_ptr<C> c(new C(77));
	std::printf("c->value=%d c->data=%d c->A::value()=%d\n", c->value, c->data(), c->A::value());
	A * const ca = c.get();
	ca->event(66);
	std::printf("c->value=%d c->data=%d c->A::value()=%d\n", c->value, c->data(), c->A::value());
	std::unique_ptr<A> cap = std::move(c);

	return 0;
}
