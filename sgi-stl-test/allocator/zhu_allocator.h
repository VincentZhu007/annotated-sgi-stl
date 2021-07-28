//
// Created by Vincent Zhu on 2021/7/28.
//

#ifndef ALLOCATOR_ZHU_ALLOCATOR_H
#define ALLOCATOR_ZHU_ALLOCATOR_H

#include <new>      // for operator new and delete
#include <cstddef>  // for ptrdiff_t, size_t
#include <climits>  // for UNIT_MAX
#include <iostream>

namespace zhustl {
template <class T>
inline T* _allocate(ptrdiff_t size, T*)
{
    std::set_new_handler(nullptr); // 分配器分配空间失败时调用的回调
    std::cout << "Calling Zhu Allocator, size = " << size << std::endl;
    T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
    if (tmp == nullptr) {
        std::cerr << "Allocate failed, out of memory" << std::endl;
        exit(1);
    }
    return tmp;
}

template <class T>
inline void _deallocate(T *buffer)
{
    ::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1 *p, T2 &value) {
    new(p) T1(value); // placement new, invoke ctor of T2
}

template <class T>
inline void _destroy(T *p)
{
    p->~T();
}

template <class T>
class ZhuAllocator {
public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef T&          reference;
    typedef const T&    const_reference;
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;

    // rebind allocator of type U
    template <class U>
    struct rebind {
        typedef ZhuAllocator<U> other;
    };

    pointer allocate(size_type n, const void *hint=0)
    {
        return _allocate((difference_type)n, (pointer)0);
    }

    void deallocate(pointer p, size_type n)
    {
        _deallocate(p);
    }

    void construct(pointer p, const_reference value)
    {
        _construct(p, value);
    }

    void destroy(pointer p)
    {
        _destroy(p);
    }

    pointer address(reference x)
    {
        return (pointer)&x;
    }

    const_pointer address(const_reference x)
    {
        return (const_pointer)&x;
    }

    size_type max_size() const
    {
        return size_type(UINT_MAX / sizeof(T));
    }
};
} // end namespace stltest
#endif // ALLOCATOR_ZHU_ALLOCATOR_H
