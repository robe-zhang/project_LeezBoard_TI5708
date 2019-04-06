/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
#ifndef CSLR_GPU_CM_CORE_H
#define CSLR_GPU_CM_CORE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for __ALL__
**************************************************************************/
typedef struct {
    volatile Uint32 CM_GPU_CLKSTCTRL_REG;
    volatile Uint32 CM_GPU_STATICDEP_REG;
    volatile Uint32 CM_GPU_DYNAMICDEP_REG;
    volatile Uint8  RSVD0[20];
    volatile Uint32 CM_GPU_GPU_CLKCTRL_REG;
} CSL_gpu_cm_coreRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* This register enables the GPU domain power state transition. It controls
 * the HW supervised domain power state transition between ON-ACTIVE and
 * ON-INACTIVE states. It also hold one status bit per clock input of the
 * domain. */
#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG                    (0x0U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL      (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG)


/* This register controls the static domain depedencies from GPU domain
 * towards 'target' domains. It is relevant only for domain having system
 * initiator(s). */
#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG                    (0x4U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP      (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG)


/* This register controls the dynamic domain depedencies from GPU domain
 * towards 'target' domains. It is relevant only for domain having OCP master
 * port(s). */
#define CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG                   (0x8U)
/* Below define for backward compatibility */
#define CM_GPU_DYNAMICDEP     (CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG)


/* This register manages the GPU clocks. */
#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG                  (0x20U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL    (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG)



