#ifndef _ANIMARION_H_
#define _ANIMARION_H_

#include "timer.h"

#include <SDL2/SDL.h>
#include <vector>
#include <functional>

/* Drawing frame data by calculating frame */
class Animation
{
public:
	typedef std::function<void()> PlayCallback;

public:
	Animation();
	~Animation() = default;

	void reset();

	// calculate rect data of current frame 
	void set_frame_data(
		SDL_Texture* texture, int num_h, int num_v, const std::vector<int>& idx_list
	);

	void set_loop(bool is_loop);

	void set_interval(double interval);

	void set_on_finished(PlayCallback on_finished);

	void on_update(double delay);

	void on_render(
		SDL_Renderer* render, const SDL_Point& pos_dst, double angle = 0
	) const;

private:
	Timer timer;
	bool need_loop = true;
	size_t ind_frame = 0;
	PlayCallback on_finished;	// animation finished event callback
	SDL_Texture* m_texture = nullptr;
	std::vector<SDL_Rect> rect_src_list;
	int width_frame = 0, height_frame = 0;
};


#endif // !_ANIMARION_H_
