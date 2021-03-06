/*! \file */
/*
 * kmp.h -- KPTS runtime header file.
 */

//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//

#ifndef KMP_H
#define KMP_H

#ifdef __cplusplus
extern "C" {
#endif

#if 0
/*!
 *  * The ident structure that describes a source location.
 */
typedef struct ident {
  kmp_int32 reserved_1; /**<  might be used in Fortran; see above  */
  kmp_int32 flags;      /**<  also f.flags; KMP_IDENT_xxx flags; KMP_IDENT_KMPC
                          identifies this union member  */
  kmp_int32 reserved_2; /**<  not really used in Fortran any more; see above */
  kmp_int32 reserved_3; /**< source[4] in Fortran, do not use for C++  */
  char const *psource;  /**< String describing the source location.
                          The string is composed of semi-colon separated fields
                          which describe the source file, the function and a
                          pair of line numbers that delimit the construct. */
} ident_t;
#endif

/*!
Values for bit flags used in the ident_t to describe the fields.
*/
/*! Use trampoline for internal microtasks */
#define KMP_IDENT_IMB 0x01
/*! Use c-style ident structure */
#define KMP_IDENT_KMPC 0x02
/* 0x04 is no longer used */
/*! Entry point generated by auto-parallelization */
#define KMP_IDENT_AUTOPAR 0x08
/*! Compiler generates atomic reduction option for kmpc_reduce* */
#define KMP_IDENT_ATOMIC_REDUCE 0x10
/*! To mark a 'barrier' directive in user code */
#define KMP_IDENT_BARRIER_EXPL 0x20
/*! To Mark implicit barriers. */
#define KMP_IDENT_BARRIER_IMPL 0x0040
#define KMP_IDENT_BARRIER_IMPL_MASK 0x01C0
#define KMP_IDENT_BARRIER_IMPL_FOR 0x0040
#define KMP_IDENT_BARRIER_IMPL_SECTIONS 0x00C0

#define KMP_IDENT_BARRIER_IMPL_SINGLE 0x0140
#define KMP_IDENT_BARRIER_IMPL_WORKSHARE 0x01C0

#define KMP_IDENT_WORK_LOOP 0x200 // static loop
#define KMP_IDENT_WORK_SECTIONS 0x400 // sections
#define KMP_IDENT_WORK_DISTRIBUTE 0x800 // distribute

extern kmp_int32 __kmpc_global_thread_num(ident_t* loc);
extern kmp_int32 __kmpc_global_num_threads(ident_t* loc);
extern void __kmpc_critical(ident_t* loc, kmp_int32 global_tid,
                            kmp_critical_name* name);
extern void __kmpc_end_critical(ident_t*, kmp_int32 global_tid,
                                kmp_critical_name*);
extern void __kmpc_barrier(ident_t* loc, kmp_int32 global_tid);
extern kmp_int32 __kmpc_barrier_master(ident_t* loc, kmp_int32 global_tid);
extern void *__kmpc_threadprivate(ident_t* loc, kmp_int32 global_tid,
                                      void* data, size_t size);
extern void *__kmpc_threadprivate_cached(ident_t* loc,
                                         kmp_int32 global_tid,
                                         void* data, size_t size,
                                         void*** cache);
extern void __kmpc_fork_call(ident_t* loc, kmp_int32 nargs,
                             void* microtask, ...);
extern void __kmpc_fork_call_fortran(ident_t* loc, kmp_int32 nargs,
                                     void* microtask, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* KMP_H */
