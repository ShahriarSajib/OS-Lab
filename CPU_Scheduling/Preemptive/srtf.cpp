#include <bits/stdc++.h>
using namespace std;

struct process {
    string id;
    int arrival, burst, remaining, waiting = 0, turnaround = 0, completion = 0;
    bool done = false;
};

int main() {
    int n;
    cin >> n;
    vector<process> p(n);
    for (auto &x : p) {
        cin >> x.id >> x.arrival >> x.burst;
        x.remaining = x.burst;
    }

    sort(p.begin(), p.end(), [](auto &a, auto &b) {
        return a.arrival < b.arrival;
    });

    int time = 0, done = 0;
    double tw = 0, tt = 0;
    vector<pair<string, int>> tl;
    string last = "";

    while (done < n) {
        int idx = -1, min_remain = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time && p[i].remaining < min_remain && p[i].remaining > 0) {
                min_remain = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) {
           /* if (last != "IDLE") {
                tl.push_back({"IDLE", time});
                last = "IDLE";
            }*/
            time++;
            continue;
        }

        if (p[idx].id != last) {
            tl.push_back({p[idx].id, time});
            last = p[idx].id;
        }

        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            p[idx].done = true;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            tw += p[idx].waiting;
            tt += p[idx].turnaround;
            done++;
        }
    }

    tl.push_back({last, time});

    cout << "Gantt Chart:\n|";
    for (int i = 0; i < tl.size() - 1; i++) cout << " " << tl[i].first << " |";
    cout << "\n" << tl[0].second;
    for (int i = 1; i < tl.size(); i++)
        cout << setw(5) << tl[i].second;

    cout << "\n\nAvg waiting time = " << tw / n;
    cout << "\nAvg turnaround time = " << tt / n;
    cout << "\n\nProcess\tWaiting\tTurnaround\n";
    for (auto &x : p)
        cout << x.id << "\t" << x.waiting << "\t" << x.turnaround << "\n";

    return 0;
}
