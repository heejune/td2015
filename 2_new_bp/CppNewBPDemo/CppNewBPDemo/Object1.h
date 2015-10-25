#ifndef __OBJECT1_H__
#define __OBJECT1_H__

#pragma once

class CObject1 : public CRefCount
{
public:
	explicit CObject1(int myint) :
		m_myint(myint)
	{}

	virtual ~CObject1()
	{
		std::cout << "CObject1 destroyed" << std::endl;
	}

	int GetMyInt()
	{
		return m_myint;
	}

	int m_myint;
};


#endif	// __OBJECT1_H__