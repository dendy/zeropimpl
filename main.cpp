
#include <cstdio>
#include <memory>

#include "lib.h"




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
