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
    int idx = 0;
    queue<int> ready;

    while (done < n) {
        while (idx < n && p[idx].at <= time)
            ready.push(idx++);

        if (ready.empty()) {
            time++;
            continue;
        }

        // Find process with shortest remaining time among ready ones
        vector<int> candidates;
        while (!ready.empty()) {
            candidates.push_back(ready.front());
            ready.pop();
        }

        int cur = *min_element(candidates.begin(), candidates.end(), [&](int a, int b) {
            return p[a].rt < p[b].rt;
        });

        for (int i : candidates)
            if (i != cur) ready.push(i);

        // Run current process for up to tq or until it finishes
        int run = min(tq, p[cur].rt);
        for (int t = 0; t < run; ++t) {
            if (gantt.empty() || gantt.back().first != p[cur].id)
                gantt.push_back({p[cur].id, time + 1});
            else
                gantt.back().second = time + 1;
            time++;
        }

        p[cur].rt -= run;

        // Check for new arrivals after execution
        while (idx < n && p[idx].at <= time)
            ready.push(idx++);

        if (p[cur].rt == 0) {
            p[cur].ft = time;
            done++;
        } else {
            ready.push(cur); // re-add to queue if not finished
        }
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (auto &g : gantt) cout << " " << g.first << " |";
    cout << "\n"<<p[0].at; 
    for (auto &g : gantt) cout << "   " << g.second;

    // Stats
    double total_wt = 0, total_tat = 0;
    cout << "\n\nProcess\tWaiting\tTurnaround\n";
    for (auto &x : p) {
        int tat = x.ft - x.at, wt = tat - x.bt;
        total_wt += wt;
        total_tat += tat;
        cout << x.id << "\t" << wt << "\t" << tat << "\n";
    }

    cout << "\nAvg Waiting Time: " << total_wt / n;
    cout << "\nAvg Turnaround Time: " << total_tat / n << "\n";

    return 0;
}
