#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Tradesman {
    int start;
    int dest;
    int appear;
};

struct Tick {
    vector<string> actions;
    vector<pair<int, int>> moves; // train_id, next_city
};

struct Proposal {
    int priority;
    int train;
    int next_city;
};

static const int INF = numeric_limits<int>::max() / 4;

static int read_strategy() {
    const char* value = getenv("STRATEGY");
    if (value == nullptr) return 0;
    return max(0, atoi(value));
}

static void build_shortest_tables(
    const vector<vector<int>>& adj,
    vector<vector<int>>& dist,
    vector<vector<int>>& next_hop
) {
    int V = (int)adj.size() - 1;
    dist.assign(V + 1, vector<int>(V + 1, INF));
    next_hop.assign(V + 1, vector<int>(V + 1, 0));

    for (int src = 1; src <= V; src++) {
        queue<int> q;
        dist[src][src] = 0;
        next_hop[src][src] = src;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dist[src][v] != INF) continue;
                dist[src][v] = dist[src][u] + 1;
                next_hop[src][v] = (u == src ? v : next_hop[src][u]);
                q.push(v);
            }
        }
    }
}

static int onboard_target_score(
    int train_pos,
    int person,
    int tick,
    int strategy,
    const vector<Tradesman>& people,
    const vector<vector<int>>& dist
) {
    int d = dist[train_pos][people[person].dest];
    int age = max(0, tick - people[person].appear);
    if (strategy == 1) return d * 4 - age;
    if (strategy == 2) return d * 2 - min(1000, age);
    if (strategy == 3) return d - min(250, age / 4);
    if (strategy == 4) return people[person].appear;
    if (strategy == 5) return d * 3 - min(1200, age * 2);
    if (strategy == 6) return d * 5 - min(1500, age * 3);
    if (strategy == 7) return d * 2 - min(2000, age * 4);
    if (strategy == 8) return people[person].appear + d;
    return d;
}

static int pickup_priority(
    int person,
    int tick,
    int strategy,
    const vector<Tradesman>& people,
    const vector<vector<int>>& dist
) {
    int route_len = dist[people[person].start][people[person].dest];
    int age = max(0, tick - people[person].appear);
    if (strategy == 1) return people[person].appear * 2 + route_len;
    if (strategy == 2) return route_len * 3 - min(1000, age);
    if (strategy == 3) return people[person].appear + route_len / 2;
    if (strategy == 4) return -age * 4 + route_len;
    if (strategy == 5) return route_len * 2 - min(1200, age * 2);
    if (strategy == 6) return people[person].appear + route_len * 2;
    if (strategy == 7) return -age * 5 + route_len * 3;
    if (strategy == 8) return route_len - min(2000, age * 3);
    return people[person].appear + route_len;
}

