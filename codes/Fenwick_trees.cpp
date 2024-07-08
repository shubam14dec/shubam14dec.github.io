#include <iostream>
#include <vector>

using namespace std;

long long getSum(vector<long long>& bit, int index) {
    long long total = 0;
    while (index > 0) {
        total += bit[index];
        index -= (index & -index);
    }
    return total;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n + 1), bit(n + 1, 0);

    for (int i = 1; i <= n; ++i) cin >> arr[i];

    for (int i = 1; i <= n; ++i) {
        int index = i;
        while (index <= n) {
            bit[index] += arr[i];
            index += (index & -index);
        }
    }

    while (q--) {
        int type, start, end;
        cin >> type >> start >> end;

        if (type == 1) {
            int pos = start;
            while (start <= n) {
                bit[start] -= arr[pos];
                bit[start] += end;
                start += (start & -start);
            }
            arr[pos] = end;
        } else if (type == 2) {
            cout << getSum(bit, end) - getSum(bit, start - 1) << endl;
        }
    }

    return 0;
}
