
typedef unsigned int size_t;
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
__extension__ typedef signed long long int __int64_t;
__extension__ typedef unsigned long long int __uint64_t;
__extension__ typedef long long int __quad_t;
__extension__ typedef unsigned long long int __u_quad_t;
__extension__ typedef __u_quad_t __dev_t;
__extension__ typedef unsigned int __uid_t;
__extension__ typedef unsigned int __gid_t;
__extension__ typedef unsigned long int __ino_t;
__extension__ typedef __u_quad_t __ino64_t;
__extension__ typedef unsigned int __mode_t;
__extension__ typedef unsigned int __nlink_t;
__extension__ typedef long int __off_t;
__extension__ typedef __quad_t __off64_t;
__extension__ typedef int __pid_t;
__extension__ typedef struct
{
  int __val[2];
} __fsid_t;
__extension__ typedef long int __clock_t;
__extension__ typedef unsigned long int __rlim_t;
__extension__ typedef __u_quad_t __rlim64_t;
__extension__ typedef unsigned int __id_t;
__extension__ typedef long int __time_t;
__extension__ typedef unsigned int __useconds_t;
__extension__ typedef long int __suseconds_t;
__extension__ typedef int __daddr_t;
__extension__ typedef long int __swblk_t;
__extension__ typedef int __key_t;
__extension__ typedef int __clockid_t;
__extension__ typedef void *__timer_t;
__extension__ typedef long int __blksize_t;
__extension__ typedef long int __blkcnt_t;
__extension__ typedef __quad_t __blkcnt64_t;
__extension__ typedef unsigned long int __fsblkcnt_t;
__extension__ typedef __u_quad_t __fsblkcnt64_t;
__extension__ typedef unsigned long int __fsfilcnt_t;
__extension__ typedef __u_quad_t __fsfilcnt64_t;
__extension__ typedef int __ssize_t;
typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;
__extension__ typedef int __intptr_t;
__extension__ typedef unsigned int __socklen_t;
struct _IO_FILE;

typedef struct _IO_FILE FILE;









typedef struct _IO_FILE __FILE;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
typedef int _G_int16_t __attribute__ ((__mode__ (__HI__)));
typedef int _G_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int _G_uint16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int _G_uint32_t __attribute__ ((__mode__ (__SI__)));
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t;
struct _IO_FILE;
typedef void _IO_lock_t;
struct _IO_marker
{
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;
  int _pos;
};
enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
struct _IO_FILE
{
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
typedef struct _IO_FILE _IO_FILE;
struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);
typedef __ssize_t __io_write_fn (void *__cookie, __const char *__buf,
				 size_t __n);
typedef int __io_seek_fn (void *__cookie, __off64_t * __pos, int __w);
typedef int __io_close_fn (void *__cookie);
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
extern int _IO_getc (_IO_FILE * __fp);
extern int _IO_putc (int __c, _IO_FILE * __fp);
extern int _IO_feof (_IO_FILE * __fp) __attribute__ ((__nothrow__));
extern int _IO_ferror (_IO_FILE * __fp) __attribute__ ((__nothrow__));
extern int _IO_peekc_locked (_IO_FILE * __fp);
extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__));
extern int _IO_vfscanf (_IO_FILE * __restrict, const char *__restrict,
			__gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE * __restrict, const char *__restrict,
			 __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);
extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);
extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__));

typedef _G_fpos_t fpos_t;

extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;

extern int remove (__const char *__filename) __attribute__ ((__nothrow__));
extern int rename (__const char *__old, __const char *__new)
  __attribute__ ((__nothrow__));

extern int renameat (int __oldfd, __const char *__old, int __newfd,
		     __const char *__new) __attribute__ ((__nothrow__));

extern FILE *tmpfile (void);







extern char *tmpnam (char *__s) __attribute__ ((__nothrow__));





extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__));
extern char *tempnam (__const char *__dir, __const char *__pfx)
  __attribute__ ((__nothrow__)) __attribute__ ((__malloc__));

extern int fclose (FILE * __stream);
extern int fflush (FILE * __stream);

extern int fflush_unlocked (FILE * __stream);

extern FILE *fopen (__const char *__restrict __filename,
		    __const char *__restrict __modes);
extern FILE *freopen (__const char *__restrict __filename,
		      __const char *__restrict __modes,
		      FILE * __restrict __stream);

extern FILE *fdopen (int __fd, __const char *__modes)
  __attribute__ ((__nothrow__));
extern FILE *fmemopen (void *__s, size_t __len, __const char *__modes)
  __attribute__ ((__nothrow__));
extern FILE *open_memstream (char **__bufloc, size_t * __sizeloc)
  __attribute__ ((__nothrow__));

extern void setbuf (FILE * __restrict __stream, char *__restrict __buf)
  __attribute__ ((__nothrow__));
extern int setvbuf (FILE * __restrict __stream, char *__restrict __buf,
		    int __modes, size_t __n) __attribute__ ((__nothrow__));

extern void setbuffer (FILE * __restrict __stream, char *__restrict __buf,
		       size_t __size) __attribute__ ((__nothrow__));
extern void setlinebuf (FILE * __stream) __attribute__ ((__nothrow__));

extern int fprintf (FILE * __restrict __stream,
		    __const char *__restrict __format, ...);
extern int printf (__const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
		    __const char *__restrict __format, ...)
  __attribute__ ((__nothrow__));
extern int vfprintf (FILE * __restrict __s, __const char *__restrict __format,
		     __gnuc_va_list __arg);
extern int vprintf (__const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, __const char *__restrict __format,
		     __gnuc_va_list __arg) __attribute__ ((__nothrow__));


extern int snprintf (char *__restrict __s, size_t __maxlen,
		     __const char *__restrict __format, ...)
  __attribute__ ((__nothrow__))
  __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
		      __const char *__restrict __format, __gnuc_va_list __arg)
  __attribute__ ((__nothrow__))
  __attribute__ ((__format__ (__printf__, 3, 0)));

extern int vdprintf (int __fd, __const char *__restrict __fmt,
		     __gnuc_va_list __arg)
  __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, __const char *__restrict __fmt, ...)
  __attribute__ ((__format__ (__printf__, 2, 3)));

extern int fscanf (FILE * __restrict __stream,
		   __const char *__restrict __format, ...);
extern int scanf (__const char *__restrict __format, ...);
extern int sscanf (__const char *__restrict __s,
		   __const char *__restrict __format, ...)
  __attribute__ ((__nothrow__));
