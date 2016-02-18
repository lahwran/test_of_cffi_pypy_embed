#define _CFFI_
#include <Python.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

/* This part is from file 'cffi/parse_c_type.h'.  It is copied at the
   beginning of C sources generated by CFFI's ffi.set_source(). */

typedef void *_cffi_opcode_t;

#define _CFFI_OP(opcode, arg)   (_cffi_opcode_t)(opcode | (((uintptr_t)(arg)) << 8))
#define _CFFI_GETOP(cffi_opcode)    ((unsigned char)(uintptr_t)cffi_opcode)
#define _CFFI_GETARG(cffi_opcode)   (((intptr_t)cffi_opcode) >> 8)

#define _CFFI_OP_PRIMITIVE       1
#define _CFFI_OP_POINTER         3
#define _CFFI_OP_ARRAY           5
#define _CFFI_OP_OPEN_ARRAY      7
#define _CFFI_OP_STRUCT_UNION    9
#define _CFFI_OP_ENUM           11
#define _CFFI_OP_FUNCTION       13
#define _CFFI_OP_FUNCTION_END   15
#define _CFFI_OP_NOOP           17
#define _CFFI_OP_BITFIELD       19
#define _CFFI_OP_TYPENAME       21
#define _CFFI_OP_CPYTHON_BLTN_V 23   // varargs
#define _CFFI_OP_CPYTHON_BLTN_N 25   // noargs
#define _CFFI_OP_CPYTHON_BLTN_O 27   // O  (i.e. a single arg)
#define _CFFI_OP_CONSTANT       29
#define _CFFI_OP_CONSTANT_INT   31
#define _CFFI_OP_GLOBAL_VAR     33
#define _CFFI_OP_DLOPEN_FUNC    35
#define _CFFI_OP_DLOPEN_CONST   37
#define _CFFI_OP_GLOBAL_VAR_F   39
#define _CFFI_OP_EXTERN_PYTHON  41

#define _CFFI_PRIM_VOID          0
#define _CFFI_PRIM_BOOL          1
#define _CFFI_PRIM_CHAR          2
#define _CFFI_PRIM_SCHAR         3
#define _CFFI_PRIM_UCHAR         4
#define _CFFI_PRIM_SHORT         5
#define _CFFI_PRIM_USHORT        6
#define _CFFI_PRIM_INT           7
#define _CFFI_PRIM_UINT          8
#define _CFFI_PRIM_LONG          9
#define _CFFI_PRIM_ULONG        10
#define _CFFI_PRIM_LONGLONG     11
#define _CFFI_PRIM_ULONGLONG    12
#define _CFFI_PRIM_FLOAT        13
#define _CFFI_PRIM_DOUBLE       14
#define _CFFI_PRIM_LONGDOUBLE   15

#define _CFFI_PRIM_WCHAR        16
#define _CFFI_PRIM_INT8         17
#define _CFFI_PRIM_UINT8        18
#define _CFFI_PRIM_INT16        19
#define _CFFI_PRIM_UINT16       20
#define _CFFI_PRIM_INT32        21
#define _CFFI_PRIM_UINT32       22
#define _CFFI_PRIM_INT64        23
#define _CFFI_PRIM_UINT64       24
#define _CFFI_PRIM_INTPTR       25
#define _CFFI_PRIM_UINTPTR      26
#define _CFFI_PRIM_PTRDIFF      27
#define _CFFI_PRIM_SIZE         28
#define _CFFI_PRIM_SSIZE        29
#define _CFFI_PRIM_INT_LEAST8   30
#define _CFFI_PRIM_UINT_LEAST8  31
#define _CFFI_PRIM_INT_LEAST16  32
#define _CFFI_PRIM_UINT_LEAST16 33
#define _CFFI_PRIM_INT_LEAST32  34
#define _CFFI_PRIM_UINT_LEAST32 35
#define _CFFI_PRIM_INT_LEAST64  36
#define _CFFI_PRIM_UINT_LEAST64 37
#define _CFFI_PRIM_INT_FAST8    38
#define _CFFI_PRIM_UINT_FAST8   39
#define _CFFI_PRIM_INT_FAST16   40
#define _CFFI_PRIM_UINT_FAST16  41
#define _CFFI_PRIM_INT_FAST32   42
#define _CFFI_PRIM_UINT_FAST32  43
#define _CFFI_PRIM_INT_FAST64   44
#define _CFFI_PRIM_UINT_FAST64  45
#define _CFFI_PRIM_INTMAX       46
#define _CFFI_PRIM_UINTMAX      47

#define _CFFI__NUM_PRIM         48
#define _CFFI__UNKNOWN_PRIM           (-1)
#define _CFFI__UNKNOWN_FLOAT_PRIM     (-2)
#define _CFFI__UNKNOWN_LONG_DOUBLE    (-3)

#define _CFFI__IO_FILE_STRUCT         (-1)


