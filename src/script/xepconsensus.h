// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Xep Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef XEP_SCRIPT_XEPCONSENSUS_H
#define XEP_SCRIPT_XEPCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_XEP_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/xep-config.h>
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
#elif defined(MSC_VER) && !defined(STATIC_LIBXEPCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define XEPCONSENSUS_API_VER 1

typedef enum xepconsensus_error_t
{
    xepconsensus_ERR_OK = 0,
    xepconsensus_ERR_TX_INDEX,
    xepconsensus_ERR_TX_SIZE_MISMATCH,
    xepconsensus_ERR_TX_DESERIALIZE,
    xepconsensus_ERR_AMOUNT_REQUIRED,
    xepconsensus_ERR_INVALID_FLAGS,
} xepconsensus_error;

/** Script verification flags */
enum
{
    xepconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    xepconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    xepconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    xepconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    xepconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    xepconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    xepconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    // NOTE: Do NOT add CHECKBLOCKATHEIGHTVERIFY here without updating verify_script to pass context!
    xepconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = xepconsensus_SCRIPT_FLAGS_VERIFY_P2SH | xepconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               xepconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | xepconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               xepconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | xepconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int xepconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, xepconsensus_error* err);

EXPORT_SYMBOL int xepconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, xepconsensus_error* err);

EXPORT_SYMBOL unsigned int xepconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // XEP_SCRIPT_XEPCONSENSUS_H
