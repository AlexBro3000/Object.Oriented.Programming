#pragma once
#include <iterator>
#include <limits>
using namespace std;

// Node
template <typename Type>
class Node
{
public:
	Type _data;
	Node* _pNext;
	Node* _pLast;

public:
	Node(Type data = Type(), Node* pNext = nullptr, Node* pLast = nullptr) :
		_data(data), _pNext(pNext), _pLast(pLast)
	{
		if (_pNext)
			_pNext->_pLast = this;
		if (_pLast)
			_pLast->_pNext = this;
	}
	Node(Type data, const Node* pNext, const Node* pLast) :
		_data(data)
	{
		_pNext = (Node*)pNext;
		_pLast = (Node*)pLast;
		_pNext->_pLast = this;
		_pLast->_pNext = this;
	}

	void insert_Node(Node<Type>* vrtx)
	{
		_pLast->_pNext = vrtx;
		vrtx->_pLast = _pLast;
		_pLast = vrtx;
		vrtx->_pNext = this;
	}
	void r_insert_Node(Node<Type>* vrtx)
	{
		_pNext->_pLast = vrtx;
		vrtx->_pNext = _pNext;
		_pNext = vrtx;
		vrtx->_pLast = this;
	}

};

// Compare
template <typename Type>
bool smaller(Type _Left, Type _Right)
{
	return _Left > _Right;
}

template <typename Type>
bool more(Type _Left, Type _Right)
{
	return _Left < _Right;
}

template <typename Type>
bool smaller_equals(Type _Left, Type _Right)
{
	return _Left >= _Right;
}

template <typename Type>
bool more_equals(Type _Left, Type _Right)
{
	return _Left <= _Right;
}

// Allocator
template <typename Type>
struct MyAlloc : allocator<Type>
{
	Type* allocate(size_t size)
	{
		return new Type[size];
	}
};

// Iterator
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
	_Container_Iterator() = default;
	_Container_Iterator(pointer vrtx);
	_Container_Iterator(const _Container_Iterator& other);
	~_Container_Iterator();

	void operator=(const _Container_Iterator<Type>& rhs);
	void swap(_Container_Iterator<Type>& rhs) noexcept;

	_Container_Iterator& operator++ () noexcept;
	_Container_Iterator& operator++ (int) noexcept;
	_Container_Iterator& operator-- () noexcept;
	_Container_Iterator& operator-- (int) noexcept;

	bool operator==(const _Container_Iterator<Type>& rhs);
	bool operator!=(const _Container_Iterator<Type>& rhs);
	auto& operator* ();

	pointer getVRTX()
	{
		return vrtx;
	}

protected:
	pointer vrtx;
	bool link;

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
	_Container_Reverse_Iterator() = default;
	_Container_Reverse_Iterator(pointer vrtx);
	~_Container_Reverse_Iterator();

	void swap(_Container_Reverse_Iterator<Type>& rhs) noexcept;
	
	_Container_Reverse_Iterator& operator++ () noexcept;
	_Container_Reverse_Iterator& operator++ (int) noexcept;
	_Container_Reverse_Iterator& operator-- () noexcept;
	_Container_Reverse_Iterator& operator-- (int) noexcept;

	bool operator==(const _Container_Reverse_Iterator<Type>& rhs);
	bool operator!=(const _Container_Reverse_Iterator<Type>& rhs);
	auto& operator* ();

	pointer getVRTX()
	{
		return _Container_Iterator<Type>::getVRTX();
	}
};

// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
// Container_Iterator                                                              //
// *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** //
template<typename Type>
inline _Container_Iterator<Type>::_Container_Iterator(pointer vrtx)
{
	this->vrtx = vrtx;
	this->link = true;
}

template<typename Type>
inline _Container_Iterator<Type>::_Container_Iterator(const _Container_Iterator& other)
{
	vrtx = other.vrtx;
	//vrtx = new Type(*other.vrtx);
	link = false;
}

template<typename Type>
inline _Container_Iterator<Type>::~_Container_Iterator()
{
	/*if(!link)
		delete vrtx;*/
}

