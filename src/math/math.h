/*
 * @BEGIN LICENSE
 *
 * ambit: C++ library for the implementation of tensor product calculations
 *        through a clean, concise user interface.
 *
 * Copyright (c) 2014-2017 Ambit developers.
 *
 * The copyrights for code used from other parties are included in
 * the corresponding files.
 *
 * This file is part of ambit.
 *
 * Ambit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * Ambit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with ambit; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * @END LICENSE
 */

#if !defined(TENSOR_MATH_H)
#define TENSOR_MATH_H

namespace ambit
{

// BLAS 1 Double routines
void C_DROT(unsigned long int ntot, double *x, int incx, double *y, int incy,
            double costheta, double sintheta);
void C_DSWAP(unsigned long int length, double *x, int incx, double *y,
             int inc_y);
void C_DSCAL(unsigned long int len, double alpha, double *vec, int inc);
void C_DCOPY(unsigned long int length, double *x, int inc_x, double *y,
             int inc_y);
void C_DAXPY(unsigned long int length, double a, double *x, int inc_x,
             double *y, int inc_y);
double C_DDOT(unsigned long int n, double *X, int inc_x, double *Y, int inc_y);
double C_DNRM2(unsigned long int n, double *X, int inc_x);
double C_DASUM(unsigned long int n, double *X, int inc_x);
unsigned long int C_IDAMAX(unsigned long int n, double *X, int inc_x);

// BLAS 2 Double routines
void C_DGBMV(char trans, int m, int n, int kl, int ku, double alpha, double *a,
             int lda, double *x, int incx, double beta, double *y, int incy);
void C_DGEMV(char trans, int m, int n, double alpha, double *a, int lda,
             double *x, int incx, double beta, double *y, int incy);
void C_DGER(int m, int n, double alpha, double *x, int incx, double *y,
            int incy, double *a, int lda);
void C_DSBMV(char uplo, int n, int k, double alpha, double *a, int lda,
             double *x, int incx, double beta, double *y, int incy);
void C_DSPMV(char uplo, int n, double alpha, double *ap, double *x, int incx,
             double beta, double *y, int incy);
void C_DSPR(char uplo, int n, double alpha, double *x, int incx, double *ap);
void C_DSPR2(char uplo, int n, double alpha, double *x, int incx, double *y,
             int incy, double *ap);
void C_DSYMV(char uplo, int n, double alpha, double *a, int lda, double *x,
             int incx, double beta, double *y, int incy);
void C_DSYR(char uplo, int n, double alpha, double *x, int incx, double *a,
            int lda);
void C_DSYR2(char uplo, int n, double alpha, double *x, int incx, double *y,
             int incy, double *a, int lda);
void C_DTBMV(char uplo, char trans, char diag, int n, int k, double *a, int lda,
             double *x, int incx);
void C_DTBSV(char uplo, char trans, char diag, int n, int k, double *a, int lda,
             double *x, int incx);
void C_DTPMV(char uplo, char trans, char diag, int n, double *ap, double *x,
             int incx);
void C_DTPSV(char uplo, char trans, char diag, int n, double *ap, double *x,
             int incx);
void C_DTRMV(char uplo, char trans, char diag, int n, double *a, int lda,
             double *x, int incx);
void C_DTRSM(char side, char uplo, char transa, char diag, int m, int n,
             double alpha, double *a, int lda, double *b, int ldb);

// BLAS 3 Double routines
void C_DGEMM(char transa, char transb, int m, int n, int k, double alpha,
             double *a, int lda, double *b, int ldb, double beta, double *c,
             int ldc);
void C_DSYMM(char side, char uplo, int m, int n, double alpha, double *a,
             int lda, double *b, int ldb, double beta, double *c, int ldc);
void C_DTRMM(char side, char uplo, char transa, char diag, int m, int n,
             double alpha, double *a, int lda, double *b, int ldb);
void C_DSYRK(char uplo, char trans, int n, int k, double alpha, double *a,
             int lda, double beta, double *c, int ldc);
void C_DSYR2K(char uplo, char trans, int n, int k, double alpha, double *a,
              int lda, double *b, int ldb, double beta, double *c, int ldc);
void C_DTRSV(char uplo, char trans, char diag, int n, double *a, int lda,
             double *x, int incx);

// => LAPACK <=
int C_DGESVD(char jobu, char jobvt, int m, int n, double *A, int lda, double *S,
             double *U, int ldu, double *Vt, int ldvt, double *work, int lwork);
int C_DBDSDC(char uplo, char compq, int n, double *d, double *e, double *u,
             int ldu, double *vt, int ldvt, double *q, int *iq, double *work,
             int *iwork);
int C_DBDSQR(char uplo, int n, int ncvt, int nru, int ncc, double *d, double *e,
             double *vt, int ldvt, double *u, int ldu, double *c, int ldc,
             double *work);
int C_DDISNA(char job, int m, int n, double *d, double *sep);
int C_DGBBRD(char vect, int m, int n, int ncc, int kl, int ku, double *ab,
             int ldab, double *d, double *e, double *q, int ldq, double *pt,
             int ldpt, double *c, int ldc, double *work);
int C_DGBCON(char norm, int n, int kl, int ku, double *ab, int ldab, int *ipiv,
             double anorm, double *rcond, double *work, int *iwork);
int C_DGBEQU(int m, int n, int kl, int ku, double *ab, int ldab, double *r,
             double *c, double *rowcnd, double *colcnd, double *amax);
int C_DGBRFS(char trans, int n, int kl, int ku, int nrhs, double *ab, int ldab,
             double *afb, int ldafb, int *ipiv, double *b, int ldb, double *x,
             int ldx, double *ferr, double *berr, double *work, int *iwork);
int C_DGBSV(int n, int kl, int ku, int nrhs, double *ab, int ldab, int *ipiv,
            double *b, int ldb);
int C_DGBSVX(char fact, char trans, int n, int kl, int ku, int nrhs, double *ab,
             int ldab, double *afb, int ldafb, int *ipiv, char equed, double *r,
             double *c, double *b, int ldb, double *x, int ldx, double *rcond,
             double *ferr, double *berr, double *work, int *iwork);
int C_DGBTRF(int m, int n, int kl, int ku, double *ab, int ldab, int *ipiv);
int C_DGBTRS(char trans, int n, int kl, int ku, int nrhs, double *ab, int ldab,
             int *ipiv, double *b, int ldb);
int C_DGEBAK(char job, char side, int n, int ilo, int ihi, double *scale, int m,
             double *v, int ldv);
int C_DGEBAL(char job, int n, double *a, int lda, int *ilo, int *ihi,
             double *scale);
int C_DGEBRD(int m, int n, double *a, int lda, double *d, double *e,
             double *tauq, double *taup, double *work, int lwork);
int C_DGECON(char norm, int n, double *a, int lda, double anorm, double *rcond,
             double *work, int *iwork);
int C_DGEEQU(int m, int n, double *a, int lda, double *r, double *c,
             double *rowcnd, double *colcnd, double *amax);
int C_DGEES(char jobvs, char sort, int n, double *a, int lda, int *sdim,
            double *wr, double *wi, double *vs, int ldvs, double *work,
            int lwork);
int C_DGEESX(char jobvs, char sort, char sense, int n, double *a, int lda,
             int *sdim, double *wr, double *wi, double *vs, int ldvs,
             double *rconde, double *rcondv, double *work, int lwork,
             int *iwork, int liwork);
int C_DGEEV(char jobvl, char jobvr, int n, double *a, int lda, double *wr,
            double *wi, double *vl, int ldvl, double *vr, int ldvr,
            double *work, int lwork);
int C_DGEEVX(char balanc, char jobvl, char jobvr, char sense, int n, double *a,
             int lda, double *wr, double *wi, double *vl, int ldvl, double *vr,
             int ldvr, int *ilo, int *ihi, double *scale, double *abnrm,
             double *rconde, double *rcondv, double *work, int lwork,
             int *iwork);
int C_DGEGS(char jobvsl, char jobvsr, int n, double *a, int lda, double *b,
            int ldb, double *alphar, double *alphai, double *beta, double *vsl,
            int ldvsl, double *vsr, int ldvsr, double *work, int lwork);
int C_DGEGV(char jobvl, char jobvr, int n, double *a, int lda, double *b,
            int ldb, double *alphar, double *alphai, double *beta, double *vl,
            int ldvl, double *vr, int ldvr, double *work, int lwork);
int C_DGEHRD(int n, int ilo, int ihi, double *a, int lda, double *tau,
             double *work, int lwork);
int C_DGELQF(int m, int n, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DGELS(char trans, int m, int n, int nrhs, double *a, int lda, double *b,
            int ldb, double *work, int lwork);
int C_DGELSD(int m, int n, int nrhs, double *a, int lda, double *b, int ldb,
             double *s, double rcond, int *rank, double *work, int lwork,
             int *iwork);
int C_DGELSS(int m, int n, int nrhs, double *a, int lda, double *b, int ldb,
             double *s, double rcond, int *rank, double *work, int lwork);
int C_DGELSX(int m, int n, int nrhs, double *a, int lda, double *b, int ldb,
             int *jpvt, double rcond, int *rank, double *work);
int C_DGELSY(int m, int n, int nrhs, double *a, int lda, double *b, int ldb,
             int *jpvt, double rcond, int *rank, double *work, int lwork);
int C_DGEQLF(int m, int n, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DGEQP3(int m, int n, double *a, int lda, int *jpvt, double *tau,
             double *work, int lwork);
int C_DGEQPF(int m, int n, double *a, int lda, int *jpvt, double *tau,
             double *work);
int C_DGEQRF(int m, int n, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DGERFS(char trans, int n, int nrhs, double *a, int lda, double *af,
             int ldaf, int *ipiv, double *b, int ldb, double *x, int ldx,
             double *ferr, double *berr, double *work, int *iwork);
int C_DGERQF(int m, int n, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DGESDD(char jobz, int m, int n, double *a, int lda, double *s, double *u,
             int ldu, double *vt, int ldvt, double *work, int lwork,
             int *iwork);
int C_DGESV(int n, int nrhs, double *a, int lda, int *ipiv, double *b, int ldb);
int C_DGESVX(char fact, char trans, int n, int nrhs, double *a, int lda,
             double *af, int ldaf, int *ipiv, char equed, double *r, double *c,
             double *b, int ldb, double *x, int ldx, double *rcond,
             double *ferr, double *berr, double *work, int *iwork);
int C_DGETRF(int m, int n, double *a, int lda, int *ipiv);
int C_DGETRI(int n, double *a, int lda, int *ipiv, double *work, int lwork);
int C_DGETRS(char trans, int n, int nrhs, double *a, int lda, int *ipiv,
             double *b, int ldb);
int C_DGGBAK(char job, char side, int n, int ilo, int ihi, double *lscale,
             double *rscale, int m, double *v, int ldv);
int C_DGGBAL(char job, int n, double *a, int lda, double *b, int ldb, int *ilo,
             int *ihi, double *lscale, double *rscale, double *work);
int C_DGGES(char jobvsl, char jobvsr, char sort, int n, double *a, int lda,
            double *b, int ldb, int *sdim, double *alphar, double *alphai,
            double *beta, double *vsl, int ldvsl, double *vsr, int ldvsr,
            double *work, int lwork);
int C_DGGESX(char jobvsl, char jobvsr, char sort, char sense, int n, double *a,
             int lda, double *b, int ldb, int *sdim, double *alphar,
             double *alphai, double *beta, double *vsl, int ldvsl, double *vsr,
             int ldvsr, double *rconde, double *rcondv, double *work, int lwork,
             int *iwork, int liwork);
int C_DGGEV(char jobvl, char jobvr, int n, double *a, int lda, double *b,
            int ldb, double *alphar, double *alphai, double *beta, double *vl,
            int ldvl, double *vr, int ldvr, double *work, int lwork);
int C_DGGEVX(char balanc, char jobvl, char jobvr, char sense, int n, double *a,
             int lda, double *b, int ldb, double *alphar, double *alphai,
             double *beta, double *vl, int ldvl, double *vr, int ldvr, int *ilo,
             int *ihi, double *lscale, double *rscale, double *abnrm,
             double *bbnrm, double *rconde, double *rcondv, double *work,
             int lwork, int *iwork);
int C_DGGGLM(int n, int m, int p, double *a, int lda, double *b, int ldb,
             double *d, double *x, double *y, double *work, int lwork);
int C_DGGHRD(char compq, char compz, int n, int ilo, int ihi, double *a,
             int lda, double *b, int ldb, double *q, int ldq, double *z,
             int ldz);
int C_DGGLSE(int m, int n, int p, double *a, int lda, double *b, int ldb,
             double *c, double *d, double *x, double *work, int lwork);
int C_DGGQRF(int n, int m, int p, double *a, int lda, double *taua, double *b,
             int ldb, double *taub, double *work, int lwork);
int C_DGGRQF(int m, int p, int n, double *a, int lda, double *taua, double *b,
             int ldb, double *taub, double *work, int lwork);
int C_DGGSVD(char jobu, char jobv, char jobq, int m, int n, int p, int *k,
             int *l, double *a, int lda, double *b, int ldb, double *alpha,
             double *beta, double *u, int ldu, double *v, int ldv, double *q,
             int ldq, double *work, int *iwork);
int C_DGGSVP(char jobu, char jobv, char jobq, int m, int p, int n, double *a,
             int lda, double *b, int ldb, double tola, double tolb, int *k,
             int *l, double *u, int ldu, double *v, int ldv, double *q, int ldq,
             int *iwork, double *tau, double *work);
int C_DGTCON(char norm, int n, double *dl, double *d, double *du, double *du2,
             int *ipiv, double anorm, double *rcond, double *work, int *iwork);
int C_DGTRFS(char trans, int n, int nrhs, double *dl, double *d, double *du,
             double *dlf, double *df, double *duf, double *du2, int *ipiv,
             double *b, int ldb, double *x, int ldx, double *ferr, double *berr,
             double *work, int *iwork);
int C_DGTSV(int n, int nrhs, double *dl, double *d, double *du, double *b,
            int ldb);
int C_DGTSVX(char fact, char trans, int n, int nrhs, double *dl, double *d,
             double *du, double *dlf, double *df, double *duf, double *du2,
             int *ipiv, double *b, int ldb, double *x, int ldx, double *rcond);
int C_DGTTRF(int n, double *dl, double *d, double *du, double *du2, int *ipiv);
int C_DGTTRS(char trans, int n, int nrhs, double *dl, double *d, double *du,
             double *du2, int *ipiv, double *b, int ldb);
int C_DHGEQZ(char job, char compq, char compz, int n, int ilo, int ihi,
             double *h, int ldh, double *t, int ldt, double *alphar,
             double *alphai, double *beta, double *q, int ldq, double *z,
             int ldz, double *work, int lwork);
int C_DHSEIN(char side, char eigsrc, char initv, int n, double *h, int ldh,
             double *wr, double *wi, double *vl, int ldvl, double *vr, int ldvr,
             int mm, int *m, double *work, int *ifaill, int *ifailr);
int C_DHSEQR(char job, char compz, int n, int ilo, int ihi, double *h, int ldh,
             double *wr, double *wi, double *z, int ldz, double *work,
             int lwork);
int C_DOPGTR(char uplo, int n, double *ap, double *tau, double *q, int ldq,
             double *work);
int C_DOPMTR(char side, char uplo, char trans, int m, int n, double *ap,
             double *tau, double *c, int ldc, double *work);
int C_DORGBR(char vect, int m, int n, int k, double *a, int lda, double *tau,
             double *work, int lwork);
int C_DORGHR(int n, int ilo, int ihi, double *a, int lda, double *tau,
             double *work, int lwork);
int C_DORGLQ(int m, int n, int k, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DORGQL(int m, int n, int k, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DORGQR(int m, int n, int k, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DORGRQ(int m, int n, int k, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DORGTR(char uplo, int n, double *a, int lda, double *tau, double *work,
             int lwork);
int C_DORMBR(char vect, char side, char trans, int m, int n, int k, double *a,
             int lda, double *tau, double *c, int ldc, double *work, int lwork);
int C_DORMHR(char side, char trans, int m, int n, int ilo, int ihi, double *a,
             int lda, double *tau, double *c, int ldc, double *work, int lwork);
int C_DORMLQ(char side, char trans, int m, int n, int k, double *a, int lda,
             double *tau, double *c, int ldc, double *work, int lwork);
int C_DORMQL(char side, char trans, int m, int n, int k, double *a, int lda,
             double *tau, double *c, int ldc, double *work, int lwork);
int C_DORMQR(char side, char trans, int m, int n, int k, double *a, int lda,
             double *tau, double *c, int ldc, double *work, int lwork);
int C_DORMR3(char side, char trans, int m, int n, int k, int l, double *a,
             int lda, double *tau, double *c, int ldc, double *work);
int C_DORMRQ(char side, char trans, int m, int n, int k, double *a, int lda,
             double *tau, double *c, int ldc, double *work, int lwork);
int C_DORMRZ(char side, char trans, int m, int n, int k, int l, double *a,
             int lda, double *tau, double *c, int ldc, double *work, int lwork);
int C_DORMTR(char side, char uplo, char trans, int m, int n, double *a, int lda,
             double *tau, double *c, int ldc, double *work, int lwork);
int C_DPBCON(char uplo, int n, int kd, double *ab, int ldab, double anorm,
             double *rcond, double *work, int *iwork);
int C_DPBEQU(char uplo, int n, int kd, double *ab, int ldab, double *s,
             double *scond, double *amax);
int C_DPBRFS(char uplo, int n, int kd, int nrhs, double *ab, int ldab,
             double *afb, int ldafb, double *b, int ldb, double *x, int ldx,
             double *ferr, double *berr, double *work, int *iwork);
int C_DPBSTF(char uplo, int n, int kd, double *ab, int ldab);
int C_DPBSV(char uplo, int n, int kd, int nrhs, double *ab, int ldab, double *b,
            int ldb);
int C_DPBSVX(char fact, char uplo, int n, int kd, int nrhs, double *ab,
             int ldab, double *afb, int ldafb, char equed, double *s, double *b,
             int ldb, double *x, int ldx, double *rcond, double *ferr,
             double *berr, double *work, int *iwork);
int C_DPBTRF(char uplo, int n, int kd, double *ab, int ldab);
int C_DPBTRS(char uplo, int n, int kd, int nrhs, double *ab, int ldab,
             double *b, int ldb);
int C_DPOCON(char uplo, int n, double *a, int lda, double anorm, double *rcond,
             double *work, int *iwork);
int C_DPOEQU(int n, double *a, int lda, double *s, double *scond, double *amax);
int C_DPORFS(char uplo, int n, int nrhs, double *a, int lda, double *af,
             int ldaf, double *b, int ldb, double *x, int ldx, double *ferr,
             double *berr, double *work, int *iwork);
int C_DPOSV(char uplo, int n, int nrhs, double *a, int lda, double *b, int ldb);
int C_DPOSVX(char fact, char uplo, int n, int nrhs, double *a, int lda,
             double *af, int ldaf, char equed, double *s, double *b, int ldb,
             double *x, int ldx, double *rcond, double *ferr, double *berr,
             double *work, int *iwork);
int C_DPOTRF(char uplo, int n, double *a, int lda);
int C_DPOTRI(char uplo, int n, double *a, int lda);
int C_DPOTRS(char uplo, int n, int nrhs, double *a, int lda, double *b,
             int ldb);
int C_DPPCON(char uplo, int n, double *ap, double anorm, double *rcond,
             double *work, int *iwork);
int C_DPPEQU(char uplo, int n, double *ap, double *s, double *scond,
             double *amax);
int C_DPPRFS(char uplo, int n, int nrhs, double *ap, double *afp, double *b,
             int ldb, double *x, int ldx, double *ferr, double *berr,
             double *work, int *iwork);
int C_DPPSV(char uplo, int n, int nrhs, double *ap, double *b, int ldb);
int C_DPPSVX(char fact, char uplo, int n, int nrhs, double *ap, double *afp,
             char equed, double *s, double *b, int ldb, double *x, int ldx,
             double *rcond, double *ferr, double *berr, double *work,
             int *iwork);
int C_DPPTRF(char uplo, int n, double *ap);
int C_DPPTRI(char uplo, int n, double *ap);
int C_DPPTRS(char uplo, int n, int nrhs, double *ap, double *b, int ldb);
int C_DPTCON(int n, double *d, double *e, double anorm, double *rcond,
             double *work);
int C_DPTEQR(char compz, int n, double *d, double *e, double *z, int ldz,
             double *work);
int C_DPTRFS(int n, int nrhs, double *d, double *e, double *df, double *ef,
             double *b, int ldb, double *x, int ldx, double *ferr, double *berr,
             double *work);
int C_DPTSV(int n, int nrhs, double *d, double *e, double *b, int ldb);
int C_DPTSVX(char fact, int n, int nrhs, double *d, double *e, double *df,
             double *ef, double *b, int ldb, double *x, int ldx, double *rcond,
             double *ferr, double *berr, double *work);
int C_DPTTRF(int n, double *d, double *e);
int C_DPTTRS(int n, int nrhs, double *d, double *e, double *b, int ldb);
int C_DSBEV(char jobz, char uplo, int n, int kd, double *ab, int ldab,
            double *w, double *z, int ldz, double *work);
int C_DSBEVD(char jobz, char uplo, int n, int kd, double *ab, int ldab,
             double *w, double *z, int ldz, double *work, int lwork, int *iwork,
             int liwork);
int C_DSBEVX(char jobz, char range, char uplo, int n, int kd, double *ab,
             int ldab, double *q, int ldq, double vl, double vu, int il, int iu,
             double abstol, int *m, double *w, double *z, int ldz, double *work,
             int *iwork, int *ifail);
int C_DSBGST(char vect, char uplo, int n, int ka, int kb, double *ab, int ldab,
             double *bb, int ldbb, double *x, int ldx, double *work);
int C_DSBGV(char jobz, char uplo, int n, int ka, int kb, double *ab, int ldab,
            double *bb, int ldbb, double *w, double *z, int ldz, double *work);
int C_DSBGVD(char jobz, char uplo, int n, int ka, int kb, double *ab, int ldab,
             double *bb, int ldbb, double *w, double *z, int ldz, double *work,
             int lwork, int *iwork, int liwork);
int C_DSBGVX(char jobz, char range, char uplo, int n, int ka, int kb,
             double *ab, int ldab, double *bb, int ldbb, double *q, int ldq,
             double vl, double vu, int il, int iu, double abstol, int *m,
             double *w, double *z, int ldz, double *work, int *iwork,
             int *ifail);
int C_DSBTRD(char vect, char uplo, int n, int kd, double *ab, int ldab,
             double *d, double *e, double *q, int ldq, double *work);
int C_DSGESV(int n, int nrhs, double *a, int lda, int *ipiv, double *b, int ldb,
             double *x, int ldx, double *work, int *iter);
int C_DSPCON(char uplo, int n, double *ap, int *ipiv, double anorm,
             double *rcond, double *work, int *iwork);
int C_DSPEV(char jobz, char uplo, int n, double *ap, double *w, double *z,
            int ldz, double *work);
int C_DSPEVD(char jobz, char uplo, int n, double *ap, double *w, double *z,
             int ldz, double *work, int lwork, int *iwork, int liwork);
int C_DSPEVX(char jobz, char range, char uplo, int n, double *ap, double vl,
             double vu, int il, int iu, double abstol, int *m, double *w,
             double *z, int ldz, double *work, int *iwork, int *ifail);
int C_DSPGST(int itype, char uplo, int n, double *ap, double *bp);
int C_DSPGV(int itype, char jobz, char uplo, int n, double *ap, double *bp,
            double *w, double *z, int ldz, double *work);
int C_DSPGVD(int itype, char jobz, char uplo, int n, double *ap, double *bp,
             double *w, double *z, int ldz, double *work, int lwork, int *iwork,
             int liwork);
int C_DSPGVX(int itype, char jobz, char range, char uplo, int n, double *ap,
             double *bp, double vl, double vu, int il, int iu, double abstol,
             int *m, double *w, double *z, int ldz, double *work, int *iwork,
             int *ifail);
int C_DSPRFS(char uplo, int n, int nrhs, double *ap, double *afp, int *ipiv,
             double *b, int ldb, double *x, int ldx, double *ferr, double *berr,
             double *work, int *iwork);
int C_DSPSV(char uplo, int n, int nrhs, double *ap, int *ipiv, double *b,
            int ldb);
int C_DSPSVX(char fact, char uplo, int n, int nrhs, double *ap, double *afp,
             int *ipiv, double *b, int ldb, double *x, int ldx, double *rcond);
int C_DSPTRD(char uplo, int n, double *ap, double *d, double *e, double *tau);
int C_DSPTRF(char uplo, int n, double *ap, int *ipiv);
int C_DSPTRI(char uplo, int n, double *ap, int *ipiv, double *work);
int C_DSPTRS(char uplo, int n, int nrhs, double *ap, int *ipiv, double *b,
             int ldb);
int C_DSTEBZ(char range, char order, int n, double vl, double vu, int il,
             int iu, double abstol, double *d, double *e, int *m, int *nsplit,
             double *w, int *iblock, int *isplit, double *work, int *iwork);
int C_DSTEDC(char compz, int n, double *d, double *e, double *z, int ldz,
             double *work, int lwork, int *iwork, int liwork);
int C_DSTEGR(char jobz, char range, int n, double *d, double *e, double vl,
             double vu, int il, int iu, double abstol, int *m, double *w,
             double *z, int ldz, int *isuppz, double *work, int lwork,
             int *iwork, int liwork);
int C_DSTEIN(int n, double *d, double *e, int m, double *w, int *iblock,
             int *isplit, double *z, int ldz, double *work, int *iwork,
             int *ifail);
int C_DSTEQR(char compz, int n, double *d, double *e, double *z, int ldz,
             double *work);
int C_DSTERF(int n, double *d, double *e);
int C_DSTEV(char jobz, int n, double *d, double *e, double *z, int ldz,
            double *work);
int C_DSTEVD(char jobz, int n, double *d, double *e, double *z, int ldz,
             double *work, int lwork, int *iwork, int liwork);
int C_DSTEVR(char jobz, char range, int n, double *d, double *e, double vl,
             double vu, int il, int iu, double abstol, int *m, double *w,
             double *z, int ldz, int *isuppz, double *work, int lwork,
             int *iwork, int liwork);
int C_DSTEVX(char jobz, char range, int n, double *d, double *e, double vl,
             double vu, int il, int iu, double abstol, int *m, double *w,
             double *z, int ldz, double *work, int *iwork, int *ifail);
int C_DSYCON(char uplo, int n, double *a, int lda, int *ipiv, double anorm,
             double *rcond, double *work, int *iwork);
int C_DSYEV(char jobz, char uplo, int n, double *a, int lda, double *w,
            double *work, int lwork);
int C_DSYEVD(char jobz, char uplo, int n, double *a, int lda, double *w,
             double *work, int lwork, int *iwork, int liwork);
int C_DSYEVR(char jobz, char range, char uplo, int n, double *a, int lda,
             double vl, double vu, int il, int iu, double abstol, int *m,
             double *w, double *z, int ldz, int *isuppz, double *work,
             int lwork, int *iwork, int liwork);
int C_DSYEVX(char jobz, char range, char uplo, int n, double *a, int lda,
             double vl, double vu, int il, int iu, double abstol, int *m,
             double *w, double *z, int ldz, double *work, int lwork, int *iwork,
             int *ifail);
int C_DSYGST(int itype, char uplo, int n, double *a, int lda, double *b,
             int ldb);
int C_DSYGV(int itype, char jobz, char uplo, int n, double *a, int lda,
            double *b, int ldb, double *w, double *work, int lwork);
int C_DSYGVD(int itype, char jobz, char uplo, int n, double *a, int lda,
             double *b, int ldb, double *w, double *work, int lwork, int *iwork,
             int liwork);
int C_DSYGVX(int itype, char jobz, char range, char uplo, int n, double *a,
             int lda, double *b, int ldb, double vl, double vu, int il, int iu,
             double abstol, int *m, double *w, double *z, int ldz, double *work,
             int lwork, int *iwork, int *ifail);
int C_DSYRFS(char uplo, int n, int nrhs, double *a, int lda, double *af,
             int ldaf, int *ipiv, double *b, int ldb, double *x, int ldx,
             double *ferr, double *berr, double *work, int *iwork);
int C_DSYSV(char uplo, int n, int nrhs, double *a, int lda, int *ipiv,
            double *b, int ldb, double *work, int lwork);
int C_DSYSVX(char fact, char uplo, int n, int nrhs, double *a, int lda,
             double *af, int ldaf, int *ipiv, double *b, int ldb, double *x,
             int ldx, double *rcond);
int C_DSYTRD(char uplo, int n, double *a, int lda, double *d, double *e,
             double *tau, double *work, int lwork);
int C_DSYTRF(char uplo, int n, double *a, int lda, int *ipiv, double *work,
             int lwork);
int C_DSYTRI(char uplo, int n, double *a, int lda, int *ipiv, double *work);
int C_DSYTRS(char uplo, int n, int nrhs, double *a, int lda, int *ipiv,
             double *b, int ldb);
int C_DTBCON(char norm, char uplo, char diag, int n, int kd, double *ab,
             int ldab, double *rcond, double *work, int *iwork);
int C_DTBRFS(char uplo, char trans, char diag, int n, int kd, int nrhs,
             double *ab, int ldab, double *b, int ldb, double *x, int ldx,
             double *ferr, double *berr, double *work, int *iwork);
int C_DTBTRS(char uplo, char trans, char diag, int n, int kd, int nrhs,
             double *ab, int ldab, double *b, int ldb);
int C_DTGEVC(char side, char howmny, int n, double *s, int lds, double *p,
             int ldp, double *vl, int ldvl, double *vr, int ldvr, int mm,
             int *m, double *work);
int C_DTGEXC(int n, double *a, int lda, double *b, int ldb, double *q, int ldq,
             double *z, int ldz, int *ifst, int *ilst, double *work, int lwork);
int C_DTGSEN(int ijob, int n, double *a, int lda, double *b, int ldb,
             double *alphar, double *alphai, double *beta, double *q, int ldq,
             double *z, int ldz, int *m, double *pl, double *pr, double *dif,
             double *work, int lwork, int *iwork, int liwork);
int C_DTGSJA(char jobu, char jobv, char jobq, int m, int p, int n, int k, int l,
             double *a, int lda, double *b, int ldb, double tola, double tolb,
             double *alpha, double *beta, double *u, int ldu, double *v,
             int ldv, double *q, int ldq, double *work, int *ncycle);
int C_DTGSNA(char job, char howmny, int n, double *a, int lda, double *b,
             int ldb, double *vl, int ldvl, double *vr, int ldvr, double *s,
             double *dif, int mm, int *m, double *work, int lwork, int *iwork);
int C_DTGSYL(char trans, int ijob, int m, int n, double *a, int lda, double *b,
             int ldb, double *c, int ldc, double *d, int ldd, double *e,
             int lde, double *f, int ldf, double *dif, double *scale,
             double *work, int lwork, int *iwork);
int C_DTPCON(char norm, char uplo, char diag, int n, double *ap, double *rcond,
             double *work, int *iwork);
int C_DTPRFS(char uplo, char trans, char diag, int n, int nrhs, double *ap,
             double *b, int ldb, double *x, int ldx, double *ferr, double *berr,
             double *work, int *iwork);
int C_DTPTRI(char uplo, char diag, int n, double *ap);
int C_DTPTRS(char uplo, char trans, char diag, int n, int nrhs, double *ap,
             double *b, int ldb);
int C_DTRCON(char norm, char uplo, char diag, int n, double *a, int lda,
             double *rcond, double *work, int *iwork);
int C_DTREVC(char side, char howmny, int n, double *t, int ldt, double *vl,
             int ldvl, double *vr, int ldvr, int mm, int *m, double *work);
int C_DTREXC(char compq, int n, double *t, int ldt, double *q, int ldq,
             int *ifst, int *ilst, double *work);
int C_DTRRFS(char uplo, char trans, char diag, int n, int nrhs, double *a,
             int lda, double *b, int ldb, double *x, int ldx, double *ferr,
             double *berr, double *work, int *iwork);
int C_DTRSEN(char job, char compq, int n, double *t, int ldt, double *q,
             int ldq, double *wr, double *wi, int *m, double *s, double *sep,
             double *work, int lwork, int *iwork, int liwork);
int C_DTRSNA(char job, char howmny, int n, double *t, int ldt, double *vl,
             int ldvl, double *vr, int ldvr, double *s, double *sep, int mm,
             int *m, double *work, int ldwork, int *iwork);
int C_DTRSYL(char trana, char tranb, int isgn, int m, int n, double *a, int lda,
             double *b, int ldb, double *c, int ldc, double *scale);
int C_DTRTRI(char uplo, char diag, int n, double *a, int lda);
int C_DTRTRS(char uplo, char trans, char diag, int n, int nrhs, double *a,
             int lda, double *b, int ldb);
int C_DTZRQF(int m, int n, double *a, int lda, double *tau);
int C_DTZRZF(int m, int n, double *a, int lda, double *tau, double *work,
             int lwork);
}

#endif
