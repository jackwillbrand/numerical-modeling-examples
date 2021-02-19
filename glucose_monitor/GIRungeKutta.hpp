template <typename T>
T GIRungeKutta<T>::operator()(const double new_h)
{
    if(new_h < 0)
        throw std::invalid_argument("step must be positive");
        
    if(new_h == 0) // if no custom h has been given
    {
        y_pred = y + h * ode(y);
        y = y + (h/2) * (ode(y) + ode(y_pred));
    }
    else // if custom h has been specified
    {
        y_pred = y + new_h * ode(y);
        y = y + (new_h/2) * (ode(y) + ode(y_pred));
    }
    return y;
}

template <typename T>
GIRungeKutta<T>::GIRungeKutta(const GIRungeKutta<T> &girk)
{
    ode = girk.ode;
    h = girk.h;
    y_pred = girk.y_pred;
    y = girk.y;
}

template <typename T>
GIRungeKutta<T>& GIRungeKutta<T>::operator=(GIRungeKutta<T> src)
{
    std::swap(*this, src);
    return *this;
}

template <typename T>
void swap(GIRungeKutta<T> &a, GIRungeKutta<T> &b)
{
    std::swap(a.ode, b.ode);
    std::swap(a.h, b.h);
    std::swap(a.y_pred, b.y_pred);
    std::swap(a.y, b.y);
}