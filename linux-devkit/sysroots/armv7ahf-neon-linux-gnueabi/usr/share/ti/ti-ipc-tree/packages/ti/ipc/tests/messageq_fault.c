/*
 * Copyright (c) 2012-2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== messageq_single.c ========
 *
 *  Single threaded test of messageq over rpmsg.
 *
 *  See:
 *      MessageQApp in Linux user space
 *
 */
#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#include <ti/ipc/MessageQ.h>

#if defined (DSP_1)
#include "gatempapp_rsc_table_vayu_dsp.h"
#endif

#define SLAVE_MESSAGEQNAME "SLAVE"

#define MessageQ_payload(m) ((void *)((char *)(m) + sizeof(MessageQ_MsgHeader)))

Int32 fxnFault(UInt32 faultId)
{
    Int32 a;
    Void (*fxn)(void) = (Void (*)())0x96000000;
    volatile Int dummy = 0;

    switch (faultId) {
        case 0:  /* no fault */
            return 0;
        case 1:
            System_printf("Generating read MMU Fault...\n");
            a = *(volatile int *)(0x96000000);
            break;
        case 2:
            System_printf("Generating write MMU Fault...\n");
            *(volatile int *)(0x96000000) = 0x1;
            break;
        case 3:
            System_printf("Generating program MMU Fault...\n");
            fxn();
            break;
        case 4:
            System_printf("Generating exception (w/ divide-by-zero...)\n");
            dummy = dummy / dummy;
            break;
        case 5:
            System_printf("Forcing Watchdog interrupt (w/ spin)...\n");
            dummy = 1;
            while(dummy);
            break;
        default:
            System_printf("Invalid fxnFault test\n");
            break;
    }

    /* don't really need to return 'a', but shuts up compiler warning */
    return(a);
}

/*
 *  ======== tsk1Fxn ========
 *  Receive and return messages
 */
Void tsk1Fxn(UArg arg0, UArg arg1)
{
    MessageQ_Msg msg;
    MessageQ_Handle  messageQ;
    MessageQ_QueueId remoteQueueId;
    Char             localQueueName[64];
    UInt16 procId;
    Int status;
    UInt32 i;
    UInt32 msgId;
    UInt32 start;
    UInt32 end;
    UInt32 numLoops;
    UInt32 print;
    UInt32 *params;
    Int32 faultId;

    /* Construct a MessageQ name adorned with core name: */
    System_sprintf(localQueueName, "%s_%s", SLAVE_MESSAGEQNAME,
                   MultiProc_getName(MultiProc_self()));

    messageQ = MessageQ_create(localQueueName, NULL);
    if (messageQ == NULL) {
        System_abort("MessageQ_create failed\n");
    }

    System_printf("tsk1Fxn: created MessageQ: %s; QueueID: 0x%x\n",
        localQueueName, MessageQ_getQueueId(messageQ));

    while (1) {
        /* handshake with host to get starting parameters */
        System_printf("Awaiting sync message from host...\n");
        MessageQ_get(messageQ, &msg, MessageQ_FOREVER);

        params = MessageQ_payload(msg);
        numLoops = params[0];
        print = params[1];

        remoteQueueId = MessageQ_getReplyQueue(msg);
        procId = MessageQ_getProcId(remoteQueueId);

        System_printf("Received msg from (procId:remoteQueueId): 0x%x:0x%x\n"
            "\tpayload: %d bytes; loops: %d %s printing.\n",
            procId, remoteQueueId,
            (MessageQ_getMsgSize(msg) - sizeof(MessageQ_MsgHeader)),
            numLoops, print ? "with" : "without");

        MessageQ_put(remoteQueueId, msg);

        start = Clock_getTicks();

        for (i = 1; i <= numLoops; i++) {
            status = MessageQ_get(messageQ, &msg, MessageQ_FOREVER);
            Assert_isTrue(status == MessageQ_S_SUCCESS, NULL);

            params = MessageQ_payload(msg);
            msgId = params[0];
	    faultId = params[2];

            if (print) {
                System_printf("Got msg #%d (%d bytes) from procId %d\n",
                    msgId, MessageQ_getMsgSize(msg), procId);
            }

            Assert_isTrue(msgId == i, NULL);

            if (faultId < 0) {
                System_printf("Generating fault %d before MessageQ_put()...\n",
                              -faultId);
                fxnFault(-faultId);
            }

            if (print) {
                System_printf("Sending msg Id #%d to procId %d\n", i, procId);
            }

            status = MessageQ_put(remoteQueueId, msg);
            Assert_isTrue(status == MessageQ_S_SUCCESS, NULL);

            if (faultId > 0) {
                System_printf("Generating fault %d after MessageQ_put()...\n",
                              faultId);
                fxnFault(faultId);
            }
        }

        end = Clock_getTicks();

        if (!print) {
            System_printf("%d iterations took %d ticks or %d usecs/msg\n",
                    numLoops, end - start,
                    ((end - start) * Clock_tickPeriod) / numLoops);
        }
    }
}

/*
 *  ======== main ========
 */
Int main(Int argc, Char* argv[])
{
    System_printf("%s:main: MultiProc id = %d\n", __FILE__, MultiProc_self());

    Task_create(tsk1Fxn, NULL, NULL);

    BIOS_start();

    return (0);
}