/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* CM_GPU_CLKSTCTRL_REG */

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_MASK     (0x00000003U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKTRCTRL_MASK               (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_RESETVAL  (0x00000003U)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_SHIFT    (0U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKTRCTRL_SHIFT              (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_NO_SLEEP  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKTRCTRL_NO_SLEEP           (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_NO_SLEEP)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_SW_SLEEP  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKTRCTRL_SW_SLEEP           (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_SW_SLEEP)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_SW_WKUP  (0x00000002U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKTRCTRL_SW_WKUP            (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_SW_WKUP)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_HW_AUTO  (0x00000003U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKTRCTRL_HW_AUTO            (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKTRCTRL_HW_AUTO)


#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_MASK  (0x00000100U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_L3_GICLK_MASK  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_SHIFT  (8U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_L3_GICLK_SHIFT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_INACT  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_L3_GICLK_INACT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_INACT)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_ACT  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_L3_GICLK_ACT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_L3_GICLK_ACT)


#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_MASK  (0x00000200U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_CORE_GCLK_MASK  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_SHIFT  (9U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_CORE_GCLK_SHIFT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_INACT  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_CORE_GCLK_INACT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_INACT)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_ACT  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_CORE_GCLK_ACT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_CORE_GCLK_ACT)


#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_MASK  (0x00000400U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_HYD_GCLK_MASK  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_SHIFT  (10U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_HYD_GCLK_SHIFT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_INACT  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_HYD_GCLK_INACT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_INACT)

#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_ACT  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_CLKSTCTRL_CLKACTIVITY_GPU_HYD_GCLK_ACT  (CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_CLKACTIVITY_GPU_HYD_GCLK_ACT)


#define CSL_GPU_CM_CORE_CM_GPU_CLKSTCTRL_REG_RESETVAL           (0x00000003U)

/* CM_GPU_STATICDEP_REG */

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_MASK   (0x00000004U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_IVA_STATDEP_MASK             (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_SHIFT  (2U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_IVA_STATDEP_SHIFT            (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_IVA_STATDEP_ENABLED          (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_ENABLED)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_IVA_STATDEP_DISABLED         (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_IVA_STATDEP_DISABLED)


#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_MASK  (0x00000010U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_EMIF_STATDEP_MASK            (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_SHIFT  (4U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_EMIF_STATDEP_SHIFT           (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_EMIF_STATDEP_ENABLED         (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_ENABLED)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_EMIF_STATDEP_DISABLED        (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_EMIF_STATDEP_DISABLED)


#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_L3MAIN1_STATDEP_MASK  (0x00000020U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_L3MAIN1_STATDEP_MASK         (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_L3MAIN1_STATDEP_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_L3MAIN1_STATDEP_RESETVAL  (0x00000001U)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_L3MAIN1_STATDEP_SHIFT  (5U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_L3MAIN1_STATDEP_SHIFT        (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_L3MAIN1_STATDEP_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_L3MAIN1_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_STATICDEP_L3MAIN1_STATDEP_ENABLED      (CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_L3MAIN1_STATDEP_ENABLED)


#define CSL_GPU_CM_CORE_CM_GPU_STATICDEP_REG_RESETVAL           (0x00000020U)

/* CM_GPU_DYNAMICDEP_REG */

#define CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_L3MAIN1_DYNDEP_MASK  (0x00000040U)
/* Below define for backward compatibility */
#define CM_GPU_DYNAMICDEP_L3MAIN1_DYNDEP_MASK         (CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_L3MAIN1_DYNDEP_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_L3MAIN1_DYNDEP_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_L3MAIN1_DYNDEP_SHIFT  (6U)
/* Below define for backward compatibility */
#define CM_GPU_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT        (CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_L3MAIN1_DYNDEP_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_L3MAIN1_DYNDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_DYNAMICDEP_L3MAIN1_DYNDEP_DISABLED     (CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_L3MAIN1_DYNDEP_DISABLED)


#define CSL_GPU_CM_CORE_CM_GPU_DYNAMICDEP_REG_RESETVAL          (0x00000000U)

/* CM_GPU_GPU_CLKCTRL_REG */

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_MASK      (0x00030000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_IDLEST_MASK                (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_RESETVAL  (0x00000003U)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_SHIFT     (16U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_IDLEST_SHIFT               (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_DISABLE   (0x00000003U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_IDLEST_DISABLE             (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_DISABLE)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_IDLE      (0x00000002U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_IDLEST_IDLE                (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_IDLE)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_FUNC      (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_IDLEST_FUNC                (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_FUNC)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_TRANS     (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_IDLEST_TRANS               (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_IDLEST_TRANS)


#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_MASK      (0x00040000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_STBYST_MASK                (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_RESETVAL  (0x00000001U)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_SHIFT     (18U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_STBYST_SHIFT               (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_FUNC      (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_STBYST_FUNC                (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_FUNC)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_STANDBY   (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_STBYST_STANDBY             (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_STBYST_STANDBY)


#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_MASK  (0x00000003U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_MODULEMODE_MASK            (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_SHIFT  (0U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_MODULEMODE_SHIFT           (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_MODULEMODE_DISABLED        (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_DISABLED)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_RESERVED_1  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_MODULEMODE_RESERVED_1      (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_RESERVED_1)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_ENABLE  (0x00000002U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_MODULEMODE_ENABLE          (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_ENABLE)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_RESERVED  (0x00000003U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_MODULEMODE_RESERVED        (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_MODULEMODE_RESERVED)


#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_MASK  (0x03000000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_CORE_CLK_MASK       (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SHIFT  (24U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_CORE_CLK_SHIFT      (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SEL_CORE_GPU_CLK  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_CORE_CLK_SEL_CORE_GPU_CLK  (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SEL_CORE_GPU_CLK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SEL_PER_GPU_CLK  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_CORE_CLK_SEL_PER_GPU_CLK  (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SEL_PER_GPU_CLK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SEL_GPU_GCLK  (0x00000002U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_CORE_CLK_SEL_GPU_GCLK  (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_SEL_GPU_GCLK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_RESERVED  (0x00000003U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_CORE_CLK_RESERVED   (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_CORE_CLK_RESERVED)


#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_MASK  (0x0C000000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_HYD_CLK_MASK        (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_MASK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_RESETVAL  (0x00000000U)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SHIFT  (26U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_HYD_CLK_SHIFT       (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SHIFT)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SEL_CORE_GPU_CLK  (0x00000000U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_HYD_CLK_SEL_CORE_GPU_CLK  (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SEL_CORE_GPU_CLK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SEL_PER_GPU_CLK  (0x00000001U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_HYD_CLK_SEL_PER_GPU_CLK  (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SEL_PER_GPU_CLK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SEL_GPU_GCLK  (0x00000002U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_HYD_CLK_SEL_GPU_GCLK  (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_SEL_GPU_GCLK)

#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_RESERVED  (0x00000003U)
/* Below define for backward compatibility */
#define CM_GPU_GPU_CLKCTRL_CLKSEL_HYD_CLK_RESERVED    (CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_CLKSEL_HYD_CLK_RESERVED)


#define CSL_GPU_CM_CORE_CM_GPU_GPU_CLKCTRL_REG_RESETVAL         (0x00070000U)

#ifdef __cplusplus
}
#endif
#endif