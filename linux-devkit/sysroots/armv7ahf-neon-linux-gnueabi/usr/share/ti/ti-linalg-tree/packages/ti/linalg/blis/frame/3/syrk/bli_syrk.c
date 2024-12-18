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

//
// Define object-based interface.
//
void bli_syrk( obj_t*  alpha,
               obj_t*  a,
               obj_t*  beta,
               obj_t*  c )
{
	num_t dt = bli_obj_datatype( *c );

#if defined (BLIS_ENABLE_C66X_BUILD)
	lib_smem_sreset(blasGetMemHandle()); /* reset BLAS scratch heap */
#endif	
	
	if      ( bli_3mh_is_enabled_dt( dt ) ) bli_syrk3mh_entry( alpha, a, beta, c );
	else if ( bli_3m_is_enabled_dt( dt ) )  bli_syrk3m_entry( alpha, a, beta, c );
	else if ( bli_4mh_is_enabled_dt( dt ) ) bli_syrk4mh_entry( alpha, a, beta, c );
	else if ( bli_4m_is_enabled_dt( dt ) )  bli_syrk4m_entry( alpha, a, beta, c );
	else                                    bli_syrk_entry( alpha, a, beta, c );
}


//
// Define BLAS-like interfaces with homogeneous-typed operands.
//
#undef  GENTFUNC
#define GENTFUNC( ctype, ch, opname, varname ) \
\
void PASTEMAC(ch,opname)( \
                          uplo_t  uploc, \
                          trans_t transa, \
                          dim_t   m, \
                          dim_t   k, \
                          ctype*  alpha, \
                          ctype*  a, inc_t rs_a, inc_t cs_a, \
                          ctype*  beta, \
                          ctype*  c, inc_t rs_c, inc_t cs_c  \
                        ) \
{ \
	const num_t dt = PASTEMAC(ch,type); \
\
	obj_t       alphao, ao, betao, co; \
\
	dim_t       m_a, n_a; \
\
	bli_set_dims_with_trans( transa, m, k, m_a, n_a ); \
\
	bli_obj_create_1x1_with_attached_buffer( dt, alpha, &alphao ); \
	bli_obj_create_1x1_with_attached_buffer( dt, beta,  &betao  ); \
\
	bli_obj_create_with_attached_buffer( dt, m_a, n_a, a, rs_a, cs_a, &ao ); \
	bli_obj_create_with_attached_buffer( dt, m,   m,   c, rs_c, cs_c, &co ); \
\
	bli_obj_set_uplo( uploc, co ); \
	bli_obj_set_conjtrans( transa, ao ); \
\
	bli_obj_set_struc( BLIS_SYMMETRIC, co ); \
\
	PASTEMAC0(opname)( &alphao, \
	                   &ao, \
	                   &betao, \
	                   &co ); \
}

INSERT_GENTFUNC_BASIC( syrk, syrk )


//
// Define BLAS-like interfaces with heterogeneous-typed operands.
//
#undef  GENTFUNC2
#define GENTFUNC2( ctype_a, ctype_c, cha, chc, opname, varname ) \
\
void PASTEMAC2(cha,chc,opname)( \
                                uplo_t    uploc, \
                                trans_t   transa, \
                                dim_t     m, \
                                dim_t     k, \
                                ctype_a*  alpha, \
                                ctype_a*  a, inc_t rs_a, inc_t cs_a, \
                                ctype_c*  beta, \
                                ctype_c*  c, inc_t rs_c, inc_t cs_c  \
                              ) \
{ \
	bli_check_error_code( BLIS_NOT_YET_IMPLEMENTED ); \
}

INSERT_GENTFUNC2_BASIC( syrk, syrk )

#ifdef BLIS_ENABLE_MIXED_DOMAIN_SUPPORT
INSERT_GENTFUNC2_MIX_D( syrk, syrk )
#endif

#ifdef BLIS_ENABLE_MIXED_PRECISION_SUPPORT
INSERT_GENTFUNC2_MIX_P( syrk, syrk )
#endif

