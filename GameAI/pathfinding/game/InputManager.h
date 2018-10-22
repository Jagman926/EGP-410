#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <Trackable.h>
#include <SDL.h>
#include <SDL_keyboard.h>

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();

	void init();
	void cleanUp();

	void update();
private:

	enum mKeyCodes
	{
		A_KEY = SDLK_a,
		D_KEY = SDLK_d,
		F_KEY = SDLK_f,
		ESC_KEY = SDLK_ESCAPE,
	};
};


#endif // !INPUT_MANAGER

