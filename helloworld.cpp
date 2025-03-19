#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main() {
    int n, l, r;
    std::cin >> n;
    std::vector<std::pair<int, int>> scanline(2 * n);
    for (int i = 0; i < n; ++i) {
        std::cin >> l >> r;
        scanline[2 * i] = {l, 1};
        scanline[2 * i + 1] = {r, -1};
    }
    std::sort(scanline.begin(), scanline.end());

    int count = 0, max_count = 0, cnt_max = 0;
    for (int i = 0; i < 2 * n; ++i) {
        count += (scanline[i].second);
        max_count = std::max(max_count, count);
    }

    count = 0;
    for (int i = 0; i < 2 * n; ++i) {
        count += (scanline[i].second);
        if (count == max_count && scanline[i].second == 1) {
                cnt_max += 1;

        }
    }

    std::cout << cnt_max << ' ' << max_count;
}