template<typename Type>
void _Container_Iterator<Type>::operator=(const _Container_Iterator<Type>& rhs)
{
	this->vrtx = rhs.vrtx;
}

template<typename Type>
inline void _Container_Iterator<Type>::swap(_Container_Iterator<Type>& rhs) noexcept
{
	if (vrtx == nullptr && rhs.vrtx == nullptr)
		return;
	if (vrtx->_pLast != nullptr && vrtx->_pNext != nullptr && rhs.vrtx->_pLast != nullptr && rhs.vrtx->_pNext != nullptr)
	{
		pointer ltemp_r = vrtx->_pNext;
		pointer ltemp_l = vrtx->_pLast;
		pointer rtemp_r = rhs.vrtx->_pNext;
		pointer rtemp_l = rhs.vrtx->_pLast;

		ltemp_r->_pLast = rhs.vrtx;
		ltemp_l->_pNext = rhs.vrtx;
		rtemp_r->_pLast = vrtx;
		rtemp_l->_pNext = vrtx;

		vrtx->_pNext = rtemp_r;
		vrtx->_pLast = rtemp_l;
		rhs.vrtx->_pNext = ltemp_r;
		rhs.vrtx->_pLast = ltemp_l;

		if (vrtx->_pLast == vrtx)
			vrtx->_pLast = rhs.vrtx;
		if (rhs.vrtx->_pNext == rhs.vrtx)
			rhs.vrtx->_pNext = vrtx;
	}
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
	_Container_Iterator<Type> _Tmp;
	_Tmp = *this;
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
	_Container_Iterator<Type> _Tmp;
	_Tmp = *this;
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
	if (vrtx != nullptr && rhs.vrtx != nullptr)
		return (vrtx->_data != rhs.vrtx->_data);
	return false;
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
	this->link = true;
}

template<typename Type>
inline _Container_Reverse_Iterator<Type>::~_Container_Reverse_Iterator()
{
	_Container_Iterator<Type>::~_Container_Iterator();
}

