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
		Q_KEY = SDLK_q,
		W_KEY = SDLK_w,
		E_KEY = SDLK_e,
		R_KEY = SDLK_r,
		T_KEY = SDLK_t,
		Y_KEY = SDLK_y,
		A_KEY = SDLK_a,
		D_KEY = SDLK_d,
		ENTER_KEY = SDLK_RETURN,
		ESC_KEY = SDLK_ESCAPE,
	};
};

#endif // !INPUT_SYSTEM_H
