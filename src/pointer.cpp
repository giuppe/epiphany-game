#include "pointer.h"
#include "entity.h"

Ntt_pointer::Ntt_pointer(): m_referenced(false), m_pointer(0)
{

}

Ntt_pointer::Ntt_pointer(Entity& ntt): m_pointer(&ntt), m_referenced(true)
{

}

Ntt_pointer::Ntt_pointer(const Ntt_pointer& cpy)
{
    m_pointer = cpy.m_pointer;
    m_referenced = cpy.m_referenced;
    DEBOUT("NTT_pointer::copyconstr()\n");
}

Ntt_pointer::~Ntt_pointer()
{
	//	DEBOUT("Calling Ntt_pointer::dtor()...\n");
    unlink();

}

Entity* Ntt_pointer::get_pointer()
{
	if(m_referenced==true)
	{
		return m_pointer;
	}
	DEBOUT("Warning: using non-referenced pointer");
	return 0;
}

void Ntt_pointer::point_to(Entity& ntt)
{
    m_pointer = &ntt;
    m_referenced = true;
}    

void Ntt_pointer::unlink()
{
    m_pointer = 0;
    m_referenced = false;
}

void Ntt_pointer::remove()
{
    if( (m_pointer != 0) && m_referenced)
			delete m_pointer;
		else
			unlink();

    m_pointer = 0;
    m_referenced = false;
}
/*
bool Ntt_pointer::is_referenced()
{
    return m_referenced;
}
*/
/*
Entity*  Ntt_pointer::operator->() const
{
    if(m_referenced)
			return m_pointer;
		return 0;
} */
/*
Ntt_pointer::~Ntt_pointer()
{
	if(m_referenced)
		delete m_pointer;
}
*/

