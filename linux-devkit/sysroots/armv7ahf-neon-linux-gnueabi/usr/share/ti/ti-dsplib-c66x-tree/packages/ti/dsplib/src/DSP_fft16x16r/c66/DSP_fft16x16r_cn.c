/* ======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  NAME                                                                   */
/*      DSP_fft16x16r_cn -- fft16x16r                                      */
/*                                                                         */
/*  USAGE                                                                  */
/*                                                                         */
/*      void DSP_fft16x16r_cn (                                            */
/*          int n,                                                         */
/*          short * ptr_x,                                                 */
/*          const short * ptr_w,                                           */
/*          short * ptr_y,                                                 */
/*          int radix,                                                     */
/*          int offset,                                                    */
/*          int n_max                                                      */
/*      );                                                                 */
/*                                                                         */
/*      N      = length of fft in complex samples, power of 2 <=16384      */
/*      ptr_x  = pointer to complex data input                             */
/*      ptr_w  = pointer to complex twiddle factor (see below)             */
/*      radix  = smallest fft butterfly used in computation for decomposi  */
/*      offset = index in complex samples of sub-fft from start of main f  */
/*      n_max  = size of main fft in complex samples                       */
/*                                                                         */
/*      (See the C compiler reference guide.)                              */
/*                                                                         */
/*  DESCRIPTION                                                            */
/*      The benchmark performs a mixed radix forwards fft using            */
/*      a special sequence of coefficients generated in the following      */
/*      way:                                                               */
/*                                                                         */
/*    int gen_twiddle_fft16x16r(short *w, int n)                           */
/*                                                                         */
/*    int i, j, k;                                                         */
/*    double M = 32767.5;                                                  */
/*                                                                         */
/*    for (j = 1, k = 0; j < n >> 2; j = j << 2)                           */
/*    {                                                                    */
/*        for (i = 0; i < n >> 2; i += j << 1)                             */
/*        {                                                                */
/*                                                                         */
/*          w[k +  3] = d2s(M * cos(2.0 * PI * (i + j) / n));              */
/*          w[k +  2] = d2s(M * sin(2.0 * PI * (i + j) / n));              */
/*          w[k +  1] = d2s(M * cos(2.0 * PI * (i    ) / n));              */
/*          w[k +  0] = d2s(M * sin(2.0 * PI * (i    ) / n));              */
/*                                                                         */
/*          k += 12;                                                       */
/*                                                                         */
/*        }                                                                */
/*    }                                                                    */
/*                                                                         */
/*      This redundent set of twiddle factors is size 2*N short samples.   */
/*      As pointed out later dividing these twiddle factors by 2 will give */
/*      an effective divide by 4 at each stage to guarentee no overflow.   */
/*      The function is accurate to about 68dB of signal to noise ratio    */
/*      to the DFT function below:                                         */
/*                                                                         */
/*       void dft(int n, short x[], short y[])                             */
/*       {                                                                 */
/*          int k,i, index;                                                */
/*          const double PI = 3.14159654;                                  */
/*          short * p_x;                                                   */
/*          double arg, fx_0, fx_1, fy_0, fy_1, co, si;                    */
/*                                                                         */
/*          for(k = 0; k<n; k++)                                           */
/*          {                                                              */
/*            p_x = x;                                                     */
/*            fy_0 = 0;                                                    */
/*            fy_1 = 0;                                                    */
/*            for(i=0; i<n; i++)                                           */
/*            {                                                            */
/*              fx_0 = (double)p_x[0];                                     */
/*              fx_1 = (double)p_x[1];                                     */
/*              p_x += 2;                                                  */
/*              index = (i*k) % n;                                         */
/*              arg = 2*PI*index/n;                                        */
/*              co = cos(arg);                                             */
/*              si = -sin(arg);                                            */
/*              fy_0 += ((fx_0 * co) - (fx_1 * si));                       */
/*              fy_1 += ((fx_1 * co) + (fx_0 * si));                       */
/*            }                                                            */
/*            y[2*k] = (short)2*fy_0/sqrt(N);                              */
/*            y[2*k+1] = (short)2*fy_1/sqrt(N);                            */
/*          }                                                              */
/*       }                                                                 */
/*      Scaling takes place at each stage except the last one.             */
/*      This is a divide by 2 to prevent overflow. All shifts are rounded  */
/*      reduce truncation noise power by 3dB.                              */
/*      The function takes the table and input data and calculates the fft */
/*      producing the frequency domain data in the Y array.                */
/*      As the fft allows every input point to effect every output point i */
/*      a cache based system such as the c64xx, this causes cache thrashin */
/*      This is mitigated by allowing the main fft of size N to be divided */
/*      into several steps, allowing as much data reuse as possible.       */
/*                                                                         */
/*      For example the following function:                                */
/*                                                                         */
/*      fft16x16r  (1024, &x_asm[0],&w[0],y_asm,4,  0,1024);               */
/*                                                                         */
/*      is equvalent to:                                                   */
/*                                                                         */
/*      fft16x16r  (1024,&x_asm[2*0],  &w[0]    ,y_asm,256,  0,1024);      */
/*      fft16x16r  (256, &x_asm[2*0],  &w[2*768],y_asm,4,    0,1024);      */
/*      fft16x16r  (256, &x_asm[2*256],&w[2*768],y_asm,4,  256,1024);      */
/*      fft16x16r  (256, &x_asm[2*512],&w[2*768],y_asm,4,  512,1024);      */
/*      fft16x16r  (256, &x_asm[2*768],&w[2*768],y_asm,4,  768,1024);      */
/*                                                                         */
/*      Notice how the 1st fft function is called on the entire 1K data se */
/*      it covers the 1st pass of the fft until the butterfly size is 256. */
/*      The following 4 ffts do 256 pt ffts 25% of the size. These continu */
/*      down to the end when the buttefly is of size 4. The use an index t */
/*      the main twiddle factor array of 0.75*2*N. This is because the     */
/*      twiddle factor array is composed of successively decimated version */
/*      of the main array.                                                 */
/*                                                                         */
/*      N not equal to a power of 4 can be used, i.e. 512. In this case to */
/*      decompose the fft the following would be needed :                  */
/*                                                                         */
/*      fft16x16r   (512, &x_asm[0],&w[0],y_asm,2,  0,512);                */
/*                                                                         */
/*      is equvalent to:                                                   */
/*                                                                         */
/*      fft16x16r   (512, &x_asm[0],    &w[0],    y_asm,128,  0,512);      */
/*      fft16x16r   (128, &x_asm[2*0],  &w[2*384],y_asm,2,    0,512);      */
/*      fft16x16r   (128, &x_asm[2*128],&w[2*384],y_asm,2,  128,512);      */
/*      fft16x16r   (128, &x_asm[2*256],&w[2*384],y_asm,2,  256,512);      */
/*      fft16x16r   (128, &x_asm[2*384],&w[2*384],y_asm,2,  384,512);      */
/*                                                                         */
/*      The twiddle factor array is composed of log4(N) sets of twiddle    */
/*      factors, (3/4)*N, (3/16)*N, (3/64)*N, etc.  The index into this    */
/*      array for each stage of the fft is calculated by summing these     */
/*      indices up appropriately.                                          */
/*      For multiple ffts they can share the same table by calling the sma */
/*      ffts from further down in the twiddle factor array. In the same wa */
/*      as the decomposition works for more data reuse.                    */
/*                                                                         */
/*      Thus, the above decomposition can be summarized for a general N ,  */
/*      radix "rad" as follows:                                            */
/*                                                                         */
/*  fft16x16r(N,  &x_cn[0],         &w[0],         y_cn, N/4, 0,     N     */
/*  fft16x16r(N/4,&x_cn[0],         &w[2*(3*N/4)], y_cn, rad, 0,     N     */
/*  fft16x16r(N/4,&x_cn[2*(N/4)],   &w[2*(3*N/4)], y_cn, rad, N/4,   N     */
/*  fft16x16r(N/4,&x_cn[2*(N/2)],   &w[2*(3*N/4)], y_cn, rad, N/2,   N     */
/*  fft16x16r(N/4,&x_cn[2*(3*N/4)], &w[2*3*N/4)],  y_cn, rad, 3*N/4, N     */
/*                                                                         */
/*      As discussed previously, N can be either a power of 4 or 2.  If  N */
/*      N is a power  of 4, rad = 4, and if N is a power of 2, and not  a  */
/*      power of 4, then rad = 2. "rad" is used to control how many stages */
/*      of decomposition are performed. It is also used to dtermine whethe */
/*      a radix4 or radix2 decomposition should be performed at the last   */
/*      stage. Hence when "rad" is set to "N/4" the first stage of the     */
/*      transform alone is performed and the code exits. To complete the   */
/*      FFT four other calls are required to perform N/4 size FFT's. In    */
/*      fact the ordering of these 4 FFT's amonst themselves does not      */
/*      matter and hence from a cahe perspective it helps to go through    */
/*      the remaining 4 FFT's in exactly the opposite order to the first.  */
/*                                                                         */
/*      This is illustrated as follows:                                    */
/*                                                                         */
/*  fft16x16r(N,  &x_cn[0],         &w[0],         y_cn, N/4, 0,     N     */
/*  fft16x16r(N/4,&x_cn[2*(3*N/4)], &w[2*3*N/4)],  y_cn, rad, 3*N/4, N     */
/*  fft16x16r(N/4,&x_cn[2*(N/2)],   &w[2*(3*N/4)], y_cn, rad, N/2,   N     */
/*  fft16x16r(N/4,&x_cn[2*(N/4)],   &w[2*(3*N/4)], y_cn, rad, N/4,   N     */
/*  fft16x16r(N/4,&x_cn[0],         &w[2*(3*N/4)], y_cn, rad, 0,     N     */
/*                                                                         */
/*      In addition this function can be used to minimize call overhead, b */
/*      completing the FFT with one function call invocation as shown belo */
/*                                                                         */
/*      fft16x16r(N, &x_cn[0], &w[0], y_cn, rad, 0, N)                     */
/*                                                                         */
/*   ASSUMPTIONS:                                                          */
/*      n must be a power of 2 and n >= 8  n <= 16384 points.              */
/*      Complex time data x and twiddle facotrs w are aligned on double    */
/*      word boundares. Real values are stored in even word positions and  */
/*      imaginary values in odd positions.                                 */
/*                                                                         */
/*      All data is in short precision integer fixed point form. The       */
/*      complex frequency data will be returned in linear order.           */
/*                                                                         */
/*   TECHNIQUES                                                            */
/*      A special sequence of coeffs. used as generated above              */
/*      produces the fft. This collapses the inner 2 loops in the          */
/*      taditional Burrus and Parks implementation Fortran Code.           */
/*                                                                         */
/*      The revised FFT uses a redundant sequence of twiddle factors to    */
/*      allow a linear access through the data. This linear access enables */
/*      data and instruction level parallelism.                            */
/*      The data produced by the fft16x16r fft is in normal form, the      */
/*      whole data array is written into a new output buffer.              */
/*                                                                         */
/*      The fft16x16r butterfly is bit reversed, i.e. the inner 2 points o */
/*      the butterfly are crossed over, this has the effect of making the  */
/*      data come out in bit reversed rather than in radix 4 digit reverse */
/*      order. This simplifies the last pass of the loop. It is performed  */
/*      using the _bitr instruction on C64x architecture.                  */
/*                                                                         */
/*   NOTES                                                                 */
/*      For more aggressive overflow control the shift in the DC term can  */
/*      adjusted to 2 and the twiddle factors shifted right by 1. This giv */
/*      a divide by 4 at each stage. For better accuracy the data can be p */
/*      asserted left by so many bits so that as it builds in magnitude th */
/*      divide by 2 prevents too much growth. An optimal point for example */
/*      with an 8192pt fft with input data precision of 8 bits is to asert */
/*      the input 4 bits left to make it 12 bits. This gives an SNR of 68d */
/*      at the output. By trying combinations the optimal can be found.    */
/*      If scaling isnot required it is possible to replace the MPY by SMP */
/*      this will give a shift left by 1 so a shift right by 16 gives a    */
/*      total 15 bit shift right. The DC term must be adjusted to give a   */
/*      zero shift.                                                        */
/*                                                                         */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#pragma CODE_SECTION(DSP_fft16x16r_cn, ".text:ansi");

