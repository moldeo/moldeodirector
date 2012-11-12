#include "moDirectorIODeviceManager.h"

#ifdef MO_WIN32
  #include "SDL.h"
#else
  #include "SDL/SDL.h"
#endif

BEGIN_EVENT_TABLE( moDirectorIODeviceManager, wxEvtHandler)
	EVT_MOUSE_EVENTS( moDirectorIODeviceManager::OnMouseEvent )
	EVT_KEY_DOWN( moDirectorIODeviceManager::OnKeyDown )
	EVT_KEY_UP( moDirectorIODeviceManager::OnKeyUp )
END_EVENT_TABLE()

/*
WXK_BACK    = 8
    WXK_TAB     = 9
    WXK_RETURN  = 13
    WXK_ESCAPE  = 27
    WXK_SPACE   = 32
    WXK_DELETE  = 127

    WXK_START   = 300
    WXK_LBUTTON
    WXK_RBUTTON
    WXK_CANCEL
    WXK_MBUTTON
    WXK_CLEAR
    WXK_SHIFT
    WXK_CONTROL
    WXK_MENU
    WXK_PAUSE
    WXK_CAPITAL
    WXK_PRIOR
    WXK_NEXT
    WXK_END
    WXK_HOME
    WXK_LEFT
    WXK_UP
    WXK_RIGHT
    WXK_DOWN
    WXK_SELECT
    WXK_PRINT
    WXK_EXECUTE
    WXK_SNAPSHOT
    WXK_INSERT
    WXK_HELP
    WXK_NUMPAD0
    WXK_NUMPAD1

    WXK_NUMPAD2
    WXK_NUMPAD3
    WXK_NUMPAD4
    WXK_NUMPAD5
    WXK_NUMPAD6
    WXK_NUMPAD7
    WXK_NUMPAD8
    WXK_NUMPAD9
    WXK_MULTIPLY
    WXK_ADD
    WXK_SEPARATOR
    WXK_SUBTRACT
    WXK_DECIMAL
    WXK_DIVIDE
    WXK_F1
    WXK_F2
    WXK_F3
    WXK_F4
    WXK_F5
    WXK_F6
    WXK_F7
    WXK_F8
    WXK_F9
    WXK_F10
    WXK_F11
    WXK_F12
    WXK_F13
    WXK_F14
    WXK_F15
    WXK_F16
    WXK_F17
    WXK_F18
    WXK_F19
    WXK_F20
    WXK_F21
    WXK_F22
    WXK_F23
    WXK_F24
    WXK_NUMLOCK

    WXK_SCROLL
    WXK_PAGEUP,
    WXK_PAGEDOWN,

    WXK_NUMPAD_SPACE,
    WXK_NUMPAD_TAB,
    WXK_NUMPAD_ENTER,
    WXK_NUMPAD_F1,
    WXK_NUMPAD_F2,
    WXK_NUMPAD_F3,
    WXK_NUMPAD_F4,
    WXK_NUMPAD_HOME,
    WXK_NUMPAD_LEFT,
    WXK_NUMPAD_UP,
    WXK_NUMPAD_RIGHT,
    WXK_NUMPAD_DOWN,
    WXK_NUMPAD_PRIOR,
    WXK_NUMPAD_PAGEUP,
    WXK_NUMPAD_NEXT,
    WXK_NUMPAD_PAGEDOWN,
    WXK_NUMPAD_END,
    WXK_NUMPAD_BEGIN,
    WXK_NUMPAD_INSERT,
    WXK_NUMPAD_DELETE,
    WXK_NUMPAD_EQUAL,
    WXK_NUMPAD_MULTIPLY,

    WXK_NUMPAD_ADD,
    WXK_NUMPAD_SEPARATOR,
    WXK_NUMPAD_SUBTRACT,
    WXK_NUMPAD_DECIMAL,
    WXK_NUMPAD_DIVIDE,

    // the following key codes are only generated under Windows currently
    WXK_WINDOWS_LEFT,
    WXK_WINDOWS_RIGHT,
    WXK_WINDOWS_MENU,
    WXK_COMMAND,

    // Hardware-specific buttons
    WXK_SPECIAL1 = 193,
    WXK_SPECIAL2,
    WXK_SPECIAL3,
    WXK_SPECIAL4,
    WXK_SPECIAL5,
    WXK_SPECIAL6,
    WXK_SPECIAL7,
    WXK_SPECIAL8,
    WXK_SPECIAL9,
    WXK_SPECIAL10,
    WXK_SPECIAL11,
    WXK_SPECIAL12,
    WXK_SPECIAL13,

    WXK_SPECIAL14,
    WXK_SPECIAL15,
    WXK_SPECIAL16,
    WXK_SPECIAL17,
    WXK_SPECIAL18,
    WXK_SPECIAL19,
    WXK_SPECIAL20
*/

