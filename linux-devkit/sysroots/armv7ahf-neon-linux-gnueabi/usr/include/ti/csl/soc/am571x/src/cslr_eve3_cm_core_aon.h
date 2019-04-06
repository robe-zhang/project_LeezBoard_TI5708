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
#ifndef CSLR_EVE3_CM_CORE_AON_H
#define CSLR_EVE3_CM_CORE_AON_H

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
    volatile Uint32 CM_EVE3_CLKSTCTRL_REG;
    volatile Uint32 CM_EVE3_STATICDEP_REG;
    volatile Uint8  RSVD0[24];
    volatile Uint32 CM_EVE3_EVE3_CLKCTRL_REG;
} CSL_eve3_cm_core_aonRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* This register enables the EVE domain power state transition. It controls 
 * the HW supervised domain power state transition between ON-ACTIVE and 
 * ON-INACTIVE states. It also hold one status bit per clock input of the 
 * domain. */
#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG              (0x0U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL  (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG)


/* This register controls the static domain depedencies from EVE3 domain 
 * towards 'target' domains. It is relevant only for domain having system 
 * initiator(s). */
#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG              (0x4U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP  (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG)


/* This register manages the EVE clocks. */
#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG           (0x20U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL  (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG)



/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* CM_EVE3_CLKSTCTRL_REG */

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_MASK  (0x00000003U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKTRCTRL_MASK              (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_RESETVAL  (0x00000003U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_SHIFT  (0U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKTRCTRL_SHIFT             (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_NO_SLEEP  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKTRCTRL_NO_SLEEP          (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_NO_SLEEP)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_SW_SLEEP  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKTRCTRL_SW_SLEEP          (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_SW_SLEEP)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_SW_WKUP  (0x00000002U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKTRCTRL_SW_WKUP           (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_SW_WKUP)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_HW_AUTO  (0x00000003U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKTRCTRL_HW_AUTO           (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKTRCTRL_HW_AUTO)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_MASK  (0x00000100U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKACTIVITY_EVE3_GFCLK_MASK  (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_RESETVAL  (0x00000000U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_SHIFT  (8U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKACTIVITY_EVE3_GFCLK_SHIFT  (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_INACT  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKACTIVITY_EVE3_GFCLK_INACT  (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_INACT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_ACT  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_CLKSTCTRL_CLKACTIVITY_EVE3_GFCLK_ACT  (CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_CLKACTIVITY_EVE3_GFCLK_ACT)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_CLKSTCTRL_REG_RESETVAL     (0x00000003U)

/* CM_EVE3_STATICDEP_REG */

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_MASK  (0x00000004U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_IVA_STATDEP_MASK            (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_RESETVAL  (0x00000000U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_SHIFT  (2U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_IVA_STATDEP_SHIFT           (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_IVA_STATDEP_ENABLED         (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_ENABLED)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_IVA_STATDEP_DISABLED        (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_IVA_STATDEP_DISABLED)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_MASK  (0x00000010U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EMIF_STATDEP_MASK           (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_RESETVAL  (0x00000001U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_SHIFT  (4U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EMIF_STATDEP_SHIFT          (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EMIF_STATDEP_ENABLED        (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_ENABLED)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EMIF_STATDEP_DISABLED       (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EMIF_STATDEP_DISABLED)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_L3MAIN1_STATDEP_MASK  (0x00000020U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_L3MAIN1_STATDEP_MASK        (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_L3MAIN1_STATDEP_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_L3MAIN1_STATDEP_RESETVAL  (0x00000001U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_L3MAIN1_STATDEP_SHIFT  (5U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_L3MAIN1_STATDEP_SHIFT       (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_L3MAIN1_STATDEP_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_L3MAIN1_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_L3MAIN1_STATDEP_ENABLED     (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_L3MAIN1_STATDEP_ENABLED)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_MASK  (0x00080000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE1_STATDEP_MASK           (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_RESETVAL  (0x00000000U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_SHIFT  (19U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE1_STATDEP_SHIFT          (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE1_STATDEP_ENABLED        (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_ENABLED)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE1_STATDEP_DISABLED       (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE1_STATDEP_DISABLED)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_MASK  (0x00100000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE2_STATDEP_MASK           (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_RESETVAL  (0x00000000U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_SHIFT  (20U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE2_STATDEP_SHIFT          (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE2_STATDEP_ENABLED        (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_ENABLED)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE2_STATDEP_DISABLED       (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE2_STATDEP_DISABLED)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_MASK  (0x00400000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE4_STATDEP_MASK           (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_RESETVAL  (0x00000000U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_SHIFT  (22U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE4_STATDEP_SHIFT          (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_ENABLED  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE4_STATDEP_ENABLED        (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_ENABLED)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_STATICDEP_EVE4_STATDEP_DISABLED       (CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_EVE4_STATDEP_DISABLED)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_STATICDEP_REG_RESETVAL     (0x00000030U)

/* CM_EVE3_EVE3_CLKCTRL_REG */

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_MASK  (0x00030000U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_IDLEST_MASK              (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_RESETVAL  (0x00000003U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_SHIFT  (16U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_IDLEST_SHIFT             (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_DISABLE  (0x00000003U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_IDLEST_DISABLE           (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_DISABLE)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_IDLE  (0x00000002U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_IDLEST_IDLE              (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_IDLE)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_FUNC  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_IDLEST_FUNC              (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_FUNC)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_TRANS  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_IDLEST_TRANS             (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_IDLEST_TRANS)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_MASK  (0x00040000U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_STBYST_MASK              (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_RESETVAL  (0x00000001U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_SHIFT  (18U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_STBYST_SHIFT             (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_FUNC  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_STBYST_FUNC              (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_FUNC)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_STANDBY  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_STBYST_STANDBY           (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_STBYST_STANDBY)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_MASK  (0x00000003U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_MODULEMODE_MASK          (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_MASK)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_RESETVAL  (0x00000000U)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_SHIFT  (0U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_MODULEMODE_SHIFT         (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_SHIFT)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_DISABLED  (0x00000000U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_MODULEMODE_DISABLED      (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_DISABLED)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_AUTO  (0x00000001U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_MODULEMODE_AUTO          (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_AUTO)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_RESERVED_2  (0x00000002U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_MODULEMODE_RESERVED_2    (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_RESERVED_2)

#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_RESERVED  (0x00000003U)
/* Below define for backward compatibility */
#define CM_EVE3_EVE3_CLKCTRL_MODULEMODE_RESERVED      (CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_MODULEMODE_RESERVED)


#define CSL_EVE3_CM_CORE_AON_CM_EVE3_EVE3_CLKCTRL_REG_RESETVAL  (0x00070000U)

#ifdef __cplusplus
}
#endif
#endif