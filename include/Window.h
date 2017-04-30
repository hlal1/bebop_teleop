#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Events.h"
#include <SDL2/SDL.h>
#include <sensor_msgs/Image.h>
#include <string>

class GUIC {
public:
	class Callback {
		virtual void call(GUIC*) = 0;
	};

	GUIC(int, int, int, int);
	~GUIC(void);

	void setText(std::string);
	std::string getText(void) const;
	void setTexture(SDL_Texture*);
	void render(SDL_Renderer*) const;
	bool inside(int, int) const;
	void callCB(void);
	void setCallback(Callback*);

private:
	SDL_Rect bounds;
	SDL_Texture* texture;
	Callback* callback;
	std::string text;
	bool dirty;
};


class Window : Listener {
public:
	Window(bool&);
	Window(void);
	~Window(void);
	void event(SDL_Event*);
	void update(void);
	void destroy(void);
	bool ok(void);

	void updateVideoTexture(const sensor_msgs::ImageConstPtr&);

private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Texture* video;
	sensor_msgs::Image image;
	std::vector<GUIC> components;
	bool video_dirty;
	bool alive;
	bool init(void);

	// Window(const Window&);
};

extern Window window;

#endif
