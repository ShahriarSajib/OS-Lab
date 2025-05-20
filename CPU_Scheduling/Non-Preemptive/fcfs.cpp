#include <bits/stdc++.h>
using namespace std;

struct process {
    string id;
    int arrival, burst, waiting = 0, turnaround = 0;
};

int main() {
    int n;
    cin >> n;
    vector<process> p(n);
    for (auto &x : p) cin >> x.id >> x.arrival >> x.burst;

    sort(p.begin(), p.end(), [](auto &a, auto &b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    double tw = 0, tt = 0;
    vector<pair<string, int>> tl;

    for (auto &x : p) {
        if (time < x.arrival) time = x.arrival;
        time += x.burst;
        x.turnaround = time - x.arrival;
        x.waiting = x.turnaround - x.burst;
        tw += x.waiting;
        tt += x.turnaround;
        tl.push_back({x.id, time});
    }

    cout << "Gantt Chart:\n|";
    for (auto &x : tl) cout << " " << x.first << " |";
    cout << "\n" << p[0].arrival;
    for (auto &x : tl) cout << setw(5) << x.second;

    cout << "\n\nAvg waiting time = " << tw / n
         << "\nAvg turnaround time = " << tt / n
         << "\n\nProcess\tArrival\tWaiting\tTurnaround\n";
    for (auto &x : p)
        cout << x.id << "\t" << x.arrival << "\t" << x.waiting << "\t" << x.turnaround << "\n";
}
