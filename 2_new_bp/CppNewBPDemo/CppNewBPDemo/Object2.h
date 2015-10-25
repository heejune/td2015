#ifndef __OBJECT2_H__
#define __OBJECT2_H__

#pragma once

class CObject2 : public CRefCount
{
public:
	explicit CObject2(int myint) :
		m_myint(myint)
	{}

	virtual ~CObject2()
	{
		std::cout << "CObject2 destroyed" << std::endl;
	}

	int GetMyInt()
	{
		return m_myint;
	}
private:
	int m_myint;
};


#endif	// __OBJECT2_H__