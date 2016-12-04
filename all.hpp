template <class T, class IStream>
T read(IStream & is)
{
    T x;
    is >> x;
    return x;
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
