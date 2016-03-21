#include "Sprite.h"
#include "ShaderLoader.h"

namespace JTL
{
	Sprite::Sprite() : offset({}), dimension({ 1,1 }), angle(0),
		frame(0), tint({ 1,1,1,1 }), shader(DEFAULT_VERT, DEFAULT_FRAG, false) {}
}