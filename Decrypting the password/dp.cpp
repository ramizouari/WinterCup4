#include <iostream>

using integer = std::int64_t;

class d_cyclic
{
    integer n;
public:
    inline static integer m = 1;
    inline static bool assume_prime = true;
    d_cyclic(integer o = 0) :n((o + m) % m) {}
    bool operator==(integer O) const
    {
        return n == (m + O) % m;
    }

    bool operator!=(integer O) const
    {
        return n != (m + O) % m;
    }

    bool operator==(d_cyclic O) const
    {
        return n == O.n;
    }

    bool operator!=(d_cyclic O) const
    {
        return n != O.n;
    }

    auto& operator+=(const d_cyclic& O)
    {
        n = (n + O.n) % m;
        return *this;
    }
    auto& operator-=(const d_cyclic& O)
    {
        n = (n + m - O.n) % m;
        return *this;
    }

    auto& operator*=(const d_cyclic& O)
    {
        n = (n * O.n) % m;
        return *this;
    }

    auto operator*(const d_cyclic& O) const
    {
        auto w = *this;
        return w *= O;
    }

    auto operator+(const d_cyclic& O) const
    {
        auto w = *this;
        return w += O;
    }

    d_cyclic operator-() const
    {
        return d_cyclic(m - n);
    }

    auto operator-(const d_cyclic& O) const
    {
        auto w = *this;
        return w -= O;
    }

    auto& operator++()
    {
        return *this += 1;
    }

    auto& operator--()
    {
        return *this -= 1;
    }

    auto operator++(int)
    {
        d_cyclic r(n);
        *this += 1;
        return r;
    }

    auto operator--(int)
    {
        d_cyclic r(n);
        *this -= 1;
        return r;
    }

    explicit operator integer& ()
    {
        return n;
    }

    explicit operator const integer& () const
    {
        return n;
    }
};

auto operator*(integer k, d_cyclic O)
{
    return O *= k;
}

auto operator+(integer k, d_cyclic s)
{
    return s + k;
}

template<integer mod>
class cyclic
{
    integer n;
public:
    inline static bool assume_prime = true;
    inline static constexpr integer m = mod;
    cyclic(integer o = 0) :n((o + m) % m) {}
    bool operator==(integer O) const
    {
        return n == (m + O) % m;
    }

    bool operator!=(integer O) const
    {
        return n != (m + O) % m;
    }

    bool operator==(cyclic O) const
    {
        return n == O.n;
    }

    bool operator!=(cyclic O) const
    {
        return n != O.n;
    }

    cyclic operator-() const
    {
        return cyclic(-n);
    }

    auto& operator+=(const cyclic& O)
    {
        n = (n + O.n) % m;
        return *this;
    }
    auto& operator-=(const cyclic& O)
    {
        n = (n + m - O.n) % m;
        return *this;
    }

    auto& operator*=(const cyclic& O)
    {
        n = (n * O.n) % m;
        return *this;
    }

    auto& operator/=(const cyclic& O)
    {
        return (*this) *= O.inv();
    }

    auto operator*(const cyclic& O) const
    {
        auto w = *this;
        return w *= O;
    }

    auto operator+(const cyclic& O) const
    {
        auto w = *this;
        return w += O;
    }

    auto operator-(const cyclic& O) const
    {
        auto w = *this;
        return w -= O;
    }

    auto operator/(const cyclic& O) const
    {
        return (*this) * O.inv();
    }

    auto inv() const
    {
        return pow(*this, m - 2);
    }

    auto& operator++()
    {
        return *this += 1;
    }

    auto& operator--()
    {
        return *this -= 1;
    }

    auto operator++(int)
    {
        cyclic r(n);
        *this += 1;
        return r;
    }

    auto operator--(int)
    {
        cyclic r(n);
        *this -= 1;
        return r;
    }

    explicit operator integer& ()
    {
        return n;
    }

    explicit operator const integer& () const
    {
        return n;
    }
};

template<integer m>
auto operator*(integer k, cyclic<m> s)
{
    return s * k;
}

template<integer m>
auto operator+(integer k, cyclic<m> s)
{
    return s + k;
}

#include <vector>


constexpr integer M = 11;
using IK = cyclic<M>;
constexpr int p = 19;

auto f(int r,char c)
{
    return static_cast<integer>(IK{r-(c - '0')});
}



int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    std::vector<int> A;
    while (T--)
    {
        int n;
        std::cin >> n;
        int m1 = 5,m2=n;
        int alpha1 = 0, alpha2 = 0;
        while (m2 % 5)
        {
            m1 *= 5;
            m2 /= 5;
            alpha1++;
        }
        while (m1 % 2)
        {
            m1 *= 2;
            m2 /= 2;
            alpha2++;
        }
        int alpha = std::max(alpha1, alpha2);
        std::vector<integer> d(11,0);
        std::string S;
        std::cin >> S; 
        std::reverse(S.begin(), S.end());
        int C1 = 0;
        d_cyclic::m = n;
        for (int i = 0; i < n; i++) 
        {
            d_cyclic w = 1,r=0;
            for (int t = 0; t+i < std::min(n, i+alpha); t++)
            {
                r += (S[t+i] - '0') * w;
                if (r == 0)
                    C1++;
                w *= 10;
            }
        }

        integer t = 1, u = 0;
        std::vector<int> I;
        for (integer k = 0; k < std::min(alpha,n); k++)
        {
            u += (S[k] - '0') * t;
            t *= 10;
        }
        if (u % t == 0)
            I.push_back(0);
        for (int i = 1; i + alpha < n; i++)
        {
            u -= S[i-1] - '0';
            u /= 10;
            u += t * (S[i + alpha - 1] - '0');
            if (u % t == 0)
                I.push_back(i);
        }
        std::vector<std::vector<integer>> T(m2);
        IK w = 1,r=0;
        for (int i = 1; i <= n; i++)
        {
            r += (S[i - 1]-'0') * w;
            d[integer{ r }]++;
            T[integer{ r }].push_back(i - 1);
            w *= 10;
        }
        integer counter = 0;
        for (const auto& R : T) for(auto i : R)
        {
            auto it = std::lower_bound(R.begin(), R.end(), i + alpha);
            if (it == R.end())
                break;
            counter += std::distance(it, R.end());
        }
        counter += d[0];
        std::cout << counter << '\n';
    }
}