moDirectorIODeviceManager::moDirectorIODeviceManager() : moIODeviceManager() {

}

moDirectorIODeviceManager::~moDirectorIODeviceManager() {

}

/*
type 	SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP
button 	The mouse button index(SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT, SDL_BUTTON_WHEELUP, SDL_BUTTON_WHEELDOWN)
state 	SDL_PRESSED or SDL_RELEASED
x, y 	The X/Y coordinates of the mouse at press/release time
*/
void
moDirectorIODeviceManager::OnMouseEvent( wxMouseEvent &event) {

	//translates wxMouseEvents to SDL mouse events type(internal events of Moldeo are based on SDL )
	//accumulate mouse events( to pass to event list later )

	//MOTION
	if( event.Moving() || event.Dragging() ) {
		GetEvents()->Add( MO_IODEVICE_MOUSE, SDL_MOUSEMOTION, event.m_x - m_MouseX/*rel*/, event.m_y - m_MouseY/*rel*/, event.m_x, event.m_y);
	}

	m_MouseX = event.m_x;
	m_MouseY = event.m_y;

	//MOUSEBUTTONDOWN
	if( event.LeftDown() ) {
		GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT , event.m_x, event.m_y);
	}
	if( event.MiddleDown() ) {
		GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONDOWN, SDL_BUTTON_MIDDLE , event.m_x, event.m_y);
	}
	if( event.RightDown() ) {
		GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONDOWN, SDL_BUTTON_RIGHT , event.m_x, event.m_y);
	}
	//MOUSEBUTTONUP
	if( event.LeftUp() ) {
		GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT , event.m_x, event.m_y);
	}
	if( event.MiddleUp() ) {
		GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONUP, SDL_BUTTON_MIDDLE , event.m_x, event.m_y);
	}
	if( event.RightUp() ) {
		GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONUP, SDL_BUTTON_RIGHT , event.m_x, event.m_y);
	}
}
/*
type 	SDL_KEYDOWN or SDL_KEYUP
state 	SDL_PRESSED or SDL_RELEASED
keysym 	Contains key press information in a SDL_keysym structure

		scancode 	Hardware specific scancode
		sym 	SDL virtual keysym
		mod 	Current key modifiers
		unicode 	Translated character
mod
KMOD_NONE 	No modifiers applicable
KMOD_LSHIFT 	Left Shift is down
KMOD_RSHIFT 	Right Shift is down
KMOD_LCTRL 	Left Control is down
KMOD_RCTRL 	Right Control is down
KMOD_LALT 	Left Alt is down
KMOD_RALT 	Right Alt is down
KMOD_LMETA 	Left Meta is down
KMOD_RMETA 	Right Meta is down
KMOD_NUM 	Numlock is down
KMOD_CAPS 	Capslock is down
KMOD_MODE 	Mode is down
KMOD_CTRL 	A Control key is down
KMOD_SHIFT 	A Shift key is down
KMOD_ALT 	An Alt key is down
KMOD_META 	A Meta key is down
*/
void moDirectorIODeviceManager::OnKeyDown( wxKeyEvent &event ) {

	SDLKey sym = SDLK_UNKNOWN;
	SDLMod mod = KMOD_NONE;

	//wxMessageBox( moText2Wx( IntToStr(event.GetKeyCode()) ) ) ;
    cout << event.GetKeyCode() << endl;

	if(event.ShiftDown())
		mod =(SDLMod)((int)mod | KMOD_SHIFT );
	if(event.ControlDown()) {
		mod =(SDLMod)((int)mod | KMOD_CTRL );
		MODebug2->Push( "keycode: " + IntToStr(event.GetKeyCode()) );
		MODebug2->Push( "event.ControlDown(): OK" );
	}

	//event.key.keysym.sym
	if( event.GetKeyCode() == WXK_SHIFT ) {
		sym = SDLK_LSHIFT;
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
	} else
	if( event.GetKeyCode() == 308 ) {
		sym = SDLK_LCTRL;
		MODebug2->Push( "sym: SDLK_LCTRL"+IntToStr(sym) );
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
	} else
	if((int)(SDLK_BACKSPACE)  <= event.GetKeyCode() && event.GetKeyCode() <=(int)(SDLK_DELETE) ) {
		if( 65<=event.GetKeyCode() && event.GetKeyCode()<=90) {
			sym = SDLKey((int)event.GetKeyCode() + 32);
		} else {
			sym =(SDLKey)(int)event.GetKeyCode();
		}
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
	} else
	if(WXK_F1  <= event.GetKeyCode() && event.GetKeyCode() <= WXK_F15 ) {
		sym = SDLKey((int)SDLK_F1 +((int)event.GetKeyCode() -(int)WXK_F1 ));
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
	} else
	if( WXK_NUMPAD0  <= event.GetKeyCode() && event.GetKeyCode() <= WXK_NUMPAD9 ) {
		sym = SDLKey((int)SDLK_KP0 +((int)event.GetKeyCode() -(int)WXK_NUMPAD0 ));
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
	} else
	switch(event.GetKeyCode()) {
		/*NUMPAD*/
		case WXK_NUMPAD_MULTIPLY:
			sym = SDLK_KP_MULTIPLY;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_DIVIDE:
			sym = SDLK_KP_DIVIDE;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_SUBTRACT:
			sym = SDLK_KP_MINUS;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_DECIMAL:
			sym = SDLK_KP_PERIOD;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_ADD:
			sym = SDLK_KP_PLUS;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_ENTER:
			sym = SDLK_KP_ENTER;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		/*SPECIALS*/
		case WXK_PAGEUP:
		case WXK_NUMPAD_PAGEUP:
			sym = SDLK_PAGEUP;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_PAGEDOWN:
		case WXK_NUMPAD_PAGEDOWN:
			sym = SDLK_PAGEDOWN;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_LEFT:
			sym = SDLK_LEFT;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_UP:
			sym = SDLK_UP;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_RIGHT:
			sym = SDLK_RIGHT;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_DOWN:
			sym = SDLK_DOWN;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		case WXK_NUMLOCK:
			sym = SDLK_NUMLOCK;
			mod = KMOD_NUM;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYDOWN, sym , mod ,0,0);
			break;
		default:
			break;
	}
}

