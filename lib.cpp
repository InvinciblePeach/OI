#include <cstdint>
#include <iostream>
#include <vector>

std::vector<int> recover(int n);

namespace {
    typedef uint32_t ui;
    typedef uint64_t ul;

    const int $n = 1000005;
    const int $l = 19;

    int n, c1, c2;
    ui v[$l + 1][$n];
    ul p[$n];
    inline ui query_min(int l, int r) {
        int len = r - l + 1, g = 31 - __builtin_clz(len);
        return std::min(v[g][l], v[g][r - (1 << g) + 1]);
    }
}

uint64_t query(int l, int r) {
    if (l > r || l < 1 || r > n) {
        std::cout << "-2\n";
        std::exit(0);
    }
    if (c1++ == n * 3) {
        std::cout << "-3\n";
        std::exit(0);
    }
    return p[r] - p[l - 1] - query_min(l, r);
}

uint32_t get(int x) {
    if (c2++ == 2) {
        std::cout << "-4\n";
        std::exit(0);
    }
    return v[0][x];
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> v[0][i];
        p[i] = p[i - 1] + v[0][i];
    }
    for (int j = 1; j <= $l; ++j) {
        int l = n - (1 << j) + 1, h = 1 << (j - 1);
        for (int i = 1; i <= l; ++i)
            v[j][i] = std::min(v[j - 1][i], v[j - 1][i + h]);
    }
    auto ans = recover(n);
    if (ans.size() != n) {
        std::cout << "-1\n";
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        if (v[0][i] != ans[i - 1]) {
            std::cout << "-1\n";
            return 0;
        }
    std::cout << "0 " << c1 << ' ' << c2 << '\n';
}