extern int
fscanf (FILE * __restrict __stream, __const char *__restrict __format, ...)
__asm__ ("" "__isoc99_fscanf");
     extern int scanf (__const char *__restrict __format,
		       ...) __asm__ ("" "__isoc99_scanf");
     extern int sscanf (__const char *__restrict __s,
			__const char *__restrict __format,
			...) __asm__ ("" "__isoc99_sscanf")
  __attribute__ ((__nothrow__));


     extern int vfscanf (FILE * __restrict __s,
			 __const char *__restrict __format,
			 __gnuc_va_list __arg)
  __attribute__ ((__format__ (__scanf__, 2, 0)));
     extern int vscanf (__const char *__restrict __format,
			__gnuc_va_list __arg)
  __attribute__ ((__format__ (__scanf__, 1, 0)));
     extern int vsscanf (__const char *__restrict __s,
			 __const char *__restrict __format,
			 __gnuc_va_list __arg) __attribute__ ((__nothrow__))
  __attribute__ ((__format__ (__scanf__, 2, 0)));
     extern int vfscanf (FILE * __restrict __s,
			 __const char *__restrict __format,
			 __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")
  __attribute__ ((__format__ (__scanf__, 2, 0)));
     extern int vscanf (__const char *__restrict __format,
			__gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")
  __attribute__ ((__format__ (__scanf__, 1, 0)));
     extern int vsscanf (__const char *__restrict __s,
			 __const char *__restrict __format,
			 __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf")
  __attribute__ ((__nothrow__))
  __attribute__ ((__format__ (__scanf__, 2, 0)));


     extern int fgetc (FILE * __stream);
     extern int getc (FILE * __stream);
     extern int getchar (void);

     extern int getc_unlocked (FILE * __stream);
     extern int getchar_unlocked (void);
     extern int fgetc_unlocked (FILE * __stream);

     extern int fputc (int __c, FILE * __stream);
     extern int putc (int __c, FILE * __stream);
     extern int putchar (int __c);

     extern int fputc_unlocked (int __c, FILE * __stream);
     extern int putc_unlocked (int __c, FILE * __stream);
     extern int putchar_unlocked (int __c);
     extern int getw (FILE * __stream);
     extern int putw (int __w, FILE * __stream);

     extern char *fgets (char *__restrict __s, int __n,
			 FILE * __restrict __stream);
     extern char *gets (char *__s);

     extern __ssize_t __getdelim (char **__restrict __lineptr,
				  size_t * __restrict __n, int __delimiter,
				  FILE * __restrict __stream);
     extern __ssize_t getdelim (char **__restrict __lineptr,
				size_t * __restrict __n, int __delimiter,
				FILE * __restrict __stream);
     extern __ssize_t getline (char **__restrict __lineptr,
			       size_t * __restrict __n,
			       FILE * __restrict __stream);

     extern int fputs (__const char *__restrict __s,
		       FILE * __restrict __stream);
     extern int puts (__const char *__s);
     extern int ungetc (int __c, FILE * __stream);
     extern size_t fread (void *__restrict __ptr, size_t __size,
			  size_t __n, FILE * __restrict __stream);
     extern size_t fwrite (__const void *__restrict __ptr, size_t __size,
			   size_t __n, FILE * __restrict __s);

     extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
				   size_t __n, FILE * __restrict __stream);
     extern size_t fwrite_unlocked (__const void *__restrict __ptr,
				    size_t __size, size_t __n,
				    FILE * __restrict __stream);

     extern int fseek (FILE * __stream, long int __off, int __whence);
     extern long int ftell (FILE * __stream);
     extern void rewind (FILE * __stream);

     extern int fseeko (FILE * __stream, __off_t __off, int __whence);
     extern __off_t ftello (FILE * __stream);

     extern int fgetpos (FILE * __restrict __stream,
			 fpos_t * __restrict __pos);
     extern int fsetpos (FILE * __stream, __const fpos_t * __pos);


     extern void clearerr (FILE * __stream) __attribute__ ((__nothrow__));
     extern int feof (FILE * __stream) __attribute__ ((__nothrow__));
     extern int ferror (FILE * __stream) __attribute__ ((__nothrow__));

     extern void clearerr_unlocked (FILE * __stream)
  __attribute__ ((__nothrow__));
     extern int feof_unlocked (FILE * __stream) __attribute__ ((__nothrow__));
     extern int ferror_unlocked (FILE * __stream)
  __attribute__ ((__nothrow__));

     extern void perror (__const char *__s);

     extern int sys_nerr;
     extern __const char *__const sys_errlist[];
     extern int fileno (FILE * __stream) __attribute__ ((__nothrow__));
     extern int fileno_unlocked (FILE * __stream)
  __attribute__ ((__nothrow__));
     extern FILE *popen (__const char *__command, __const char *__modes);
     extern int pclose (FILE * __stream);
     extern char *ctermid (char *__s) __attribute__ ((__nothrow__));
     extern void flockfile (FILE * __stream) __attribute__ ((__nothrow__));
     extern int ftrylockfile (FILE * __stream) __attribute__ ((__nothrow__));
     extern void funlockfile (FILE * __stream) __attribute__ ((__nothrow__));

     typedef int wchar_t;


     typedef struct
     {
       int quot;
       int rem;
     } div_t;
     typedef struct
     {
       long int quot;
       long int rem;
     } ldiv_t;


     __extension__ typedef struct
     {
       long long int quot;
       long long int rem;
     } lldiv_t;

     extern size_t __ctype_get_mb_cur_max (void)
  __attribute__ ((__nothrow__));

     extern double atof (__const char *__nptr)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));
     extern int atoi (__const char *__nptr) __attribute__ ((__nothrow__))
  __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
     extern long int atol (__const char *__nptr) __attribute__ ((__nothrow__))
  __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


     __extension__ extern long long int atoll (__const char *__nptr)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));


     extern double strtod (__const char *__restrict __nptr,
			   char **__restrict __endptr)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


     extern float strtof (__const char *__restrict __nptr,
			  char **__restrict __endptr)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern long double strtold (__const char *__restrict __nptr,
				 char **__restrict __endptr)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


     extern long int strtol (__const char *__restrict __nptr,
			     char **__restrict __endptr, int __base)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern unsigned long int strtoul (__const char *__restrict __nptr,
				       char **__restrict __endptr, int __base)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));

     __extension__
       extern long long int strtoq (__const char *__restrict __nptr,
				    char **__restrict __endptr, int __base)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     __extension__
       extern unsigned long long int strtouq (__const char *__restrict __nptr,
					      char **__restrict __endptr,
					      int __base)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));

     __extension__
       extern long long int strtoll (__const char *__restrict __nptr,
				     char **__restrict __endptr, int __base)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     __extension__
       extern unsigned long long int strtoull (__const char *__restrict
					       __nptr,
					       char **__restrict __endptr,
					       int __base)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));

     extern char *l64a (long int __n) __attribute__ ((__nothrow__));
     extern long int a64l (__const char *__s)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));

     typedef __u_char u_char;
     typedef __u_short u_short;
     typedef __u_int u_int;
     typedef __u_long u_long;
     typedef __quad_t quad_t;
     typedef __u_quad_t u_quad_t;
     typedef __fsid_t fsid_t;
     typedef __loff_t loff_t;
     typedef __ino_t ino_t;
     typedef __dev_t dev_t;
     typedef __gid_t gid_t;
     typedef __mode_t mode_t;
     typedef __nlink_t nlink_t;
     typedef __uid_t uid_t;
     typedef __off_t off_t;
     typedef __pid_t pid_t;
     typedef __id_t id_t;
     typedef __ssize_t ssize_t;
     typedef __daddr_t daddr_t;
     typedef __caddr_t caddr_t;
     typedef __key_t key_t;

     typedef __time_t time_t;


     typedef __clockid_t clockid_t;
     typedef __timer_t timer_t;
     typedef unsigned long int ulong;
     typedef unsigned short int ushort;
     typedef unsigned int uint;
     typedef int int8_t __attribute__ ((__mode__ (__QI__)));
     typedef int int16_t __attribute__ ((__mode__ (__HI__)));
     typedef int int32_t __attribute__ ((__mode__ (__SI__)));
     typedef int int64_t __attribute__ ((__mode__ (__DI__)));
     typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
     typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
     typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
     typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));
     typedef int register_t __attribute__ ((__mode__ (__word__)));
     typedef int __sig_atomic_t;
     typedef struct
     {
       unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
     } __sigset_t;
     typedef __sigset_t sigset_t;
     struct timespec
     {
       __time_t tv_sec;
       long int tv_nsec;
     };
     struct timeval
     {
       __time_t tv_sec;
       __suseconds_t tv_usec;
     };
     typedef __suseconds_t suseconds_t;
     typedef long int __fd_mask;
     typedef struct
     {
       __fd_mask __fds_bits[1024 / (8 * sizeof (__fd_mask))];
     }
