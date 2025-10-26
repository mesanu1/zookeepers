/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a 0-indexed 
 * directed graph. If vertices $u, v$ belong to the same component,
 * color[u] = color[v].
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

struct Kosaraju {
    int n, sccCnt;
    vector<vi> g, g2;
    vi s, color;
    vector<bool> vis;

    Kosaraju(int n) : n(n), g(n), g2(n), color(n), vis(n) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g2[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = true;
        for (int v : g[u]) if (!vis[v]) dfs1(v);
		s.push_back(u);
    }

    void dfs2(int u) {
        color[u] = sccCnt;
        for (int v : g2[u]) if (!color[v]) dfs2(v);
    }

    void work() {
        sccCnt = 0;
        rep(i, 0, n) if (!vis[i]) dfs1(i);
        for (int i = n - 1; i >= 0; --i) if (!color[s[i]]) {
			++sccCnt;
			dfs2(s[i]);
		}
    }
};