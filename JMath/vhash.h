#pragma once

#include "Vector2.h"
#include <unordered_set>


namespace JTL
{
	const float feps = FLT_EPSILON;


	inline unsigned int hash(float f)
	{
		unsigned int ui, fe;
		memcpy(&ui, &f, sizeof(float));	
		memcpy(&fe, &feps, sizeof(float));

		return ui & (0xfffffff-fe); // adjust this bitmask to change the significant bits
	}
	
	
struct Vector2Hasher
{
	size_t operator()(const Vector2 &t) const
	{
		return hash(t.x) ^ (hash(t.y) << 1);
	}
};

}