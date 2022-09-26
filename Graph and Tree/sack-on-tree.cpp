// 1 base, sack on tree (basically small to large merging)
const int N=100001;
vector<int>v[N];
int a[N],sz[N],ans[N];
vector<int>subtree[N];
void sz_dfs(int node,int p=0) {
    sz[node] = 1;
    for (auto &c: v[node]) {
        if (c != p) {
            sz_dfs(c, node);
            sz[node] += sz[c];
        }
    }
}
void add(int node){}
void remove(int node){}
int get_ans() {}
void sack_dfs(int node,int p,bool keep) {
    int big = 0;
    for (auto &c: v[node]) {
        if (c != p && sz[big] < sz[c])
            big = c;
    }
    for (auto &c: v[node]) {
        if (c != p && c != big) {
            sack_dfs(c, node, false);
        }
    }
    if (big) {
        sack_dfs(big, node, true);
        swap(subtree[big], subtree[node]);
    }
    subtree[node].push_back(node);
    add(node);
    for (auto &c: v[node]) {
        if (c != p && c != big) {
            for (auto &d: subtree[c]) {
                add(d);
                subtree[node].push_back(d);
            }
        }
    }
    ans[node]=get_ans();
    if (!keep) {
        for (auto &c: subtree[node]) {
            remove(c);
        }
    }
}
// sz_dfs(1);
// sack_dfs(1,0,false);