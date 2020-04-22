// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2014-2020 The Minerium Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MINERIUM_MINERIUMCONSENSUS_H
#define MINERIUM_MINERIUMCONSENSUS_H

#if defined(BUILD_MINERIUM_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/minerium-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBMINERIUMCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MINERIUMCONSENSUS_API_VER 0

typedef enum mineriumconsensus_error_t
{
    mineriumconsensus_ERR_OK = 0,
    mineriumconsensus_ERR_TX_INDEX,
    mineriumconsensus_ERR_TX_SIZE_MISMATCH,
    mineriumconsensus_ERR_TX_DESERIALIZE,
    mineriumconsensus_ERR_INVALID_FLAGS,
} mineriumconsensus_error;

/** Script verification flags */
enum
{
    mineriumconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    mineriumconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    mineriumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    mineriumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    mineriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    mineriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    mineriumconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = mineriumconsensus_SCRIPT_FLAGS_VERIFY_P2SH | mineriumconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                            mineriumconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | mineriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                            mineriumconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int mineriumconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, mineriumconsensus_error* err);

EXPORT_SYMBOL unsigned int mineriumconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // MINERIUM_MINERIUMCONSENSUS_H
