/*
 * @Description: desc
 * @Author: Firmin.Sun
 * @Date: 2022-03-31 09:44:26
 * @FilePath: /tutorial/unique_ptr.cpp
 */
//
// Created by syh on 2022/3/31.
//

#include "utility"

using namespace std;

namespace zjai
{
    template <class T, class U = T>
    T exchange(T &obj, U &&new_value)
    {
        T old_value = std::move(obj);
        obj = std::forward<U>(new_value);
        return old_value;
    }
}

template <typename T>
class unique_ptr
{
public:
    unique_ptr() {}
    unique_ptr(T *ptr) : ptr_{ptr} {}
    unique_ptr(const unique_ptr &) = delete;
    unique_ptr(unique_ptr &&rhs) : ptr_{rhs.release()} {}

    ~unique_ptr()
    {
        delete ptr_;
    }

    unique_ptr &operator=(const unique_ptr &) = delete;
    unique_ptr &operator=(unique_ptr &&rhs)
    {
        reset(rhs.release());
        return *this;
    }

    T *get() const noexcept
    {
        return ptr_;
    }

    T *release()
    {
        return zjai::exchange(ptr_, nullptr);
    }

    void reset(T *ptr)
    {
        delete zjai::exchange(ptr_, ptr);
    }
    void swap(unique_ptr &rhs) noexcept
    {
        std::swap(ptr_, rhs.ptr_);
    }

    T &operator*() const
    {
        return *ptr_;
    }

    T *operator->() const
    {
        return ptr_;
    }

    explicit operator bool() const noexcept
    {
        return static_cast<bool>(ptr_);
    }

private:
    T *ptr_;
};

#include <iostream>
int main()
{
    unique_ptr<int> p1(new int(100));
    cout << *p1 << endl;

    unique_ptr<int> p2(std::move(p1));
    cout << *p2 << endl;
}