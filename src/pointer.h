// -*- C++ -*-

#ifndef POINTER_H
#define POINTER_H

class Entity;

class Ntt_pointer
{
private:
    Entity* m_pointer;
    bool m_referenced;

public:
    Ntt_pointer();
    Ntt_pointer(Entity*);
    Ntt_pointer(Entity&);
    Ntt_pointer(const Ntt_pointer&);
    ~Ntt_pointer();

    void point_to(Entity&);
    void unlink(); // unlink
    void remove(); // delete pointed object
    bool is_referenced()
    {
    return m_referenced;
    }
    Entity* get_pointer();

    Entity* operator->() const
    {
      if(m_referenced)
        return m_pointer;
      return 0;
    }
};

#endif // POINTER_H
