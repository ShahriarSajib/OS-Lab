#include <bits/stdc++.h>
using namespace std;

struct Process {
    string id;
    int at, bt, rt, ft = 0;
};

int main() {
    int n, tq, time = 0, done = 0;
    cout << "Enter number of processes and time quantum: ";
    cin >> n >> tq;

    vector<Process> p(n);
    cout << "Enter ID, arrival time, burst time:\n";
    for (auto &x : p) {
        cin >> x.id >> x.at >> x.bt;
        x.rt = x.bt;
    }

    vector<pair<string, int>> gantt;
    int idx = 0, cur = -1, rem_q = 0;
    queue<int> ready;

    while (done < n || cur != -1) {
        while (idx < n && p[idx].at <= time) ready.push(idx++);

        // Combine current + ready queue to select process with min remaining time
        vector<int> temp;
        if (cur != -1) temp.push_back(cur);
        while (!ready.empty()) {
            temp.push_back(ready.front());
            ready.pop();
        }

        if (!temp.empty()) {
            cur = *min_element(temp.begin(), temp.end(), [&](int a, int b) {
                return p[a].rt < p[b].rt;
            });

            for (int i : temp)
                if (i != cur) ready.push(i);
        } else {
            time++;
            continue;
        }

        // Execute one time unit
        if (gantt.empty() || gantt.back().first != p[cur].id)
            gantt.push_back({p[cur].id, time + 1});
        else
            gantt.back().second = time + 1;

        p[cur].rt--;
        time++;
        rem_q++;

        // Check new arrivals while running
        while (idx < n && p[idx].at <= time)
            ready.push(idx++);

        if (p[cur].rt == 0) {
            p[cur].ft = time;
            done++;
            cur = -1;
            rem_q = 0;
        } else if (rem_q == tq) {
            ready.push(cur);
            cur = -1;
            rem_q = 0;
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (auto &g : gantt) cout << " " << g.first << " |";
    cout << "\n0"; for (auto &g : gantt) cout << "   " << g.second;

    // Stats
    double total_wt = 0, total_tat = 0;
    cout << "\n\nProcess\tWaiting\tTurnaround\n";
    for (auto &x : p) {
        int tat = x.ft - x.at, wt = tat - x.bt;
        total_wt += wt; total_tat += tat;
        cout << x.id << "\t" << wt << "\t" << tat << "\n";
    }

    cout << "\nAvg Waiting Time: " << total_wt / n;
    cout << "\nAvg Turnaround Time: " << total_tat / n << "\n";

    return 0;
}
