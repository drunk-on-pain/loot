enum class enum_class {
    enum_type
};

enum old_enum {
    old_type
};

int main()
{
	return enum_class::enum_type == old_type ? 0 : 1;
}