fd_set;
     typedef __fd_mask fd_mask;

     extern int select (int __nfds, fd_set * __restrict __readfds,
			fd_set * __restrict __writefds,
			fd_set * __restrict __exceptfds,
			struct timeval *__restrict __timeout);
     extern int pselect (int __nfds, fd_set * __restrict __readfds,
			 fd_set * __restrict __writefds,
			 fd_set * __restrict __exceptfds,
			 const struct timespec *__restrict __timeout,
			 const __sigset_t * __restrict __sigmask);

     __extension__
       extern unsigned int gnu_dev_major (unsigned long long int __dev)
  __attribute__ ((__nothrow__));
     __extension__
       extern unsigned int gnu_dev_minor (unsigned long long int __dev)
  __attribute__ ((__nothrow__));
     __extension__
       extern unsigned long long int gnu_dev_makedev (unsigned int __major,
						      unsigned int __minor)
  __attribute__ ((__nothrow__));
     typedef __blkcnt_t blkcnt_t;
     typedef __fsblkcnt_t fsblkcnt_t;
     typedef __fsfilcnt_t fsfilcnt_t;
     typedef unsigned long int pthread_t;
     typedef union
     {
       char __size[36];
       long int __align;
     } pthread_attr_t;
     typedef struct __pthread_internal_slist
     {
       struct __pthread_internal_slist *__next;
     } __pthread_slist_t;
     typedef union
     {
       struct __pthread_mutex_s
       {
	 int __lock;
	 unsigned int __count;
	 int __owner;
	 int __kind;
	 unsigned int __nusers;
	 __extension__ union
	 {
	   int __spins;
	   __pthread_slist_t __list;
	 };
       } __data;
       char __size[24];
       long int __align;
     } pthread_mutex_t;
     typedef union
     {
       char __size[4];
       int __align;
     } pthread_mutexattr_t;
     typedef union
     {
       struct
       {
	 int __lock;
	 unsigned int __futex;
	 __extension__ unsigned long long int __total_seq;
	 __extension__ unsigned long long int __wakeup_seq;
	 __extension__ unsigned long long int __woken_seq;
	 void *__mutex;
	 unsigned int __nwaiters;
	 unsigned int __broadcast_seq;
       } __data;
       char __size[48];
       __extension__ long long int __align;
     } pthread_cond_t;
     typedef union
     {
       char __size[4];
       int __align;
     } pthread_condattr_t;
     typedef unsigned int pthread_key_t;
     typedef int pthread_once_t;
     typedef union
     {
       struct
       {
	 int __lock;
	 unsigned int __nr_readers;
	 unsigned int __readers_wakeup;
	 unsigned int __writer_wakeup;
	 unsigned int __nr_readers_queued;
	 unsigned int __nr_writers_queued;
	 unsigned char __flags;
	 unsigned char __shared;
	 unsigned char __pad1;
	 unsigned char __pad2;
	 int __writer;
       } __data;
       char __size[32];
       long int __align;
     } pthread_rwlock_t;
     typedef union
     {
       char __size[8];
       long int __align;
     } pthread_rwlockattr_t;
     typedef volatile int pthread_spinlock_t;
     typedef union
     {
       char __size[20];
       long int __align;
     } pthread_barrier_t;
     typedef union
     {
       char __size[4];
       int __align;
     } pthread_barrierattr_t;

     extern long int random (void) __attribute__ ((__nothrow__));
     extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__));
     extern char *initstate (unsigned int __seed, char *__statebuf,
			     size_t __statelen) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (2)));
     extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));
     struct random_data
     {
       int32_t *fptr;
       int32_t *rptr;
       int32_t *state;
       int rand_type;
       int rand_deg;
       int rand_sep;
       int32_t *end_ptr;
     };
     extern int random_r (struct random_data *__restrict __buf,
			  int32_t * __restrict __result)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int srandom_r (unsigned int __seed, struct random_data *__buf)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));
     extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
			     size_t __statelen,
			     struct random_data *__restrict __buf)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 4)));
     extern int setstate_r (char *__restrict __statebuf,
			    struct random_data *__restrict __buf)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

     extern int rand (void) __attribute__ ((__nothrow__));
     extern void srand (unsigned int __seed) __attribute__ ((__nothrow__));

     extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__));
     extern double drand48 (void) __attribute__ ((__nothrow__));
     extern double erand48 (unsigned short int __xsubi[3])
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern long int lrand48 (void) __attribute__ ((__nothrow__));
     extern long int nrand48 (unsigned short int __xsubi[3])
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern long int mrand48 (void) __attribute__ ((__nothrow__));
     extern long int jrand48 (unsigned short int __xsubi[3])
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern void srand48 (long int __seedval) __attribute__ ((__nothrow__));
     extern unsigned short int *seed48 (unsigned short int __seed16v[3])
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern void lcong48 (unsigned short int __param[7])
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     struct drand48_data
     {
       unsigned short int __x[3];
       unsigned short int __old_x[3];
       unsigned short int __c;
       unsigned short int __init;
       unsigned long long int __a;
     };
     extern int drand48_r (struct drand48_data *__restrict __buffer,
			   double *__restrict __result)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int erand48_r (unsigned short int __xsubi[3],
			   struct drand48_data *__restrict __buffer,
			   double *__restrict __result)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int lrand48_r (struct drand48_data *__restrict __buffer,
			   long int *__restrict __result)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int nrand48_r (unsigned short int __xsubi[3],
			   struct drand48_data *__restrict __buffer,
			   long int *__restrict __result)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int mrand48_r (struct drand48_data *__restrict __buffer,
			   long int *__restrict __result)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int jrand48_r (unsigned short int __xsubi[3],
			   struct drand48_data *__restrict __buffer,
			   long int *__restrict __result)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));
     extern int seed48_r (unsigned short int __seed16v[3],
			  struct drand48_data *__buffer)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int lcong48_r (unsigned short int __param[7],
			   struct drand48_data *__buffer)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

     extern void *malloc (size_t __size) __attribute__ ((__nothrow__))
  __attribute__ ((__malloc__));
     extern void *calloc (size_t __nmemb, size_t __size)
  __attribute__ ((__nothrow__)) __attribute__ ((__malloc__));


     extern void *realloc (void *__ptr, size_t __size)
  __attribute__ ((__nothrow__)) __attribute__ ((__warn_unused_result__));
     extern void free (void *__ptr) __attribute__ ((__nothrow__));

     extern void cfree (void *__ptr) __attribute__ ((__nothrow__));

     extern void *alloca (size_t __size) __attribute__ ((__nothrow__));

     extern void *valloc (size_t __size) __attribute__ ((__nothrow__))
  __attribute__ ((__malloc__));
     extern int posix_memalign (void **__memptr, size_t __alignment,
				size_t __size) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));

     extern void abort (void) __attribute__ ((__nothrow__))
  __attribute__ ((__noreturn__));
     extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));

     extern int on_exit (void (*__func) (int __status, void *__arg),
			 void *__arg) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));

     extern void exit (int __status) __attribute__ ((__nothrow__))
  __attribute__ ((__noreturn__));


     extern void _Exit (int __status) __attribute__ ((__nothrow__))
  __attribute__ ((__noreturn__));


     extern char *getenv (__const char *__name) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));

     extern char *__secure_getenv (__const char *__name)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern int putenv (char *__string) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));
     extern int setenv (__const char *__name, __const char *__value,
			int __replace) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (2)));
     extern int unsetenv (__const char *__name) __attribute__ ((__nothrow__));
     extern int clearenv (void) __attribute__ ((__nothrow__));
     extern char *mktemp (char *__template) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));
     extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1)));
     extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));

     extern int system (__const char *__command);

     extern char *realpath (__const char *__restrict __name,
			    char *__restrict __resolved)
  __attribute__ ((__nothrow__));
     typedef int (*__compar_fn_t) (__const void *, __const void *);

     extern void *bsearch (__const void *__key, __const void *__base,
			   size_t __nmemb, size_t __size,
			   __compar_fn_t __compar)
  __attribute__ ((__nonnull__ (1, 2, 5)));
     extern void qsort (void *__base, size_t __nmemb, size_t __size,
			__compar_fn_t __compar)
  __attribute__ ((__nonnull__ (1, 4)));
     extern int abs (int __x) __attribute__ ((__nothrow__))
  __attribute__ ((__const__));
     extern long int labs (long int __x) __attribute__ ((__nothrow__))
  __attribute__ ((__const__));

     __extension__ extern long long int llabs (long long int __x)
  __attribute__ ((__nothrow__)) __attribute__ ((__const__));

     extern div_t div (int __numer, int __denom)
  __attribute__ ((__nothrow__)) __attribute__ ((__const__));
     extern ldiv_t ldiv (long int __numer, long int __denom)
  __attribute__ ((__nothrow__)) __attribute__ ((__const__));


     __extension__ extern lldiv_t lldiv (long long int __numer,
					 long long int __denom)
  __attribute__ ((__nothrow__)) __attribute__ ((__const__));








     extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
			int *__restrict __sign) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (3, 4)));




     extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
			int *__restrict __sign) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (3, 4)));




     extern char *gcvt (double __value, int __ndigit, char *__buf)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3)));




     extern char *qecvt (long double __value, int __ndigit,
			 int *__restrict __decpt, int *__restrict __sign)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4)));
     extern char *qfcvt (long double __value, int __ndigit,
			 int *__restrict __decpt, int *__restrict __sign)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4)));
     extern char *qgcvt (long double __value, int __ndigit, char *__buf)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3)));




     extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
			int *__restrict __sign, char *__restrict __buf,
			size_t __len) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (3, 4, 5)));
     extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
			int *__restrict __sign, char *__restrict __buf,
			size_t __len) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (3, 4, 5)));

     extern int qecvt_r (long double __value, int __ndigit,
			 int *__restrict __decpt, int *__restrict __sign,
			 char *__restrict __buf, size_t __len)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));
     extern int qfcvt_r (long double __value, int __ndigit,
			 int *__restrict __decpt, int *__restrict __sign,
			 char *__restrict __buf, size_t __len)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (3, 4, 5)));







     extern int mblen (__const char *__s, size_t __n)
  __attribute__ ((__nothrow__));


     extern int mbtowc (wchar_t * __restrict __pwc,
			__const char *__restrict __s, size_t __n)
  __attribute__ ((__nothrow__));


     extern int wctomb (char *__s, wchar_t __wchar)
  __attribute__ ((__nothrow__));



     extern size_t mbstowcs (wchar_t * __restrict __pwcs,
			     __const char *__restrict __s, size_t __n)
  __attribute__ ((__nothrow__));

     extern size_t wcstombs (char *__restrict __s,
			     __const wchar_t * __restrict __pwcs, size_t __n)
  __attribute__ ((__nothrow__));








     extern int rpmatch (__const char *__response)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern int posix_openpt (int __oflag);
     extern int getloadavg (double __loadavg[], int __nelem)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



     extern void *memcpy (void *__restrict __dest,
			  __const void *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern void *memmove (void *__dest, __const void *__src, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));

     extern void *memccpy (void *__restrict __dest,
			   __const void *__restrict __src, int __c,
			   size_t __n) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1, 2)));

     extern void *memset (void *__s, int __c, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
     extern int memcmp (__const void *__s1, __const void *__s2, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern void *memchr (__const void *__s, int __c, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));


     extern char *strcpy (char *__restrict __dest,
			  __const char *__restrict __src)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *strncpy (char *__restrict __dest,
			   __const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *strcat (char *__restrict __dest,
			  __const char *__restrict __src)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *strncat (char *__restrict __dest,
			   __const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern int strcmp (__const char *__s1, __const char *__s2)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern int strncmp (__const char *__s1, __const char *__s2, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern int strcoll (__const char *__s1, __const char *__s2)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern size_t strxfrm (char *__restrict __dest,
			    __const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));

     typedef struct __locale_struct
     {
       struct locale_data *__locales[13];
       const unsigned short int *__ctype_b;
       const int *__ctype_tolower;
       const int *__ctype_toupper;
       const char *__names[13];
     } *__locale_t;
     typedef __locale_t locale_t;
     extern int strcoll_l (__const char *__s1, __const char *__s2,
			   __locale_t __l) __attribute__ ((__nothrow__))
  __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
     extern size_t strxfrm_l (char *__dest, __const char *__src, size_t __n,
			      __locale_t __l) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (2, 4)));
     extern char *strdup (__const char *__s) __attribute__ ((__nothrow__))
  __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
     extern char *strndup (__const char *__string, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__malloc__))
  __attribute__ ((__nonnull__ (1)));

     extern char *strchr (__const char *__s, int __c)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));
     extern char *strrchr (__const char *__s, int __c)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));


     extern size_t strcspn (__const char *__s, __const char *__reject)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern size_t strspn (__const char *__s, __const char *__accept)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern char *strpbrk (__const char *__s, __const char *__accept)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern char *strstr (__const char *__haystack, __const char *__needle)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern char *strtok (char *__restrict __s,
			  __const char *__restrict __delim)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));

     extern char *__strtok_r (char *__restrict __s,
			      __const char *__restrict __delim,
			      char **__restrict __save_ptr)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3)));
     extern char *strtok_r (char *__restrict __s,
			    __const char *__restrict __delim,
			    char **__restrict __save_ptr)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2, 3)));

     extern size_t strlen (__const char *__s)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));

     extern size_t strnlen (__const char *__string, size_t __maxlen)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));

     extern char *strerror (int __errnum) __attribute__ ((__nothrow__));

     extern int strerror_r (int __errnum, char *__buf,
			    size_t __buflen) __asm__ ("" "__xpg_strerror_r")
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (2)));
     extern char *strerror_l (int __errnum, __locale_t __l)
  __attribute__ ((__nothrow__));
     extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));
     extern void bcopy (__const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__))
  __attribute__ ((__nonnull__ (1)));
     extern int bcmp (__const void *__s1, __const void *__s2, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern char *index (__const char *__s, int __c)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));
     extern char *rindex (__const char *__s, int __c)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1)));
     extern int ffs (int __i) __attribute__ ((__nothrow__))
  __attribute__ ((__const__));
     extern int strcasecmp (__const char *__s1, __const char *__s2)
  __attribute__ ((__nothrow__)) __attribute__ ((__pure__))
  __attribute__ ((__nonnull__ (1, 2)));
     extern int strncasecmp (__const char *__s1, __const char *__s2,
			     size_t __n) __attribute__ ((__nothrow__))
  __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *strsep (char **__restrict __stringp,
			  __const char *__restrict __delim)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *strsignal (int __sig) __attribute__ ((__nothrow__));
     extern char *__stpcpy (char *__restrict __dest,
			    __const char *__restrict __src)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *stpcpy (char *__restrict __dest,
			  __const char *__restrict __src)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *__stpncpy (char *__restrict __dest,
			     __const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
     extern char *stpncpy (char *__restrict __dest,
			   __const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));


     extern int *__errno_location (void) __attribute__ ((__nothrow__))
  __attribute__ ((__const__));

     typedef unsigned char uint8_t;
     typedef unsigned short int uint16_t;
     typedef unsigned int uint32_t;
     __extension__ typedef unsigned long long int uint64_t;
     typedef signed char int_least8_t;
     typedef short int int_least16_t;
     typedef int int_least32_t;
     __extension__ typedef long long int int_least64_t;
     typedef unsigned char uint_least8_t;
     typedef unsigned short int uint_least16_t;
     typedef unsigned int uint_least32_t;
     __extension__ typedef unsigned long long int uint_least64_t;
     typedef signed char int_fast8_t;
     typedef int int_fast16_t;
     typedef int int_fast32_t;
     __extension__ typedef long long int int_fast64_t;
     typedef unsigned char uint_fast8_t;
     typedef unsigned int uint_fast16_t;
     typedef unsigned int uint_fast32_t;
     __extension__ typedef unsigned long long int uint_fast64_t;
     typedef int intptr_t;
     typedef unsigned int uintptr_t;
     __extension__ typedef long long int intmax_t;
     __extension__ typedef unsigned long long int uintmax_t;


     struct iovec
     {
       void *iov_base;
       size_t iov_len;
     };
     extern ssize_t readv (int __fd, __const struct iovec *__iovec,
			   int __count);
     extern ssize_t writev (int __fd, __const struct iovec *__iovec,
			    int __count);
     extern ssize_t preadv (int __fd, __const struct iovec *__iovec,
			    int __count, __off_t __offset);
     extern ssize_t pwritev (int __fd, __const struct iovec *__iovec,
			     int __count, __off_t __offset);

     typedef __socklen_t socklen_t;
     enum __socket_type
     {
       SOCK_STREAM = 1,
       SOCK_DGRAM = 2,
       SOCK_RAW = 3,
       SOCK_RDM = 4,
       SOCK_SEQPACKET = 5,
       SOCK_DCCP = 6,
       SOCK_PACKET = 10,
       SOCK_CLOEXEC = 02000000,
       SOCK_NONBLOCK = 04000
     };
     typedef unsigned short int sa_family_t;
     struct sockaddr
     {
       sa_family_t sa_family;
       char sa_data[14];
     };
     struct sockaddr_storage
     {
       sa_family_t ss_family;
       unsigned long int __ss_align;
       char __ss_padding[(128 - (2 * sizeof (unsigned long int)))];
     };
     enum
     {
       MSG_OOB = 0x01,
       MSG_PEEK = 0x02,
       MSG_DONTROUTE = 0x04,
       MSG_CTRUNC = 0x08,
       MSG_PROXY = 0x10,
       MSG_TRUNC = 0x20,
       MSG_DONTWAIT = 0x40,
       MSG_EOR = 0x80,
       MSG_WAITALL = 0x100,
       MSG_FIN = 0x200,
       MSG_SYN = 0x400,
       MSG_CONFIRM = 0x800,
       MSG_RST = 0x1000,
       MSG_ERRQUEUE = 0x2000,
       MSG_NOSIGNAL = 0x4000,
       MSG_MORE = 0x8000,
       MSG_CMSG_CLOEXEC = 0x40000000
     };
     struct msghdr
     {
       void *msg_name;
       socklen_t msg_namelen;
       struct iovec *msg_iov;
       size_t msg_iovlen;
       void *msg_control;
       size_t msg_controllen;
       int msg_flags;
     };
     struct cmsghdr
     {
       size_t cmsg_len;
       int cmsg_level;
       int cmsg_type;
       __extension__ unsigned char __cmsg_data[];
     };
     extern struct cmsghdr *__cmsg_nxthdr (struct msghdr *__mhdr,
					   struct cmsghdr *__cmsg)
  __attribute__ ((__nothrow__));
     enum
     {
       SCM_RIGHTS = 0x01
     };
     struct linger
     {
       int l_onoff;
       int l_linger;
     };
     struct osockaddr
     {
       unsigned short int sa_family;
       unsigned char sa_data[14];
     };
     enum
     {
       SHUT_RD = 0,
       SHUT_WR,
       SHUT_RDWR
     };
     extern int socket (int __domain, int __type, int __protocol)
  __attribute__ ((__nothrow__));
     extern int socketpair (int __domain, int __type, int __protocol,
			    int __fds[2]) __attribute__ ((__nothrow__));
     extern int bind (int __fd, __const struct sockaddr *__addr,
		      socklen_t __len) __attribute__ ((__nothrow__));
     extern int getsockname (int __fd, struct sockaddr *__restrict __addr,
			     socklen_t * __restrict __len)
  __attribute__ ((__nothrow__));
     extern int connect (int __fd, __const struct sockaddr *__addr,
			 socklen_t __len);
     extern int getpeername (int __fd, struct sockaddr *__restrict __addr,
			     socklen_t * __restrict __len)
  __attribute__ ((__nothrow__));
     extern ssize_t send (int __fd, __const void *__buf, size_t __n,
			  int __flags);
     extern ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);
     extern ssize_t sendto (int __fd, __const void *__buf, size_t __n,
			    int __flags, __const struct sockaddr *__addr,
			    socklen_t __addr_len);
     extern ssize_t recvfrom (int __fd, void *__restrict __buf, size_t __n,
			      int __flags, struct sockaddr *__restrict __addr,
			      socklen_t * __restrict __addr_len);
     extern ssize_t sendmsg (int __fd, __const struct msghdr *__message,
			     int __flags);
     extern ssize_t recvmsg (int __fd, struct msghdr *__message, int __flags);
     extern int getsockopt (int __fd, int __level, int __optname,
			    void *__restrict __optval,
			    socklen_t * __restrict __optlen)
  __attribute__ ((__nothrow__));
     extern int setsockopt (int __fd, int __level, int __optname,
			    __const void *__optval, socklen_t __optlen)
  __attribute__ ((__nothrow__));
     extern int listen (int __fd, int __n) __attribute__ ((__nothrow__));
     extern int accept (int __fd, struct sockaddr *__restrict __addr,
			socklen_t * __restrict __addr_len);
     extern int shutdown (int __fd, int __how) __attribute__ ((__nothrow__));
     extern int sockatmark (int __fd) __attribute__ ((__nothrow__));
     extern int isfdtype (int __fd, int __fdtype)
  __attribute__ ((__nothrow__));


     enum
     {
       IPPROTO_IP = 0,
       IPPROTO_HOPOPTS = 0,
       IPPROTO_ICMP = 1,
       IPPROTO_IGMP = 2,
       IPPROTO_IPIP = 4,
       IPPROTO_TCP = 6,
       IPPROTO_EGP = 8,
       IPPROTO_PUP = 12,
       IPPROTO_UDP = 17,
       IPPROTO_IDP = 22,
       IPPROTO_TP = 29,
       IPPROTO_DCCP = 33,
       IPPROTO_IPV6 = 41,
       IPPROTO_ROUTING = 43,
       IPPROTO_FRAGMENT = 44,
       IPPROTO_RSVP = 46,
       IPPROTO_GRE = 47,
       IPPROTO_ESP = 50,
       IPPROTO_AH = 51,
       IPPROTO_ICMPV6 = 58,
       IPPROTO_NONE = 59,
       IPPROTO_DSTOPTS = 60,
       IPPROTO_MTP = 92,
       IPPROTO_ENCAP = 98,
       IPPROTO_PIM = 103,
       IPPROTO_COMP = 108,
       IPPROTO_SCTP = 132,
       IPPROTO_UDPLITE = 136,
       IPPROTO_RAW = 255,
       IPPROTO_MAX
     };
     typedef uint16_t in_port_t;
     enum
     {
       IPPORT_ECHO = 7,
       IPPORT_DISCARD = 9,
       IPPORT_SYSTAT = 11,
       IPPORT_DAYTIME = 13,
       IPPORT_NETSTAT = 15,
       IPPORT_FTP = 21,
       IPPORT_TELNET = 23,
       IPPORT_SMTP = 25,
       IPPORT_TIMESERVER = 37,
       IPPORT_NAMESERVER = 42,
       IPPORT_WHOIS = 43,
       IPPORT_MTP = 57,
       IPPORT_TFTP = 69,
       IPPORT_RJE = 77,
       IPPORT_FINGER = 79,
       IPPORT_TTYLINK = 87,
       IPPORT_SUPDUP = 95,
       IPPORT_EXECSERVER = 512,
       IPPORT_LOGINSERVER = 513,
       IPPORT_CMDSERVER = 514,
       IPPORT_EFSSERVER = 520,
       IPPORT_BIFFUDP = 512,
       IPPORT_WHOSERVER = 513,
       IPPORT_ROUTESERVER = 520,
       IPPORT_RESERVED = 1024,
       IPPORT_USERRESERVED = 5000
     };
     typedef uint32_t in_addr_t;
     struct in_addr
     {
       in_addr_t s_addr;
     };
     struct in6_addr
     {
       union
       {
	 uint8_t __u6_addr8[16];
	 uint16_t __u6_addr16[8];
	 uint32_t __u6_addr32[4];
       } __in6_u;
     };
     extern const struct in6_addr in6addr_any;
     extern const struct in6_addr in6addr_loopback;
     struct sockaddr_in
     {
       sa_family_t sin_family;
       in_port_t sin_port;
       struct in_addr sin_addr;
       unsigned char sin_zero[sizeof (struct sockaddr) -
			      (sizeof (unsigned short int)) -
			      sizeof (in_port_t) - sizeof (struct in_addr)];
     };
     struct sockaddr_in6
     {
       sa_family_t sin6_family;
       in_port_t sin6_port;
       uint32_t sin6_flowinfo;
       struct in6_addr sin6_addr;
       uint32_t sin6_scope_id;
     };
     struct ip_mreq
     {
       struct in_addr imr_multiaddr;
       struct in_addr imr_interface;
     };
     struct ip_mreq_source
     {
       struct in_addr imr_multiaddr;
       struct in_addr imr_interface;
       struct in_addr imr_sourceaddr;
     };
     struct ipv6_mreq
     {
       struct in6_addr ipv6mr_multiaddr;
       unsigned int ipv6mr_interface;
     };
     struct group_req
     {
       uint32_t gr_interface;
       struct sockaddr_storage gr_group;
     };
     struct group_source_req
     {
       uint32_t gsr_interface;
       struct sockaddr_storage gsr_group;
       struct sockaddr_storage gsr_source;
     };
     struct ip_msfilter
     {
       struct in_addr imsf_multiaddr;
       struct in_addr imsf_interface;
       uint32_t imsf_fmode;
       uint32_t imsf_numsrc;
       struct in_addr imsf_slist[1];
     };
     struct group_filter
     {
       uint32_t gf_interface;
       struct sockaddr_storage gf_group;
       uint32_t gf_fmode;
       uint32_t gf_numsrc;
       struct sockaddr_storage gf_slist[1];
     };
     struct ip_opts
     {
       struct in_addr ip_dst;
       char ip_opts[40];
     };
     struct ip_mreqn
     {
       struct in_addr imr_multiaddr;
       struct in_addr imr_address;
       int imr_ifindex;
     };
     struct in_pktinfo
     {
       int ipi_ifindex;
       struct in_addr ipi_spec_dst;
       struct in_addr ipi_addr;
     };
     extern uint32_t ntohl (uint32_t __netlong) __attribute__ ((__nothrow__))
  __attribute__ ((__const__));
     extern uint16_t ntohs (uint16_t __netshort) __attribute__ ((__nothrow__))
  __attribute__ ((__const__));
     extern uint32_t htonl (uint32_t __hostlong) __attribute__ ((__nothrow__))
  __attribute__ ((__const__));
     extern uint16_t htons (uint16_t __hostshort)
  __attribute__ ((__nothrow__)) __attribute__ ((__const__));
     extern int bindresvport (int __sockfd, struct sockaddr_in *__sock_in)
  __attribute__ ((__nothrow__));
     extern int bindresvport6 (int __sockfd, struct sockaddr_in6 *__sock_in)
  __attribute__ ((__nothrow__));

     union u_sockaddr
     {
       struct sockaddr_storage sas;
       struct sockaddr sa;
       struct sockaddr_in sa_in;
       struct sockaddr_in6 sa_in6;
     };
     struct polymorphic_sockaddr
     {
       union u_sockaddr sockaddr;
       unsigned int sa_len;
     };
     union u_addr
     {
       struct in_addr ipv4_addr;
       struct in6_addr ipv6_addr;
     };
     struct polymorphic_addr
     {
       union u_addr addr;
       int addr_len;
       int family;
     };
     struct socket_data_listening
     {
       int backlog;
       struct polymorphic_sockaddr address;
       int v6only_option;
     };
     struct socket_data_communicating
     {
       struct polymorphic_sockaddr local_address;
       struct polymorphic_sockaddr remote_address;
     };
     union u_socket_data_per_state
     {
       struct socket_data_listening listening;
       struct socket_data_communicating communicating;
     };
     enum socket_state
     {
       socket_state_created,
       socket_state_listening,
       socket_state_communicating
     };
     struct socket_data
     {
       int fd;
       int type;
       int protocol;
       enum socket_state state;
       union u_socket_data_per_state data_per_state;
       int flag_data_registered;
     };
     int get_socket_type (int fd);
     void register_socket_type (int fd, int type);
     enum socket_state get_socket_state (int fd);
     void register_socket_state (int fd, enum socket_state state);
     int get_socket_protocol (int fd);
     void register_socket_protocol (int fd, int protocol);
     struct polymorphic_sockaddr *get_listening_socket_address (int fd);
     void register_listening_socket_address (int fd,
					     struct polymorphic_sockaddr *sa);
     int get_listening_socket_backlog (int fd);
     void register_listening_socket_backlog (int fd, int backlog);
     int get_listening_socket_v6only_option (int fd);
     void register_listening_socket_v6only_option (int fd, int v6only_option);
     struct polymorphic_sockaddr *get_local_socket_address (int fd);
     void register_local_socket_address (int fd,
					 struct polymorphic_sockaddr *sa);
     struct polymorphic_sockaddr *get_remote_socket_address (int fd);
     void register_remote_socket_address (int fd,
					  struct polymorphic_sockaddr *sa);
     struct socket_info_entry
     {
       struct socket_data data;
       struct
       {
	 struct socket_info_entry *le_next;
	 struct socket_info_entry **le_prev;
       } entries;
     };
     struct socket_info_list_head_type
     {
       struct socket_info_entry *lh_first;
     } socket_info_list_head;
     int socket_info_list_initialised = 0;
     void init_socket_info_list_if_needed ()
{
  if (socket_info_list_initialised == 0)
    {
      do
	{
	  (&socket_info_list_head)->lh_first = ((void *) 0);
	}
      while (0);
      socket_info_list_initialised = 1;
    }
}

