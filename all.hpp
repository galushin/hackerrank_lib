template <class T, class IStream>
T read(IStream & is)
{
    T x;
    is >> x;
    return x;
}

template <class T, class IStream>
vector<T> read_vector(IStream & is, typename vector<T>::size_type n)
{
    vector<T> xs;
    
    for(; n > 0; -- n)
    {
        xs.push_back(read<int>(is));
    }
    
    return xs;
}

/**
@todo Пропускать чётные
*/
template <class IntType>
vector<IntType> make_primes_below(IntType p_max)
{
    vector<IntType> primes;
    
    {
        vector<bool> seive(p_max, true);
        
        for(auto i = seive.begin(); i != seive.end(); i = find(i, seive.end(), true))
        {
            auto const p = (i - seive.begin()) + 2;

            primes.push_back(p);

            for(auto j = p - 2; j < seive.size(); j += p)
            {
                seive[j] = false;
            }

            ++ i;
        }
    }
    
    return primes;
}

template <class IntType>
IntType gcd(IntType x, IntType y)
{
    auto const zero = IntType(0);
    
    if(y == zero)
    {
        return x;
    }
    
    if(x == zero)
    {
        return y;
    }
    
    if(x < y)
    {
        return gcd(y, x);
    }
    
    return gcd(x % y, y);
}
