
#include "FramedImage.h"

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

FramedImage::FramedImage(Texture* tex, int row, int column, float time, int numframes_ = 0) : frametime(time), tex_(tex), row_(row), column_(column), numframes(numframes_), repeat_(false), repeating_(false)
{
	m_clip.w = tex_->width() / column;
	m_clip.h = tex_->height() / row;
	initime = sdlutils().currRealTime();
}
//
FramedImage::~FramedImage()
{
}

void FramedImage::select_sprite(int x, int y)
{
	m_clip.x = x * m_clip.w;
	m_clip.y = y * m_clip.h;
}

void FramedImage::render(Transform* tr_)
{
	if (!repeating_)
		select_sprite(i, j);

	if (!repeating_ && sdlutils().currRealTime() - initime >= frametime / numframes) {

		select_sprite(i, j);

		currentnumframes++;
		if (i < column_ - 1) {
			i++;
		}
		else {
			i = 0;
			j++;
		}
		if ((currentnumframes >= numframes - 1)) {
			j = 0; i = 0; currentnumframes = 0;
			if (repeat_) {
				repeating_ = true;
			}

			//repeating_ = false;
		}

		initime = sdlutils().currRealTime();
	}

	float multiplierX = 1.4f;
	float multiplierY = 1.3f;
	float xOffset = -10;
	float yOffset = -20;

	// Aplicar propiedades
	SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_ * multiplierX,
		tr_->height_ * multiplierY);
	dest.x += xOffset;
	dest.y += yOffset;

	assert(tex_ != nullptr);
	tex_->render(m_clip, dest, tr_->rot_, nullptr);
}
