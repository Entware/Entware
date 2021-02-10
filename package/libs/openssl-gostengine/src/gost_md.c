/**********************************************************************
 *                          md_gost.c                                 *
 *             Copyright (c) 2005-2006 Cryptocom LTD                  *
 *         This file is distributed under the same license as OpenSSL *
 *                                                                    *
 *       OpenSSL interface to GOST R 34.11-94 hash functions          *
 *          Requires OpenSSL 0.9.9 for compilation                    *
 **********************************************************************/
#include <string.h>
#include "gost_lcl.h"
#include "gosthash.h"
#include "e_gost_err.h"

/* implementation of GOST 34.11 hash function See gost_md.c*/
static int gost_digest_init(EVP_MD_CTX *ctx);
static int gost_digest_update(EVP_MD_CTX *ctx, const void *data,
                              size_t count);
static int gost_digest_final(EVP_MD_CTX *ctx, unsigned char *md);
static int gost_digest_copy(EVP_MD_CTX *to, const EVP_MD_CTX *from);
static int gost_digest_cleanup(EVP_MD_CTX *ctx);

static EVP_MD *_hidden_GostR3411_94_md = NULL;

EVP_MD *digest_gost(void)
{
    if (_hidden_GostR3411_94_md == NULL) {
        EVP_MD *md;

        if ((md = EVP_MD_meth_new(NID_id_GostR3411_94, NID_undef)) == NULL
            || !EVP_MD_meth_set_result_size(md, 32)
            || !EVP_MD_meth_set_input_blocksize(md, 32)
            || !EVP_MD_meth_set_app_datasize(md,
                                             sizeof(struct
                                                    ossl_gost_digest_ctx))
            || !EVP_MD_meth_set_init(md, gost_digest_init)
            || !EVP_MD_meth_set_update(md, gost_digest_update)
            || !EVP_MD_meth_set_final(md, gost_digest_final)
            || !EVP_MD_meth_set_copy(md, gost_digest_copy)
            || !EVP_MD_meth_set_cleanup(md, gost_digest_cleanup)) {
            EVP_MD_meth_free(md);
            md = NULL;
        }
        _hidden_GostR3411_94_md = md;
    }
    return _hidden_GostR3411_94_md;
}

void digest_gost_destroy(void)
{
    EVP_MD_meth_free(_hidden_GostR3411_94_md);
    _hidden_GostR3411_94_md = NULL;
}

int gost_digest_init(EVP_MD_CTX *ctx)
{
    struct ossl_gost_digest_ctx *c = EVP_MD_CTX_md_data(ctx);
    memset(&(c->dctx), 0, sizeof(gost_hash_ctx));
    gost_init(&(c->cctx), &GostR3411_94_CryptoProParamSet);
    c->dctx.cipher_ctx = &(c->cctx);
    return 1;
}

int gost_digest_update(EVP_MD_CTX *ctx, const void *data, size_t count)
{
    return hash_block((gost_hash_ctx *) EVP_MD_CTX_md_data(ctx), data, count);
}

int gost_digest_final(EVP_MD_CTX *ctx, unsigned char *md)
{
    return finish_hash((gost_hash_ctx *) EVP_MD_CTX_md_data(ctx), md);

}

int gost_digest_copy(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
    struct ossl_gost_digest_ctx *md_ctx = EVP_MD_CTX_md_data(to);
    if (EVP_MD_CTX_md_data(to) && EVP_MD_CTX_md_data(from)) {
        memcpy(EVP_MD_CTX_md_data(to), EVP_MD_CTX_md_data(from),
               sizeof(struct ossl_gost_digest_ctx));
        md_ctx->dctx.cipher_ctx = &(md_ctx->cctx);
    }
    return 1;
}

int gost_digest_cleanup(EVP_MD_CTX *ctx)
{
    if (EVP_MD_CTX_md_data(ctx))
        memset(EVP_MD_CTX_md_data(ctx), 0,
               sizeof(struct ossl_gost_digest_ctx));
    return 1;
}
