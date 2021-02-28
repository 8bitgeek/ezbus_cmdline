/*****************************************************************************
* Copyright © 2021 Mike Sharkey <mike@8bitgeek.net>                          *
*                                                                            *
* Permission is hereby granted, free of charge, to any person obtaining a    *
* copy of this software and associated documentation files (the "Software"), *
* to deal in the Software without restriction, including without limitation  *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
* and/or sell copies of the Software, and to permit persons to whom the      *
* Software is furnished to do so, subject to the following conditions:       *
*                                                                            *
* The above copyright notice and this permission notice shall be included in *
* all copies or substantial portions of the Software.                        *
*                                                                            *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        *
* DEALINGS IN THE SOFTWARE.                                                  *
*****************************************************************************/
#include <ezbus_cmdline_unix.h>
#include <getopt.h>
#include <stdlib.h>

#if !defined(EZBUS_UDP_ADDRESS)
    #define EZBUS_UDP_ADDRESS           "224.0.0.1"
#endif

#if !defined(EZBUS_UDP_PORT)
    #define EZBUS_UDP_PORT              8260
#endif

extern char *optarg;
extern int optind, opterr, optopt;

extern int ezbus_cmdline_unix_setup(
                                ezbus_cmdline_t* ezbus_cmdline, 
                                ezbus_cmdline_unix_t* ezbus_cmdline_unix
                                )
{
    memset(ezbus_cmdline_unix,0,sizeof(ezbus_cmdline_unix_t)); 
    ezbus_cmdline->platform = ezbus_cmdline_unix;

    ezbus_cmdline_unix->host = EZBUS_UDP_ADDRESS;
    ezbus_cmdline_unix->port = EZBUS_UDP_PORT;

    while ( (ezbus_cmdline_set_opt( 
                                    ezbus_cmdline,
                                    getopt(
                                            ezbus_cmdline_get_argc(ezbus_cmdline), 
                                            ezbus_cmdline_get_argv(ezbus_cmdline), 
                                            "h:p:a:s:b:?")
                                    ) ) >= 0 )
    {
        switch (ezbus_cmdline_get_opt(ezbus_cmdline)) 
        {
            case 'h':
                ezbus_cmdline_unix->host = optarg;
                break;
            case 'p':
                ezbus_cmdline_unix->port = atoi(optarg);
                break;
            case 'a':
                ezbus_cmdline_unix->address = (uint32_t)atoi(optarg);
                break;
            case 's':
                ezbus_cmdline_unix->serial_device = optarg;
                break;
            case 'b':
                ezbus_cmdline_unix->serial_baud = atoi(optarg);
                break;
            case '?':
            default: /* '?' */
                fprintf(stderr, "Usage: %s "
                                " [-h host-bind-address]"
                                " [-p multicast-udp-port]"
                                " [-a ezbus-address]"
                                " [-s rs485-serial device]"
                                " [-b rs485-serial-baud]\n", ezbus_cmdline_get_argv(ezbus_cmdline)[0]);
                return -1;
        }
    }

    return 0;
}
