template <typename T>
T SIRDEuler<T>::operator()(const double new_h) const
{
    T new_y;
    if(new_h == 0) // if no custom h has been given
        new_y = ode(y);
    else // if custom h has been specified
        new_y = ode(y);
    return new_y;
}