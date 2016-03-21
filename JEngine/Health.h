/******************************************************

-----------------------Health.h------------------------

	Purpose -
		To give objects durability and regeneration.



	Functionality -
		Capable of the following,


		* Return the objects current health.

			(float getCurrentHealth())

		* Return the objects max health.

			(float getMaxHealth())

		* Return the objects health regeneration rate.

			(float getRegenRate())

		* Set the objects current health.

			(void setCurrentHealth(const float&))

		* Set the objects max health.

			(void setMaxHealth(const float&))

		* Set the objects health regeneration rate.

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
	class Health : public ComponentData<Health>
	{
		float curHealth;
		float maxHealth;
		float regenRate;

	public:
		float getCurrentHealth() { return curHealth; }
		float getMaxHealth()	 { return maxHealth; }
		float getRegenRate()	 { return regenRate; }

		void setCurrentHeath(const float &hp) { curHealth = hp; }
		void setMaxHealth(const float &hp)	  { maxHealth = hp; }
		void setRegenRate(const float &hp)	  { regenRate = hp; }
	};
}