static int choose_onboard_destination(
    int train,
    int tick,
    int strategy,
    const vector<int>& train_pos,
    const vector<vector<int>>& onboard,
    const vector<Tradesman>& people,
    const vector<vector<int>>& dist
) {
    int target = 0;
    int best_score = INF;
    int best_dist = INF;
    int best_person = INF;

    for (int person : onboard[train]) {
        int d = dist[train_pos[train]][people[person].dest];
        int score = onboard_target_score(train_pos[train], person, tick, strategy, people, dist);
        if (
            score < best_score ||
            (score == best_score && d < best_dist) ||
            (score == best_score && d == best_dist && person < best_person)
        ) {
            target = people[person].dest;
            best_score = score;
            best_dist = d;
            best_person = person;
        }
    }

    return target;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    if (!(cin >> V >> E)) return 0;

    vector<vector<int>> adj(V + 1);
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= V; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    int T;
    cin >> T;
    vector<int> train_start(T + 1);
    for (int i = 1; i <= T; i++) cin >> train_start[i];

    int C;
    cin >> C;

    int N;
    cin >> N;
    vector<Tradesman> people(N + 1);
    vector<vector<int>> by_start(V + 1);
    for (int i = 1; i <= N; i++) {
        cin >> people[i].start >> people[i].dest >> people[i].appear;
        by_start[people[i].start].push_back(i);
    }

    vector<vector<int>> dist;
    vector<vector<int>> next_hop;
    build_shortest_tables(adj, dist, next_hop);

    int strategy = read_strategy();
    vector<int> train_pos = train_start;
    vector<vector<int>> onboard(T + 1);
    vector<int> status(N + 1, 0); // 0 waiting, 1 onboard, 2 delivered
    vector<Tick> plan;

    int completed = 0;
    for (int tick = 1; completed < N && tick <= 1'000'000; tick++) {
        Tick out;

        for (int train = 1; train <= T; train++) {
            vector<int> still_onboard;
            for (int person : onboard[train]) {
                if (train_pos[train] == people[person].dest) {
                    out.actions.push_back("drop " + to_string(train) + " " + to_string(person));
                    status[person] = 2;
                    completed++;
                } else {
                    still_onboard.push_back(person);
                }
            }
            onboard[train] = still_onboard;
        }

        for (int train = 1; train <= T; train++) {
            int city = train_pos[train];
            vector<int> candidates;
            vector<int> dest_count(V + 1, 0);
            for (int person : by_start[city]) {
                if (status[person] == 0 && people[person].appear <= tick) {
                    candidates.push_back(person);
                    dest_count[people[person].dest]++;
                }
            }

            if (strategy >= 5) {
                while ((int)onboard[train].size() < C) {
                    int best_person = 0;
                    int best_score = INF;
                    for (int person : candidates) {
                        if (status[person] != 0) continue;

                        int score = pickup_priority(person, tick, strategy, people, dist);
                        score -= dest_count[people[person].dest] * 8;

                        if (!onboard[train].empty()) {
                            int compat = INF;
                            for (int held : onboard[train]) {
                                compat = min(compat, dist[people[person].dest][people[held].dest]);
                            }
                            score += compat * 4;
                        }

                        if (
                            score < best_score ||
                            (score == best_score && person < best_person)
                        ) {
                            best_person = person;
                            best_score = score;
                        }
                    }

                    if (best_person == 0) break;
                    out.actions.push_back("pick " + to_string(train) + " " + to_string(best_person));
                    onboard[train].push_back(best_person);
                    status[best_person] = 1;
                }
            } else {
                sort(candidates.begin(), candidates.end(), [&](int a, int b) {
                    int sa = pickup_priority(a, tick, strategy, people, dist);
                    int sb = pickup_priority(b, tick, strategy, people, dist);
                    if (sa != sb) return sa < sb;
                    return a < b;
                });

                for (int person : candidates) {
                    if ((int)onboard[train].size() >= C) break;
                    if (status[person] != 0) continue;
                    out.actions.push_back("pick " + to_string(train) + " " + to_string(person));
                    onboard[train].push_back(person);
                    status[person] = 1;
                }
            }
        }

        vector<int> best_any_city(V + 1, 0);
        vector<int> best_available_city(V + 1, 0);
        vector<int> best_any_score(V + 1, INF);
        vector<int> best_available_score(V + 1, INF);
        vector<int> waiting_count(V + 1, 0);
        vector<int> remaining_count(V + 1, 0);
        vector<int> oldest_waiting_age(V + 1, 0);
        for (int person = 1; person <= N; person++) {
            if (status[person] != 0) continue;
            int city = people[person].start;
            remaining_count[city]++;
            if (people[person].appear <= tick) {
                waiting_count[city]++;
                oldest_waiting_age[city] = max(oldest_waiting_age[city], tick - people[person].appear);
            }
            int route_len = dist[people[person].start][people[person].dest];
            int any_score = max(tick, people[person].appear) + route_len - people[person].appear;
            if (strategy == 2) any_score = people[person].appear + route_len * 2;
            if (strategy == 3) any_score = people[person].appear + route_len / 2;
            if (strategy == 4) any_score = max(0, people[person].appear - tick) + route_len;
            if (strategy == 5) any_score = max(0, people[person].appear - tick) + route_len * 2;
            if (strategy == 6) any_score = people[person].appear + route_len * 3;
            if (strategy == 7) any_score = max(tick, people[person].appear) - min(2000, max(0, tick - people[person].appear) * 3) + route_len;
            if (strategy == 8) any_score = route_len + max(0, people[person].appear - tick) / 2;

            if (
                any_score < best_any_score[city] ||
                (any_score == best_any_score[city] && person < best_any_city[city])
            ) {
                best_any_city[city] = person;
                best_any_score[city] = any_score;
            }

            if (people[person].appear <= tick) {
                int available_score = pickup_priority(person, tick, strategy, people, dist);
                if (
                    available_score < best_available_score[city] ||
                    (
                        available_score == best_available_score[city] &&
                        person < best_available_city[city]
                    )
                ) {
                    best_available_city[city] = person;
                    best_available_score[city] = available_score;
                }
            }
        }

        vector<Proposal> proposals;
        vector<int> city_claims(V + 1, 0);
        for (int train = 1; train <= T; train++) {
            int target = 0;
            bool loaded = !onboard[train].empty();

            if (loaded) {
                int direct_target = choose_onboard_destination(
                    train, tick, strategy, train_pos, onboard, people, dist
                );
                target = direct_target;

                if ((int)onboard[train].size() < C && direct_target != 0) {
                    int direct_dist = dist[train_pos[train]][direct_target];
                    int best_detour_score = INF;
                    int best_detour_city = 0;
                    int detour_limit = 1 + strategy;
                    if (strategy >= 5) detour_limit = 3 + (strategy - 5) * 2;

                    for (int city = 1; city <= V; city++) {
                        int person = best_available_city[city];
                        if (person == 0) continue;
                        int detour_dist = dist[train_pos[train]][city] + dist[city][direct_target];
                        if (detour_dist > direct_dist + detour_limit) continue;

                        int age = max(0, tick - people[person].appear);
                        int score = detour_dist * 4 - age;
                        if (strategy == 4) score = dist[train_pos[train]][city] - age * 2;
                        if (strategy >= 5) {
                            int demand_bonus = waiting_count[city] * 8 + oldest_waiting_age[city] * 2;
                            int toward_bonus = max(0, direct_dist - dist[city][direct_target]) * 3;
                            score = detour_dist * 6 - demand_bonus - toward_bonus - age * (strategy - 3);
                        }
                        if (
                            score < best_detour_score ||
                            (score == best_detour_score && city < best_detour_city)
                        ) {
                            best_detour_score = score;
                            best_detour_city = city;
                        }
                    }

                    if (best_detour_city != 0) {
                        target = best_detour_city;
                    }
                }
            } else {
                int best_score = INF;
                int best_city = 0;
                int best_person = INF;
                for (int city = 1; city <= V; city++) {
                    int person = best_any_city[city];
                    if (person == 0) continue;
                    int travel = dist[train_pos[train]][city];
                    int pickup_tick = max(tick + travel, people[person].appear);
                    int route_len = dist[city][people[person].dest];
                    int delay = pickup_tick + route_len - people[person].appear;
                    int score = delay + travel;
                    if (strategy == 1) score = pickup_tick + route_len;
                    if (strategy == 2) score = travel * 3 + route_len + max(0, people[person].appear - tick);
                    if (strategy == 3) score = delay + route_len / 2;
                    if (strategy == 4) score = travel + max(0, people[person].appear - tick) / 2;
                    if (strategy >= 5) {
                        int needed_trains = max(1, (waiting_count[city] + C - 1) / C);
                        int claim_penalty = city_claims[city] >= needed_trains ? 350 : city_claims[city] * 45;
                        int demand_bonus = waiting_count[city] * 12 + oldest_waiting_age[city] * (strategy - 3);
                        int future_wait = max(0, people[person].appear - tick);
                        score = delay * 3 + travel * 2 + route_len - demand_bonus + claim_penalty;
                        if (strategy == 6) score = pickup_tick + route_len * 2 + travel - demand_bonus + claim_penalty;
                        if (strategy == 7) score = delay * 2 + travel * 3 - oldest_waiting_age[city] * 5 + claim_penalty;
                        if (strategy == 8) score = travel * 4 + future_wait + route_len - waiting_count[city] * 20 + claim_penalty;
                    }

                    if (
                        score < best_score ||
                        (score == best_score && pickup_tick < max(tick + dist[train_pos[train]][best_city], best_person == INF ? INF : people[best_person].appear)) ||
                        (score == best_score && person < best_person)
                    ) {
                        best_score = score;
                        best_city = city;
                        best_person = person;
                    }
                }
                target = best_city;
                if (target != 0 && strategy >= 5) {
                    city_claims[target]++;
                }
            }

            if (target == 0 || target == train_pos[train]) continue;
            int nxt = next_hop[train_pos[train]][target];
            if (nxt == 0) continue;

            int max_age = 0;
            for (int person : onboard[train]) {
                max_age = max(max_age, tick - people[person].appear);
            }

            int priority = (loaded ? 1'000'000 : 0) + (int)onboard[train].size() * 10'000 + max_age;
            if (!loaded) priority -= dist[train_pos[train]][target] * 10;
            if (strategy >= 5) {
                priority = (loaded ? 2'000'000 : 0) +
                    (int)onboard[train].size() * 25'000 +
                    max_age * 20 -
                    dist[train_pos[train]][target] * 20;
                if (!loaded) {
                    priority += waiting_count[target] * 100 + oldest_waiting_age[target] * 5;
                }
            }
            proposals.push_back({priority, train, nxt});
        }

        sort(proposals.begin(), proposals.end(), [](const Proposal& a, const Proposal& b) {
            if (a.priority != b.priority) return a.priority > b.priority;
            return a.train < b.train;
        });

        set<pair<int, int>> used_edges;
        set<int> moved_trains;
        vector<int> new_pos = train_pos;
        for (const Proposal& proposal : proposals) {
            int train = proposal.train;
            if (moved_trains.count(train)) continue;
            pair<int, int> edge = {
                min(train_pos[train], proposal.next_city),
                max(train_pos[train], proposal.next_city)
            };
            if (used_edges.count(edge)) continue;

            moved_trains.insert(train);
            used_edges.insert(edge);
            out.moves.push_back({train, proposal.next_city});
            new_pos[train] = proposal.next_city;
        }

        train_pos = new_pos;
        plan.push_back(out);
    }

    cout << plan.size() << '\n';
    for (const Tick& tick : plan) {
        cout << tick.actions.size() << '\n';
        for (const string& action : tick.actions) {
            cout << action << '\n';
        }
        cout << tick.moves.size() << '\n';
        for (auto [train, city] : tick.moves) {
            cout << train << ' ' << city << '\n';
        }
    }

    return 0;
}
