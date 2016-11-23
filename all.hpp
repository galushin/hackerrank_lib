template <class T, class IStream>
T read(IStream & is)
{
    T x;
    is >> x;
    return x;
}
