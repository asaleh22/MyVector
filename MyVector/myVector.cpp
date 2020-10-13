
#include "myVector.h"
template<typename T>
void disp(const myVector<T>& obj) {
    for (int i = 0; i < obj.getSize(); ++i)
        std::cout << obj[i] << " ";
    std::cout << std::endl;
}

int main()
{
    myVector<int> m;
    m.add(1, 2, 3, 4);
    disp(m);

    return 0;
}


