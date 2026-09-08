#include "screen_state.h"

void ScreenState::update_fixed_all(Uint64 elapsed)
{
    if(m_substate == NULL || m_persistent_update)
        this->update_fixed(elapsed);
    
    if(m_substate != NULL)
    {
        m_substate->update_fixed(elapsed);
    }
}

void ScreenState::update_all(double elapsed)
{
    if(m_kill_substate_next)
    {
        this->real_kill_substate_();
        m_kill_substate_next = false;
    }

    if(m_substate_to_launch != NULL)
    {
        real_launch_substate_();
    }

    if(m_substate == NULL || m_persistent_update)
        this->update(elapsed);

    if(m_substate != NULL)
    {
        m_substate->update(elapsed);
        //DEBWARN("Persistent update: "<<m_persistent_update<<"\n");
        //DEBWARN("Persistent draw: "<<m_persistent_draw<<"\n");
    }
}

void ScreenState::draw_all()
{
    if(m_substate == NULL || m_persistent_draw)
        this->draw();

    if(m_substate != NULL)
    {
        m_substate->draw();
    }
}

void ScreenState::launch_substate(ScreenState* substate)
{
    m_substate_to_launch = substate;
    m_substate_to_launch->set_parent(this);
}

void ScreenState::kill_substate()
{
    if(m_substate != NULL)
    {
        m_kill_substate_next = true;
        
    }
}

void ScreenState::set_parent(ScreenState* parent)
{
    m_parent = parent;
}

void ScreenState::close()
{
    if(m_parent != NULL)
    {
        m_parent->kill_substate();
    }

}

void ScreenState::real_launch_substate_()
{
    if(m_substate == NULL && m_substate_to_launch != NULL)
    {
        m_substate = m_substate_to_launch;
        m_substate->create();
        m_substate_to_launch = NULL;
    }
    else
    {
        DEBWARN("Attempting to launch a substate but another one is running.");
    }
}

void ScreenState::real_kill_substate_()
{
    if(m_substate != NULL)
    {
        m_substate->deinit();
        delete m_substate;
        m_substate = NULL;
    }
}

ScreenState::~ScreenState()
{
    if(m_substate != NULL)
    {
        real_kill_substate_();
    }
}