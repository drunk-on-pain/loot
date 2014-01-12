class deleg_constructor {
public:
	int _dummy;
    
	deleg_constructor(int dummy)
		: _dummy(dummy)
	{}

	deleg_constructor()
		: deleg_constructor(0)
	{}
};

int main()
{
    deleg_constructor dc;
	return 0;
}
