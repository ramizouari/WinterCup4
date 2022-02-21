#include <iostream>

using integer = std::int64_t;
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


constexpr int alpha = 20;

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
        int m1 = 50,m2=7;
        std::vector<integer> d(11,0);
        std::string S;
        std::cin >> S; 
        std::reverse(S.begin(), S.end());
        integer t = 1,u=0;
        std::vector<int> I;
        int C1 = 0;
        for (int i = 0; i < n; i++) for (int j = i; j <std::min(n,alpha); j++)
        {

        }
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