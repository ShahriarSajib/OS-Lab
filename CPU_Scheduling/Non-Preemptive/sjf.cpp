#include <bits/stdc++.h>
using namespace std;

struct process {
    string id;
    int arrival, burst, waiting = 0, turnaround = 0;
    bool done = false;
};

int main() {
    int n;
    cin >> n;
    vector<process> p(n);
    for (auto &x : p) cin >> x.id >> x.arrival >> x.burst;

    sort(p.begin(), p.end(), [](auto &a, auto &b) {
        return a.arrival == b.arrival ? a.burst < b.burst : a.arrival < b.arrival;
    });

    int time = 0, done = 0;
    double tw = 0, tt = 0;
    vector<pair<string, int>> tl;

    while (done < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].arrival <= time)
                if (idx == -1 || p[i].burst < p[idx].burst) idx = i;

        if (idx == -1) { time++; continue; }

        time = max(time, p[idx].arrival) + p[idx].burst;
        p[idx].turnaround = time - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        p[idx].done = true;
        tw += p[idx].waiting;
        tt += p[idx].turnaround;
        tl.push_back({p[idx].id, time});
        done++;
    }

    cout << "Gantt Chart:\n|";
    for (auto &x : tl) cout << " " << x.first << " |";
    cout << "\n"<<p[0].arrival;
    for (auto &x : tl) cout << setw(5) << x.second;

    cout << "\n\nAvg waiting time = " << tw / n
         << "\nAvg turnaround time = " << tt / n
         << "\n\nProcess\tWaiting\tTurnaround\n";
    for (auto &x : p)
        cout << x.id << "\t" << x.waiting << "\t" << x.turnaround << "\n";

    return 0;
}