struct _cffi_global_s {
    const char *name;
    void *address;
    _cffi_opcode_t type_op;
    void *size_or_direct_fn;  // OP_GLOBAL_VAR: size, or 0 if unknown
                              // OP_CPYTHON_BLTN_*: addr of direct function
};

struct _cffi_getconst_s {
    unsigned long long value;
    const struct _cffi_type_context_s *ctx;
    int gindex;
};

struct _cffi_struct_union_s {
    const char *name;
    int type_index;          // -> _cffi_types, on a OP_STRUCT_UNION
    int flags;               // _CFFI_F_* flags below
    size_t size;
    int alignment;
    int first_field_index;   // -> _cffi_fields array
    int num_fields;
};
#define _CFFI_F_UNION         0x01   // is a union, not a struct
#define _CFFI_F_CHECK_FIELDS  0x02   // complain if fields are not in the
                                     // "standard layout" or if some are missing
#define _CFFI_F_PACKED        0x04   // for CHECK_FIELDS, assume a packed struct
#define _CFFI_F_EXTERNAL      0x08   // in some other ffi.include()
#define _CFFI_F_OPAQUE        0x10   // opaque

struct _cffi_field_s {
    const char *name;
    size_t field_offset;
    size_t field_size;
    _cffi_opcode_t field_type_op;
};

struct _cffi_enum_s {
    const char *name;
    int type_index;          // -> _cffi_types, on a OP_ENUM
    int type_prim;           // _CFFI_PRIM_xxx
    const char *enumerators; // comma-delimited string
};

struct _cffi_typename_s {
    const char *name;
    int type_index;   /* if opaque, points to a possibly artificial
                         OP_STRUCT which is itself opaque */
};

struct _cffi_type_context_s {
    _cffi_opcode_t *types;
    const struct _cffi_global_s *globals;
    const struct _cffi_field_s *fields;
    const struct _cffi_struct_union_s *struct_unions;
    const struct _cffi_enum_s *enums;
    const struct _cffi_typename_s *typenames;
    int num_globals;
    int num_struct_unions;
    int num_enums;
    int num_typenames;
    const char *const *includes;
    int num_types;
    int flags;      /* future extension */
};

struct _cffi_parse_info_s {
    const struct _cffi_type_context_s *ctx;
    _cffi_opcode_t *output;
    unsigned int output_size;
    size_t error_location;
    const char *error_message;
};

struct _cffi_externpy_s {
    const char *name;
    size_t size_of_result;
    void *reserved1, *reserved2;
};

#ifdef _CFFI_INTERNAL
static int parse_c_type(struct _cffi_parse_info_s *info, const char *input);
static int search_in_globals(const struct _cffi_type_context_s *ctx,
                             const char *search, size_t search_len);
static int search_in_struct_unions(const struct _cffi_type_context_s *ctx,
                                   const char *search, size_t search_len);
#endif

/* this block of #ifs should be kept exactly identical between
   c/_cffi_backend.c, cffi/vengine_cpy.py, cffi/vengine_gen.py
   and cffi/_cffi_include.h */
#if defined(_MSC_VER)
# include <malloc.h>   /* for alloca() */
# if _MSC_VER < 1600   /* MSVC < 2010 */
   typedef __int8 int8_t;
   typedef __int16 int16_t;
   typedef __int32 int32_t;
   typedef __int64 int64_t;
   typedef unsigned __int8 uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int64 uint64_t;
   typedef __int8 int_least8_t;
   typedef __int16 int_least16_t;
   typedef __int32 int_least32_t;
   typedef __int64 int_least64_t;
   typedef unsigned __int8 uint_least8_t;
   typedef unsigned __int16 uint_least16_t;
   typedef unsigned __int32 uint_least32_t;
   typedef unsigned __int64 uint_least64_t;
   typedef __int8 int_fast8_t;
   typedef __int16 int_fast16_t;
   typedef __int32 int_fast32_t;
   typedef __int64 int_fast64_t;
   typedef unsigned __int8 uint_fast8_t;
   typedef unsigned __int16 uint_fast16_t;
   typedef unsigned __int32 uint_fast32_t;
   typedef unsigned __int64 uint_fast64_t;
   typedef __int64 intmax_t;
   typedef unsigned __int64 uintmax_t;
# else
#  include <stdint.h>
# endif
# if _MSC_VER < 1800   /* MSVC < 2013 */
   typedef unsigned char _Bool;
# endif
#else
# include <stdint.h>
# if (defined (__SVR4) && defined (__sun)) || defined(_AIX) || defined(__hpux)
#  include <alloca.h>
# endif
#endif

#ifdef __GNUC__
# define _CFFI_UNUSED_FN  __attribute__((unused))
#else
# define _CFFI_UNUSED_FN  /* nothing */
#endif

/**********  CPython-specific section  **********/
#ifndef PYPY_VERSION


#if PY_MAJOR_VERSION >= 3
# define PyInt_FromLong PyLong_FromLong
#endif

