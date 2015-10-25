#pragma once

// ----------------------------------------------------------------------------
// CRefCount

class CRefCount
{
public:
    CRefCount():
		m_ulcRef(0) 
	{
		AddRef();
    }

	virtual ~CRefCount()
    {
    }

    // IUnknown methods
public:
    STDMETHOD_(ULONG, AddRef)(void)
    {
        ULONG ulcRef = (ULONG)(InterlockedIncrement((LPLONG)(&m_ulcRef)));
        return ulcRef;
    }

	STDMETHOD_(ULONG, Release)(void)
    {
        ULONG ulcRef = (ULONG)(InterlockedDecrement( (LPLONG) (&m_ulcRef) ));

        if (ulcRef == 0)
            delete this;

        return ulcRef;
    }

    // ref count
private:
    ULONG m_ulcRef;
};
