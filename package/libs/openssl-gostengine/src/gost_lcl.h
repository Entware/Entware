#ifndef GOST_TOOLS_H
# define GOST_TOOLS_H
/**********************************************************************
 *                        gost_lcl.h                                  *
 *             Copyright (c) 2006 Cryptocom LTD                       *
 *       This file is distributed under the same license as OpenSSL   *
 *                                                                    *
 *         Internal declarations  used in GOST engine                *
 *         OpenSSL 0.9.9 libraries required to compile and use        *
 *                              this code                             *
 **********************************************************************/
# include <openssl/bn.h>
# include <openssl/evp.h>
# include <openssl/dsa.h>
# include <openssl/asn1t.h>
# include <openssl/x509.h>
# include <openssl/engine.h>
# include <openssl/ec.h>
# include "gost89.h"
# include "gosthash.h"
/* Control commands */
# define GOST_PARAM_CRYPT_PARAMS 0
# define GOST_PARAM_PBE_PARAMS 1
# define GOST_PARAM_MAX 1
# define GOST_CTRL_CRYPT_PARAMS (ENGINE_CMD_BASE+GOST_PARAM_CRYPT_PARAMS)
# define GOST_CTRL_PBE_PARAMS   (ENGINE_CMD_BASE+GOST_PARAM_PBE_PARAMS)

typedef struct R3410_ec {
    int nid;
    char *a;
    char *b;
    char *p;
    char *q;
    char *x;
    char *y;
} R3410_ec_params;

extern R3410_ec_params R3410_2001_paramset[],
    *R3410_2012_256_paramset, R3410_2012_512_paramset[];

extern const ENGINE_CMD_DEFN gost_cmds[];
int gost_control_func(ENGINE *e, int cmd, long i, void *p, void (*f) (void));
const char *get_gost_engine_param(int param);
int gost_set_default_param(int param, const char *value);
void gost_param_free(void);

/* method registration */

int register_ameth_gost(int nid, EVP_PKEY_ASN1_METHOD **ameth,
                        const char *pemstr, const char *info);
int register_pmeth_gost(int id, EVP_PKEY_METHOD **pmeth, int flags);

/* Gost-specific pmeth control-function parameters */
/* For GOST R34.10 parameters */
# define param_ctrl_string "paramset"
# define EVP_PKEY_CTRL_GOST_PARAMSET (EVP_PKEY_ALG_CTRL+1)
/* For GOST 28147 MAC */
# define key_ctrl_string "key"
# define hexkey_ctrl_string "hexkey"
# define maclen_ctrl_string "size"
# define EVP_PKEY_CTRL_GOST_MAC_HEXKEY (EVP_PKEY_ALG_CTRL+3)
# define EVP_PKEY_CTRL_MAC_LEN (EVP_PKEY_ALG_CTRL+5)
/* Pmeth internal representation */
struct gost_pmeth_data {
    int sign_param_nid;         /* Should be set whenever parameters are
                                 * filled */
    EVP_MD *md;
    unsigned char *shared_ukm;
    int peer_key_used;
};

struct gost_mac_pmeth_data {
    short int key_set;
    short int mac_size;
    int mac_param_nid;
    EVP_MD *md;
    unsigned char key[32];
};

struct gost_mac_key {
    int mac_param_nid;
    unsigned char key[32];
    short int mac_size;
};
/* GOST-specific ASN1 structures */

typedef struct {
    ASN1_OCTET_STRING *encrypted_key;
    ASN1_OCTET_STRING *imit;
} GOST_KEY_INFO;

DECLARE_ASN1_FUNCTIONS(GOST_KEY_INFO)

typedef struct {
    ASN1_OBJECT *cipher;
    X509_PUBKEY *ephem_key;
    ASN1_OCTET_STRING *eph_iv;
} GOST_KEY_AGREEMENT_INFO;

DECLARE_ASN1_FUNCTIONS(GOST_KEY_AGREEMENT_INFO)

