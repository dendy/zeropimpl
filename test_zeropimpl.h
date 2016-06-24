
#pragma once

#include "lib.h"




class ZObject
{
public:
	ZObject(int value);
	virtual ~ZObject();

	DECLARE_PRIVATE(ZObject)
};




class ZWidget : public ZObject
{
public:
	ZWidget(int value, int data);
	~ZWidget() override;

	DECLARE_PRIVATE(ZWidget)
};