template<typename Type>
inline void _Container_Reverse_Iterator<Type>::swap(_Container_Reverse_Iterator<Type>& rhs) noexcept
{
	_Container_Iterator<Type>::swap(rhs);
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
	_Container_Reverse_Iterator<Type> _Tmp;
	_Tmp = *this;
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
	_Container_Reverse_Iterator<Type> _Tmp;
	_Tmp = *this;
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
template <typename Type, class _Alloc = allocator<Type>>
class Container
{
public:
	using iterator_category = bidirectional_iterator_tag;
	using value_type = Node<Type>;
	using const_value_type = Node<const Type>;
	using allocator_type = _Alloc;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const_value_type*;
	using reference = Type&;
	using const_reference = const Type&;        
	using size_type = size_t;

	using iterator = _Container_Iterator<value_type>;
	using const_iterator = _Container_Iterator<const_value_type>;
	using reverse_iterator = _Container_Reverse_Iterator<value_type>;
	using const_reverse_iterator = _Container_Reverse_Iterator<const_value_type>;

public:
	// Constructor
	Container();
	~Container();

	Container& operator=(const Container<Type>& rhs);
	void assign(size_t count, const Type& val);

	// Iterators
	iterator begin();
	iterator end();
	const_iterator cbegin();
	const_iterator cend();
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator crbegin();
	const_reverse_iterator crend();

	// Element access
	reference front();
	reference back();

	// Capacity
	// Проверка пустоты контайнера
	bool empty() const;
	size_t size();
	size_type max_size() const;
	// Устанавливает размер контейнера
	void resize(size_t count, const Type& val);

	// Modifiers
	void clear();
	void insert(iterator pos, const pointer& val);
	void insert(const_iterator pos, const pointer& val);
	void insert(reverse_iterator pos, const pointer& val);
	void insert(const_reverse_iterator pos, const pointer& val);
	// Удаляет элемент
	void erase(iterator pos);
	void erase(const_iterator pos);
	void push_front(Type data);
	void pop_front();
	void push_back(Type data);
	void pop_back();
	void swap(Container& other) noexcept;
	void swap(iterator lhs, iterator rhs) noexcept;

	// List operations
	size_t remove(const Type& value);
	template<class UnaryPredicate>
	size_t remove_if(UnaryPredicate pred);
	void reverse();
	size_t unique();
	template<class BinaryPredicate>
	size_t unique(BinaryPredicate pred);
	template<typename Compare = bool>
	void sort(Compare comp(Type&, Type&) = smaller);

	// Allocator
	allocator_type get_allocator() const noexcept;

private:
	void swap(pointer lhs, pointer rhs) noexcept
	{
		rhs->_pLast = lhs->_pLast;
		lhs->_pNext = rhs->_pNext;
		rhs->_pNext->_pLast = lhs;
		rhs->_pNext = lhs;
		lhs->_pLast->_pNext = rhs;
		lhs->_pLast = rhs;
	}
	void  delete_vrtx(pointer v)
	{
		pointer last = v->_pLast;
		pointer next = v->_pNext;
		size_p--;

		last->_pNext = next;
		next->_pLast = last;

		if (vrtx == v)
			if (vrtx->_pLast == null_l)
				vrtx = vrtx->_pNext;
			else
				vrtx = vrtx->_pLast;
		delete v;
	}

private:
	pointer vrtx;
	pointer null_n;
	pointer null_l;
	size_t size_p;

};

template<typename Type, class _Alloc>
inline Container<Type, _Alloc>::Container()
{
	vrtx = nullptr;
	null_n = new Node<Type>();
	null_l = new Node<Type>();
	size_p = 0;
}

template<typename Type, class _Alloc>
inline Container<Type, _Alloc>::~Container()
{
	clear();
	delete null_l;
	delete null_n;
}

template<typename Type, class _Alloc>
inline Container<Type, _Alloc>& Container<Type, _Alloc>::operator=(const Container<Type>& rhs)
{
	clear();

	if (rhs.vrtx != nullptr && rhs.vrtx != rhs.null_l && rhs.vrtx != rhs.null_n)
	{
		push_back(rhs.vrtx->_data);

		pointer cur = rhs.vrtx;
		while (cur->_pLast != rhs.null_l)
		{
			cur = cur->_pLast;
			push_front(cur->_data);
		}

		cur = rhs.vrtx;
		while (cur->_pNext != rhs.null_n)
		{
			cur = cur->_pNext;
			push_back(cur->_data);
		}
	}

	return *this;
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::assign(size_t count, const Type& val)
{
	clear();
	while (count > 0)
	{
		if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
		{
			vrtx = new Node<Type>(val, null_n, null_l);
			size_p++;
		}
		else
		{
			Node<Type>* cur = vrtx;

			while (cur->_pNext != null_n)
				cur = cur->_pNext;
			cur->_pNext = new Node<Type>(val, null_n, cur);
			size_p++;
		}
		//push_back(val);

		count--;
	}
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::iterator Container<Type, _Alloc>::begin()
{
	pointer cur = vrtx;
	while (vrtx != nullptr && cur->_pLast != null_l)
		cur = cur->_pLast;
	return iterator(cur);
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::iterator Container<Type, _Alloc>::end()
{
	return iterator(null_n);
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::const_iterator Container<Type, _Alloc>::cbegin()
{
	const_pointer cur = (const_pointer)vrtx;
	while (vrtx != nullptr && cur->_pLast != (const_pointer)null_l)
		cur = cur->_pLast;
	return const_iterator(cur);
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::const_iterator Container<Type, _Alloc>::cend()
{
	return const_iterator((const_pointer)null_n);
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::reverse_iterator Container<Type, _Alloc>::rbegin()
{
	pointer cur = vrtx;
	while (vrtx != nullptr && cur->_pNext != null_n)
		cur = cur->_pNext;
	return reverse_iterator(cur);
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::reverse_iterator Container<Type, _Alloc>::rend()
{
	return reverse_iterator(null_l);
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::const_reverse_iterator Container<Type, _Alloc>::crbegin()
{
	const_pointer cur = (const_pointer)vrtx;
	while (vrtx != nullptr && cur->_pNext != (const_pointer)null_n)
		cur = cur->_pNext;
	return const_reverse_iterator(cur);
}

template<typename Type, class _Alloc>
inline inline typename Container<Type, _Alloc>::const_reverse_iterator Container<Type, _Alloc>::crend()
{
	return const_reverse_iterator((const_pointer)null_l);
}

template<typename Type, class _Alloc>
inline typename Container<Type, _Alloc>::reference Container<Type, _Alloc>::front()
{
	return *begin();
}

template<typename Type, class _Alloc>
inline typename Container<Type, _Alloc>::reference Container<Type, _Alloc>::back()
{
	return *rbegin();
}

template<typename Type, class _Alloc>
inline bool Container<Type, _Alloc>::empty() const
{
	if (size_p)
		return false;
	return true;
}

template<typename Type, class _Alloc>
inline size_t Container<Type, _Alloc>::size()
{
	return size_p;
}

template<typename Type, class _Alloc>
inline typename Container<Type, _Alloc>::size_type Container<Type, _Alloc>::max_size() const
{
	return std::numeric_limits<difference_type>::max();
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::resize(size_t count, const Type& val)
{
	while (size_p > count)
		pop_back();
	while (size_p < count)
	{
		if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
		{
			vrtx = new Node<Type>(val, null_n, null_l);
			size_p++;
		}
		else
		{
			Node<Type>* cur = vrtx;

			while (cur->_pNext != null_n)
				cur = cur->_pNext;
			cur->_pNext = new Node<Type>(val, null_n, cur);
			size_p++;
		}
	}
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::clear()
{
	while (vrtx != nullptr && vrtx != null_l && vrtx != null_n && vrtx->_pLast != null_l)
		vrtx = vrtx->_pLast;
	while (size_p)
		pop_front();
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::insert(iterator pos, const pointer& val)
{
	pointer v = pos.getVRTX();
	v->insert_Node(val);
	size_p++;
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::insert(const_iterator pos, const pointer& val)
{
	const_pointer v = pos.getVRTX();
	v->insert_Node((const_pointer)val);
	size_p++;
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::insert(reverse_iterator pos, const pointer& val)
{
	pointer v = pos.getVRTX();
	v->r_insert_Node(val);
	size_p++;
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::insert(const_reverse_iterator pos, const pointer& val)
{
	const_pointer v = pos.getVRTX();
	v->r_insert_Node((const_pointer)val);
	size_p++;
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::erase(iterator pos)
{
	pointer v = pos.getVRTX();
	if (v != nullptr && v->_pLast != nullptr && v->_pNext != nullptr)
	{
		v->_pLast->_pNext = v->_pNext;
		v->_pNext->_pLast = v->_pLast;

		if (vrtx == v)
			if (vrtx->_pNext == nullptr || vrtx->_pNext == null_n)
				vrtx = vrtx->_pLast;
			else
				vrtx = vrtx->_pNext;
		delete v;
		size_p--;
	}
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::erase(const_iterator pos)
{
	const_pointer v = pos.getVRTX();
	if (v != nullptr && v->_pLast != nullptr && v->_pNext != nullptr)
	{
		v->_pLast->_pNext = v->_pNext;
		v->_pNext->_pLast = v->_pLast;

		if ((const_pointer)vrtx == v)
			if (vrtx->_pNext == nullptr || vrtx->_pNext == null_n)
				vrtx = vrtx->_pLast;
			else
				vrtx = vrtx->_pNext;
		delete v;
		size_p--;
	}
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::push_front(Type data)
{
	if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
	{
		vrtx = new Node<Type>(data, null_n, null_l);
		size_p++;
	}
	else
	{
		Node<Type>* cur = vrtx;

		while (cur->_pLast != null_l)
			cur = cur->_pLast;
		cur->_pLast = new Node<Type>(data, cur, null_l);
		size_p++;
	}
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::pop_front()
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

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::push_back(Type data)
{
	if (vrtx == nullptr || vrtx == null_l || vrtx == null_n)
	{
		vrtx = new Node<Type>(data, null_n, null_l);
		size_p++;
	}
	else
	{
		Node<Type>* cur = vrtx;

		while (cur->_pNext != null_n)
			cur = cur->_pNext;
		cur->_pNext = new Node<Type>(data, null_n, cur);
		size_p++;
	}
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::pop_back()
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

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::swap(Container& other) noexcept
{
	pointer delta;
	size_t t;

	delta = vrtx;
	vrtx = other.vrtx;
	other.vrtx = delta;

	delta = null_l;
	null_l = other.null_l;
	other.null_l = delta;

	delta = null_n;
	null_n = other.null_n;
	other.null_n = delta;

	t = size_p;
	size_p = other.size_p;
	other.size_p = t;
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::swap(iterator lhs, iterator rhs) noexcept
{
	lhs.swap(rhs);
}

template<typename Type, class _Alloc>
inline size_t Container<Type, _Alloc>::remove(const Type& value)
{
	return remove_if([&](const Type& _Other) { return _Other == value; });
}

template<typename Type, class _Alloc> template<class UnaryPredicate>
size_t Container<Type, _Alloc>::remove_if(UnaryPredicate pred)
{
	if (vrtx != nullptr)
	{
		size_t n = 0;

		pointer cur = vrtx;
		while (cur != null_l)
			if (pred(cur->_data))
			{
				cur = cur->_pLast;
				delete_vrtx(cur->_pNext);
				n++;
			}
			else
				cur = cur->_pLast;

		cur = vrtx;
		while (cur != null_n)
			if (pred(cur->_data))
			{
				cur = cur->_pNext;
				delete_vrtx(cur->_pLast);
				n++;
			}
			else
				cur = cur->_pNext;
		return n;
	}
	return 0;
}

template<typename Type, class _Alloc>
inline void Container<Type, _Alloc>::reverse()
{
	iterator it_l = begin();
	iterator it_r = rbegin();
	size_t n = size_p;

	while (n > 1)
	{
		iterator l = it_l;
		iterator r = it_r;
		it_l++;
		it_r--;

		swap(l, r);

		n -= 2;
	}
}

template<typename Type, class _Alloc>
inline size_t Container<Type, _Alloc>::unique()
{
	return unique([&](const Type& lhs, const Type& rhs) { return lhs == rhs; });
}

template<typename Type, class _Alloc> template<class BinaryPredicate>
inline size_t Container<Type, _Alloc>::unique(BinaryPredicate pred)
{
	if (vrtx != nullptr)
	{
		size_t n = 0;

		pointer cur = vrtx;
		while (cur->_pLast != null_l)
			cur = cur->_pLast;

		while (cur->_pNext != null_n)
		{
			if (pred(cur->_data, cur->_pNext->_data))
			{
				delete_vrtx(cur->_pNext);

				n++;
			}
			else
				cur = cur->_pNext;
		}
		return n;
	}
	return 0;
}

template<typename Type, class _Alloc> template<typename Compare>
inline void Container<Type, _Alloc>::sort(Compare comp(Type&, Type&))
{
	if (vrtx != nullptr && vrtx != null_l && vrtx != null_n)
	{
		pointer cur = vrtx;
		size_t n = size_p - 1;
		bool b = true;

		while (cur->_pLast != null_l)
			cur = cur->_pLast;

		while (n && b)
		{
			b = false;
			for (size_t i = 0; i < n; i++)
			{
				if (comp(cur->_data, cur->_pNext->_data))
				{
					swap(cur, cur->_pNext);
					cur = cur->_pLast;
					b = true;
				}
				cur = cur->_pNext;
			}
			cur = cur->_pLast;

			for (size_t i = 0; i < n - 1; i++)
			{
				if (comp(cur->_pLast->_data, cur->_data))
				{
					swap(cur->_pLast, cur);
					cur = cur->_pNext;
					b = true;
				}
				cur = cur->_pLast;
			}
			cur = cur->_pNext;

			n -= 2;
		}
	}
}

template<typename Type, class _Alloc>
inline typename Container<Type, _Alloc>::allocator_type Container<Type, _Alloc>::get_allocator() const noexcept
{
	MyAlloc<allocator_type> alloc;
	return (allocator_type)(*alloc.allocate(1));
}
