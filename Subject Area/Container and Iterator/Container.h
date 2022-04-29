#pragma once
#include <iterator>
using namespace std;

template <typename Type>
class Node
{
public:
	Type _data = Type();
	Node* _pNext = nullptr;
	Node* _pLast = nullptr;

public:
	Node(Type data = Type(), Node* pNext = nullptr, Node* pLast = nullptr) :
		_data(data), _pNext(pNext), _pLast(pLast)
	{
		if (_pNext)
			_pNext->_pLast = this;
		if (_pLast)
			_pLast->_pNext = this;
	}

};

template <typename Type>
class _Container_Iterator
{
public:
	using iterator_category = bidirectional_iterator_tag;
	using value_type = Type;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	using size_type = size_t;

public:
	_Container_Iterator() {};
	_Container_Iterator(pointer vrtx);

	_Container_Iterator& operator++ () noexcept;
	_Container_Iterator& operator++ (int) noexcept;
	_Container_Iterator& operator-- () noexcept;
	_Container_Iterator& operator-- (int) noexcept;

	bool operator==(const _Container_Iterator<Type>& rhs);
	bool operator!=(const _Container_Iterator<Type>& rhs);
	auto& operator* ();

protected:
	pointer vrtx;

};

template <typename Type>
class _Container_Reverse_Iterator : public _Container_Iterator<Type>
{
public:
	using iterator_category = bidirectional_iterator_tag;
	using value_type = Type;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	using size_type = size_t;

public:
	_Container_Reverse_Iterator(pointer vrtx);
	
	_Container_Reverse_Iterator& operator++ () noexcept;
	_Container_Reverse_Iterator& operator++ (int) noexcept;
	_Container_Reverse_Iterator& operator-- () noexcept;
	_Container_Reverse_Iterator& operator-- (int) noexcept;

	bool operator==(const _Container_Reverse_Iterator<Type>& rhs);
	bool operator!=(const _Container_Reverse_Iterator<Type>& rhs);
	auto& operator* ();

};

// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
// Container_Iterator                                                              //
// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
template<typename Type>
inline _Container_Iterator<Type>::_Container_Iterator(pointer vrtx)
{
	this->vrtx = vrtx;
}

template<typename Type>
inline _Container_Iterator<Type>& _Container_Iterator<Type>::operator++() noexcept
{
	this->vrtx = vrtx->_pNext;
	return *this;
}

template<typename Type>
inline _Container_Iterator<Type>& _Container_Iterator<Type>::operator++(int) noexcept
{
	_Container_Iterator<Type> _Tmp = *this;
	this->vrtx = vrtx->_pNext;
	return _Tmp;
}

template<typename Type>
inline _Container_Iterator<Type>& _Container_Iterator<Type>::operator--() noexcept
{
	this->vrtx = vrtx->_pLast;
	return *this;
}

template<typename Type>
inline _Container_Iterator<Type>& _Container_Iterator<Type>::operator--(int) noexcept
{
	_Container_Iterator<Type> _Tmp = *this;
	this->vrtx = vrtx->_pLast;
	return _Tmp;
}

template<typename Type>
inline bool _Container_Iterator<Type>::operator==(const _Container_Iterator<Type>& rhs)
{
	return (vrtx->_data == rhs.vrtx->_data);
}

template<typename Type>
inline bool _Container_Iterator<Type>::operator!=(const _Container_Iterator<Type>& rhs)
{
	return (vrtx->_data != rhs.vrtx->_data);
}

template<typename Type>
inline auto& _Container_Iterator<Type>::operator*()
{
	return (this->vrtx->_data);
}

// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
// Container_Reverse_Iterator                                                      //
// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
template<typename Type>
inline _Container_Reverse_Iterator<Type>::_Container_Reverse_Iterator(pointer vrtx)
{
	this->vrtx = vrtx;
}

template<typename Type>
inline _Container_Reverse_Iterator<Type>& _Container_Reverse_Iterator<Type>::operator++() noexcept
{
	_Container_Iterator<Type>::operator--();
	return *this;
}

template<typename Type>
inline _Container_Reverse_Iterator<Type>& _Container_Reverse_Iterator<Type>::operator++(int) noexcept
{
	_Container_Reverse_Iterator<Type> _Tmp = *this;
	_Container_Iterator<Type>::operator--();
	return _Tmp;
}

template<typename Type>
inline _Container_Reverse_Iterator<Type>& _Container_Reverse_Iterator<Type>::operator--() noexcept
{
	_Container_Iterator<Type>::operator++();
	return *this;
}

template<typename Type>
inline _Container_Reverse_Iterator<Type>& _Container_Reverse_Iterator<Type>::operator--(int) noexcept
{
	_Container_Reverse_Iterator<Type> _Tmp = *this;
	_Container_Iterator<Type>::operator++();
	return _Tmp;
}

template<typename Type>
inline bool _Container_Reverse_Iterator<Type>::operator==(const _Container_Reverse_Iterator<Type>& rhs)
{
	return _Container_Iterator<Type>::operator== (rhs);
}

template<typename Type>
inline bool _Container_Reverse_Iterator<Type>::operator!=(const _Container_Reverse_Iterator<Type>& rhs)
{
	return _Container_Iterator<Type>::operator!= (rhs);
}

