#ifndef _PROG_PARMS_H_
#define _PROG_PARMS_H_

#include <stdint.h>

typedef struct {
    char *signKey; /**< Private key PEM file for signing */
    uint32_t signKeyLength; /**< Length of the key in bytes */
    char *authenticationKey; /**< Public key PEM file used in verification */
    uint32_t authenticationKeyLength; /**< Length of the key in bytes */
    uint8_t debug; /**< Boolean flag to signal whether to run in debug */
    uint8_t showVersion; /**< Boolean flag to display version and exit */
    char *agentAddress; /**< For the monitor, the IP of the agent, ignored by the agent */
    char *configFile; /**< If provide, a config file for keys and the agent address */
} Parameters;

Parameters* ParseCommandLine(int argc, char **argv);

#endif