struct socket_data *
get_socket_info (int fd)
{
  struct socket_info_entry *entry;
  static __thread struct socket_data *result;
  static __thread int last_fd = -1;
  if (fd != last_fd)
    {
      init_socket_info_list_if_needed ();
      result = ((void *) 0);
      for (entry = socket_info_list_head.lh_first; entry != ((void *) 0);
	   entry = entry->entries.le_next)
	{
	  if (entry->data.fd == fd)
	    {
	      result = &entry->data;
	      break;
	    }
	}
      if (result == ((void *) 0))
	{
	  entry = calloc (1, sizeof (struct socket_info_entry));
	  entry->data.fd = fd;
	  do
	    {
	      if (((entry)->entries.le_next =
		   (&socket_info_list_head)->lh_first) != ((void *) 0))
		(&socket_info_list_head)->lh_first->entries.le_prev =
		  &(entry)->entries.le_next;
	      (&socket_info_list_head)->lh_first = (entry);
	      (entry)->entries.le_prev = &(&socket_info_list_head)->lh_first;
	    }
	  while (0);
	  result = &entry->data;
	}
      last_fd = fd;
    }
  return result;
}

void
compute_socket_type (int fd, struct socket_data *data)
{
  unsigned int socktype_size;
  socktype_size = sizeof (data->type);
  getsockopt (fd, 1, 3, (char *) &data->type, &socktype_size);
}