template<typename Type>
inline auto& _Container_Reverse_Iterator<Type>::operator*()
{
	return _Container_Iterator<Type>::operator* ();
}

// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
// Container                                                                       //
// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
template <typename Type>
class Container
{
public:
	using iterator_category = bidirectional_iterator_tag;
	using value_type = Node<Type>;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = size_t;

	using iterator = _Container_Iterator<value_type>;
	using const_iterator = _Container_Iterator<const value_type>;
	using reverse_iterator = _Container_Reverse_Iterator<value_type>;
	using const_reverse_iterator = std::reverse_iterator<_Container_Iterator<const value_type>>;

public:
	Container();
	~Container();

	iterator begin()
	{
		pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pLast != null_l)
			cur = cur->_pLast;
		return iterator(cur);
	}
	iterator end()
	{
		/*pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pNext != null)
			cur = cur->_pNext;
		return iterator(cur);*/
		return iterator(null_n);
	}
	const_iterator cbegin()
	{
		pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pLast != null_l)
			cur = cur->_pLast;
		return const_iterator(cur);
	}
	const_iterator cend()
	{
		/*pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pNext != null)
			cur = cur->_pNext;
		return const_iterator(cur);*/
		return const_iterator(null_n);
	}
	reverse_iterator rbegin()
	{
		pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pNext != null_n)
			cur = cur->_pNext;
		return reverse_iterator(cur);
	}
	reverse_iterator rend()
	{
		/*pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pNext != nullptr)
			cur = cur->_pNext;
		return reverse_iterator(cur);*/
		return reverse_iterator(null_l);
	}
	const_reverse_iterator crbegin()
	{
		pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pNext != null_n)
			cur = cur->_pNext;
		return const_reverse_iterator(cur);
	}
	const_reverse_iterator crend()
	{
		/*pointer cur = vrtx;
		while (vrtx != nullptr && cur->_pNext != nullptr)
			cur = cur->_pNext;
		return reverse_iterator(cur);*/
		return const_reverse_iterator(null_l);
	}

	void push_front(Type data);
	void push_back(Type data);
	void pop_front();
	void pop_back();
	void clear();

	size_t size();

private:
	pointer vrtx;
	pointer null_n;
	pointer null_l;
	size_t size_p;

};

template<typename Type>
inline Container<Type>::Container()
{
	vrtx = nullptr;
	null_n = new Node<Type>();
	null_l = new Node<Type>();
	size_p = 0;
}

template<typename Type>
inline Container<Type>::~Container()
{
	clear();
	delete null_l;
	delete null_n;
}

template<typename Type>
inline void Container<Type>::push_front(Type data)
{
	if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
	{
		vrtx = new Node<Type>(data, null_n, null_l);
		size_p++;
	}
	else
	{
		bool step_b = true;
		Node<Type>* cur = vrtx;

		while (step_b && cur->_pLast != null_l)
		{
			if (cur->_data == data)
			{
				cur->_data = cur->_data + data;
				step_b = false;
			}
			else
				cur = cur->_pLast;
		}
		if (step_b)
		{
			cur->_pLast = new Node<Type>(data, cur, null_l);
			size_p++;
		}
	}
}

template<typename Type>
inline void Container<Type>::push_back(Type data)
{
	if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
	{
		vrtx = new Node<Type>(data, null_n, null_l);
		size_p++;
	}
	else
	{
		bool step_b = true;
		Node<Type>* cur = vrtx;

		while (step_b && cur->_pNext != null_n)
		{
			if (cur->_data == data)
			{
				cur->_data = cur->_data + data;
				step_b = false;
			}
			else
				cur = cur->_pNext;
		}
		if (step_b)
		{
			cur->_pNext = new Node<Type>(data, null_n, cur);
			size_p++;
		}
	}
}

template<typename Type>
inline void Container<Type>::pop_front()
{
	if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
		return;

	Node<Type>* cur = vrtx;
	if (vrtx->_pLast == null_l)
	{
		vrtx = vrtx->_pNext;
		delete cur;

		if (vrtx != nullptr && vrtx != null_n)
			vrtx->_pLast = null_l;
		size_p--;
	}
	else
	{
		while (cur->_pLast->_pLast != null_l)
			cur = cur->_pLast;

		delete cur->_pLast;

		cur->_pLast = null_l;
		size_p--;
	}
}

template<typename Type>
inline void Container<Type>::pop_back()
{
	if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
		return;

	Node<Type>* cur = vrtx;
	if (vrtx->_pNext == null_n)
	{
		vrtx = vrtx->_pLast;
		delete cur;

		if (vrtx != nullptr && vrtx != null_l)
			vrtx->_pNext = null_n;
		size_p--;
	}
	else
	{
		while (cur->_pNext->_pNext != null_n)
			cur = cur->_pNext;

		delete cur->_pNext;

		cur->_pNext = null_n;
		size_p--;
	}
}

template<typename Type>
inline void Container<Type>::clear()
{
	while (vrtx != nullptr && vrtx != null_l && vrtx != null_n && vrtx->_pLast != null_l)
		vrtx = vrtx->_pLast;
	while (size_p)
		pop_front();
}

template<typename Type>
inline size_t Container<Type>::size()
{
	return size_p;
}
