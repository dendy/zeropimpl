
#pragma once

//#define USE_DEBUG

#include <cstddef>
#include <memory>




namespace Zeropimpl {




// Memory layout is next:
//   sizeof(size_t)  - size of private data
//   sizeof(Private) - instance private data memory
//   sizeof(size_t)  - size of private data (again)
//   size            - instance memory

template <typename T>
void * alloc(std::size_t size)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizeo = sizeof(std::size_t);
	constexpr std::size_t sizep = sizeof(Private);

	uint8_t * const data = static_cast<uint8_t*>(std::malloc(sizeo + sizep + sizeo + size));

	reinterpret_cast<std::size_t&>(*data) = sizep;
	reinterpret_cast<std::size_t&>(*(data + sizeo + sizep)) = sizep;
	void * const i = data + sizeo + sizep + sizeo;
	Private * const p = new (data + sizeo) Private;

#ifdef USE_DEBUG
	std::printf("%s %d class=%p private=%p sizep=%d\n", __PRETTY_FUNCTION__, int(size), i, p, int(sizep));
	std::fflush(stdout);
#endif

	return i;
}


template <typename T>
void free(void * const ptr)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizeo = sizeof(std::size_t);
	constexpr std::size_t sizep = sizeof(Private);

	uint8_t * const data = static_cast<uint8_t*>(ptr) - sizeo - sizep - sizeo;
	Private * const p = reinterpret_cast<Private*>(data + sizeo);
	p->~Private();
	std::free(data);

#ifdef USE_DEBUG
	std::printf("%s class=%p private=%p\n", __PRETTY_FUNCTION__, ptr, p);
	std::fflush(stdout);
#endif
}


template <typename T>
static const T & fromPrivate(const typename T::Private & p)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizeo = sizeof(std::size_t);

	const std::size_t sizep = reinterpret_cast<const std::size_t&>(*(reinterpret_cast<const uint8_t*>(&p) - sizeo));

	return reinterpret_cast<const T&>(*(reinterpret_cast<const uint8_t*>(&p) + sizep + sizeo));
}


template <typename T>
static const typename T::Private & toPrivate(const T & t)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizeo = sizeof(std::size_t);

	const std::size_t sizep = reinterpret_cast<const std::size_t&>(*(reinterpret_cast<const uint8_t*>(&t) - sizeo));

	const Private & p = reinterpret_cast<const Private&>(*(reinterpret_cast<const uint8_t*>(&t) - sizeo - sizep));

#ifdef USE_DEBUG
	std::printf("%s class=%p private=%p sizep=%d\n", __PRETTY_FUNCTION__, &t, &p, int(sizep));
	std::fflush(stdout);
#endif

	return p;
}




#define DECLARE_PRIVATE(T) \
public: \
	void * operator new(std::size_t size); \
	void operator delete(void * ptr); \
\
	class Private; \
\
	template <typename... Args> \
	static std::unique_ptr<T> make(Args... args) \
	{ \
		return std::unique_ptr<T>(new T(std::forward<Args...>(args...))); \
	} \
\
private: \
	static const T & from_private(const Private & p); \
	static T & from_private(Private & p); \
	const Private & to_private() const; \
	Private & to_private();


#define DEFINE_PRIVATE(T) \
	void * T::operator new(const std::size_t size) { return Zeropimpl::alloc<T>(size); } \
	void T::operator delete(void * const ptr) { Zeropimpl::free<T>(ptr); } \
	inline const T & T::from_private(const Private & p) { return Zeropimpl::fromPrivate<T>(p); } \
	inline T & T::from_private(Private & p) { return const_cast<T&>(Zeropimpl::fromPrivate<T>(p)); } \
	inline const T::Private & T::to_private() const { return Zeropimpl::toPrivate<T>(*this); } \
	inline T::Private & T::to_private() { return const_cast<T::Private&>(Zeropimpl::toPrivate<T>(*this)); }




} // Zeropimpl
