// TODO : Documentation

#pragma once
#include <vector>
#include <queue>

namespace JTL
{
	template<typename T>
	struct Handle
	{
		int index;
		Handle(int i = -1) : index(i), dataref(&ComponentData<T>::getData()) {}

		T *operator->()		  { return &ComponentData<T>::at(index); }
		T *operator->() const { return &ComponentData<T>::at(index); }
		T  operator* () const { return  ComponentData<T>::at(index); }
		T &operator* ()		  { return  ComponentData<T>::at(index); }
		T *operator& ()		  { return &ComponentData<T>::at(index); }

			operator int()		 { return index; }
		operator int() const { return index; }
	private:
		std::vector<T> *dataref;
	};

	template<typename T>
	class ComponentData
	{
		int index;
		bool isVacant;

		static std::queue<int> &getQueue() { static std::queue<int> q; return q; }

	public:

#pragma region StaticFunctions

		static std::vector<T> &getData() { static std::vector<T> d; return d; }

		static T &at(int i) { return getData()[i]; }

		static void free(int i)
		{
			if (i > -1 && !at(i).isVacant)
			{
				at(i).onFree();
				getQueue().push(i);
				at(i).isVacant = true;
				at(i).index = -1;
			}
		}

		static Handle<T> make()
		{
			int i = -1;

			if (getQueue().size() > 0)
			{
				i = getQueue().front();
				getQueue().pop();
				at(i) = T();
			}
			else
			{
				i = getData().size();
				getData().emplace_back();
			}

			at(i).index = i;
			at(i).isVacant = false;
			return Handle<T>{i};
		}

#pragma endregion

#pragma region Functions

		int getIndex() { return index; }

		bool isValid() { return !isVacant; };

		virtual void onFree() {}

#pragma endregion

	};
}