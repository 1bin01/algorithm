// 난수 생성기
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 배열 무작위 정렬
shuffle(all(v), rng);
