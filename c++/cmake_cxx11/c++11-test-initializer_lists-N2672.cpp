#include <initializer_list>

template<class T>
class init_list {
public:
	init_list(std::initializer_list<T> list) {
	}
};

int main()
{
    init_list<int> il({3, 4});
	return 0;
}
