/**
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: Builds suffix automaton for a string.
 * st[0] is the empty state, st represents the automaton
 * next maps to transitions
 * Time: O(n \log 26)
 */
#pragma once

struct SuffixAutomaton {
    struct state {
        int len, link;
        map<char, int> next;
    };
    vector<state> st;
    int sz, last;
    SuffixAutomaton (string s) {
        st.resize(2 * (int)(s.size()) + 1);
        st[0].len = 0, st[0].link = -1, sz = 1, last = 0;
        for(auto it : s) {
            sa_extend(it);
        }
    }
    void sa_extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    // st[i].len - st[st[i].link].len gives the number of different substrings starting from node i
    // example calculates the number of different substrings
    int sa_count_str() {
        int rez = 0;
        for(int i=sz-1;i>=1;i--) {
            rez += st[i].len - st[st[i].link].len; 
        }
        return rez;
    }
};