typedef struct {
    GOST_KEY_INFO *key_info;
    GOST_KEY_AGREEMENT_INFO *key_agreement_info;
} GOST_KEY_TRANSPORT;

DECLARE_ASN1_FUNCTIONS(GOST_KEY_TRANSPORT)

typedef struct {                /* FIXME incomplete */
    GOST_KEY_TRANSPORT *gkt;
} GOST_CLIENT_KEY_EXCHANGE_PARAMS;

/*
 * Hacks to shorten symbols to 31 characters or less, or OpenVMS. This mimics
 * what's done in symhacks.h, but since this is a very local header file, I
 * prefered to put this hack directly here. -- Richard Levitte
 */
# ifdef OPENSSL_SYS_VMS
#  undef GOST_CLIENT_KEY_EXCHANGE_PARAMS_it
#  define GOST_CLIENT_KEY_EXCHANGE_PARAMS_it      GOST_CLIENT_KEY_EXC_PARAMS_it
#  undef GOST_CLIENT_KEY_EXCHANGE_PARAMS_new
#  define GOST_CLIENT_KEY_EXCHANGE_PARAMS_new     GOST_CLIENT_KEY_EXC_PARAMS_new
#  undef GOST_CLIENT_KEY_EXCHANGE_PARAMS_free
#  define GOST_CLIENT_KEY_EXCHANGE_PARAMS_free    GOST_CLIENT_KEY_EXC_PARAMS_free
#  undef d2i_GOST_CLIENT_KEY_EXCHANGE_PARAMS
#  define d2i_GOST_CLIENT_KEY_EXCHANGE_PARAMS     d2i_GOST_CLIENT_KEY_EXC_PARAMS
#  undef i2d_GOST_CLIENT_KEY_EXCHANGE_PARAMS
#  define i2d_GOST_CLIENT_KEY_EXCHANGE_PARAMS     i2d_GOST_CLIENT_KEY_EXC_PARAMS
# endif                         /* End of hack */
DECLARE_ASN1_FUNCTIONS(GOST_CLIENT_KEY_EXCHANGE_PARAMS)
typedef struct {
    ASN1_OBJECT *key_params;
    ASN1_OBJECT *hash_params;
    ASN1_OBJECT *cipher_params;
} GOST_KEY_PARAMS;

DECLARE_ASN1_FUNCTIONS(GOST_KEY_PARAMS)

typedef struct {
    ASN1_OCTET_STRING *iv;
    ASN1_OBJECT *enc_param_set;
} GOST_CIPHER_PARAMS;

DECLARE_ASN1_FUNCTIONS(GOST_CIPHER_PARAMS)

typedef struct {
    ASN1_OCTET_STRING *masked_priv_key;
    ASN1_OCTET_STRING *public_key;
} MASKED_GOST_KEY;

DECLARE_ASN1_FUNCTIONS(MASKED_GOST_KEY)

/*============== Message digest  and cipher related structures  ==========*/
    /*
     * Structure used as EVP_MD_CTX-md_data. It allows to avoid storing
     * in the md-data pointers to dynamically allocated memory. I
     * cannot invent better way to avoid memory leaks, because openssl
     * insist on invoking Init on Final-ed digests, and there is no
     * reliable way to find out whether pointer in the passed md_data is
     * valid or not.
     */
