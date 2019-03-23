// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/android/keystore.h"

#include <vector>

#include "base/android/jni_android.h"
#include "base/android/jni_array.h"
#include "base/android/jni_string.h"
#include "base/logging.h"
#include "jni/AndroidKeyStore_jni.h"

using base::android::AttachCurrentThread;
using base::android::ConvertJavaStringToUTF8;
using base::android::ConvertUTF8ToJavaString;
using base::android::HasException;
using base::android::JavaByteArrayToByteVector;
using base::android::JavaRef;
using base::android::ScopedJavaLocalRef;
using base::android::ToJavaByteArray;

namespace net {
namespace android {

std::string GetPrivateKeyClassName(const JavaRef<jobject>& key) {
  JNIEnv* env = AttachCurrentThread();
  ScopedJavaLocalRef<jstring> name =
      Java_AndroidKeyStore_getPrivateKeyClassName(env, key);
  return ConvertJavaStringToUTF8(env, name);
}

bool SignWithPrivateKey(const JavaRef<jobject>& private_key_ref,
                        base::StringPiece algorithm,
                        base::span<const uint8_t> input,
                        std::vector<uint8_t>* signature) {
  JNIEnv* env = AttachCurrentThread();

  ScopedJavaLocalRef<jstring> algorithm_ref =
      ConvertUTF8ToJavaString(env, algorithm);
  DCHECK(!algorithm_ref.is_null());

  // Convert message to byte[] array.
  ScopedJavaLocalRef<jbyteArray> input_ref =
      ToJavaByteArray(env, input.data(), input.size());
  DCHECK(!input_ref.is_null());

  // Invoke platform API
  ScopedJavaLocalRef<jbyteArray> signature_ref =
      Java_AndroidKeyStore_signWithPrivateKey(env, private_key_ref,
                                              algorithm_ref, input_ref);
  if (HasException(env) || signature_ref.is_null())
    return false;

  // Write signature to string.
  JavaByteArrayToByteVector(env, signature_ref, signature);
  return true;
}

}  // namespace android
}  // namespace net