void
compute_listening_socket_v6only_option (int fd, struct socket_data *data)
{
  unsigned int sockoption_size;
  sockoption_size = sizeof (data->data_per_state.listening.v6only_option);
  getsockopt (fd, IPPROTO_IPV6, 26,
	      (char *) &data->data_per_state.listening.v6only_option,
	      &sockoption_size);
}

void
compute_socket_protocol (int fd
			 __attribute__ ((unused)), struct socket_data *data)
{
  data->protocol = 0;
}

void
compute_listening_socket_backlog (int fd
				  __attribute__ ((unused)),
				  struct socket_data *data)
{
  data->data_per_state.listening.backlog = 128;
}

void
compute_socket_state (int fd, struct socket_data *data)
{
  unsigned int option_size, sas_size;
  unsigned int option_listening;
  union u_sockaddr sa;
  option_size = sizeof (option_listening);
  getsockopt (fd, 1, 30, (char *) &option_listening, &option_size);
  if (option_listening == 1)
    {
      data->state = socket_state_listening;
    }
  else
    {
      sas_size = sizeof (sa.sas);
      if ((getpeername (fd, &sa.sa, &sas_size) == -1)
	  && ((*__errno_location ()) == 107))
	{
	  data->state = socket_state_created;
	}
      else
	{
	  memcpy (&data->data_per_state.communicating.remote_address, &sa,
		  sizeof (union u_sockaddr));
	  data->state = socket_state_communicating;
	  data->flag_data_registered |= 0x2;
	}
    }
}