void moDirectorIODeviceManager::OnKeyUp( wxKeyEvent &event ) {

	SDLKey sym = SDLK_UNKNOWN;
	SDLMod mod = KMOD_NONE;

	if(event.ShiftDown())
		mod =(SDLMod)((int)mod | KMOD_SHIFT );
	if(event.ControlDown()) {
		mod =(SDLMod)((int)mod | KMOD_CTRL );
		MODebug2->Push( "keycode UP: " + IntToStr(event.GetKeyCode()) );
		MODebug2->Push( "event.ControlDown(): Still Down" );
	}

	//event.key.keysym.sym
	if( event.GetKeyCode() == WXK_SHIFT ) {
		sym = SDLK_LSHIFT;
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
	} else
	if( event.GetKeyCode() == 308 ) {
		sym = SDLK_LCTRL;
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
	} else
	if((int)(SDLK_BACKSPACE)  <= event.GetKeyCode() && event.GetKeyCode() <=(int)(SDLK_DELETE) ) {
		if( 65<=event.GetKeyCode() && event.GetKeyCode()<=90) {
			sym = SDLKey((int)event.GetKeyCode() + 32);
		} else {
			sym =(SDLKey)(int)event.GetKeyCode();
		}
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
	} else
	if( WXK_F1  <= event.GetKeyCode() && event.GetKeyCode() <= WXK_F15 ) {
		sym = SDLKey((int)SDLK_F1 +((int)event.GetKeyCode() -(int)WXK_F1 ));
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
	} else
	if( WXK_NUMPAD0  <= event.GetKeyCode() && event.GetKeyCode() <= WXK_NUMPAD9 ) {
		sym = SDLKey((int)SDLK_KP0 +((int)event.GetKeyCode() -(int)WXK_NUMPAD0 ));
		GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
	} else
	switch(event.GetKeyCode()) {
		/*NUMPAD*/
		case WXK_NUMPAD_MULTIPLY:
			sym = SDLK_KP_MULTIPLY;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_DIVIDE:
			sym = SDLK_KP_DIVIDE;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_SUBTRACT:
			sym = SDLK_KP_MINUS;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_DECIMAL:
			sym = SDLK_KP_PERIOD;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_ADD:
			sym = SDLK_KP_PLUS;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_NUMPAD_ENTER:
			sym = SDLK_KP_ENTER;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		/*SPECIALS*/
		case WXK_PAGEUP:
		case WXK_NUMPAD_PAGEUP:
			sym = SDLK_PAGEUP;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_PAGEDOWN:
		case WXK_NUMPAD_PAGEDOWN:
			sym = SDLK_PAGEDOWN;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_LEFT:
			sym = SDLK_LEFT;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_UP:
			sym = SDLK_UP;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_RIGHT:
			sym = SDLK_RIGHT;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_DOWN:
			sym = SDLK_DOWN;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		case WXK_NUMLOCK:
			sym = SDLK_NUMLOCK;
			mod = KMOD_NUM;
			GetEvents()->Add( MO_IODEVICE_KEYBOARD, SDL_KEYUP, sym , mod ,0,0);
			break;
		default:
			break;
	}


}