struct ossl_gost_digest_ctx {
    gost_hash_ctx dctx;
    gost_ctx cctx;
};
/* EVP_MD structure for GOST R 34.11 */
EVP_MD *digest_gost(void);
void digest_gost_destroy(void);
/* EVP MD structure for GOST R 34.11-2012 algorithms */
EVP_MD *digest_gost2012_256(void);
EVP_MD *digest_gost2012_512(void);
void digest_gost2012_256_destroy(void);
void digest_gost2012_512_destroy(void);
/* EVP_MD structure for GOST 28147 in MAC mode */
EVP_MD *imit_gost_cpa(void);
void imit_gost_cpa_destroy(void);
EVP_MD *imit_gost_cp_12(void);
void imit_gost_cp_12_destroy(void);
/* Cipher context used for EVP_CIPHER operation */
struct ossl_gost_cipher_ctx {
    int paramNID;
    unsigned int count;
    int key_meshing;
    gost_ctx cctx;
};
/* Structure to map parameter NID to S-block */
struct gost_cipher_info {
    int nid;
    gost_subst_block *sblock;
    int key_meshing;
};
/* Context for MAC */
struct ossl_gost_imit_ctx {
    gost_ctx cctx;
    unsigned char buffer[8];
    unsigned char partial_block[8];
    unsigned int count;
    int key_meshing;
    int bytes_left;
    int key_set;
    int dgst_size;
};
/* Table which maps parameter NID to S-blocks */
extern struct gost_cipher_info gost_cipher_list[];
/* Find encryption params from ASN1_OBJECT */
const struct gost_cipher_info *get_encryption_params(ASN1_OBJECT *obj);
/* Implementation of GOST 28147-89 cipher in CFB and CNT modes */
const EVP_CIPHER *cipher_gost();
const EVP_CIPHER *cipher_gost_cbc();
const EVP_CIPHER *cipher_gost_cpacnt();
const EVP_CIPHER *cipher_gost_cpcnt_12();
void cipher_gost_destroy();
# define EVP_MD_CTRL_KEY_LEN (EVP_MD_CTRL_ALG_CTRL+3)
# define EVP_MD_CTRL_SET_KEY (EVP_MD_CTRL_ALG_CTRL+4)
# define EVP_MD_CTRL_MAC_LEN (EVP_MD_CTRL_ALG_CTRL+5)
/* EVP_PKEY_METHOD key encryption callbacks */
/* From gost_ec_keyx.c */
int pkey_GOST_ECcp_encrypt(EVP_PKEY_CTX *ctx, unsigned char *out,
                           size_t *outlen, const unsigned char *key,
                           size_t key_len);

int pkey_GOST_ECcp_decrypt(EVP_PKEY_CTX *ctx, unsigned char *out,
                           size_t *outlen, const unsigned char *in,
                           size_t in_len);
/* derive functions */
/* From gost_ec_keyx.c */
int pkey_gost_ec_derive(EVP_PKEY_CTX *ctx, unsigned char *key,
                        size_t *keylen);
int fill_GOST_EC_params(EC_KEY *eckey, int nid);
int gost_sign_keygen(DSA *dsa);
int gost_ec_keygen(EC_KEY *ec);

DSA_SIG *gost_ec_sign(const unsigned char *dgst, int dlen, EC_KEY *eckey);

int gost_do_verify(const unsigned char *dgst, int dgst_len,
                   DSA_SIG *sig, DSA *dsa);
int gost_ec_verify(const unsigned char *dgst, int dgst_len,
                   DSA_SIG *sig, EC_KEY *ec);
int gost_ec_compute_public(EC_KEY *ec);
/*============== miscellaneous functions============================= */
/* from gost_sign.c */
/* Convert GOST R 34.11 hash sum to bignum according to standard */
BIGNUM *hashsum2bn(const unsigned char *dgst, int len);
/*
 * Store bignum in byte array of given length, prepending by zeros if
 * nesseccary
 */
int store_bignum(const BIGNUM *bn, unsigned char *buf, int len);
/* Pack GOST R 34.10 signature according to CryptoPro rules */
int pack_sign_cp(DSA_SIG *s, int order, unsigned char *sig, size_t *siglen);
/* from ameth.c */
/* Get private key as BIGNUM from both 34.10-2001 keys*/
/* Returns pointer into EVP_PKEY structure */
BIGNUM *gost_get0_priv_key(const EVP_PKEY *pkey);

#endif
