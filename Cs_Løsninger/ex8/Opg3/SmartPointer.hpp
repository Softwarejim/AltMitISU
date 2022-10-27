template <class T>
class SmartPointer
{
private:
    T* t_;
    unsigned int* counter_;

public:
    SmartPointer(T* t);
    SmartPointer(const SmartPointer& other);
    T* get();
    unsigned int getCount() const;
    void swap(SmartPointer& other);
    T* operator->();
    T& operator*();
    SmartPointer& operator=(const SmartPointer& other);
    ~SmartPointer();
};

template <class T>
SmartPointer<T>::SmartPointer(T* t) : t_(t), counter_(new unsigned int(1))
{
    std::cout << "Creating " << *t_ << ". SmartPointer counter++. Counter is now: " << *counter_ << "\n";
}

template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer& other) : t_(other.t_), counter_(other.counter_)
{
    ++(*counter_);
    std::cout << "Creating " << *t_ << ". SmartPointer counter++. Counter is now: " << *counter_ << "\n";
}

template <class T>
T* SmartPointer<T>::get()
{
    return t_;
}

template <class T>
unsigned int SmartPointer<T>::getCount() const
{
    return *counter_;
}

template <class T>
void SmartPointer<T>::swap(SmartPointer& other)
{
    std::swap(t_, other.t_);
    std::swap(counter_, other.counter_);
}

template <class T>
T* SmartPointer<T>::operator->()
{
    return t_;
}

template <class T>
T& SmartPointer<T>::operator*()
{
    return *t_;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& other)
{
    std::cout << "Creating " << *t_ << ". SmartPointer counter++. Counter is now: " << *counter_ << "\n";
    SmartPointer(other).swap(*this);
    return *this;
}

template <class T>
SmartPointer<T>::~SmartPointer()
{
    --(*counter_);

    std::cout << "Destroying " << *t_ << ". SmartPointer counter--. Counter is now: " << *counter_ << "\n";

    if(*counter_ == 0)
    {
        delete t_;
        delete counter_;
    }
}

