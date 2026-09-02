
#include "dephine.h"
#include "screen_state.h"
#include <vector>
#include <string>

class CreditsState : public ScreenState
{
    private:
        std::vector<std::string> credits;

    public:
        void create();

        void update(double elapsed);

        void deinit(){};

        void draw();
};