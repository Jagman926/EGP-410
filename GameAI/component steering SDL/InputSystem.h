#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <Trackable.h>
#include <SDL.h>
#include <SDL_keyboard.h>

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();

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

#endif // !INPUT_SYSTEM_H
