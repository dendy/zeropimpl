
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
	static const T & from_private(const Private & p); \
	static T & from_private(Private & p); \
	const Private & to_private() const; \
	Private & to_private();




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
