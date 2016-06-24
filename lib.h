
#pragma once

//#define USE_DEBUG

#include <cstddef>
#include <memory>




namespace Zeropimpl {








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

#ifdef USE_DEBUG
	std::printf("%s %d class=%p private=%p\n", __PRETTY_FUNCTION__, int(size), i, p);
	std::fflush(stdout);
#endif

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

#ifdef USE_DEBUG
	std::printf("%s class=%p private=%p\n", __PRETTY_FUNCTION__, ptr, p);
	std::fflush(stdout);
#endif
}


template <typename T>
static const T & fromPrivate(const typename T::Private & p)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizep = sizeof(Private);

	return reinterpret_cast<const T&>(*(reinterpret_cast<const uint8_t*>(&p) + sizep));
}


template <typename T>
static const typename T::Private & toPrivate(const T & t)
{
	typedef typename T::Private Private;
	constexpr std::size_t sizep = sizeof(Private);

	return reinterpret_cast<const Private&>(*(reinterpret_cast<const uint8_t*>(&t) - sizep));
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
