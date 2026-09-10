
#include "dephine.h"
#include "screen_state.h"
#include <vector>
#include <string>

class Loading_State : public ScreenState
{
    private:
        Sint32 m_timeout = 1940;

    public:
        void create();

        void update(double elapsed);

        void deinit(){};

        void draw();
};