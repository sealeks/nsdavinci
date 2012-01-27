/*
 * Copyright (C) 2010 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "V8Event.h"

#include "DOMWindow.h"
#include "Element.h"

#include "Clipboard.h"
#include "ClipboardEvent.h"
#include "CustomEvent.h"
#include "Event.h"
#include "V8BeforeLoadEvent.h"
#include "V8Binding.h"
#include "V8Clipboard.h"
#include "V8CloseEvent.h"
#include "V8CompositionEvent.h"
#include "V8CustomEvent.h"
#include "V8DeviceMotionEvent.h"
#include "V8DeviceOrientationEvent.h"
#include "V8ErrorEvent.h"
#include "V8HashChangeEvent.h"
#include "V8IDBVersionChangeEvent.h"
#include "V8KeyboardEvent.h"
#include "V8MessageEvent.h"
#include "V8MouseEvent.h"
#include "V8MutationEvent.h"
#include "V8OverflowEvent.h"
#include "V8PageTransitionEvent.h"
#include "V8PopStateEvent.h"
#include "V8ProgressEvent.h"
#include "V8Proxy.h"
#include "V8SpeechInputEvent.h"
#include "V8StorageEvent.h"
#include "V8StreamEvent.h"
#include "V8TextEvent.h"
#include "V8TouchEvent.h"
#include "V8UIEvent.h"
#include "V8WebKitAnimationEvent.h"
#include "V8WebKitTransitionEvent.h"
#include "V8WheelEvent.h"
#include "V8XMLHttpRequestProgressEvent.h"

#if ENABLE(SVG)
#include "V8SVGZoomEvent.h"
#endif

#if ENABLE(WEB_AUDIO)
#include "V8AudioProcessingEvent.h"
#include "V8OfflineAudioCompletionEvent.h"
#endif

namespace WebCore {

	inline v8::Handle<v8::Value> toV8(WebCore::external::alarmrow* impl){

	v8::HandleScope handle_scope;

	v8::Handle<v8::Array> array = v8::Array::New(5);

    if (array.IsEmpty())
       return v8::Handle<v8::Array>();

	if (impl){
	array->Set(0, v8::Date::New(impl->time));
	array->Set(1, v8::Integer::New(impl->level));
	array->Set(2, v8::Integer::New(impl->kvit));
	array->Set(3, impl->tag.data() ? v8::String::New(impl->tag.data()) : v8::Null());
    array->Set(4, impl->text.data() ? v8::String::New(impl->text.data()) : v8::Null());
	array->Set(5, impl->value.data() ? v8::String::New(impl->value.data()) : v8::Null());}
	else{
    array->Set(0, v8::Null());
	array->Set(1, v8::Null());
	array->Set(2, v8::Null());
	array->Set(3, v8::Null());
    array->Set(4, v8::Null());
	array->Set(5, v8::Null());
	}

    // Return the value through Close.
   return handle_scope.Close(array);}

   inline v8::Handle<v8::Value> toV8(DVNAlarmEvent* impl)
    {
    if (!impl)
        return v8::Null();

	if (!impl->table())
        return v8::Null();

	if (impl->table()->size()==0)
        return v8::Null();

	v8::HandleScope handle_scope;

	v8::Handle<v8::Array> array = v8::Array::New(impl->table()->size());

    // Return an empty result if there was an error creating the array.
    if (array.IsEmpty())
       return v8::Handle<v8::Array>();

     // Fill out the values
	for (int i=0;i<impl->table()->size();++i){
		   array->Set(i, toV8(impl->table()->get(i)));}
	

    // Return the value through Close.
	return handle_scope.Close(array);}


	inline v8::Handle<v8::Value> toV8(WebCore::external::trendrow* impl){

	v8::HandleScope handle_scope;

	v8::Handle<v8::Array> array = v8::Array::New(2);

    if (array.IsEmpty())
       return v8::Handle<v8::Array>();

	if (impl){
	array->Set(0, v8::Date::New(impl->time));
	array->Set(1, v8::Number::New(impl->value));}
	else{
    array->Set(0, v8::Null());
	array->Set(1, v8::Null());
	}
	return handle_scope.Close(array);}

    inline v8::Handle<v8::Value> toV8(DVNTrendEvent* impl, v8::Handle<v8::Value> vl)
    {
    if (!impl)
        return v8::Null();

	if (!impl->table())
        return v8::Null();

	if (impl->table()->size()==0)
        return v8::Null();

	v8::HandleScope handle_scope;

    v8::Handle<v8::Array> array = v8::Array::New(2);

	    
	if (array.IsEmpty())
       return v8::Handle<v8::Array>();

	v8::Handle<v8::Array> array2 = v8::Array::New(impl->table()->size());

	if (array2.IsEmpty())
       return v8::Handle<v8::Array>();


     // Fill out the values
	for (int i=0;i<impl->table()->size();++i){
		array2->Set(i, toV8(impl->table()->get(i)));}

	array->Set(0, impl->target() ? vl : v8::Null());
	array->Set(1, array2);


	return handle_scope.Close(array);}



void V8Event::valueAccessorSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
{
    Event* event = V8Event::toNative(info.Holder());
    event->setDefaultPrevented(!value->BooleanValue());
}

v8::Handle<v8::Value> V8Event::dataTransferAccessorGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    Event* event = V8Event::toNative(info.Holder());

    if (event->isDragEvent())
        return toV8(static_cast<MouseEvent*>(event)->clipboard());

    return v8::Undefined();
}

v8::Handle<v8::Value> V8Event::clipboardDataAccessorGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    Event* event = V8Event::toNative(info.Holder());

    if (event->isClipboardEvent())
        return toV8(static_cast<ClipboardEvent*>(event)->clipboard());

    return v8::Undefined();
}

v8::Handle<v8::Value> toV8(Event* impl)
{
    if (!impl)
        return v8::Null();
    if (impl->isUIEvent()) {
        if (impl->isKeyboardEvent())
            return toV8(static_cast<KeyboardEvent*>(impl));
        if (impl->isTextEvent())
            return toV8(static_cast<TextEvent*>(impl));
        if (impl->isMouseEvent())
            return toV8(static_cast<MouseEvent*>(impl));
        if (impl->isWheelEvent())
            return toV8(static_cast<WheelEvent*>(impl));
#if ENABLE(SVG)
        if (impl->isSVGZoomEvent())
            return toV8(static_cast<SVGZoomEvent*>(impl));
#endif
        if (impl->isCompositionEvent())
            return toV8(static_cast<CompositionEvent*>(impl));
#if ENABLE(TOUCH_EVENTS)
        if (impl->isTouchEvent())
            return toV8(static_cast<TouchEvent*>(impl));
#endif
        return toV8(static_cast<UIEvent*>(impl));
    }
    if (impl->isHashChangeEvent())
        return toV8(static_cast<HashChangeEvent*>(impl));
    if (impl->isMutationEvent())
        return toV8(static_cast<MutationEvent*>(impl));
    if (impl->isOverflowEvent())
        return toV8(static_cast<OverflowEvent*>(impl));
    if (impl->isMessageEvent())
        return toV8(static_cast<MessageEvent*>(impl));
    if (impl->isPageTransitionEvent())
        return toV8(static_cast<PageTransitionEvent*>(impl));
    if (impl->isPopStateEvent())
        return toV8(static_cast<PopStateEvent*>(impl));
    if (impl->isProgressEvent()) {
        if (impl->isXMLHttpRequestProgressEvent())
            return toV8(static_cast<XMLHttpRequestProgressEvent*>(impl));
        return toV8(static_cast<ProgressEvent*>(impl));
    }
    if (impl->isWebKitAnimationEvent())
        return toV8(static_cast<WebKitAnimationEvent*>(impl));
    if (impl->isWebKitTransitionEvent())
        return toV8(static_cast<WebKitTransitionEvent*>(impl));
#if ENABLE(WORKERS)
    if (impl->isErrorEvent())
        return toV8(static_cast<ErrorEvent*>(impl));
#endif
#if ENABLE(DOM_STORAGE)
    if (impl->isStorageEvent())
        return toV8(static_cast<StorageEvent*>(impl));
#endif
#if ENABLE(INDEXED_DATABASE)
    if (impl->isIDBVersionChangeEvent())
        return toV8(static_cast<IDBVersionChangeEvent*>(impl));
#endif
    if (impl->isBeforeLoadEvent())
        return toV8(static_cast<BeforeLoadEvent*>(impl));
#if ENABLE(DEVICE_ORIENTATION)
    if (impl->isDeviceMotionEvent())
        return toV8(static_cast<DeviceMotionEvent*>(impl));
    if (impl->isDeviceOrientationEvent())
        return toV8(static_cast<DeviceOrientationEvent*>(impl));
#endif
#if ENABLE(WEB_AUDIO)
    if (impl->isAudioProcessingEvent())
        return toV8(static_cast<AudioProcessingEvent*>(impl));
    if (impl->isOfflineAudioCompletionEvent())
        return toV8(static_cast<OfflineAudioCompletionEvent*>(impl));
#endif
#if ENABLE(INPUT_SPEECH)
    if (impl->isSpeechInputEvent())
        return toV8(static_cast<SpeechInputEvent*>(impl));
#endif
    if (impl->isCustomEvent())
        return toV8(static_cast<CustomEvent*>(impl));
#if ENABLE(WEB_SOCKETS)
    if (impl->isCloseEvent())
        return toV8(static_cast<CloseEvent*>(impl));
#endif
#if ENABLE(MEDIA_STREAM)
    if (impl->isStreamEvent())
        return toV8(static_cast<StreamEvent*>(impl));
#endif
	if (impl->isDVNAlarmEvent())
        return toV8(static_cast<DVNAlarmEvent*>(impl));
	if (impl->isDVNTrendEvent())
        return toV8(static_cast<DVNTrendEvent*>(impl), V8Event::wrap(impl));
    return V8Event::wrap(impl);
}
} // namespace WebCore