#define _cffi_from_c_double PyFloat_FromDouble
#define _cffi_from_c_float PyFloat_FromDouble
#define _cffi_from_c_long PyInt_FromLong
#define _cffi_from_c_ulong PyLong_FromUnsignedLong
#define _cffi_from_c_longlong PyLong_FromLongLong
#define _cffi_from_c_ulonglong PyLong_FromUnsignedLongLong

#define _cffi_to_c_double PyFloat_AsDouble
#define _cffi_to_c_float PyFloat_AsDouble

#define _cffi_from_c_int(x, type)                                        \
    (((type)-1) > 0 ? /* unsigned */                                     \
        (sizeof(type) < sizeof(long) ?                                   \
            PyInt_FromLong((long)x) :                                    \
         sizeof(type) == sizeof(long) ?                                  \
            PyLong_FromUnsignedLong((unsigned long)x) :                  \
            PyLong_FromUnsignedLongLong((unsigned long long)x)) :        \
        (sizeof(type) <= sizeof(long) ?                                  \
            PyInt_FromLong((long)x) :                                    \
            PyLong_FromLongLong((long long)x)))

#define _cffi_to_c_int(o, type)                                          \
    ((type)(                                                             \
     sizeof(type) == 1 ? (((type)-1) > 0 ? (type)_cffi_to_c_u8(o)        \
                                         : (type)_cffi_to_c_i8(o)) :     \
     sizeof(type) == 2 ? (((type)-1) > 0 ? (type)_cffi_to_c_u16(o)       \
                                         : (type)_cffi_to_c_i16(o)) :    \
     sizeof(type) == 4 ? (((type)-1) > 0 ? (type)_cffi_to_c_u32(o)       \
                                         : (type)_cffi_to_c_i32(o)) :    \
     sizeof(type) == 8 ? (((type)-1) > 0 ? (type)_cffi_to_c_u64(o)       \
                                         : (type)_cffi_to_c_i64(o)) :    \
     (Py_FatalError("unsupported size for type " #type), (type)0)))

#define _cffi_to_c_i8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[1])
#define _cffi_to_c_u8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[2])
#define _cffi_to_c_i16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[3])
#define _cffi_to_c_u16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[4])
#define _cffi_to_c_i32                                                   \
                 ((int(*)(PyObject *))_cffi_exports[5])
#define _cffi_to_c_u32                                                   \
                 ((unsigned int(*)(PyObject *))_cffi_exports[6])
#define _cffi_to_c_i64                                                   \
                 ((long long(*)(PyObject *))_cffi_exports[7])
#define _cffi_to_c_u64                                                   \
                 ((unsigned long long(*)(PyObject *))_cffi_exports[8])
#define _cffi_to_c_char                                                  \
                 ((int(*)(PyObject *))_cffi_exports[9])
#define _cffi_from_c_pointer                                             \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[10])
#define _cffi_to_c_pointer                                               \
    ((char *(*)(PyObject *, CTypeDescrObject *))_cffi_exports[11])
#define _cffi_get_struct_layout                                          \
    not used any more
#define _cffi_restore_errno                                              \
    ((void(*)(void))_cffi_exports[13])
#define _cffi_save_errno                                                 \
    ((void(*)(void))_cffi_exports[14])
#define _cffi_from_c_char                                                \
    ((PyObject *(*)(char))_cffi_exports[15])
#define _cffi_from_c_deref                                               \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[16])
#define _cffi_to_c                                                       \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[17])
#define _cffi_from_c_struct                                              \
    ((PyObject *(*)(char *, CTypeDescrObject *))_cffi_exports[18])
#define _cffi_to_c_wchar_t                                               \
    ((wchar_t(*)(PyObject *))_cffi_exports[19])
#define _cffi_from_c_wchar_t                                             \
    ((PyObject *(*)(wchar_t))_cffi_exports[20])
#define _cffi_to_c_long_double                                           \
    ((long double(*)(PyObject *))_cffi_exports[21])
#define _cffi_to_c__Bool                                                 \
    ((_Bool(*)(PyObject *))_cffi_exports[22])
#define _cffi_prepare_pointer_call_argument                              \
    ((Py_ssize_t(*)(CTypeDescrObject *, PyObject *, char **))_cffi_exports[23])
#define _cffi_convert_array_from_object                                  \
    ((int(*)(char *, CTypeDescrObject *, PyObject *))_cffi_exports[24])
#define _CFFI_CPIDX  25
#define _cffi_call_python                                                \
    ((void(*)(struct _cffi_externpy_s *, char *))_cffi_exports[_CFFI_CPIDX])
#define _CFFI_NUM_EXPORTS 26

typedef struct _ctypedescr CTypeDescrObject;

static void *_cffi_exports[_CFFI_NUM_EXPORTS];

#define _cffi_type(index)   (                           \
    assert((((uintptr_t)_cffi_types[index]) & 1) == 0), \
    (CTypeDescrObject *)_cffi_types[index])

static PyObject *_cffi_init(const char *module_name, Py_ssize_t version,
                            const struct _cffi_type_context_s *ctx)
{
    PyObject *module, *o_arg, *new_module;
    void *raw[] = {
        (void *)module_name,
        (void *)version,
        (void *)_cffi_exports,
        (void *)ctx,
    };

    module = PyImport_ImportModule("_cffi_backend");
    if (module == NULL)
        goto failure;

    o_arg = PyLong_FromVoidPtr((void *)raw);
    if (o_arg == NULL)
        goto failure;

    new_module = PyObject_CallMethod(
        module, (char *)"_init_cffi_1_0_external_module", (char *)"O", o_arg);

    Py_DECREF(o_arg);
    Py_DECREF(module);
    return new_module;

  failure:
    Py_XDECREF(module);
    return NULL;
}

_CFFI_UNUSED_FN
static PyObject **_cffi_unpack_args(PyObject *args_tuple, Py_ssize_t expected,
                                    const char *fnname)
{
    if (PyTuple_GET_SIZE(args_tuple) != expected) {
        PyErr_Format(PyExc_TypeError,
                     "%.150s() takes exactly %zd arguments (%zd given)",
                     fnname, expected, PyTuple_GET_SIZE(args_tuple));
        return NULL;
    }
    return &PyTuple_GET_ITEM(args_tuple, 0);   /* pointer to the first item,
                                                  the others follow */
}

/**********  end CPython-specific section  **********/
#else
_CFFI_UNUSED_FN
static void (*_cffi_call_python_org)(struct _cffi_externpy_s *, char *);
# define _cffi_call_python  _cffi_call_python_org
#endif


#define _cffi_array_len(array)   (sizeof(array) / sizeof((array)[0]))

#define _cffi_prim_int(size, sign)                                      \
    ((size) == 1 ? ((sign) ? _CFFI_PRIM_INT8  : _CFFI_PRIM_UINT8)  :    \
     (size) == 2 ? ((sign) ? _CFFI_PRIM_INT16 : _CFFI_PRIM_UINT16) :    \
     (size) == 4 ? ((sign) ? _CFFI_PRIM_INT32 : _CFFI_PRIM_UINT32) :    \
     (size) == 8 ? ((sign) ? _CFFI_PRIM_INT64 : _CFFI_PRIM_UINT64) :    \
     _CFFI__UNKNOWN_PRIM)

#define _cffi_prim_float(size)                                          \
    ((size) == sizeof(float) ? _CFFI_PRIM_FLOAT :                       \
     (size) == sizeof(double) ? _CFFI_PRIM_DOUBLE :                     \
     (size) == sizeof(long double) ? _CFFI__UNKNOWN_LONG_DOUBLE :       \
     _CFFI__UNKNOWN_FLOAT_PRIM)

#define _cffi_check_int(got, got_nonpos, expected)      \
    ((got_nonpos) == (expected <= 0) &&                 \
     (got) == (unsigned long long)expected)

#ifdef MS_WIN32
# define _cffi_stdcall  __stdcall
#else
# define _cffi_stdcall  /* nothing */
#endif

#ifdef __cplusplus
}
#endif

#define _CFFI_MODULE_NAME  "my_plugin"
#define _CFFI_PYTHON_STARTUP_CODE  "from my_plugin import ffi\n" \
"\n" \
"@ffi.def_extern()\n" \
"def do_stuff(p):\n" \
"    print(\"adding %d and %d\" % (p.x, p.y))\n" \
"    return p.x + p.y\n"
#ifdef PYPY_VERSION
# define _CFFI_PYTHON_STARTUP_FUNC  _cffi_pypyinit_my_plugin
#elif PY_MAJOR_VERSION >= 3
# define _CFFI_PYTHON_STARTUP_FUNC  PyInit_my_plugin
#else
# define _CFFI_PYTHON_STARTUP_FUNC  initmy_plugin
#endif

/***** Support code for embedding *****/

#if defined(_MSC_VER)
#  define CFFI_DLLEXPORT  __declspec(dllexport)
#elif defined(__GNUC__)
#  define CFFI_DLLEXPORT  __attribute__((visibility("default")))
#else
#  define CFFI_DLLEXPORT  /* nothing */
#endif


/* There are two global variables of type _cffi_call_python_fnptr:

   * _cffi_call_python, which we declare just below, is the one called
     by ``extern "Python"`` implementations.

   * _cffi_call_python_org, which on CPython is actually part of the
     _cffi_exports[] array, is the function pointer copied from
     _cffi_backend.

   After initialization is complete, both are equal.  However, the
   first one remains equal to &_cffi_start_and_call_python until the
   very end of initialization, when we are (or should be) sure that
   concurrent threads also see a completely initialized world, and
   only then is it changed.
*/
#undef _cffi_call_python
typedef void (*_cffi_call_python_fnptr)(struct _cffi_externpy_s *, char *);
static void _cffi_start_and_call_python(struct _cffi_externpy_s *, char *);
static _cffi_call_python_fnptr _cffi_call_python = &_cffi_start_and_call_python;


#ifndef _MSC_VER
   /* --- Assuming a GCC not infinitely old --- */
# define cffi_compare_and_swap(l,o,n)  __sync_bool_compare_and_swap(l,o,n)
# define cffi_write_barrier()          __sync_synchronize()
# if !defined(__amd64__) && !defined(__x86_64__) &&   \
     !defined(__i386__) && !defined(__i386)
#   define cffi_read_barrier()         __sync_synchronize()
# else
#   define cffi_read_barrier()         (void)0
# endif
#else
   /* --- Windows threads version --- */
# include <Windows.h>
# define cffi_compare_and_swap(l,o,n) \
                               (InterlockedCompareExchangePointer(l,n,o) == (o))
# define cffi_write_barrier()       InterlockedCompareExchange(&_cffi_dummy,0,0)
# define cffi_read_barrier()           (void)0
static volatile LONG _cffi_dummy;
#endif

#ifdef WITH_THREAD
# ifndef _MSC_VER
#  include <pthread.h>
   static pthread_mutex_t _cffi_embed_startup_lock;
# else
   static CRITICAL_SECTION _cffi_embed_startup_lock;
# endif
  static char _cffi_embed_startup_lock_ready = 0;
#endif

static void _cffi_acquire_reentrant_mutex(void)
{
    static void *volatile lock = NULL;

    while (!cffi_compare_and_swap(&lock, NULL, (void *)1)) {
        /* should ideally do a spin loop instruction here, but
           hard to do it portably and doesn't really matter I
           think: pthread_mutex_init() should be very fast, and
           this is only run at start-up anyway. */
    }

#ifdef WITH_THREAD
    if (!_cffi_embed_startup_lock_ready) {
# ifndef _MSC_VER
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&_cffi_embed_startup_lock, &attr);
# else
        InitializeCriticalSection(&_cffi_embed_startup_lock);
# endif
        _cffi_embed_startup_lock_ready = 1;
    }
#endif

    while (!cffi_compare_and_swap(&lock, (void *)1, NULL))
        ;

#ifndef _MSC_VER
    pthread_mutex_lock(&_cffi_embed_startup_lock);
#else
    EnterCriticalSection(&_cffi_embed_startup_lock);
#endif
}

static void _cffi_release_reentrant_mutex(void)
{
#ifndef _MSC_VER
    pthread_mutex_unlock(&_cffi_embed_startup_lock);
#else
    LeaveCriticalSection(&_cffi_embed_startup_lock);
#endif
}


/**********  CPython-specific section  **********/
#ifndef PYPY_VERSION


#define _cffi_call_python_org  _cffi_exports[_CFFI_CPIDX]

PyMODINIT_FUNC _CFFI_PYTHON_STARTUP_FUNC(void);   /* forward */

static void _cffi_py_initialize(void)
{
    /* XXX use initsigs=0, which "skips initialization registration of
       signal handlers, which might be useful when Python is
       embedded" according to the Python docs.  But review and think
       if it should be a user-controllable setting.

       XXX we should also give a way to write errors to a buffer
       instead of to stderr.

       XXX if importing 'site' fails, CPython (any version) calls
       exit().  Should we try to work around this behavior here?
    */
    Py_InitializeEx(0);
}

static int _cffi_initialize_python(void)
{
    /* This initializes Python, imports _cffi_backend, and then the
       present .dll/.so is set up as a CPython C extension module.
    */
    int result;
    PyGILState_STATE state;
    PyObject *pycode=NULL, *global_dict=NULL, *x;

#if PY_MAJOR_VERSION >= 3
    /* see comments in _cffi_carefully_make_gil() about the
       Python2/Python3 difference 
    */
#else
    /* Acquire the GIL.  We have no threadstate here.  If Python is 
       already initialized, it is possible that there is already one
       existing for this thread, but it is not made current now.
    */
    PyEval_AcquireLock();

    _cffi_py_initialize();

    /* The Py_InitializeEx() sometimes made a threadstate for us, but
       not always.  Indeed Py_InitializeEx() could be called and do
       nothing.  So do we have a threadstate, or not?  We don't know,
       but we can replace it with NULL in all cases.
    */
    (void)PyThreadState_Swap(NULL);

    /* Now we can release the GIL and re-acquire immediately using the
       logic of PyGILState(), which handles making or installing the
       correct threadstate.
    */
    PyEval_ReleaseLock();
#endif
    state = PyGILState_Ensure();

    /* Call the initxxx() function from the present module.  It will
       create and initialize us as a CPython extension module, instead
       of letting the startup Python code do it---it might reimport
       the same .dll/.so and get maybe confused on some platforms.
       It might also have troubles locating the .dll/.so again for all
       I know.
    */
    (void)_CFFI_PYTHON_STARTUP_FUNC();
    if (PyErr_Occurred())
        goto error;

    /* Now run the Python code provided to ffi.embedding_init_code().
     */
    pycode = Py_CompileString(_CFFI_PYTHON_STARTUP_CODE,
                              "<init code for '" _CFFI_MODULE_NAME "'>",
                              Py_file_input);
    if (pycode == NULL)
        goto error;
    global_dict = PyDict_New();
    if (global_dict == NULL)
        goto error;
    if (PyDict_SetItemString(global_dict, "__builtins__",
                             PyThreadState_GET()->interp->builtins) < 0)
        goto error;
    x = PyEval_EvalCode(
#if PY_MAJOR_VERSION < 3
                        (PyCodeObject *)
#endif
                        pycode, global_dict, global_dict);
    if (x == NULL)
        goto error;
    Py_DECREF(x);

    /* Done!  Now if we've been called from
       _cffi_start_and_call_python() in an ``extern "Python"``, we can
       only hope that the Python code did correctly set up the
       corresponding @ffi.def_extern() function.  Otherwise, the
       general logic of ``extern "Python"`` functions (inside the
       _cffi_backend module) will find that the reference is still
       missing and print an error.
     */
    result = 0;
 done:
    Py_XDECREF(pycode);
    Py_XDECREF(global_dict);
    PyGILState_Release(state);
    return result;

 error:;
    {
        /* Print as much information as potentially useful.
           Debugging load-time failures with embedding is not fun
        */
        PyObject *exception, *v, *tb, *f, *modules, *mod;
        PyErr_Fetch(&exception, &v, &tb);
        if (exception != NULL) {
            PyErr_NormalizeException(&exception, &v, &tb);
            PyErr_Display(exception, v, tb);
        }
        Py_XDECREF(exception);
        Py_XDECREF(v);
        Py_XDECREF(tb);

        f = PySys_GetObject((char *)"stderr");
        if (f != NULL && f != Py_None) {
            PyFile_WriteString("\nFrom: " _CFFI_MODULE_NAME
                               "\ncompiled with cffi version: 1.5.2"
                               "\n_cffi_backend module: ", f);
            modules = PyImport_GetModuleDict();
            mod = PyDict_GetItemString(modules, "_cffi_backend");
            if (mod == NULL) {
                PyFile_WriteString("not loaded", f);
            }
            else {
                v = PyObject_GetAttrString(mod, "__file__");
                PyFile_WriteObject(v, f, 0);
                Py_XDECREF(v);
            }
            PyFile_WriteString("\nsys.path: ", f);
            PyFile_WriteObject(PySys_GetObject((char *)"path"), f, 0);
            PyFile_WriteString("\n\n", f);
        }
    }
    result = -1;
    goto done;
}

PyAPI_DATA(char *) _PyParser_TokenNames[];  /* from CPython */

static int _cffi_carefully_make_gil(void)
{
    /* This does the basic initialization of Python.  It can be called
       completely concurrently from unrelated threads.  It assumes
       that we don't hold the GIL before (if it exists), and we don't
       hold it afterwards.

       What it really does is completely different in Python 2 and 
       Python 3.

    Python 2
    ========

       Initialize the GIL, without initializing the rest of Python,
       by calling PyEval_InitThreads().

       PyEval_InitThreads() must not be called concurrently at all.
       So we use a global variable as a simple spin lock.  This global
       variable must be from 'libpythonX.Y.so', not from this
       cffi-based extension module, because it must be shared from
       different cffi-based extension modules.  We choose
       _PyParser_TokenNames[0] as a completely arbitrary pointer value
       that is never written to.  The default is to point to the
       string "ENDMARKER".  We change it temporarily to point to the
       next character in that string.  (Yes, I know it's REALLY
       obscure.)

    Python 3
    ========

       In Python 3, PyEval_InitThreads() cannot be called before
       Py_InitializeEx() any more.  So this function calls
       Py_InitializeEx() first.  It uses the same obscure logic to
       make sure we never call it concurrently.

       Arguably, this is less good on the spinlock, because
       Py_InitializeEx() takes much longer to run than
       PyEval_InitThreads().  But I didn't find a way around it.
    */

#ifdef WITH_THREAD
    char *volatile *lock = (char *volatile *)_PyParser_TokenNames;
    char *old_value;

    while (1) {    /* spin loop */
        old_value = *lock;
        if (old_value[0] == 'E') {
            assert(old_value[1] == 'N');
            if (cffi_compare_and_swap(lock, old_value, old_value + 1))
                break;
        }
        else {
            assert(old_value[0] == 'N');
            /* should ideally do a spin loop instruction here, but
               hard to do it portably and doesn't really matter I
               think: PyEval_InitThreads() should be very fast, and
               this is only run at start-up anyway. */
        }
    }
#endif

#if PY_MAJOR_VERSION >= 3
    /* Python 3: call Py_InitializeEx() */
    {
        PyGILState_STATE state = PyGILState_UNLOCKED;
        if (!Py_IsInitialized())
            _cffi_py_initialize();
        else
            state = PyGILState_Ensure();

        PyEval_InitThreads();
        PyGILState_Release(state);
    }
#else
    /* Python 2: call PyEval_InitThreads() */
# ifdef WITH_THREAD
    if (!PyEval_ThreadsInitialized()) {
        PyEval_InitThreads();    /* makes the GIL */
        PyEval_ReleaseLock();    /* then release it */
    }
    /* else: there is already a GIL, but we still needed to do the
       spinlock dance to make sure that we see it as fully ready */
# endif
#endif

#ifdef WITH_THREAD
    /* release the lock */
    while (!cffi_compare_and_swap(lock, old_value + 1, old_value))
        ;
#endif

    return 0;
}

/**********  end CPython-specific section  **********/


#else


/**********  PyPy-specific section  **********/

PyMODINIT_FUNC _CFFI_PYTHON_STARTUP_FUNC(const void *[]);   /* forward */

static struct _cffi_pypy_init_s {
    const char *name;
    void (*func)(const void *[]);
    const char *code;
} _cffi_pypy_init = {
    _CFFI_MODULE_NAME,
    _CFFI_PYTHON_STARTUP_FUNC,
    _CFFI_PYTHON_STARTUP_CODE,
};

extern int pypy_carefully_make_gil(const char *);
extern int pypy_init_embedded_cffi_module(int, struct _cffi_pypy_init_s *);

static int _cffi_carefully_make_gil(void)
{
    return pypy_carefully_make_gil(_CFFI_MODULE_NAME);
}

static int _cffi_initialize_python(void)
{
    return pypy_init_embedded_cffi_module(0xB011, &_cffi_pypy_init);
}

/**********  end PyPy-specific section  **********/


#endif


#ifdef __GNUC__
__attribute__((noinline))
#endif
static _cffi_call_python_fnptr _cffi_start_python(void)
{
    /* Delicate logic to initialize Python.  This function can be
       called multiple times concurrently, e.g. when the process calls
       its first ``extern "Python"`` functions in multiple threads at
       once.  It can also be called recursively, in which case we must
       ignore it.  We also have to consider what occurs if several
       different cffi-based extensions reach this code in parallel
       threads---it is a different copy of the code, then, and we
       can't have any shared global variable unless it comes from
       'libpythonX.Y.so'.

       Idea:

       * _cffi_carefully_make_gil(): "carefully" call
         PyEval_InitThreads() (possibly with Py_InitializeEx() first).

       * then we use a (local) custom lock to make sure that a call to this
         cffi-based extension will wait if another call to the *same*
         extension is running the initialization in another thread.
         It is reentrant, so that a recursive call will not block, but
         only one from a different thread.

       * then we grab the GIL and (Python 2) we call Py_InitializeEx().
         At this point, concurrent calls to Py_InitializeEx() are not
         possible: we have the GIL.

       * do the rest of the specific initialization, which may
         temporarily release the GIL but not the custom lock.
         Only release the custom lock when we are done.
    */
    static char called = 0;

    if (_cffi_carefully_make_gil() != 0)
        return NULL;

    _cffi_acquire_reentrant_mutex();

    /* Here the GIL exists, but we don't have it.  We're only protected
       from concurrency by the reentrant mutex. */

    /* This file only initializes the embedded module once, the first
       time this is called, even if there are subinterpreters. */
    if (!called) {
        called = 1;  /* invoke _cffi_initialize_python() only once,
                        but don't set '_cffi_call_python' right now,
                        otherwise concurrent threads won't call
                        this function at all (we need them to wait) */
        if (_cffi_initialize_python() == 0) {
            /* now initialization is finished.  Switch to the fast-path. */

            /* We would like nobody to see the new value of
               '_cffi_call_python' without also seeing the rest of the
               data initialized.  However, this is not possible.  But
               the new value of '_cffi_call_python' is the function
               'cffi_call_python()' from _cffi_backend.  So:  */
            cffi_write_barrier();
            /* ^^^ we put a write barrier here, and a corresponding
               read barrier at the start of cffi_call_python().  This
               ensures that after that read barrier, we see everything
               done here before the write barrier.
            */

            assert(_cffi_call_python_org != NULL);
            _cffi_call_python = (_cffi_call_python_fnptr)_cffi_call_python_org;
        }
        else {
            /* initialization failed.  Reset this to NULL, even if it was
               already set to some other value.  Future calls to
               _cffi_start_python() are still forced to occur, and will
               always return NULL from now on. */
            _cffi_call_python_org = NULL;
        }
    }

    _cffi_release_reentrant_mutex();

    return (_cffi_call_python_fnptr)_cffi_call_python_org;
}

static
void _cffi_start_and_call_python(struct _cffi_externpy_s *externpy, char *args)
{
    _cffi_call_python_fnptr fnptr;
    int current_err = errno;
#ifdef _MSC_VER
    int current_lasterr = GetLastError();
#endif
    fnptr = _cffi_start_python();
    if (fnptr == NULL) {
        fprintf(stderr, "function %s() called, but initialization code "
                        "failed.  Returning 0.\n", externpy->name);
        memset(args, 0, externpy->size_of_result);
    }
#ifdef _MSC_VER
    SetLastError(current_lasterr);
#endif
    errno = current_err;

    if (fnptr != NULL)
        fnptr(externpy, args);
}


/* The cffi_start_python() function makes sure Python is initialized
   and our cffi module is set up.  It can be called manually from the
   user C code.  The same effect is obtained automatically from any
   dll-exported ``extern "Python"`` function.  This function returns
   -1 if initialization failed, 0 if all is OK.  */
_CFFI_UNUSED_FN
static int cffi_start_python(void)
{
    if (_cffi_call_python == &_cffi_start_and_call_python) {
        if (_cffi_start_python() == NULL)
            return -1;
    }
    cffi_read_barrier();
    return 0;
}

#undef cffi_compare_and_swap
#undef cffi_write_barrier
#undef cffi_read_barrier

/************************************************************/

#include "plugin.h"


/************************************************************/

static void *_cffi_types[] = {
/*  0 */ _CFFI_OP(_CFFI_OP_FUNCTION, 4), // int()(point_t *)
/*  1 */ _CFFI_OP(_CFFI_OP_POINTER, 5), // point_t *
/*  2 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/*  3 */ _CFFI_OP(_CFFI_OP_POINTER, 0), // int(*)(point_t *)
/*  4 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 7), // int
/*  5 */ _CFFI_OP(_CFFI_OP_STRUCT_UNION, 0), // point_t
};

_CFFI_UNUSED_FN
static void _cffi_checkfld_typedef_point_t(point_t *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  (void)((p->x) << 1);  /* check that 'point_t.x' is an integer */
  (void)((p->y) << 1);  /* check that 'point_t.y' is an integer */
}
struct _cffi_align_typedef_point_t { char x; point_t y; };

static struct _cffi_externpy_s _cffi_externpy__do_stuff =
  { "do_stuff", (int)sizeof(int) };

CFFI_DLLEXPORT int do_stuff(point_t * a0)
{
  char a[8];
  char *p = a;
  *(point_t * *)(p + 0) = a0;
  _cffi_call_python(&_cffi_externpy__do_stuff, p);
  return *(int *)p;
}

static const struct _cffi_global_s _cffi_globals[] = {
  { "do_stuff", (void *)&_cffi_externpy__do_stuff, _CFFI_OP(_CFFI_OP_EXTERN_PYTHON, 3), (void *)do_stuff },
};

static const struct _cffi_field_s _cffi_fields[] = {
  { "x", offsetof(point_t, x),
         sizeof(((point_t *)0)->x),
         _CFFI_OP(_CFFI_OP_NOOP, 4) },
  { "y", offsetof(point_t, y),
         sizeof(((point_t *)0)->y),
         _CFFI_OP(_CFFI_OP_NOOP, 4) },
};

static const struct _cffi_struct_union_s _cffi_struct_unions[] = {
  { "$point_t", 5, _CFFI_F_CHECK_FIELDS,
    sizeof(point_t), offsetof(struct _cffi_align_typedef_point_t, y), 0, 2 },
};

static const struct _cffi_typename_s _cffi_typenames[] = {
  { "point_t", 5 },
};

static const struct _cffi_type_context_s _cffi_type_context = {
  _cffi_types,
  _cffi_globals,
  _cffi_fields,
  _cffi_struct_unions,
  NULL,  /* no enums */
  _cffi_typenames,
  1,  /* num_globals */
  1,  /* num_struct_unions */
  0,  /* num_enums */
  1,  /* num_typenames */
  NULL,  /* no includes */
  6,  /* num_types */
  1,  /* flags */
};

#ifdef PYPY_VERSION
PyMODINIT_FUNC
_cffi_pypyinit_my_plugin(const void *p[])
{
    if (((intptr_t)p[0]) >= 0x0A03) {
        _cffi_call_python_org = (void(*)(struct _cffi_externpy_s *, char *))p[1];
    }
    p[0] = (const void *)0x2701;
    p[1] = &_cffi_type_context;
}
#  ifdef _MSC_VER
     PyMODINIT_FUNC
#  if PY_MAJOR_VERSION >= 3
     PyInit_my_plugin(void) { return NULL; }
#  else
     initmy_plugin(void) { }
#  endif
#  endif
#elif PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC
PyInit_my_plugin(void)
{
  return _cffi_init("my_plugin", 0x2701, &_cffi_type_context);
}
#else
PyMODINIT_FUNC
initmy_plugin(void)
{
  _cffi_init("my_plugin", 0x2701, &_cffi_type_context);
}
#endif