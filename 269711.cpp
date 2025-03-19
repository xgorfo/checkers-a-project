#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    int cnt_parking, cnt_request, start_time, end_time, start_parking, end_parking, max_cnt = 0, cnt = 0, max_parking = 0;
    std::cin >> cnt_parking >> cnt_request;
    std::vector<std::pair<int, int>> scanline(2 * cnt_parking);
    std::vector<std::pair<int, int>> times(2 * cnt_parking);

    for (int i = 0; i < cnt_request; ++i) {
        std::cin >> start_time >> end_time >> start_parking >> end_parking;
        scanline[2 * i] = {start_parking, -1};
        scanline[2 * i + 1] = {end_parking, 1};
        
    }
    
    std::sort(scanline.begin(), scanline.end());

    for (int i = 0; i < 2 * cnt_parking - 1; ++i) {
        if (scanline[i].first == scanline[i + 1].first) {
            if 
        }
    }

    for (int i = 0; i < cnt_request; ++i) {
        cnt += (-scanline[i].second);
        max_cnt = std::max(max_cnt, cnt);
    }



    std::cout << max_cnt << ' ' << max_parking;

    return 0;
}