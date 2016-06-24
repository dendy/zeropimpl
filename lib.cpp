
#include "lib.h"

#include <cstdio>
#include <stdexcept>




// Memory layout is next:
//   sizeof(Private) - instance private data memory
//   size            - instance memory

template <typename T>
void * alloc(std::size_t size)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizep = sizeof(Private);

	uint8_t * const data = static_cast<uint8_t*>(std::malloc(sizep + size));

	void * const i = data + sizep;
	Private * const p = new (data) Private;

	std::printf("%s %d class=%p private=%p\n", __PRETTY_FUNCTION__, int(size), i, p);
	std::fflush(stdout);

	return i;
}


template <typename T>
void free(void * const ptr)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizep = sizeof(Private);

	uint8_t * const data = static_cast<uint8_t*>(ptr) - sizep;
	Private * const p = reinterpret_cast<Private*>(data);
	p->~Private();
	std::free(data);

	std::printf("%s class=%p private=%p\n", __PRETTY_FUNCTION__, ptr, p);
	std::fflush(stdout);
}


template <typename T>
static const T & t_from_private(const typename T::Private & p)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizep = sizeof(Private);

	return reinterpret_cast<const T&>(*(reinterpret_cast<const uint8_t*>(&p) + sizep));
}


template <typename T>
static const typename T::Private & t_to_private(const T & t)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizep = sizeof(Private);

	return reinterpret_cast<const Private&>(*(reinterpret_cast<const uint8_t*>(&t) - sizep));
}




#define DEFINE_PRIVATE(T) \
	void * T::operator new(const std::size_t size) { return alloc<T>(size); } \
	void T::operator delete(void * const ptr) { free<T>(ptr); } \
	inline const T & T::from_private(const Private & p) { return t_from_private<T>(p); } \
	inline T & T::from_private(Private & p) { return const_cast<T&>(t_from_private<T>(p)); } \
	inline const T::Private & T::to_private() const { return t_to_private<T>(*this); } \
	inline T::Private & T::to_private() { return const_cast<T::Private&>(t_to_private<T>(*this)); }




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
	~Private() override
	{
		std::printf("%s %p\n", __PRETTY_FUNCTION__, this);
	}

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


void B::event(const int what)
{
	std::printf("%s %p %d\n", __PRETTY_FUNCTION__, this, what);
	to_private().value = what + 100;
}
