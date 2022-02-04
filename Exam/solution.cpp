#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long

bool matrix_existence(int n, std::vector<int> R, std::vector<int> C) 
{
    std::sort(C.begin(), C.end(), std::greater<int>());
    for (int i = 0; i < n; ++i) {
        std::sort(R.begin(), R.end(), std::greater<int>());
        for (int j = 0; j < n; ++j) {
            if (C[i] && R[j]) {
                R[j]--;
                C[i]--;
            }
        }
    }
    bool flag = true;
    for (int i = 0; i < n; ++i) flag = flag && (!C[i]);
    for (int i = 0; i < n; ++i) flag = flag && (!R[i]);
    return flag;
}

bool matrix_existence_correct(int n,const std::vector<int> &row, const std::vector<int> &column)
{
    int r = n;
    int c = n;
    int row_sum = 0;
    int column_sum = 0;
    int row_max = -1;
    int column_max = -1;
    int row_non_zero = 0;
    int column_non_zero = 0;

    // Store sum of rowsums, max of row sum
    // number of non zero row sums
    for (int i = 0; i < r; i++) {
        row_sum += row[i];
        row_max = std::max(row_max, row[i]);
        if (row[i])
            row_non_zero++;
    }

    // Store sum of column sums, max of column sum
    // number of non zero column sums
    for (int i = 0; i < c; i++) {
        column_sum += column[i];
        column_max = std::max(column_max, column[i]);
        if (column[i])
            column_non_zero++;
    }

    // Check condition 1, 2, 3
    if ((row_sum != column_sum) ||
        (row_max > column_non_zero) ||
        (column_max > row_non_zero))
        return false;

    return true;
}

bool satisfiable(std::vector<int> a, std::vector<int> b) {
    while (!a.empty()) {
        std::sort(b.begin(), b.end(), std::greater<int>());
        int k = a.back();
        a.pop_back();
        if (k > b.size()) return false;
        if (k == 0) continue;
        if (b[k - 1] == 0) return false;
        for (int i = 0; i < k; i++)
            b[i]--;
    }
    for (std::vector<int>::iterator i = b.begin(); i != b.end(); i++)
        if (*i != 0)
            return false;
    return true;
}

bool all_zero(const auto &P)
{
    return std::all_of(P.begin(), P.end(), [](const auto& x) {return x == 0; });
}

void next_iteration(auto& P,int &sum, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (P[i] != n)
        {
            sum++;
            P[i]++;
            break;
        }
        P[i] = 0;
        sum -= n;
    }
}

int main()
{
    int a,b;
    std::cin >> a >> b;
    std::vector<int> row(a,0), col(b,0);
    int col_sum = 0;
    int row_sum = 0;
    int count;
    std::cin >> count;
    for (int i = a; i <= b; i++)
    {
        do
        {
            do
            {
                if( col_sum == row_sum && matrix_existence(i,row,col)!=satisfiable(row,col))
                {
                    std::cout << "-\tn=" << i;
                    std::cout << "\n-\trow= ";
                    for (auto s : row) std::cout << s << ' ';
                    std::cout << "\n-\tcol= ";
                    for (auto s : col) std::cout << s << ' ';
                    std::cout << "\n\n";
                    count--;
                }
                if (count == 0)
                    return true;
                next_iteration(col,col_sum, i);
            } while (!all_zero(col));
            next_iteration(row,row_sum, i);
        } while (!all_zero(row));
        row.push_back(0);
        col.push_back(0);
    }
}