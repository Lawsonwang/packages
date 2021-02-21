// Code By WLS
#ifndef HASH_H
#define HASH_H

#include <cstring>
#define ull unsigned long long
using namespace std;

int len;
ull pw[100010], h[100010];
void init(int base) {
    pw[0] = 1;
    for (int i = 1; i <= 1e5; i++) {
        pw[i] = pw[i - 1] * base;
    }
}
void initstr(char s[], int base) {
	len = strlen(s);
    for (int i = 0; i < len; i++) {
    	h[i] = h[i - 1] * base + s[i] - 'a' + 1;
	}
	
}
ull Hash(int start = 0) {
	int l = start, r = len + l - 1;
    return (h[r] - h[l - 1] * pw[r - l + 1]);
}
ull Hash(int l, int r) {
    return (h[r] - h[l - 1] * pw[r - l + 1]);
}


#endif // HASH_H
