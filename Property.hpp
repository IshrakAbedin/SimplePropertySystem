#pragma once

#include <functional>
#include <iostream>

#include "EventDispatcher.hpp"

template<typename T>
class Property
{
protected:
    std::function<T(void)> m_Getter;
    std::function<void(T)> m_Setter;

public:
    T& Var;

    Property(T& variable, std::function<T(void)> getter, std::function<void(T)> setter)
        : Var{variable}, m_Getter{getter}, m_Setter{setter} { }

    Property(T& variable) : Property(variable,
        [&](){ return Var; },
        [&](const T& other) { Var = other; }
    ){ }

    inline T* operator->() { return &Var; }
    inline virtual T& operator=(T arg)
    {
        m_Setter(arg);
        return Var;
    }
    inline virtual operator T() { return m_Getter(); }
};

template<typename T>
class ObservableProperty : public Property<T>
{
public:
    using Property<T>::Property;
    EventDispatcher<const T&> OnValueChange;

    inline virtual T& operator=(T arg) override
    {
        this->m_Setter(arg);
        OnValueChange.Dispatch(this->Var);
        return this->Var;
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Property<T>& arg)
{
    out << arg.Var;
    return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, Property<T>& arg)
{
    T temp;
    in >> temp;
    arg = temp;
    return in;
}