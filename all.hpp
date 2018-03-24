#include <cassert>

// Input/Output
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
        xs.push_back(read<T>(is));
    }
    
    return xs;
}

template <class T, class IStream>
std::vector<T> 
read_vector(IStream & is)
{
    return read_vector<T>(is, read<typename std::vector<T>::size_type>(is));
}

// STL extensions
template <class ForwardIterator>
std::pair<ForwardIterator, typename std::iterator_traits<ForwardIterator>::difference_type>
max_count(ForwardIterator first, ForwardIterator last)
{
    using Count = typename std::iterator_traits<ForwardIterator>::difference_type;
    
    if(first == last)
    {
        return {std::move(first), Count{0}};
    }
    
    std::pair<ForwardIterator, Count> result{first, Count{1}};
    ++ first;
    
    for(; first != last; ++ first)
    {
        if(*result.first < *first)
        {
            result.first = first;
            result.second = Count{1};
        }
        else if(!(*first < *result.first))
        {
            result.first = first;
            result.second += 1;
        }
    }
    
    return result;
}

// Number theory
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

template <class IntType>
IntType sum_of_divisible_below(IntType N, IntType K){
    auto const n = N / K - (N % K == IntType{0});
    
    auto const last = K * n;
    
    return (K + last) * n / IntType{2};
}

template <class Integer>
Integer divide_out_factor(Integer n, Integer factor)
{
    assert(n > Integer{0});

    while(n % factor == Integer{0})
    {
        n /= factor;
    }

    return n;
}

template <class Integer>
Integer divide_out_factor(Integer n, Integer factor, Integer & mf)
{
    if(n % factor == Integer{0})
    {
        mf = factor;
        n /= factor;

        n = divide_out_factor(n, factor);
    }

    return n;
}

// Powers
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

// Digits
template <class IntType>
IntType digits_sum(IntType num, IntType base)
{
    auto sum = IntType{0};
    
    for(; num > 0; num /= base)
    {
        sum += num % base;
    }
    
    return sum;
}
