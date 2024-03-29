/*

   BLIS    
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2014, The University of Texas at Austin

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name of The University of Texas at Austin nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"
#include "test_libblis.h"

// Static variables.
static char*     op_str                    = "gemm";
static char*     o_types                   = "mmm"; // a b c
static char*     p_types                   = "hh";  // transa transb
static thresh_t  thresh[BLIS_NUM_FP_TYPES] = { { 1e-04, 1e-05 },   // warn, pass for s
                                               { 1e-04, 1e-05 },   // warn, pass for c
                                               { 1e-13, 1e-14 },   // warn, pass for d
                                               { 1e-13, 1e-14 } }; // warn, pass for z

// Local prototypes.
void libblis_test_gemm_deps( test_params_t* params,
                             test_op_t*     op );

void libblis_test_gemm_experiment( test_params_t* params,
                                   test_op_t*     op,
                                   iface_t        iface,
                                   num_t          datatype,
                                   char*          pc_str,
                                   char*          sc_str,
                                   unsigned int   p_cur,
                                   perf_t*        perf,
                                   double*        resid );

void libblis_test_gemm_impl( iface_t   iface,
                             obj_t*    alpha,
                             obj_t*    a,
                             obj_t*    b,
                             obj_t*    beta,
                             obj_t*    c );

void libblis_test_gemm_check( obj_t*  alpha,
                              obj_t*  a,
                              obj_t*  b,
                              obj_t*  beta,
                              obj_t*  c,
                              obj_t*  c_orig,
                              double* resid );



void libblis_test_gemm_deps( test_params_t* params, test_op_t* op )
{
	libblis_test_randv( params, &(op->ops->randv) );
	libblis_test_randm( params, &(op->ops->randm) );
	libblis_test_setv( params, &(op->ops->setv) );
	libblis_test_normfv( params, &(op->ops->normfv) );
	libblis_test_subv( params, &(op->ops->subv) );
	libblis_test_scalv( params, &(op->ops->scalv) );
	libblis_test_copym( params, &(op->ops->copym) );
	libblis_test_scalm( params, &(op->ops->scalm) );
	libblis_test_gemv( params, &(op->ops->gemv) );
}



void libblis_test_gemm( test_params_t* params, test_op_t* op )
{

	// Return early if this test has already been done.
	if ( op->test_done == TRUE ) return;

	// Return early if operation is disabled.
	if ( op->op_switch == DISABLE_ALL ||
	     op->ops->l3_over == DISABLE_ALL ) return;

	// Call dependencies first.
	if ( TRUE ) libblis_test_gemm_deps( params, op );

	// Execute the test driver for each implementation requested.
	if ( op->front_seq == ENABLE )
	{
		libblis_test_op_driver( params,
		                        op,
		                        BLIS_TEST_SEQ_FRONT_END,
		                        op_str,
		                        p_types,
		                        o_types,
		                        thresh,
		                        libblis_test_gemm_experiment );
	}
}



void libblis_test_gemm_experiment( test_params_t* params,
                                   test_op_t*     op,
                                   iface_t        iface,
                                   num_t          datatype,
                                   char*          pc_str,
                                   char*          sc_str,
                                   unsigned int   p_cur,
                                   perf_t*        perf,
                                   double*        resid )
{
	unsigned int n_repeats = params->n_repeats;
	unsigned int i,j;

	double       time_min  = 1e9;
	double       time;

	dim_t        m, n, k;

	trans_t      transa;
	trans_t      transb;

	obj_t        kappa;
	obj_t        alpha, a, b, beta;

#ifdef BLIS_ENABLE_MULTITHREAD_TEST
	dim_t 		 test_way = bli_read_nway_from_env( "BLIS_LB_NT" );
	obj_t	     c[test_way];
	obj_t        c_save[test_way];
	double       resid_local[test_way];
#else
	obj_t        c, c_save;
#endif


	// Map the dimension specifier to actual dimensions.
	m = libblis_test_get_dim_from_prob_size( op->dim_spec[0], p_cur );
	n = libblis_test_get_dim_from_prob_size( op->dim_spec[1], p_cur );
	k = libblis_test_get_dim_from_prob_size( op->dim_spec[2], p_cur );

	// Map parameter characters to BLIS constants.
	bli_param_map_char_to_blis_trans( pc_str[0], &transa );
	bli_param_map_char_to_blis_trans( pc_str[1], &transb );

	// Create test scalars.
	bli_obj_scalar_init_detached( datatype, &kappa );
	bli_obj_scalar_init_detached( datatype, &alpha );
	bli_obj_scalar_init_detached( datatype, &beta );

	// Create test operands (vectors and/or matrices).
	libblis_test_mobj_create( params, datatype, transa,
	                          sc_str[0], m, k, &a );
	//printf("Created object a, buffer address is 0x%x.\n", (unsigned int)bli_obj_buffer(a));
	
	libblis_test_mobj_create( params, datatype, transb,
	                          sc_str[1], k, n, &b );
	//printf("Created object b, buffer address is 0x%x.\n", (unsigned int)bli_obj_buffer(b));

#ifdef BLIS_ENABLE_MULTITHREAD_TEST
	for(i = 0; i < test_way; i++)
	{
		libblis_test_mobj_create( params, datatype, BLIS_NO_TRANSPOSE,
		                          sc_str[2], m, n, &c[i] );
		libblis_test_mobj_create( params, datatype, BLIS_NO_TRANSPOSE,
		                          sc_str[2], m, n, &c_save[i] );
	}
#else
	libblis_test_mobj_create( params, datatype, BLIS_NO_TRANSPOSE,
	                          sc_str[2], m, n, &c );
	libblis_test_mobj_create( params, datatype, BLIS_NO_TRANSPOSE,
	                          sc_str[2], m, n, &c_save );
#endif
	//printf("Created object c, buffer address is 0x%x.\n", (unsigned int)bli_obj_buffer(c[0]));
	//printf("Created object c_save, buffer address is 0x%x.\n", (unsigned int)bli_obj_buffer(c_save[0]));

	// Set alpha and beta.
#ifdef BLIS_ENABLE_MULTITHREAD_TEST
	if ( bli_obj_is_real( c[0] ) )
#else
	if ( bli_obj_is_real( c ) )
#endif
	{
		bli_setsc(  1.2,  0.0, &alpha );
		bli_setsc( -1.0,  0.0, &beta );
	}
	else
	{
		bli_setsc(  1.2,  0.8, &alpha );
		bli_setsc( -1.0,  1.0, &beta );
	}

//	//dnparikh: setting beta & alpha for sgemm tests
	//bli_setsc(0.0, 0.0, &beta);
	//bli_setsc(1.0, 0.0, &alpha);

	// Randomize A, B, and C, and save C.
	bli_randm( &a );
	bli_randm( &b );

#ifdef BLIS_ENABLE_MULTITHREAD_TEST
	for(i = 0; i < test_way; i++)
	{
		bli_randm( &c[i] );
		bli_copym( &c[i], &c_save[i] );
	}
#else
	bli_randm( &c );
	bli_copym( &c, &c_save );

#endif


	// Normalize by k.
	bli_setsc( 1.0/( double )k, 0.0, &kappa );
	bli_scalm( &kappa, &a );
	bli_scalm( &kappa, &b );

	// Apply the parameters.
	bli_obj_set_conjtrans( transa, a );
	bli_obj_set_conjtrans( transb, b );

	//bli_printm( "c_save = [", &c_save[0], "%f", "];" );

	// Repeat the experiment n_repeats times and record results. 
	for ( i = 0; i < n_repeats; ++i )
	{
#ifdef BLIS_ENABLE_MULTITHREAD_TEST
		// Need only one call to initialize the CBLAS OpenCL kernel
		bli_copym( &c_save[0], &c[0] );
		libblis_test_gemm_impl( iface, &alpha, &a, &b, &beta, &c[0] );

		//but need to re-initialize C for each of iteration of n_repeats
		for(j = 0; j < test_way; j++)
		{
			bli_copym( &c_save[j], &c[j] );
		}

#else
		bli_copym( &c_save, &c );
		libblis_test_gemm_impl( iface, &alpha, &a, &b, &beta, &c );
		bli_copym( &c_save, &c );
#endif

		time = bli_clock();

//		bli_printm( "a = [", &a, "%f", "];" );
//		bli_printm( "b = [", &b, "%f", "];" );
//		bli_printm( "c = [", &c, "%f", "];" );

#ifdef BLIS_ENABLE_MULTITHREAD_TEST
#pragma omp parallel num_threads(test_way)
		{
			#pragma omp for
			for(j = 0; j < test_way; j++)
			{
				libblis_test_gemm_impl( iface, &alpha, &a, &b, &beta, &c[j] );
			}
		}
#else
		libblis_test_gemm_impl( iface, &alpha, &a, &b, &beta, &c );
#endif

//		bli_printm( "a_after = [", &a, "%f", "];" );
//		bli_printm( "b_after = [", &b, "%f", "];" );
//		bli_printm( "c_after = [", &c, "%f", "];" );

		time_min = bli_clock_min_diff( time_min, time );
	}

	// Estimate the performance of the best experiment repeat.
#ifdef BLIS_ENABLE_MULTITHREAD_TEST
	perf->gflops = ( 2.0 * m * n * k ) / time_min * test_way / FLOPS_PER_UNIT_PERF;
	if ( bli_obj_is_complex( c[0] ) ) perf->gflops *= 4.0;
#else
	perf->gflops = ( 2.0 * m * n * k ) / time_min / FLOPS_PER_UNIT_PERF;
	if ( bli_obj_is_complex( c ) ) perf->gflops *= 4.0;
#endif
    perf->time = time_min;

	// Perform checks.
#ifdef BLIS_ENABLE_MULTITHREAD_TEST
	// Check output of each thread, and send max residue to main
	for(i = 0; i < test_way; i++)
	{
		libblis_test_gemm_check( &alpha, &a, &b, &beta, &c[i], &c_save[i], &resid_local[i] );
		libblis_test_check_empty_problem( &c[i], perf, &resid_local[i] );

		if(i == 0)
		{
			*resid = resid_local[i];
		}
		else if (resid_local[i] > *resid)
		{
			*resid = resid_local[i];
		}
	}

#else
	libblis_test_gemm_check( &alpha, &a, &b, &beta, &c, &c_save, resid );

	// Zero out performance and residual if output matrix is empty.
	libblis_test_check_empty_problem( &c, perf, resid );
#endif

	// Free the test objects.
	bli_obj_free( &a );
	bli_obj_free( &b );
#ifdef BLIS_ENABLE_MULTITHREAD_TEST
	for(i = 0; i < test_way; i++)
	{
		bli_obj_free( &c[i] );
		bli_obj_free( &c_save[i] );
	}
#else
	bli_obj_free( &c );
	bli_obj_free( &c_save );
#endif
}



void libblis_test_gemm_impl( iface_t   iface,
                             obj_t*    alpha,
                             obj_t*    a,
                             obj_t*    b,
                             obj_t*    beta,
                             obj_t*    c )
{
	switch ( iface )
	{
		case BLIS_TEST_SEQ_FRONT_END:
;
#ifdef CBLAS
       enum CBLAS_ORDER order;
       enum CBLAS_TRANSPOSE transA, transB;
       int m, n, k;
       int lda, ldb, ldc;

       m     = bli_obj_length( *c );
       k     = bli_obj_width_after_trans( *a );
       n     = bli_obj_width( *c );

//       printf("m %d k %d n %d \n", m, k, n);
//       printf("A %d %d\n", bli_obj_length( *a ), bli_obj_width( *a) );
//       printf("B %d %d\n", bli_obj_length( *b ), bli_obj_width( *b) );
//       printf("C %d %d\n", bli_obj_length( *c ), bli_obj_width( *c) );
//       printf("A %d %d\n", bli_obj_row_stride( *a ), bli_obj_col_stride( *a) );
//       printf("B %d %d\n", bli_obj_row_stride( *b ), bli_obj_col_stride( *b) );
//       printf("C %d %d\n", bli_obj_row_stride( *c ), bli_obj_col_stride( *c) );

       if(bli_obj_is_row_stored( *c ))
       {
           order = CblasRowMajor;
           lda = bli_obj_row_stride(*a);
           ldb = bli_obj_row_stride(*b);
           ldc = bli_obj_row_stride(*c);
       }
       else if(bli_obj_is_col_stored( *c ))
       {
           order = CblasColMajor;
           lda = bli_obj_col_stride(*a);
           ldb = bli_obj_col_stride(*b);
           ldc = bli_obj_col_stride(*c);
       }
       else
       {
    	   bli_check_error_code( BLIS_INVALID_DIM_STRIDE_COMBINATION );
    	   return;
       }

       if(bli_obj_has_notrans( *a ) && bli_obj_has_noconj( *a ))
       {
    	   transA = CblasNoTrans;
       }
       else if(bli_obj_has_trans( *a ) && bli_obj_has_noconj( *a ))
       {
    	   transA = CblasTrans;
       }
       else if(bli_obj_has_trans( *a ) && bli_obj_has_conj( *a ))
       {
    	   transA = CblasConjTrans;
       }
       else
       {
    	   bli_check_error_code( BLIS_INVALID_TRANS );
    	   return;
       }

       if(bli_obj_has_notrans( *b ) && bli_obj_has_noconj( *b ))
       {
    	   transB = CblasNoTrans;
       }
       else if(bli_obj_has_trans( *b ) && bli_obj_has_noconj( *b ))
       {
    	   transB = CblasTrans;
       }
       else if(bli_obj_has_trans( *b ) && bli_obj_has_conj( *b ))
       {
    	   transB = CblasConjTrans;
       }
       else
       {
    	   bli_check_error_code( BLIS_INVALID_TRANS );
    	   return;
       }

       if (bli_obj_is_float( *a ))
       {
    	   float *cblas_alpha, *cblas_beta;
    	   float *cblas_a, *cblas_b, *cblas_c;

    	   //obj_t *c_save;


    	   cblas_alpha = (float *) bli_obj_buffer( *alpha );
    	   cblas_beta  = (float *) bli_obj_buffer( *beta );
    	   cblas_a     = (float *) bli_obj_buffer( *a );
    	   cblas_b     = (float *) bli_obj_buffer( *b );
    	   cblas_c     = (float *) bli_obj_buffer( *c );

    	   //printf("test_gemm %d %d %d %d %d, 0x%x, 0x%x, 0x%x\n", order, transA, transB, lda, ldb, (unsigned int)cblas_a,(unsigned int)cblas_b,(unsigned int)cblas_c);
           //printf("Start sgemm for (m,k,n) = (%d,%d,%d) \n", m, k, n);
    	   cblas_sgemm(order, transA, transB, m, n, k, *cblas_alpha, cblas_a, lda, cblas_b, ldb, *cblas_beta, cblas_c, ldc);
           //printf("sgemm for (m,k,n) = (%d,%d,%d) finished.\n", m, k, n);

       }
       else if (bli_obj_is_double( *a ))
       {
    	   double *cblas_alpha, *cblas_beta;
    	   double *cblas_a, *cblas_b, *cblas_c;

    	   cblas_alpha = (double *) bli_obj_buffer( *alpha );
    	   cblas_beta  = (double *) bli_obj_buffer( *beta );
    	   cblas_a     = (double *) bli_obj_buffer( *a );
    	   cblas_b     = (double *) bli_obj_buffer( *b );
    	   cblas_c     = (double *) bli_obj_buffer( *c );

    	   //printf("test_gemm %d %d %d %d %d, 0x%x, 0x%x, 0x%x\n", order, transA, transB, lda, ldb, (unsigned int)cblas_a,(unsigned int)cblas_b,(unsigned int)cblas_c);
    	   cblas_dgemm(order, transA, transB, m, n, k, *cblas_alpha, cblas_a, lda, cblas_b, ldb, *cblas_beta, cblas_c, ldc);

       }
       else if (bli_obj_is_scomplex( *a ))
       {
       	   void *cblas_alpha, *cblas_beta;
           void *cblas_a, *cblas_b, *cblas_c;

           cblas_alpha = bli_obj_buffer( *alpha );
       	   cblas_beta  = bli_obj_buffer( *beta );
       	   cblas_a     = bli_obj_buffer( *a );
       	   cblas_b     = bli_obj_buffer( *b );
       	   cblas_c     = bli_obj_buffer( *c );

           cblas_cgemm(order, transA, transB, m, n, k, cblas_alpha, cblas_a, lda, cblas_b, ldb, cblas_beta, cblas_c, ldc);
       }
       else if (bli_obj_is_dcomplex( *a ))
       {
       	   void *cblas_alpha, *cblas_beta;
           void *cblas_a, *cblas_b, *cblas_c;

           cblas_alpha = bli_obj_buffer( *alpha );
       	   cblas_beta  = bli_obj_buffer( *beta );
       	   cblas_a     = bli_obj_buffer( *a );
       	   cblas_b     = bli_obj_buffer( *b );
       	   cblas_c     = bli_obj_buffer( *c );

           //printf("Start zgemm for (m,k,n) = (%d,%d,%d) \n", m, k, n);
           cblas_zgemm(order, transA, transB, m, n, k, cblas_alpha, cblas_a, lda, cblas_b, ldb, cblas_beta, cblas_c, ldc);
           //printf("zgemm for (m,k,n) = (%d,%d,%d) finished.\n", m, k, n);
       }
#else
		bli_gemm( alpha, a, b, beta, c );
		//bli_gemm4m( alpha, a, b, beta, c );
		//bli_gemm3m( alpha, a, b, beta, c );
#endif
		break;

		default:
		libblis_test_printf_error( "Invalid interface type.\n" );
	}
}



void libblis_test_gemm_check( obj_t*  alpha,
                              obj_t*  a,
                              obj_t*  b,
                              obj_t*  beta,
                              obj_t*  c,
                              obj_t*  c_orig,
                              double* resid )
{
	num_t  dt      = bli_obj_datatype( *c );
	num_t  dt_real = bli_obj_datatype_proj_to_real( *c );

	dim_t  m       = bli_obj_length( *c );
	dim_t  n       = bli_obj_width( *c );
	dim_t  k       = bli_obj_width_after_trans( *a );

	obj_t  kappa, norm;
	obj_t  t, v, w, z;

	double junk;

	//
	// Pre-conditions:
	// - a is randomized.
	// - b is randomized.
	// - c_orig is randomized.
	// Note:
	// - alpha and beta should have non-zero imaginary components in the
	//   complex cases in order to more fully exercise the implementation.
	//
	// Under these conditions, we assume that the implementation for
	//
	//   C := beta * C_orig + alpha * transa(A) * transb(B)
	//
	// is functioning correctly if
	//
	//   normf( v - z )
	//
	// is negligible, where
	//
	//   v = C * t
	//   z = ( beta * C_orig + alpha * transa(A) * transb(B) ) * t
	//     = beta * C_orig * t + alpha * transa(A) * transb(B) * t
	//     = beta * C_orig * t + alpha * transa(A) * w
	//     = beta * C_orig * t + z
	//

	bli_obj_scalar_init_detached( dt,      &kappa );
	bli_obj_scalar_init_detached( dt_real, &norm );

	bli_obj_create( dt, n, 1, 0, 0, &t );
	bli_obj_create( dt, m, 1, 0, 0, &v );
	bli_obj_create( dt, k, 1, 0, 0, &w );
	bli_obj_create( dt, m, 1, 0, 0, &z );

	bli_randv( &t );
	bli_setsc( 1.0/( double )n, 0.0, &kappa );
	bli_scalv( &kappa, &t );

	bli_gemv( &BLIS_ONE, c, &t, &BLIS_ZERO, &v );

	bli_gemv( &BLIS_ONE, b, &t, &BLIS_ZERO, &w );
	bli_gemv( alpha, a, &w, &BLIS_ZERO, &z );
	bli_gemv( beta, c_orig, &t, &BLIS_ONE, &z );

	bli_subv( &z, &v );
	bli_normfv( &v, &norm );
	bli_getsc( &norm, resid, &junk );

	bli_obj_free( &t );
	bli_obj_free( &v );
	bli_obj_free( &w );
	bli_obj_free( &z );
}

