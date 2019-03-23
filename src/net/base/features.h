// Copyright (c) 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_FEATURES_H_
#define NET_BASE_FEATURES_H_

#include "base/feature_list.h"
#include "net/base/net_export.h"

namespace net {
namespace features {

// Uses a site isolated code cache that is keyed on the resource url and the
// origin lock of the renderer that is requesting the resource. The requests
// to site-isolated code cache are handled by the content/GeneratedCodeCache
// When this flag is enabled, the metadata field of the HttpCache is unused.
NET_EXPORT extern const base::Feature kIsolatedCodeCache;

// Enables the additional TLS 1.3 server-random-based downgrade protection
// described in https://tools.ietf.org/html/rfc8446#section-4.1.3
//
// This is a MUST-level requirement of TLS 1.3, but has compatibility issues
// with some buggy non-compliant TLS-terminating proxies.
NET_EXPORT extern const base::Feature kEnforceTLS13Downgrade;

// Splits cache entries by the request's top frame's origin if one is available.
NET_EXPORT extern const base::Feature kSplitCacheByTopFrameOrigin;

// Enables sending TLS 1.3 Key Update messages on TLS 1.3 connections in order
// to ensure that this corner of the spec is exercised. This is enabled by
// default and exists as a feature to allow it to be remotely disabled if
// needed.
NET_EXPORT extern const base::Feature kTLS13KeyUpdate;

}  // namespace features
}  // namespace net

#endif  // NET_BASE_FEATURES_H_
