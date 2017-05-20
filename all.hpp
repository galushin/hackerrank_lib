template <class T, class IStream>
T read(IStream & is)
{
    T x;
    is >> x;
    return x;
}

template <class T, class IStream>
std::vector<T> 
read_vector(IStream & is, typename std::vector<T>::size_type n)
{
    std::vector<T> xs;
    
    for(; n > 0; -- n)
    {
        xs.push_back(read<int>(is));
    }
    
    return xs;
}

template <class T, class IStream>
std::vector<T> 
read_vector(IStream & is)
{
    return read_vector<T>(is, read<typename std::vector<T>::size_type>(is));
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

template <class T, class N, class BinaryOperation>
T power_positive(T x, N n, BinaryOperation op)
{
    if(n == N(1))
    {
        return x;
    }
    
    auto result = power_positive(x, n / 2, op);
    
    result = op(result, result);
    
    if(n % 2 == 1)
    {
        result = op(result, x);
    }
    
    return result;
}