typedef int (*address_filling_function_t) (int, struct sockaddr *,
					   socklen_t *);
void
fill_address (int fd, struct polymorphic_sockaddr *psa,
	      address_filling_function_t function)
{
  psa->sa_len = sizeof (psa->sockaddr.sas);
  function (fd, &psa->sockaddr.sa, &psa->sa_len);
}

void
compute_listening_socket_address (int fd, struct socket_data *data)
{
  fill_address (fd, &data->data_per_state.listening.address, getsockname);
}

void
compute_local_socket_address (int fd, struct socket_data *data)
{
  fill_address (fd, &data->data_per_state.communicating.local_address,
		getsockname);
}

void
compute_remote_socket_address (int fd, struct socket_data *data)
{
  fill_address (fd, &data->data_per_state.communicating.remote_address,
		getpeername);
}

int
get_socket_type (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x8) == 0)
    {
      compute_socket_type (fd, data);
      data->flag_data_registered |= 0x8;
    }
  return *(&data->type);
}

void
register_socket_type (int fd, int value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->type, &value, sizeof (*(&data->type)));
  data->flag_data_registered |= 0x8;
}

enum socket_state
get_socket_state (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x40) == 0)
    {
      compute_socket_state (fd, data);
      data->flag_data_registered |= 0x40;
    }
  return *(&data->state);
}

