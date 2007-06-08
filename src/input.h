#ifndef INPUT_H_
#define INPUT_H_
class Input
{
private:
// states
	bool m_left;
    bool m_right;
    bool m_up;
    bool m_down;
    bool m_alt;
    bool m_quit;
    bool m_die;
    bool m_fire;
    bool m_pause;
    bool m_enter;
    bool m_fullscreen;

public:

    //int event_filter(const SDL_Event *event);
    bool get_left(){return m_left;}
    bool get_right(){return m_right;}
    bool get_up(){return m_up;}
    bool get_down(){return m_down;}
    bool get_quit(){return m_quit;}
    bool get_die(){return m_die;}
    bool get_fire(){return m_fire;}
    bool get_pause(){return m_pause;}
    bool get_enter(){return m_enter;}
    void update();
    void init();

    void reset_states();
            
// begin Singleton stuff

private:

	static Input* _instance;

protected:

	Input(){};

public:

	static Input* instance();

// end Singleton stuff

};
#endif /*INPUT_H_*/
