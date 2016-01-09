#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

C_MODE_START;

my_bool myfunc_int_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
longlong myfunc_int(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

C_MODE_END;


my_bool myfunc_int_init(UDF_INIT *initid __attribute__((unused)),
                        UDF_ARGS *args __attribute__((unused)),
                        char *message __attribute__((unused)))
{
  return 0;
}

longlong myfunc_int(UDF_INIT *initid __attribute__((unused)),
                    UDF_ARGS *args,
                    char *is_null __attribute__((unused)),
                    char *error __attribute__((unused)))
{
  longlong val = 0;
  uint i;

  for (i = 0; i < args->arg_count; i++)
  {
    if (args->args[i] == NULL)
      continue;
    switch (args->arg_type[i]) {
    case STRING_RESULT:			/* Add string lengths */
      val += args->lengths[i];
      break;
    case INT_RESULT:			/* Add numbers */
      val += *((longlong*) args->args[i]);
      break;
    case REAL_RESULT:			/* Add numers as longlong */
      val += (longlong) *((double*) args->args[i]);
      break;
    default:
      break;
    }
  }
  return val;
}
