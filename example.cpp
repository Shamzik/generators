/*
    Let we want to implement Python generator like this:

    def StangeGenerator(seed):
        if seed > 228:
            yield 42
            i = 1
            while ((seed + i) % 42 != (seed - i) % 228):
                yield seed // i
                i += 1
        else:
            yield -1

    We can do it!
*/

#include <iostream>
#include "base.h"

class StrangeGenerator : public Generator<int>
{
    int seed, i = 0;

    GENERATE
        if (seed > 228) {
            YIELD(42);
            i = 1;
            while ((seed + i) % 42 != (seed - i) % 22)
            {
                YIELD(seed / i);
                i += 1;
            }
        }
        else {
            YIELD(-1);
        }
    TERMINATE
public:
    explicit StrangeGenerator(int seed) : seed(seed) {}
};

using namespace std;

int main() {
    for (auto e : StrangeGenerator(2000)) {
        cout << e << endl;
    }
}
