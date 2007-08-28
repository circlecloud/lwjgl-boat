/*
 * Copyright (c) 2002-2004 LWJGL Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of 'LWJGL' nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * $Id: org_lwjgl_d3d_WindowsPeerInfo.c 2619 2006-10-30 15:49:02Z elias_naur $
 *
 * @author elias_naur <elias_naur@users.sourceforge.net>
 * @version $Revision: 2619 $
 */

#include <jni.h>
#include "org_lwjgl_d3d_WindowsPeerInfo.h"
#include "context.h"
#include "common_tools.h"

JNIEXPORT jobject JNICALL Java_org_lwjgl_d3d_WindowsPeerInfo_createHandle
  (JNIEnv *env, jclass clazz) {
    return newJavaManagedByteBuffer(env, sizeof(WindowsPeerInfo));
}

JNIEXPORT void JNICALL Java_org_lwjgl_d3d_WindowsPeerInfo_nChoosePixelFormat
  (JNIEnv *env, jclass clazz, jobject peer_info_handle, jint origin_x, jint origin_y, jobject pixel_format, jobject pixel_format_caps, jboolean use_hdc_bpp, jboolean window, jboolean pbuffer, jboolean double_buffer) {
    WindowsPeerInfo *peer_info = (WindowsPeerInfo *)(*env)->GetDirectBufferAddress(env, peer_info_handle);
    jclass cls_pixel_format = (*env)->GetObjectClass(env, pixel_format);
    bool floating_point = (bool)(*env)->GetBooleanField(env, pixel_format, (*env)->GetFieldID(env, cls_pixel_format, "floating_point", "Z"));
    int pixel_format_id = findPixelFormatOnDC(env, peer_info->drawable_hdc, origin_x, origin_y, pixel_format, pixel_format_caps, use_hdc_bpp, window, pbuffer, double_buffer, floating_point);
    if (pixel_format_id == -1)
        return;
    // Let it throw
    applyPixelFormat(env, peer_info->drawable_hdc, pixel_format_id);
}

JNIEXPORT jlong JNICALL Java_org_lwjgl_d3d_WindowsPeerInfo_nGetHwnd(JNIEnv *env, jclass unused, jobject peer_info_handle) {
    WindowsPeerInfo *peer_info = (WindowsPeerInfo *)(*env)->GetDirectBufferAddress(env, peer_info_handle);
    return (intptr_t)peer_info->u.hwnd;
}