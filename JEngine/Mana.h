/******************************************************

------------------------Mana.h-------------------------

	Purpose -
		To give objects a resource to draw from.



	Functionality -
		Capable of the following,


		* Return the objects current mana.

			(float getCurrentMana())

		* Return the objects max mana.

			(float getMaxMana())

		* Return the objects mana regeneration rate.

			(float getRegenRate())

		* Set the objects current mana.

			(void setCurrentMana(const float&))

		* Set the objects max mana.

			(void setMaxMana(const float&))

		* Set the objects mana regeneration rate.

			(void setRegenRate(const float&))



	Credits -
		Justin T Hamm -
			- Creator of JTL -

		Esmeralda Salamone -
			- Programming Instructor -

		Terry Nguyen -
			- Assistant Instructor -



	License -
		The MIT License (MIT)

			Copyright (c) [2016] [Justin T Hamm]

			Permission is hereby granted, free of charge, to any person obtaining a copy
			of this software and associated documentation files (the "Software"), to deal
			in the Software without restriction, including without limitation the rights
			to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
			copies of the Software, and to permit persons to whom the Software is
			furnished to do so, subject to the following conditions:

			The above copyright notice and this permission notice shall be included in all
			copies or substantial portions of the Software.

			THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
			IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
			FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
			AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
			LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
			OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
			SOFTWARE.


*******************************************************/

#pragma once
#include "ComponentData.h"

namespace JTL
{
	class Mana : public ComponentData<Mana>
	{
		float curMana;
		float maxMana;
		float regenRate;

	public:
		float getCurrentMana() { return curMana;   }
		float getMaxMana()	   { return maxMana;   }
		float getRegenRate()   { return regenRate; }

		void setCurrentMana(float mp) { curMana = mp;   }
		void setMaxMana(float mp)	  { maxMana = mp;   }
		void setRegenRate(float mp)   { regenRate = mp; }
	};
}