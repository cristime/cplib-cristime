#include <bits/stdc++.h>

using namespace std;

stack<int> st;
int opnum;

int main(int argc, char* argv[])
{
    // Preconfig IOs
    ios::sync_with_stdio(false);
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> opnum;

    for (int i = 1, op, x; i <= opnum; ++i) {
        fin >> op;
        if (op == 1)
            fout << st.size() << endl;
        else if (op == 2)
            fout << st.top() << endl;
        else if (op == 3) {
            if (st.empty()) {
                fout << "Pop failed!" << endl;
                break;
            }
            st.pop();
        } else {
            fin >> x;
            st.push(x);
        }
    }

    fin.close();
    fout.close();

    return 0;
}