#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    int line[10000];
    int n, l, r;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> l >> r;
        line[l]++;
        line[r]--;
    }
    int cnt = 0, max_cnt = 0;
    for (size_t i = 0; i < 10000; ++i) {
        cnt += line[i];
        max_cnt = std::max(cnt, max_cnt);
    }

    cnt = 0;
    int cnt_max = 0;
    for (size_t i = 0; i < 10000; ++i) {
        cnt += line[i];
        if (cnt == max_cnt && line[i] == 1) {
            cnt_max += 1;
        }
    }
    std::cout << cnt_max << ' '<< max_cnt ;
}