#include "DSP_fft16x16r_cn.h"

/*---------------------------------------------------------------------------*/
/* Define macro for bit reversal. This macro computes a bit reversed index   */
/* for a given index "i" and returns it in "j". The bit reversed index is    */
/* returned to be of the same size as "i" using the size argument "m".       */
/* For the natural form of C code, this is done by first interchanging every */
/* set of "2 bit" pairs, followed by exchanging nibbles, followed by exchan- */
/* ging bytes, and finally halfwords. To give an example, condider the       */
/* following number:                                                         */
/*                                                                           */
/* N = FEDCBA9876543210, where each digit represents a bit, the following    */
/* steps illustrate the changes as the exchanges are performed:              */
/* M = DCFE98BA54761032 is the number after every "2 bits" are exchanged.    */
/* O = 98BADCFE10325476 is the number after every nibble is exchanged.       */
/* P = 1032547698BADCFE is the number after every byte is exchanged.         */
/* Q = 0123456789ABCDEF is the bit reversed number.                          */
/* Since only 16 digits were considered this represents the digit reversed   */
/* index. Since the numbers are represented as 32 bits, there is one more    */
/* step typically of exchanging the half words as well.                      */
/*---------------------------------------------------------------------------*/

#define DIG_REV(i, m, j)                                                    \
do {                                                                        \
        unsigned _ = (i);                                                   \
        _ = ((_ & 0x33333333) <<  2) | ((_ & ~0x33333333) >>  2);           \
        _ = ((_ & 0x0F0F0F0F) <<  4) | ((_ & ~0x0F0F0F0F) >>  4);           \
        _ = ((_ & 0x00FF00FF) <<  8) | ((_ & ~0x00FF00FF) >>  8);           \
        _ = ((_ & 0x0000FFFF) << 16) | ((_ & ~0x0000FFFF) >> 16);           \
        _ = ((_ & 0x55555555) <<  1) | ((_ & ~0x55555555) >>  1);           \
        (j) = _ >> (m);                                                     \
} while (0)


