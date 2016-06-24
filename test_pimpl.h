
#pragma once




class PObject
{
public:
	PObject(int value);
	virtual ~PObject();

protected:
	class Private;

	PObject(int value, Private & p);

protected:
	Private * p;
};




class PWidget : public PObject
{
public:
	PWidget(int value, int data);
	~PWidget() override;

protected:
	class Private;
};
