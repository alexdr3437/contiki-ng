/*
 * Copyright (c) 2018, RISE SICS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Node-id management
 * \author
 *         Simon Duquennoy <simon.duquennoy@ri.se>
 */

#include "contiki.h"
#include "sys/node-id.h"
#include "net/linkaddr.h"
#include "services/deployment/deployment.h"
#include "arch/platform/cooja/dev/moteid.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "DEP"
#define LOG_LEVEL LOG_LEVEL_INFO

uint16_t node_id = 0;

void node_id_init(void)
{
#if BUILD_WITH_DEPLOYMENT
    deployment_init();
#else  /* BUILD_WITH_DEPLOYMENT */
    #ifndef NODE_ID // this will be defined when compiling for hardware (defined in makefile), undefined when compiling for cooja
        LOG_INFO("link addr = ");
        LOG_INFO_LLADDR(&linkaddr_node_addr);
        LOG_INFO_("\n");
        node_id = linkaddr_node_addr.u8[0];
    #else
        linkaddr_node_addr.u8[0] = NODE_ID;
        linkaddr_node_addr.u8[1] = 0x00;
        node_id = NODE_ID;
    #endif
#endif /* BUILD_WITH_DEPLOYMENT */
}
