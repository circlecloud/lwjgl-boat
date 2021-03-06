/*
 * Copyright (c) 2002-2011 LWJGL Project
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
 * GLX extension implementations.
 *
 * @author Spasi
 */
#include "EGL.h"

// NV_present_video functions 

typedef struct {
	//GLXExtensions extension_flags;
	EGLContext context;
} BoatContext;

/*
jint extgl_EnumerateVideoDevicesNV(JNIEnv *env, jobject peer_info_handle, jobject devices, jint devices_position) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);
	jlong *devices_address = ((jlong *)safeGetBufferAddress(env, devices)) + devices_position;
	unsigned int *result;
	int i, elements;

	result = lwjgl_glXEnumerateVideoDevicesNV(peer_info->display, peer_info->screen, &elements);
	if ( devices_address != NULL ) {
		for ( i = 0; i < elements; i++ )
			devices_address[i] = (jlong)result[i];
	}
	XFree(result);

	return elements;
}

jboolean extgl_BindVideoDeviceNV(JNIEnv *env, jobject peer_info_handle, jint video_slot, jlong video_device, jobject attrib_list, jint attrib_list_position) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);
	const int *attrib_list_address = ((const int *)safeGetBufferAddress(env, attrib_list)) + attrib_list_position;

	return lwjgl_glXBindVideoDeviceNV(peer_info->display, video_slot, (unsigned int)video_device, attrib_list_address);
}

jboolean extgl_QueryContextNV(JNIEnv *env, jobject peer_info_handle, jobject context_handle, jint attrib, jobject value, jint value_position) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);
	X11Context *context_info = (*env)->GetDirectBufferAddress(env, context_handle);
	int *value_address = ((int *)(*env)->GetDirectBufferAddress(env, value)) + value_position;

	return lwjgl_glXQueryContext(peer_info->display, context_info->context, attrib, value_address) == GLX_BAD_ATTRIBUTE ? 0 : 1;
}

//NV_video_capture functions 

jboolean extgl_BindVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jint video_slot, jlong device) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);

	return lwjgl_glXBindVideoCaptureDeviceNV(peer_info->display, video_slot, (GLXVideoCaptureDeviceNV)device);
}

jint extgl_EnumerateVideoCaptureDevicesNV(JNIEnv *env, jobject peer_info_handle, jobject devices, jint devices_position) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);
	jlong *devices_address = ((jlong *)safeGetBufferAddress(env, devices)) + devices_position;
	GLXVideoCaptureDeviceNV *result;
	int i, elements;

	result = lwjgl_glXEnumerateVideoCaptureDevicesNV(peer_info->display, peer_info->screen, &elements);
	if ( devices_address != NULL ) {
		for ( i = 0; i < elements; i++ )
			devices_address[i] = (jlong)result[i];
	}
	XFree(devices);

	return elements;
}

jboolean extgl_LockVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jlong device) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);

	lwjgl_glXLockVideoCaptureDeviceNV(peer_info->display, (GLXVideoCaptureDeviceNV)device);
	return true;
}

jboolean extgl_QueryVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jlong device, jint attribute, jobject value, jint value_position) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);
	int *value_address = ((int *)(*env)->GetDirectBufferAddress(env, value)) + value_position;

	return lwjgl_glXQueryVideoCaptureDeviceNV(peer_info->display, (GLXVideoCaptureDeviceNV)device, attribute, value_address);
}

jboolean extgl_ReleaseVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jlong device) {
	X11PeerInfo *peer_info = (*env)->GetDirectBufferAddress(env, peer_info_handle);

	lwjgl_glXReleaseVideoCaptureDeviceNV(peer_info->display, (GLXVideoCaptureDeviceNV)device);
	return true;
}
*/

// Fake stubs

jint extgl_EnumerateVideoDevicesNV(JNIEnv *env, jobject peer_info_handle, jobject devices, jint devices_position) {
        return 0;
}
jboolean extgl_BindVideoDeviceNV(JNIEnv *env, jobject peer_info_handle, jint video_slot, jlong video_device, jobject attrib_list, jint attrib_list_position) {
        return 0;
}
jboolean extgl_QueryContextNV(JNIEnv *env, jobject peer_info_handle, jobject context_handle, jint attrib, jobject value, jint value_position) {
        return 0;
}

// NV_video_capture functions 
jboolean extgl_BindVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jint video_slot, jlong device) {
        return 0;
}
jint extgl_EnumerateVideoCaptureDevicesNV(JNIEnv *env, jobject peer_info_handle, jobject devices, jint devices_position) {
        return 0;
}
jboolean extgl_LockVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jlong device) {
        return 0;
}
jboolean extgl_QueryVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jlong device, jint attribute, jobject value, jint value_position) {
        return 0;
}
jboolean extgl_ReleaseVideoCaptureDeviceNV(JNIEnv *env, jobject peer_info_handle, jlong device) {
        return 0;
}