void
register_socket_state (int fd, enum socket_state value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->state, &value, sizeof (*(&data->state)));
  data->flag_data_registered |= 0x40;
}

int
get_socket_protocol (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x10) == 0)
    {
      compute_socket_protocol (fd, data);
      data->flag_data_registered |= 0x10;
    }
  return *(&data->protocol);
}

void
register_socket_protocol (int fd, int value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->protocol, &value, sizeof (*(&data->protocol)));
  data->flag_data_registered |= 0x10;
}

int
get_listening_socket_backlog (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x20) == 0)
    {
      compute_listening_socket_backlog (fd, data);
      data->flag_data_registered |= 0x20;
    }
  return *(&data->data_per_state.listening.backlog);
}

void
register_listening_socket_backlog (int fd, int value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->data_per_state.listening.backlog, &value,
	  sizeof (*(&data->data_per_state.listening.backlog)));
  data->flag_data_registered |= 0x20;
}

int
get_listening_socket_v6only_option (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x80) == 0)
    {
      compute_listening_socket_v6only_option (fd, data);
      data->flag_data_registered |= 0x80;
    }
  return *(&data->data_per_state.listening.v6only_option);
}

void
register_listening_socket_v6only_option (int fd, int value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->data_per_state.listening.v6only_option, &value,
	  sizeof (*(&data->data_per_state.listening.v6only_option)));
  data->flag_data_registered |= 0x80;
}

