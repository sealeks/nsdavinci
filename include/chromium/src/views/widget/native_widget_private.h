// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VIEWS_WIDGET_NATIVE_WIDGET_PRIVATE_H_
#define VIEWS_WIDGET_NATIVE_WIDGET_PRIVATE_H_
#pragma once

#include "ui/gfx/native_widget_types.h"
#include "views/widget/native_widget.h"

namespace gfx {
class Rect;
}

namespace ui {
class OSExchangeData;
}

namespace views {
class InputMethod;
class TooltipManager;
namespace internal {
    /*
    top=0[%](0),left=0[%](0),width=100[%](400),left=100[%](200),resizable=yes|no|0|1(no), 
    decorated=yes|no|0|1(no),tooltip=yes|no|0|1(no),modal=yes|no|0|1(no),allwaystop=yes|no|0|1(no),
	state=normal|minimized|maximized(normal)
	*/
	class WindowParam{
	public:
		WindowParam(const std::wstring& parm = L""): eparam_(parm)  {}

		~WindowParam(){};

		std::wstring caption() const { 
			  std::wstring result=L"";
	          std::wstring::size_type it=eparam_.find(L"caption=");
	          if (it==std::wstring::npos)
	          	return result;
			  result=eparam_.substr(it);
	          result=result.substr(8);
	          it=result.find_first_of(L",");
	          if (it!=std::wstring::npos)
	               result=result.substr(0,it);
			return result;
		};

		bool isResizeble() const {
              return  (eparam_.find(L"resizable=yes")!=std::wstring::npos) || (eparam_.find(L"resizable=1")!=std::wstring::npos);
	    }

		bool isUndecorated() const{
	          return  ((eparam_.find(L"decorated=no")!=std::wstring::npos) || (eparam_.find(L"decorated=0")!=std::wstring::npos));
	    }

        bool isToolTip() const{
	          return  (eparam_.find(L"tooltip=yes")!=std::wstring::npos) || (eparam_.find(L"tooltip=1")!=std::wstring::npos);
	    }

		bool isModal() const{
	          return  (eparam_.find(L"modal=yes")!=std::wstring::npos) || (eparam_.find(L"modal=1")!=std::wstring::npos);
	    }

		bool isAllawaysTop() const{
	          return  (eparam_.find(L"allwaystop=yes")!=std::wstring::npos) || (eparam_.find(L"allwaystop=1")!=std::wstring::npos);
	    }

		bool isMaximized() const{
	          return  (eparam_.find(L"state=maximized")!=std::wstring::npos);
	    }

		bool isMinimized() const{
	          return  (eparam_.find(L"state=minimized")!=std::wstring::npos);
	    }

		int Bounds(const std::wstring name, int display=0,  int dflt=0) const{
	          int result=dflt;
	          std::wstring::size_type it=eparam_.find(name+L"=");
	          if (it==std::wstring::npos)
	          	return result;
	          std::wstring temp=eparam_.substr(it);
	          temp=temp.substr(name.size()+1);
	          it=temp.find_first_of(L",");
	          if (it!=std::wstring::npos)
	               temp=temp.substr(0,it);
	          it=temp.find_last_of(L"%");
	          if (it!=std::wstring::npos){
	          	temp=temp.substr(0,it);
	          	result = _wtoi(temp.c_str());
	            result = result * display / 100;
	          }
	          else{
	          	result = _wtoi(temp.c_str());
	          }
    
	          if (result<0) result=dflt;
	          return result;
	          }

	private:
		std::wstring eparam_;
	};

////////////////////////////////////////////////////////////////////////////////
// NativeWidgetPrivate interface
//
//  A NativeWidget subclass internal to views that provides Widget a conduit for
//  communication with a backend-specific native widget implementation.
//
//  Many of the methods here are pass-thrus for Widget, and as such there is no
//  documentation for them here. In that case, see methods of the same name in
//  widget.h.
//
//  IMPORTANT: This type is intended for use only by the views system and for
//             NativeWidget implementations. This file should not be included
//             in code that does not fall into one of these use cases.
//
class NativeWidgetPrivate : public NativeWidget {
 public:
  virtual ~NativeWidgetPrivate() {}

