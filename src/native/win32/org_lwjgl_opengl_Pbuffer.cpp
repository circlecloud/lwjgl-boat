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
 * $Id$
 *
 * Win32 Pbuffer.
 *
 * @author elias_naur <elias_naur@users.sourceforge.net>
 * @version $Revision$
 */

#include <stdlib.h>
#include "org_lwjgl_opengl_Pbuffer.h"
#include "Window.h"

#include "extgl.h"
#include "extgl_wgl.h"

#include "common_tools.h"

typedef struct _PbufferInfo {

	HGLRC Pbuffer_context;

	HPBUFFERARB Pbuffer;

	HDC Pbuffer_dc;

} PbufferInfo;

/*
 * Class:     org_lwjgl_opengl_Pbuffer
 * Method:    isPbufferSupported
 * Signature: ()Z
 */
JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_Pbuffer_getPbufferCaps
  (JNIEnv *env, jclass clazz)
{
	int caps = 0;
	if ( extgl_Extensions.WGL_ARB_pixel_format && extgl_Extensions.WGL_ARB_pbuffer )
		caps |= org_lwjgl_opengl_Pbuffer_PBUFFER_SUPPORTED;

	if ( extgl_Extensions.WGL_ARB_render_texture )
		caps |= org_lwjgl_opengl_Pbuffer_RENDER_TEXTURE_SUPPORTED;

	if ( extgl_Extensions.WGL_NV_render_texture_rectangle )
		caps |= org_lwjgl_opengl_Pbuffer_RENDER_TEXTURE_RECTANGLE_SUPPORTED;

	if ( extgl_Extensions.WGL_NV_render_depth_texture )
		caps |= org_lwjgl_opengl_Pbuffer_RENDER_DEPTH_TEXTURE_SUPPORTED;

	return caps;
}

/*
 * Class:     org_lwjgl_opengl_Pbuffer
 * Method:    nCreate
 */
JNIEXPORT jint JNICALL Java_org_lwjgl_opengl_Pbuffer_nCreate
  (JNIEnv *env, jclass clazz,
  jint width, jint height, jobject pixel_format,
  jobject pixelFormatCaps, jobject pBufferAttribs)
{
	int iPixelFormat = findPixelFormatARB(env, pixel_format, pixelFormatCaps, false, false, false);
	if (iPixelFormat == -1) {
		throwException(env, "Could not choose pixel formats.");
		return (jint)NULL;

	}

	HPBUFFERARB Pbuffer;

	if ( pBufferAttribs != NULL ) {
		GLuint *pBufferAttribs_ptr = (GLuint *)env->GetDirectBufferAddress(pBufferAttribs);
		jlong pBufferAttribsSize = env->GetDirectBufferCapacity(pBufferAttribs);

		int pBufferAttribList[9];

		jlong i;
		for ( i = 0; i < pBufferAttribsSize; )
			pBufferAttribList[i++] = pBufferAttribs_ptr[i];

		pBufferAttribList[i] = 0;

		Pbuffer = wglCreatePbufferARB(hdc, iPixelFormat, width, height, pBufferAttribList);
	} else {
		Pbuffer = wglCreatePbufferARB(hdc, iPixelFormat, width, height, NULL);
	}

	if (Pbuffer == NULL) {
		throwException(env, "Could not create Pbuffer.");
		return (jint)NULL;
	}

	HDC Pbuffer_dc = wglGetPbufferDCARB(Pbuffer);
	if (Pbuffer_dc == NULL) {
		wglDestroyPbufferARB(Pbuffer);
		throwException(env, "Could not get Pbuffer dc.");
		return (jint)NULL;
	}

	// Create a rendering context
	HGLRC Pbuffer_context = wglCreateContext(Pbuffer_dc);
	if (Pbuffer_context == NULL) {
		wglReleasePbufferDCARB(Pbuffer, Pbuffer_dc);
		wglDestroyPbufferARB(Pbuffer);
		throwException(env, "Failed to create Pbuffer rendering context");
		return (jint)NULL;
	}

	if (!wglShareLists(hglrc, Pbuffer_context)) {
		wglDeleteContext(Pbuffer_context);
		wglReleasePbufferDCARB(Pbuffer, Pbuffer_dc);
		wglDestroyPbufferARB(Pbuffer);
		throwException(env, "Could not share buffer context.");
		return (jint)NULL;

	}

	PbufferInfo *Pbuffer_info = (PbufferInfo *)malloc(sizeof(PbufferInfo));
	Pbuffer_info->Pbuffer = Pbuffer;
	Pbuffer_info->Pbuffer_context = Pbuffer_context;
	Pbuffer_info->Pbuffer_dc = Pbuffer_dc;

	return (jint)Pbuffer_info;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_Pbuffer_nReleaseContext
  (JNIEnv *env, jclass clazz)
{
	wglMakeCurrent(hdc, hglrc);
}

JNIEXPORT jboolean JNICALL Java_org_lwjgl_opengl_Pbuffer_nIsBufferLost
  (JNIEnv *env, jclass clazz, jint handle)
{
	PbufferInfo *Pbuffer_info = (PbufferInfo *)handle;
	BOOL buffer_lost;
	wglQueryPbufferARB(Pbuffer_info->Pbuffer, WGL_PBUFFER_LOST_ARB, &buffer_lost);
	return buffer_lost ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_Pbuffer_nMakeCurrent
  (JNIEnv *env, jclass clazz, jint handle)
{
	PbufferInfo *Pbuffer_info = (PbufferInfo *)handle;
	if (!wglMakeCurrent(Pbuffer_info->Pbuffer_dc, Pbuffer_info->Pbuffer_context))
		throwException(env, "Could not make pbuffer context current");
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_Pbuffer_nDestroy
  (JNIEnv *env, jclass clazz, jint handle)
{
	PbufferInfo *Pbuffer_info = (PbufferInfo *)handle;
	wglDeleteContext(Pbuffer_info->Pbuffer_context);
	wglReleasePbufferDCARB(Pbuffer_info->Pbuffer, Pbuffer_info->Pbuffer_dc);
	wglDestroyPbufferARB(Pbuffer_info->Pbuffer);
	free(Pbuffer_info);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_Pbuffer_nSetAttrib
  (JNIEnv *env, jclass clazz, jint handle, jint attrib, jint value)
{
	PbufferInfo *Pbuffer_info = (PbufferInfo *)handle;

	int attribs[3];

	attribs[0] = attrib;
	attribs[1] = value;
	attribs[2] = 0;

	wglSetPbufferAttribARB(Pbuffer_info->Pbuffer, attribs);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_Pbuffer_nBindTexImage
  (JNIEnv *env, jclass clazz, jint handle, jint buffer)
{
	PbufferInfo *Pbuffer_info = (PbufferInfo *)handle;
	wglBindTexImageARB(Pbuffer_info->Pbuffer, buffer);
}

JNIEXPORT void JNICALL Java_org_lwjgl_opengl_Pbuffer_nReleaseTexImage
  (JNIEnv *env, jclass clazz, jint handle, jint buffer)
{
	PbufferInfo *Pbuffer_info = (PbufferInfo *)handle;
	wglReleaseTexImageARB(Pbuffer_info->Pbuffer, buffer);
}
