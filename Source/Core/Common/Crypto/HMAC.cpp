// Copyright 2023 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include <mbedtls/hmac_drbg.h>

#include "Common/ScopeGuard.h"
#include "Common/Crypto/HMAC.h"

namespace Common::HMAC
{
bool HMACWithSHA1(const u8* key, const size_t key_len, const u8* msg, const size_t msg_len, u8* out)
{
  mbedtls_md_context_t ctx;
  Common::ScopeGuard guard{[&ctx] { mbedtls_md_free(&ctx); }};
  mbedtls_md_init(&ctx);
  if (mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(MBEDTLS_MD_SHA1), 1))
    return false;

  if (mbedtls_md_hmac_starts(&ctx, key, key_len) || mbedtls_md_hmac_update(&ctx, msg, msg_len) ||
      mbedtls_md_hmac_finish(&ctx, out))
  {
    return false;
  }

  return true;
}
}  // namespace Common::HMAC
