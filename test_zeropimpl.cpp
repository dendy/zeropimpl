
#include "test_zeropimpl.h"




class ZObject::Private
{
public:
	virtual ~Private() {}

	int value;
};

DEFINE_PRIVATE(ZObject)


ZObject::ZObject(int value)
{
	to_private().value = value;
}


ZObject::~ZObject()
{
}




class ZWidget::Private : public ZObject::Private
{
public:
	int data;
};

DEFINE_PRIVATE(ZWidget)


ZWidget::ZWidget(int value, int data) :
	ZObject(value)
{
	to_private().data = data;
}


ZWidget::~ZWidget()
{
}
