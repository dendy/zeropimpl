
#include "test_pimpl.h"




class PObject::Private
{
public:
	virtual ~Private() {}

	int value;
};


PObject::PObject(int value) :
	p(new Private)
{
	p->value = value;
}


PObject::PObject(int value, Private & p) :
	p(&p)
{
	this->p->value = value;
}


PObject::~PObject()
{
	delete p;
}




class PWidget::Private : public PObject::Private
{
public:
	int data;
};


PWidget::PWidget(int value, int data) :
	PObject(value, *new PWidget::Private)
{
	Private * const p = static_cast<Private*>(this->p);
	p->data = data;
}


PWidget::~PWidget()
{
}
