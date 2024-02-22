#ifndef ENHANCEDLIST_HPP
#define ENHANCEDLIST_HPP

#include <iostream>
#include <list>

template <class T>
using Filter = bool(*)(T);

template <class T>
using Map = void(*)(T&);
	
template <class F, class V>
struct Where
{
	F m_filter;
	Where(F _f) : m_filter(_f) {}
	bool operator()(const V& _v) { return m_filter(_v); }
};

template <class M, class V>
struct Then
{
	M m_map;
	Then(M _m) : m_map(_m) {}
	void operator()(V& _v) { m_map(_v); }
};

template <class T>
class EnhancedList
{
private:
	std::list<T> m_list;

	std::list<Filter<T>> m_filters;
	std::list<Map<T>> m_maps;

	EnhancedList(const std::list<T>& _list) : m_list(_list) {}
public:

	EnhancedList& operator|(const Filter<T>&& _filter)
	{
		m_filters.push_back(_filter);
		return *this;
	}

	EnhancedList& operator|(const Map<T>&& _map)
	{
		m_maps.push_back(_map);
		return *this;
	}

	std::list<T> ToList()
	{
		std::list<T> returnedList;

		for (T& t : m_list)
		{
			bool shouldAdd = true;

			for (Filter<T> filter : m_filters)
			{
				if (!filter(t))
				{
					shouldAdd = false;
					break;
				}
			}

			if (shouldAdd)
			{
				for (Map<T> map : m_maps)
				{
					map(t);
				}

				returnedList.push_back(t);
			}
		}

		return returnedList;
	}

	void ForEach(const Map<T>& _map)
	{
		std::list<T> list = ToList();

		for (T& t : list)
		{
			_map(t);
		}
	}

	template <class T>
	static EnhancedList<T> of(const std::list<T>& _list)
	{
		return EnhancedList(_list);
	}
};

#endif