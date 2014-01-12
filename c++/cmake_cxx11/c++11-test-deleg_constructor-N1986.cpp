class deleg_constructor {
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
    deleg_constructor();
	return 0;
}