struct polymorphic_sockaddr *
get_listening_socket_address (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x4) == 0)
    {
      compute_listening_socket_address (fd, data);
      data->flag_data_registered |= 0x4;
    }
  return (&data->data_per_state.listening.address);
}

void
register_listening_socket_address (int fd, struct polymorphic_sockaddr *value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->data_per_state.listening.address, value,
	  sizeof (*(&data->data_per_state.listening.address)));
  data->flag_data_registered |= 0x4;
}

struct polymorphic_sockaddr *
get_local_socket_address (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x1) == 0)
    {
      compute_local_socket_address (fd, data);
      data->flag_data_registered |= 0x1;
    }
  return (&data->data_per_state.communicating.local_address);
}

void
register_local_socket_address (int fd, struct polymorphic_sockaddr *value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->data_per_state.communicating.local_address, value,
	  sizeof (*(&data->data_per_state.communicating.local_address)));
  data->flag_data_registered |= 0x1;
}

struct polymorphic_sockaddr *
get_remote_socket_address (int fd)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  if ((data->flag_data_registered & 0x2) == 0)
    {
      compute_remote_socket_address (fd, data);
      data->flag_data_registered |= 0x2;
    }
  return (&data->data_per_state.communicating.remote_address);
}

void
register_remote_socket_address (int fd, struct polymorphic_sockaddr *value)
{
  struct socket_data *data;
  data = get_socket_info (fd);
  memcpy (&data->data_per_state.communicating.remote_address, value,
	  sizeof (*(&data->data_per_state.communicating.remote_address)));
  data->flag_data_registered |= 0x2;
}
