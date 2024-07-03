#include "animation/animation.h"

Animation::Animation() {
	timer.set_one_shot(false);
	// set timeout callback func
	timer.set_on_timeout(
		[&]() 
		{
			++ind_frame;
			if (ind_frame >= rect_src_list.size())
			{
				ind_frame = need_loop ? 0 : rect_src_list.size() - 1;
				// destroy
				if (!need_loop && on_finished)
				{
					on_finished();
				}
			}

		}
	);
}

void Animation::set_frame_data(
	SDL_Texture* texture, int num_h, int num_v, const std::vector<int>& idx_list
) 
{
	int width_tex, height_tex;

	this->m_texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &width_tex, &height_tex);
	width_frame = width_tex / num_h, height_frame = height_tex / num_v;

	rect_src_list.resize(idx_list.size());
	for (size_t i = 0; i < idx_list.size(); i++)
	{
		int idx = idx_list[i];
		SDL_Rect& rect_src = rect_src_list[i];

		rect_src.x = (idx % num_h) * width_frame;
		rect_src.y = (idx / num_h) * height_frame;
		rect_src.w = width_frame, rect_src.h = height_frame;
	}
}

void Animation::reset() 
{
	timer.restart();
	ind_frame = 0;
}

void Animation::set_loop(bool need_loop)
{
	this->need_loop = need_loop;
}

void Animation::set_interval(double interval)
{
	timer.set_wait_time(interval);
}

void Animation::set_on_finished(PlayCallback on_finished)
{
	this->on_finished = on_finished;
}

void Animation::on_update(double delay)
{
	timer.on_update(delay);
}

void Animation::on_render(SDL_Renderer* render, const SDL_Point& pos_dst, double angle) const
{
	static SDL_Rect rect_dst;

	rect_dst.x = pos_dst.x, rect_dst.y = pos_dst.y;
	rect_dst.w = width_frame, rect_dst.h = height_frame;

	// advanced flush functions
	// [double angle] -> rotate angle
	// [SDL_Point center] -> rotate center point, nullptr means [0.5*rect.x, 0.5*rect.y]
	// [flip] -> if need flip
	SDL_RenderCopyEx(render, m_texture, &rect_src_list[ind_frame], &rect_dst, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}
