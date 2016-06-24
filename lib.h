
#pragma once

#include <cstddef>
#include <memory>




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
	static const T & from_private(const Private & p) { return reinterpret_cast<const T&>(p); } \
	static T & from_private(Private & p) { return reinterpret_cast<T&>(p); } \
	const Private & to_private() const { return reinterpret_cast<const Private&>(*this); } \
	Private & to_private() { return reinterpret_cast<Private&>(*this); }




class A
{
public:
	~A();

	int value() const;
	void setValue(int value);

protected:
	A(int value = 42);

	DECLARE_PRIVATE(A)
};





class B : public A
{
public:
	~B();

	int data() const;

protected:
	B(int data = 73);

	DECLARE_PRIVATE(B)
};
