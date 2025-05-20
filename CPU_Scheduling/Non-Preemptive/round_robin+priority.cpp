#include <bits/stdc++.h>
using namespace std;

struct Process {
    string id;
    int at, bt, prio, rt, wt = 0, tat = 0, ft = 0;
};

int main() {
    int n, q, time = 0, done = 0, idx = 0;
    cout << "Enter number of processes and time quantum: ";
    cin >> n >> q;

    vector<Process> p(n);
    cout << "Enter process ID, arrival time, burst time, and priority:\n";
    for (auto &x : p) {
        cin >> x.id >> x.at >> x.bt >> x.prio;
        x.rt = x.bt;
    }

    sort(p.begin(), p.end(), [](auto &a, auto &b) { return a.at < b.at; });

    map<int, queue<int>> pq; // priority → process queue
    vector<pair<string, int>> gantt;

    while (done < n) {
        while (idx < n && p[idx].at <= time)
            pq[p[idx++].prio].push(idx - 1);

        int pr = -1;
        for (auto &[k, q] : pq)
            if (!q.empty()) { pr = k; break; }

        if (pr == -1) { time++; continue; }

        int i = pq[pr].front(); pq[pr].pop();
        int run = min(q, p[i].rt);

        for (int j = 0; j < run; ++j) {
            if (gantt.empty() || gantt.back().first != p[i].id)
                gantt.push_back({p[i].id, time + 1});
            else gantt.back().second = time + 1;
            time++; p[i].rt--;

            while (idx < n && p[idx].at <= time)
                pq[p[idx++].prio].push(idx - 1);
        }

        if (p[i].rt == 0) {
            p[i].ft = time;
            p[i].tat = p[i].ft - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            done++;
        } else pq[pr].push(i);
    }

    // Gantt chart
    cout << "\nGantt Chart:\n|";
    for (auto &x : gantt) cout << " " << x.first << " |";
    cout << "\n0"; for (auto &x : gantt) cout << "   " << x.second;

    // Stats
    double total_wt = 0, total_tat = 0;
    cout << "\n\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n";
    for (auto &x : p) {
        total_wt += x.wt;
        total_tat += x.tat;
        cout << x.id << "\t" << x.at << "\t" << x.bt << "\t" << x.prio
             << "\t\t" << x.wt << "\t" << x.tat << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << "\n";
    return 0;
}