void
moDirectorIODeviceManager::PollEvents() {

	//m_AuxEvents.First();

	SDL_Event event;

	   //SDL_KEYDOWN,			// Keys pressed
       //SDL_KEYUP,				// Keys released
       //SDL_MOUSEMOTION,		// Mouse moved
       //SDL_MOUSEBUTTONDOWN,	// Mouse button pressed
       //SDL_MOUSEBUTTONUP,		// Mouse button released
/*
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
				case SDL_MOUSEMOTION:
					GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEMOTION, event.motion.xrel, event.motion.yrel, event.motion.x, event.motion.y);
					break;
				case SDL_MOUSEBUTTONDOWN:
					GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONDOWN, event.button.button, event.button.x, event.button.y);
					break;
				case SDL_MOUSEBUTTONUP:
					GetEvents()->Add(MO_IODEVICE_MOUSE,SDL_MOUSEBUTTONUP, event.button.button, event.button.x, event.button.y);
					break;
				case SDL_KEYDOWN:
					// Ignore ALT-TAB for windows
					if((event.key.keysym.sym == SDLK_LALT) ||
						(event.key.keysym.sym == SDLK_RALT) ||
						(event.key.keysym.sym == SDLK_TAB)) {
						break;
					}
					GetEvents()->Add(MO_IODEVICE_KEYBOARD,SDL_KEYDOWN, event.key.keysym.sym, event.key.keysym.mod,0,0);
					break;

				case SDL_KEYUP:
					if((event.key.keysym.sym == SDLK_LALT) ||
						(event.key.keysym.sym == SDLK_RALT) ||
						(event.key.keysym.sym == SDLK_TAB)) {
						break;
					}
					GetEvents()->Add(MO_IODEVICE_KEYBOARD,SDL_KEYUP, event.key.keysym.sym, event.key.keysym.mod,0,0);
					break;
				default:
					break;
		}
	}
*/
}