  // Creates an appropriate default NativeWidgetPrivate implementation for the
  // current OS/circumstance.
  static NativeWidgetPrivate* CreateNativeWidget(
      internal::NativeWidgetDelegate* delegate);

  static NativeWidgetPrivate* GetNativeWidgetForNativeView(
      gfx::NativeView native_view);
  static NativeWidgetPrivate* GetNativeWidgetForNativeWindow(
      gfx::NativeWindow native_window);

  // Retrieves the top NativeWidgetPrivate in the hierarchy containing the given
  // NativeView, or NULL if there is no NativeWidgetPrivate that contains it.
  static NativeWidgetPrivate* GetTopLevelNativeWidget(
      gfx::NativeView native_view);

  static void GetAllChildWidgets(gfx::NativeView native_view,
                                 Widget::Widgets* children);
  static void ReparentNativeView(gfx::NativeView native_view,
                                 gfx::NativeView new_parent);

  // Returns true if any mouse button is currently down.
  static bool IsMouseButtonDown();

  // Initializes the NativeWidget.
  virtual void InitNativeWidget(const Widget::InitParams& params) = 0;

  // Returns a NonClientFrameView for the widget's NonClientView, or NULL if
  // the NativeWidget wants no special NonClientFrameView.
  virtual NonClientFrameView* CreateNonClientFrameView() = 0;

  virtual void UpdateFrameAfterFrameChange() = 0;
  virtual bool ShouldUseNativeFrame() const = 0;
  virtual void FrameTypeChanged() = 0;

  // Returns the Widget associated with this NativeWidget. This function is
  // guaranteed to return non-NULL for the lifetime of the NativeWidget.
  virtual Widget* GetWidget() = 0;
  virtual const Widget* GetWidget() const = 0;

  // Returns the NativeView/Window associated with this NativeWidget.
  virtual gfx::NativeView GetNativeView() const = 0;
  virtual gfx::NativeWindow GetNativeWindow() const = 0;

  // Returns the topmost Widget in a hierarchy.
  virtual Widget* GetTopLevelWidget() = 0;

  // Returns the Compositor, or NULL if there isn't one associated with this
  // NativeWidget.
  virtual const ui::Compositor* GetCompositor() const = 0;
  virtual ui::Compositor* GetCompositor() = 0;

  // See description in View for details.
  virtual void MarkLayerDirty() = 0;
  virtual void CalculateOffsetToAncestorWithLayer(gfx::Point* offset,
                                                  View** ancestor) = 0;

  // Notifies the NativeWidget that a view was removed from the Widget's view
  // hierarchy.
  virtual void ViewRemoved(View* view) = 0;

  // Sets/Gets a native window property on the underlying native window object.
  // Returns NULL if the property does not exist. Setting the property value to
  // NULL removes the property.
  virtual void SetNativeWindowProperty(const char* name, void* value) = 0;
  virtual void* GetNativeWindowProperty(const char* name) const = 0;

  // Returns the native widget's tooltip manager. Called from the View hierarchy
  // to update tooltips.
  virtual TooltipManager* GetTooltipManager() const = 0;

  // Returns true if a system screen reader is active for the NativeWidget.
  virtual bool IsScreenReaderActive() const = 0;

  // Notify native Accessibility clients of an event.
  virtual void SendNativeAccessibilityEvent(
      View* view,
      ui::AccessibilityTypes::Event event_type) = 0;

  // Sets or releases event capturing for this native widget.
  virtual void SetMouseCapture() = 0;
  virtual void ReleaseMouseCapture() = 0;

  // Returns true if this native widget is capturing mouse events.
  virtual bool HasMouseCapture() const = 0;

  // Sets or release keyboard capture.
  virtual void SetKeyboardCapture() = 0;
  virtual void ReleaseKeyboardCapture() = 0;

  // Returns true if this native widget is capturing keyboard events.
  virtual bool HasKeyboardCapture() = 0;

