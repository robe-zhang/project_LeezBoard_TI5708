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

void bli_gemv_blk_var2( obj_t*  alpha,
                        obj_t*  a,
                        obj_t*  x,
                        obj_t*  beta,
                        obj_t*  y,
                        gemv_t* cntl )
{
	obj_t a1, a1_pack;
	obj_t x1, x1_pack;

	dim_t n_trans;
	dim_t i;
	dim_t b_alg;

	// Initialize objects for packing.
	bli_obj_init_pack( &a1_pack );
	bli_obj_init_pack( &x1_pack );

	// Query dimension in partitioning direction.
	n_trans = bli_obj_width_after_trans( *a );

	// y = beta * y;
	bli_scalv_int( beta,
	               y,
	               cntl_sub_scalv( cntl ) );

	// Partition along the "k" dimension (n dimension of A).
	for ( i = 0; i < n_trans; i += b_alg )
	{
		// Determine the current algorithmic blocksize.
		b_alg = bli_determine_blocksize_f( i, n_trans, a,
		                                   cntl_blocksize( cntl ) );

		// Acquire partitions for A1 and x1.
		bli_acquire_mpart_l2r( BLIS_SUBPART1,
		                       i, b_alg, a, &a1 );
		bli_acquire_vpart_f2b( BLIS_SUBPART1,
		                       i, b_alg, x, &x1 );

		// Initialize objects for packing A1 and x1 (if needed).
		bli_packm_init( &a1, &a1_pack,
		                cntl_sub_packm_a( cntl ) );
		bli_packv_init( &x1, &x1_pack,
		                cntl_sub_packv_x( cntl ) );

		// Copy/pack A1, x1 (if needed).
		bli_packm_int( &a1, &a1_pack,
		               cntl_sub_packm_a( cntl ),
                       &BLIS_PACKM_SINGLE_THREADED );
		bli_packv_int( &x1, &x1_pack,
		               cntl_sub_packv_x( cntl ) );

		// y = y + alpha * A1 * x1;
		bli_gemv_int( BLIS_NO_TRANSPOSE,
		              BLIS_NO_CONJUGATE,
		              alpha,
		              &a1_pack,
		              &x1_pack,
		              &BLIS_ONE,
		              y,
		              cntl_sub_gemv( cntl ) );
	}

	// If any packing buffers were acquired within packm, release them back
	// to the memory manager.
	bli_obj_release_pack( &a1_pack , cntl_sub_packm_a( cntl ) );
	bli_obj_release_pack( &x1_pack , cntl_sub_packv_x( cntl ) );
}

