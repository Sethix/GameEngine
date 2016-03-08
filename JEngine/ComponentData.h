#pragma once
#include <vector>
#include <queue>

namespace JTL
{

	template<typename T>
	struct Handle
	{
		int index;
		Handle(int i = -1) : index(i) {}

		T *operator->() { return &ComponentData<T>::at(index); }
		T *operator->() const { return &ComponentData<T>::at(index); }
		T *operator& () const { return &ComponentData<T>::at(index); }
		T  operator* () const { return  ComponentData<T>::at(index); }

		operator int() { return index; }
		operator int() const { return index; }
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
			if (!at(i).isVacant)
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

		bool isValid() { return !isVacant };

		virtual void onFree() {}

#pragma endregion

	};

}