  // Returns the InputMethod for this native widget.
  // Note that all widgets in a widget hierarchy share the same input method.
  // TODO(suzhe): rename to GetInputMethod() when NativeWidget implementation
  // class doesn't inherit Widget anymore.
  virtual InputMethod* GetInputMethodNative() = 0;

  // Sets a different InputMethod instance to this native widget. The instance
  // must not be initialized, the ownership will be assumed by the native
  // widget. It's only for testing purpose.
  virtual void ReplaceInputMethod(InputMethod* input_method) = 0;

  // Centers the window and sizes it to the specified size.
  virtual void CenterWindow(const gfx::Size& size) = 0;

  // Retrieves the window's current restored bounds and maximized state, for
  // persisting.
  virtual void GetWindowBoundsAndMaximizedState(gfx::Rect* bounds,
                                                bool* maximized) const = 0;

  // Sets the NativeWindow title.
  virtual void SetWindowTitle(const std::wstring& title) = 0;

  // Sets the Window icons. |window_icon| is a 16x16 icon suitable for use in
  // a title bar. |app_icon| is a larger size for use in the host environment
  // app switching UI.
  virtual void SetWindowIcons(const SkBitmap& window_icon,
                              const SkBitmap& app_icon) = 0;

  // Update native accessibility properties on the native window.
  virtual void SetAccessibleName(const std::wstring& name) = 0;
  virtual void SetAccessibleRole(ui::AccessibilityTypes::Role role) = 0;
  virtual void SetAccessibleState(ui::AccessibilityTypes::State state) = 0;

  enum ShowState {
    SHOW_RESTORED,
    SHOW_MAXIMIZED,
    SHOW_INACTIVE
  };

  // Makes the NativeWindow modal.
  virtual void BecomeModal() = 0;

  // See method documentation in Widget.
  virtual gfx::Rect GetWindowScreenBounds() const = 0;
  virtual gfx::Rect GetClientAreaScreenBounds() const = 0;
  virtual gfx::Rect GetRestoredBounds() const = 0;
  virtual void SetBounds(const gfx::Rect& bounds) = 0;
  virtual void SetSize(const gfx::Size& size) = 0;
  virtual void SetBoundsConstrained(const gfx::Rect& bounds,
                                    Widget* other_widget) = 0;
  virtual void MoveAbove(gfx::NativeView native_view) = 0;
  virtual void MoveToTop() = 0;
  virtual void SetShape(gfx::NativeRegion shape) = 0;
  virtual void Close() = 0;
  virtual void CloseNow() = 0;
  virtual void EnableClose(bool enable) = 0;
  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void ShowNativeWidget(ShowState state) = 0;
  virtual bool IsVisible() const = 0;
  virtual void Activate() = 0;
  virtual void Deactivate() = 0;
  virtual bool IsActive() const = 0;
  virtual void SetAlwaysOnTop(bool always_on_top) = 0;
  virtual void Maximize() = 0;
  virtual void Minimize() = 0;
  virtual bool IsMaximized() const = 0;
  virtual bool IsMinimized() const = 0;
  virtual void Restore() = 0;
  virtual void SetFullscreen(bool fullscreen) = 0;
  virtual bool IsFullscreen() const = 0;
  virtual void SetWindowProperty(const std::wstring& param = L"") {};
  virtual bool IsUndecorated() const { return false;}
  virtual bool IsToolTip() const { return false;}
  virtual void SetOpacity(unsigned char opacity) = 0;
  virtual void SetUseDragFrame(bool use_drag_frame) = 0;
  virtual bool IsAccessibleWidget() const = 0;
  virtual void RunShellDrag(View* view,
                            const ui::OSExchangeData& data,
                            int operation) = 0;
  virtual void SchedulePaintInRect(const gfx::Rect& rect) = 0;
  virtual void SetCursor(gfx::NativeCursor cursor) = 0;
  virtual void ClearNativeFocus() = 0;

  // Overridden from NativeWidget:
  virtual internal::NativeWidgetPrivate* AsNativeWidgetPrivate() OVERRIDE;

};

}  // namespace internal
}  // namespace views

#endif  // VIEWS_WIDGET_NATIVE_WIDGET_PRIVATE_H_
