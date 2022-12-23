#include "../../lib/SimpleStack/stack.h"
#include <fstream>

int opnum;
SimpleStack<int> st;

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    fin >> opnum;

    for (int i = 1, op, x; i <= opnum; ++i) {
        fin >> op;
        if (op == 1)
            fout << st.size() << std::endl;
        else if (op == 2)
            fout << st.top() << std::endl;
        else if (op == 3) {
            if (!st.pop()) {
                fout << "Pop failed!" << std::endl;
                break;
            }
        } else {
            fin >> x;
            st.push(x);
        }
    }

    fin.close();
    fout.close();

    return 0;
}