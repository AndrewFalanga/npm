#include "ProgParams.h"

#include <getopt.h>
#include <stdio.h>

static Parameters programParameters = {0};

/* The options defined in Issues #32
-s|--signing-key <path/to/private.pem>
-a|--authentication-key <path/to/public.pem>
-c|--config-file <path/to/netpm.config>
-d|--debug flag parameter to signal whether debugging of the binary is to be done. This flag also prevents the program from forking to a daemon
-v|--version print the version of the program
-u|--udp-address The address which the monitor is to use for monitoring power event
*/

/* The pattern used in most applications of GNU long options is that the use of
 * the long option returns the short counterpoint.
 */
const char *shortOpts = "s:a:c:dvu:";
const struct option longOptions[] = {
    {
        .name = "signing-key",
        .has_arg = required_argument,
        .flag = NULL,
        .val = 's',
    },
    {
        .name = "authentication-key",
        .has_arg = required_argument,
        .flag = NULL,
        .val = 'a',
    },
    {
        .name = "config-file",
        .has_arg = required_argument,
        .flag = NULL,
        .val = 'c',
    },
    {
        .name = "debug",
        .has_arg = no_argument,
        .flag = NULL,
        .val = 'd',
    },
    {
        .name = "version",
        .has_arg = no_argument,
        .flag = NULL,
        .val = 'v',
    },
    {
        .name = "udp-address",
        .has_arg = required_argument,
        .flag = NULL,
        .val = 'u',
    },
    { 0 },
};

Parameters* ParseCommandLine(int argc, char **argv)
{
    int arg;

    while ((arg = getopt_long(argc, argv, shortOpts, longOptions, NULL)) >= 0)
    {
        /* Perhaps showing my age. This pattern helps to trigger when someone
         * forgot to use == instead of = in a conditional check. Most modern
         * compilers catch this so it isn't as aggrivating now as it once was.
         * (Yes, I'm that old. ;-)
         */
        if ('s' == arg)
        {
            programParameters.signKey = optarg;
        }
        else if ('a' == arg )
        {
            programParameters.authenticationKey = optarg;
        }
        else if ('c' == arg)
        {
            programParameters.configFile = optarg;
        }
        else if ('d' == arg)
        {
            programParameters.debug = 1;
        }
        else if ('v' == arg)
        {
            programParameters.showVersion = 1;
        }
        else if ('u' == arg)
        {
            programParameters.agentAddress = optarg;
        }
        else if ('?' == arg)
        {
            fprintf(stderr, "The option %c is unknown\n", optopt);
        }
        else
        {
            int i = 0;
            fprintf(stderr, "Unexpected command arguments parsed. Provided...\n");
            for ( ; i < argc; i++)
            {
                fprintf(stderr, "Arg %d -> %s\n", (i + 1), argv[i]);
            }
            return NULL;
        }
    }

    return &programParameters;
}