void DSP_fft16x16r_cn (
    int n,
    short * ptr_x,
    const short * ptr_w,
    short * ptr_y,
    int radix,
    int offset,
    int nmax
)
{
    const short *w;
    short *ptr_x0, *x, *x2, *x0;
    short *y0, *y1, *y2, *y3;
    short yt0, yt1, yt2, yt3, yt4, yt5, yt6, yt7;

    short xt0_0, xt1_0, xt2_0;
    short yt0_0, yt1_0, yt2_0;
    short xt0_1, xt1_1, xt2_1;
    short yt0_1, yt1_1, yt2_1;
    short xh0_0, xh1_0, xh20_0, xh21_0, xh0_1, xh1_1, xh20_1, xh21_1;
    short xl0_0, xl1_0, xl20_0, xl21_0, xl0_1, xl1_1, xl20_1, xl21_1;

    short x_0, x_1, x_2, x_3, x_4, x_5, x_6, x_7;
    short x_l1_0, x_l1_1, x_l1_2, x_l1_3, x_l2_0, x_l2_1, x_l2_2, x_l2_3;
    short x_h2_0, x_h2_1, x_h2_2, x_h2_3;

    short si10, si20, si30, si11, si21, si31;
    short co10, co20, co30, co11, co21, co31;

    unsigned int j, k;
    int i, l0, l1, h2, l2;
    int predj, tw_offset, stride, fft_jmp, norm, tw_jmp;

    /*----------------------------------------------------------------------*/
    /* The stride is quartered with every iteration of the outer loop. It   */
    /* denotes the seperation between any two adjacent inputs to the butter */
    /* -fly. This should start out at N/4, hence stride is initially set to */
    /* N. For every stride, 2*stride twiddle factors are accessed. The      */
    /* "tw_offset" is the offset within the current twiddle factor sub-     */
    /* table. This is set to zero, at the start of the code and is used to  */
    /* obtain the appropriate sub-table twiddle pointer by offseting it     */
    /* with the base pointer "ptr_w".                                       */
    /*----------------------------------------------------------------------*/
    stride    = n;
    tw_offset = 0;
    fft_jmp   = 6 * stride;
    tw_jmp    = 2 * stride;

    #ifndef NOASSUME
    _nassert(stride > 4);
    #pragma MUST_ITERATE(1,,1);
    #endif

    while (stride > radix) {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "w" is pointing to the correct location within the  */
        /* twiddle factor array. For every iteration of the inner loop     */
        /* 2 * stride twiddle factors are accessed. For eg,                */
        /*                                                                 */
        /* #Iteration of outer loop  # twiddle factors    #times cycled    */
        /*  1                          2 N/4               1               */
        /*  2                          2 N/16              4               */
        /*  ...                                                            */
        /*-----------------------------------------------------------------*/
        j =  0;
        fft_jmp >>= 2;
        tw_jmp  >>= 2;

        /*-----------------------------------------------------------------*/
        /* Set up offsets to access "N/4", "N/2", "3N/4" complex point or  */
        /* "N/2", "N", "3N/2" half word                                    */
        /*-----------------------------------------------------------------*/
        h2 = stride >> 1;
        l1 = stride;
        l2 = stride + (stride >> 1);

        /*-----------------------------------------------------------------*/
        /*  Reset "x" to point to the start of the input data array.       */
        /* "tw_offset" starts off at 0, and increments by "6 * stride"     */
        /*  The stride quarters with every iteration of the outer loop     */
        /*-----------------------------------------------------------------*/
        x = ptr_x;
        w = ptr_w + tw_offset;
        tw_offset += tw_jmp;

        stride >>= 2;

        /*----------------------------------------------------------------*/
        /* The following loop iterates through the different butterflies, */
        /* within a given stage. Recall that there are logN to base 4     */
        /* stages. Certain butterflies share the twiddle factors. These   */
        /* are grouped together. On the very first stage there are no     */
        /* butterflies that share the twiddle factor, all N/4 butter-     */
        /* flies have different factors. On the next stage two sets of    */
        /* N/8 butterflies share the same twiddle factor. Hence after     */
        /* half the butterflies are performed, j the index into the       */
        /* factor array resets to 0, and the twiddle factors are reused.  */
        /* When this happens, the data pointer 'x' is incremented by the  */
        /* fft_jmp amount. In addition the following code is unrolled to  */
        /* perform "2" radix4 butterflies in parallel.                    */
        /*----------------------------------------------------------------*/
        #ifndef NOASSUME
        _nassert((int)(w) % 8 == 0);
        _nassert((int)(x) % 8 == 0);
        _nassert(h2 % 8 == 0);
        _nassert(l1 % 8 == 0);
        _nassert(l2 % 8 == 0);
        #pragma MUST_ITERATE(1,,1);
        #endif

        for (i = 0; i < n; i += 8) {
            /*------------------------------------------------------------*/
            /* Read the first 4 twiddle factors, two of which are used    */
            /* for one radix 4 butterfly and two of which are used for    */
            /* next one.                                                  */
            /*------------------------------------------------------------*/

            /* twiddle factors for first butterfly */
#ifdef _LITTLE_ENDIAN            
            co10 = w[j+1];
            si10 = w[j+0];
#else
            co10 = w[j+0];
            si10 =-w[j+1];
#endif            
            co20 = (co10 * co10 - si10 * si10 + 0x4000) >> 15;
            si20 = (co10 * si10 + co10 * si10 + 0x4000) >> 15;
            co30 = (co10 * co20 - si10 * si20 + 0x4000) >> 15;
            si30 = (co10 * si20 + co20 * si10 + 0x4000) >> 15;

            /* twiddle factors for second butterfly */
#ifdef _LITTLE_ENDIAN            
            co11 = w[j+3];
            si11 = w[j+2];
#else
            co11 = w[j+2];
            si11 =-w[j+3];
#endif            
            co21 = (co11 * co11 - si11 * si11 + 0x4000) >> 15;
            si21 = (co11 * si11 + co11 * si11 + 0x4000) >> 15;
            co31 = (co11 * co21 - si11 * si21 + 0x4000) >> 15;
            si31 = (co11 * si21 + co21 * si11 + 0x4000) >> 15;

            /*------------------------------------------------------------*/
            /* Read in the first complex input for the butterflies.       */
            /* 1st complex input to 1st butterfly: x[0] + jx[1]           */
            /* 1st complex input to 2nd butterfly: x[2] + jx[3]           */
            /*------------------------------------------------------------*/
            x_0 = x[0];    x_1 = x[1];
            x_2 = x[2];    x_3 = x[3];

            /*------------------------------------------------------------*/
            /* Read in the complex inputs for the butterflies. Each of the*/
            /* successive complex inputs of the butterfly are seperated   */
            /* by a fixed amount known as stride. The stride starts out   */
            /* at N/4, and quarters with every stage.                     */
            /*------------------------------------------------------------*/
            x_l1_0 = x[l1 + 0];    x_l1_1 = x[l1 + 1];
            x_l1_2 = x[l1 + 2];    x_l1_3 = x[l1 + 3];

            x_l2_0 = x[l2 + 0];    x_l2_1 = x[l2 + 1];
            x_l2_2 = x[l2 + 2];    x_l2_3 = x[l2 + 3];

            x_h2_0 = x[h2 + 0];    x_h2_1 = x[h2 + 1];
            x_h2_2 = x[h2 + 2];    x_h2_3 = x[h2 + 3];

            /*-----------------------------------------------------------*/
            /* Two butterflies are evaluated in parallel. The following  */
            /* results will be shown for one butterfly only, although    */
            /* both are being evaluated in parallel.                     */
            /*                                                           */
            /* Perform radix2 style DIF butterflies.                     */
            /*-----------------------------------------------------------*/
            xh0_0 = x_0 + x_l1_0;    xh1_0 = x_1 + x_l1_1;
            xh0_1 = x_2 + x_l1_2;    xh1_1 = x_3 + x_l1_3;
            xl0_0 = x_0 - x_l1_0;    xl1_0 = x_1 - x_l1_1;
            xl0_1 = x_2 - x_l1_2;    xl1_1 = x_3 - x_l1_3;

            xh20_0 = x_h2_0 + x_l2_0;    xh21_0 = x_h2_1 + x_l2_1;
            xh20_1 = x_h2_2 + x_l2_2;    xh21_1 = x_h2_3 + x_l2_3;
            xl20_0 = x_h2_0 - x_l2_0;    xl21_0 = x_h2_1 - x_l2_1;
            xl20_1 = x_h2_2 - x_l2_2;    xl21_1 = x_h2_3 - x_l2_3;

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/
            x0 = x;
            x2 = x0;

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 4, to reflect the fact that 4 half words   */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 4. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/
            j += 4;
            x += 4;

            predj = (3*j - fft_jmp);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;

            /*----------------------------------------------------------*/
            /* These four partial results can be re-written to show     */
            /* the underlying DIF structure similar to radix2 as        */
            /* follows:                                                 */
            /*                                                          */
            /* X(4k)  = (x(n)+x(n + N/2)) + (x(n+N/4)+ x(n + 3N/4))     */
            /* X(4k+1)= (x(n)-x(n + N/2)) -j(x(n+N/4) - x(n + 3N/4))    */
            /* x(4k+2)= (x(n)+x(n + N/2)) - (x(n+N/4)+ x(n + 3N/4))     */
            /* X(4k+3)= (x(n)-x(n + N/2)) +j(x(n+N/4) - x(n + 3N/4))    */
            /*                                                          */
            /* which leads to the real and imaginary values as foll:    */
            /*                                                          */
            /* y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20           */
            /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21           */
            /* y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21           */
            /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20           */
            /* y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20           */
            /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21           */
            /* y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21           */
            /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20           */
            /*                                                          */
            /* Note that in this version of the code voth rounding and  */
            /* scaling are implemented.                                 */
            /* ---------------------------------------------------------*/
            x0[0] = (xh0_0 + xh20_0 + 1) >> 1;
            x0[1] = (xh1_0 + xh21_0 + 1) >> 1;
            x0[2] = (xh0_1 + xh20_1 + 1) >> 1;
            x0[3] = (xh1_1 + xh21_1 + 1) >> 1;

            xt0_0 = xh0_0 - xh20_0;    yt0_0 = xh1_0 - xh21_0;
            xt0_1 = xh0_1 - xh20_1;    yt0_1 = xh1_1 - xh21_1;

            xt1_0 = xl0_0 + xl21_0;    yt2_0 = xl1_0 + xl20_0;
            xt2_0 = xl0_0 - xl21_0;    yt1_0 = xl1_0 - xl20_0;

            xt1_1 = xl0_1 + xl21_1;    yt2_1 = xl1_1 + xl20_1;
            xt2_1 = xl0_1 - xl21_1;    yt1_1 = xl1_1 - xl20_1;

            /*---------------------------------------------------------*/
            /* Notice that in this version of the code the two middle  */
            /* legs are swapped as indicated by the stores to x[l1]..  */
            /* x[l1 + 3] which preceede the stores to x[h2]..x[h2 + 3] */
            /* This reversal guarantees that a radix4 DIF butterfly    */
            /* produces results in digit reversed order. Note that in  */
            /* addition to the rounding, the shift is performed by 16, */
            /* as opposed to 15, to give scaling.                      */
            /*---------------------------------------------------------*/

            // Following equations have been modified with si' = -si

            x2[l1+0] = (co10 * xt1_0 + si10 * yt1_0 + 0x8000) >> 16;
            x2[l1+1] = (co10 * yt1_0 - si10 * xt1_0 + 0x8000) >> 16;

            x2[l1+2] = (co11 * xt1_1 + si11 * yt1_1 + 0x8000) >> 16;
            x2[l1+3] = (co11 * yt1_1 - si11 * xt1_1 + 0x8000) >> 16;

            x2[h2+0] = (co20 * xt0_0 + si20 * yt0_0 + 0x8000) >> 16;
            x2[h2+1] = (co20 * yt0_0 - si20 * xt0_0 + 0x8000) >> 16;

            x2[h2+2] = (co21 * xt0_1 + si21 * yt0_1 + 0x8000) >> 16;
            x2[h2+3] = (co21 * yt0_1 - si21 * xt0_1 + 0x8000) >> 16;

            x2[l2+0] = (co30 * xt2_0 + si30 * yt2_0 + 0x8000) >> 16;
            x2[l2+1] = (co30 * yt2_0 - si30 * xt2_0 + 0x8000) >> 16;

            x2[l2+2] = (co31 * xt2_1 + si31 * yt2_1 + 0x8000) >> 16;
            x2[l2+3] = (co31 * yt2_1 - si31 * xt2_1 + 0x8000) >> 16;
        }
    }

    /*----------------------------------------------------------------*/
    /* The following condition allows the fft to become a multiple    */
    /* call FFT as it exits as soon as stride, between two legs       */
    /* becomes greater than the radix.                                */
    /*----------------------------------------------------------------*/
    if (radix > 4) return;

    /*-----------------------------------------------------------------*/
    /* Use index at offset/4 for bit reversal. Set up input , output   */
    /* pointers to store away the result. The last stage perfoms 1     */
    /* radix4 butterfly or 4 radix2 burtterflies per iteration.        */
    /*-----------------------------------------------------------------*/
    j = offset >> 2;
    ptr_x0 = ptr_x;

    y0 = ptr_y;
    y1 = y0 + (nmax >> 1);
    y2 = y1 + (nmax >> 1);
    y3 = y2 + (nmax >> 1);

    /*-----------------------------------------------------------------*/
    /* Use the following loop to determine norm as determined by C6x   */
    /*-----------------------------------------------------------------*/
    for (i = 31, norm = 1; (nmax & (1 << i)) == 0; i--, norm++)
        ;
    norm -= 2;
    l0 = norm + 3;

    #ifndef NOASSUME
    _nassert((int)(n) % 4 == 0);
    _nassert((int)(x0) % 8 == 0);
    _nassert((int)(x2) % 8 == 0);
    _nassert((int)(y0) % 8 == 0);
    #pragma MUST_ITERATE(2,,2);
    #endif

    for (i = 0; i < n; i += 4) {
        /*--------------------------------------------------------*/
        /* The following macro performs bit reversal of index "j" */
        /* of size "l0" bits into index "k". This forms the index */
        /* with respect to pointers y0, y1, y2, y3 into which  4  */
        /* consecutive inputs map into.                           */
        /*--------------------------------------------------------*/
        DIG_REV(j, l0, k);
        j +=  1;

        x_0 = ptr_x0[0];    x_1 = ptr_x0[1];
        x_2 = ptr_x0[2];    x_3 = ptr_x0[3];
        x_4 = ptr_x0[4];    x_5 = ptr_x0[5];
        x_6 = ptr_x0[6];    x_7 = ptr_x0[7];
        ptr_x0 += 8;

        /*--------------------------------------------------------*/
        /* Read in the input data, from the first eight locations.*/
        /* These results are transformed as radix 4               */
        /*--------------------------------------------------------*/
        xl0_0 = x_0 - x_4;    xl1_0 = x_1 - x_5;
        xl0_1 = x_2 - x_6;    xl1_1 = x_3 - x_7;

        if (radix == 2) {
            /*----------------------------------------------------*/
            /* These results are appropriately changed if radix   */
            /* is 2, so that when the next set of radix 4 steps   */
            /* performed then the results are same as radix 2.    */
            /*----------------------------------------------------*/
            xl0_0 = x_4;    xl1_0 = x_5;
            xl1_1 = x_6;    xl0_1 = -x_7;
        }

        /*--------------------------------------------------------*/
        /* Perform nest step of radix4 for lower leg. This will   */
        /* result in the correct results radix4 or radix2         */
        /*--------------------------------------------------------*/
        yt2 = xl0_0 + xl1_1;    yt7 = xl1_0 + xl0_1;
        yt6 = xl0_0 - xl1_1;    yt3 = xl1_0 - xl0_1;

        if (radix == 2) {
            /*-----------------------------------------------------*/
            /* Zero out the contributions of x4..x7 for the high   */
            /* leg if the radix is 2, rememebering that the cont-  */
            /* ributions are restricted within four points.        */
            /*-----------------------------------------------------*/
            x_4 = x_5 = x_6 = x_7 = 0;
        }

        /*---------------------------------------------------------*/
        /* Perform radix4 decomposition as a series of radix2 DIF  */
        /* compositions. This yields yt1:yt0 and yt5:yt4           */
        /*---------------------------------------------------------*/
        xh0_0 = x_0 + x_4;      xh1_0 = x_1 + x_5;
        xh0_1 = x_2 + x_6;      xh1_1 = x_3 + x_7;
        yt0 = xh0_0 + xh0_1;    yt1 = xh1_0 + xh1_1;
        yt4 = xh0_0 - xh0_1;    yt5 = xh1_0 - xh1_1;

        /*---------------------------------------------------------*/
        /*  Store out the results of the radix4 butterfly as 4 o/p */
        /* or the result of 2 radix2 butterflies.                  */
        /*---------------------------------------------------------*/
        y0[k] = yt0;    y0[k+1] = yt1;
        y1[k] = yt2;    y1[k+1] = yt3;
        y2[k] = yt4;    y2[k+1] = yt5;
        y3[k] = yt6;    y3[k+1] = yt7;
    }
}

/* ======================================================================== */
/*  End of file: DSP_fft16x16r_cn.c                                         */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2011 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

