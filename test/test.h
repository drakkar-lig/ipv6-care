
#define CHECK(a, args...)		args
#define RETURN_VALUE_IF_FAILURE_int	hop, -1
#define RETURN_VALUE_IF_FAILURE_other	NULL
#define RETURN_TYPE(x)			CHECK(RETURN_VALUE_IF_FAILURE_ ## x)


RETURN_TYPE(int)
RETURN_TYPE(char *)
