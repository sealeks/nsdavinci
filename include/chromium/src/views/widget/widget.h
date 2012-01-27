// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VIEWS_WIDGET_WIDGET_H_
#define VIEWS_WIDGET_WIDGET_H_
#pragma once

#include <stack>

#include "base/memory/scoped_ptr.h"
#include "ui/base/accessibility/accessibility_types.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"
#include "views/focus/focus_manager.h"
#include "views/widget/native_widget_delegate.h"
#include "views/window/client_view.h"
#include "views/window/non_client_view.h"

#if defined(OS_WIN)
// Windows headers define macros for these function names which screw with us.
#if defined(IsMaximized)
#undef IsMaximized
#endif
#if defined(IsMinimized)
#undef IsMinimized
#endif
#if defined(CreateWindow)
#undef CreateWindow
#endif
#endif

namespace gfx {
class Canvas;
class Path;
class Point;
class Rect;
}

namespace ui {
class Accelerator;
class Compositor;
class OSExchangeData;
class ThemeProvider;
enum TouchStatus;
}
using ui::ThemeProvider;

namespace views {

class DefaultThemeProvider;
class InputMethod;
class NativeWidget;
class NonClientFrameView;
class ScopedEvent;
class TooltipManager;
class View;
class WidgetDelegate;
namespace internal {
class NativeWidgetPrivate;
class RootView;
}

////////////////////////////////////////////////////////////////////////////////
// Widget class
//
//  Encapsulates the platform-specific rendering, event receiving and widget
//  management aspects of the UI framework.
//
//  Owns a RootView and thus a View hierarchy. Can contain child Widgets.
//  Widget is a platform-independent type that communicates with a platform or
//  context specific NativeWidget implementation.
//
//  A special note on ownership:
//
//    Depending on the value of the InitParams' ownership field, the Widget
//    either owns or is owned by its NativeWidget:
//
//    ownership = NATIVE_WIDGET_OWNS_WIDGET (default)
//      The Widget instance is owned by its NativeWidget. When the NativeWidget
//      is destroyed (in response to a native destruction message), it deletes
//      the Widget from its destructor.
//    ownership = WIDGET_OWNS_NATIVE_WIDGET (non-default)
//      The Widget instance owns its NativeWidget. This state implies someone
//      else wants to control the lifetime of this object. When they destroy
//      the Widget it is responsible for destroying the NativeWidget (from its
//      destructor).
//
class Widget : public internal::NativeWidgetDelegate,
               public FocusTraversable {
 public:
  typedef std::set<Widget*> Widgets;

  enum FrameType {
    FRAME_TYPE_DEFAULT,         // Use whatever the default would be.
    FRAME_TYPE_FORCE_CUSTOM,    // Force the custom frame.
    FRAME_TYPE_FORCE_NATIVE     // Force the native frame.
  };

  struct InitParams {
    enum Type {
      TYPE_WINDOW,      // A decorated Window, like a frame window.
                        // Widgets of TYPE_WINDOW will have a NonClientView.
      TYPE_WINDOW_FRAMELESS,
                        // An undecorated Window.
      TYPE_CONTROL,     // A control, like a button.
      TYPE_POPUP,       // An undecorated Window, with transient properties.
      TYPE_MENU,        // An undecorated Window, with transient properties
                        // specialized to menus.
      TYPE_TOOLTIP,
    };
    enum Ownership {
      // Default. Creator is not responsible for managing the lifetime of the
      // Widget, it is destroyed when the corresponding NativeWidget is
      // destroyed.
      NATIVE_WIDGET_OWNS_WIDGET,
      // Used when the Widget is owned by someone other than the NativeWidget,
      // e.g. a scoped_ptr in tests.
      WIDGET_OWNS_NATIVE_WIDGET
    };

    InitParams();
    explicit InitParams(Type type);

    Type type;
    // If NULL, a default implementation will be constructed.
    WidgetDelegate* delegate;
    bool child;
    bool transient;
    bool transparent;
    bool accept_events;
    bool can_activate;
    bool keep_on_top;
    Ownership ownership;
    bool mirror_origin_in_rtl;
    bool has_dropshadow;
    // Should the widget be double buffered? Default is false.
    bool double_buffer;
    gfx::NativeView parent;
    Widget* parent_widget;
    // Specifies the initial bounds of the Widget. Default is empty, which means
    // the NativeWidget may specify a default size.
    gfx::Rect bounds;
    // When set, this value is used as the Widget's NativeWidget implementation.
    // The Widget will not construct a default one. Default is NULL.
    NativeWidget* native_widget;
  };
  static InitParams WindowInitParams();

  Widget();
  virtual ~Widget();

  // Creates a decorated window Widget with the specified properties.
  static Widget* CreateWindow(WidgetDelegate* delegate);
  static Widget* CreateWindowWithParent(WidgetDelegate* delegate,
                                        gfx::NativeWindow parent);
  static Widget* CreateWindowWithBounds(WidgetDelegate* delegate,
                                        const gfx::Rect& bounds);
  static Widget* CreateWindowWithParentAndBounds(WidgetDelegate* delegate,
                                                 gfx::NativeWindow parent,
                                                 const gfx::Rect& bounds);

  // Enumerates all windows pertaining to us and notifies their
  // view hierarchies that the locale has changed.
  static void NotifyLocaleChanged();

  // Closes all Widgets that aren't identified as "secondary widgets". Called
  // during application shutdown when the last non-secondary widget is closed.
  static void CloseAllSecondaryWidgets();

  // Converts a rectangle from one Widget's coordinate system to another's.
  // Returns false if the conversion couldn't be made, because either these two
  // Widgets do not have a common ancestor or they are not on the screen yet.
  // The value of |*rect| won't be changed when false is returned.
  static bool ConvertRect(const Widget* source,
                          const Widget* target,
                          gfx::Rect* rect);

  // SetPureViews and IsPureViews update and return the state of a global
  // setting that tracks whether to use available pure Views implementations.
  static void SetPureViews(bool pure);
  static bool IsPureViews();

  // Retrieves the Widget implementation associated with the given
  // NativeView or Window, or NULL if the supplied handle has no associated
  // Widget.
  static Widget* GetWidgetForNativeView(gfx::NativeView native_view);
  static Widget* GetWidgetForNativeWindow(gfx::NativeWindow native_window);

  // Retrieves the highest Widget in a native view hierarchy starting at
  // |native_view|, which may or may not be a Widget itself.
  static Widget* GetTopLevelWidgetForNativeView(gfx::NativeView native_view);

  // Returns all Widgets in |native_view|'s hierarchy, including itself if
  // it is one.
  static void GetAllChildWidgets(gfx::NativeView native_view,
                                 Widgets* children);

  // Re-parent a NativeView and notify all Widgets in |native_view|'s hierarchy
  // of the change.
  static void ReparentNativeView(gfx::NativeView native_view,
                                 gfx::NativeView new_parent);

  // Returns the preferred size of the contents view of this window based on
  // its localized size data. The width in cols is held in a localized string
  // resource identified by |col_resource_id|, the height in the same fashion.
  // TODO(beng): This should eventually live somewhere else, probably closer to
  //             ClientView.
  static int GetLocalizedContentsWidth(int col_resource_id);
  static int GetLocalizedContentsHeight(int row_resource_id);
  static gfx::Size GetLocalizedContentsSize(int col_resource_id,
                                            int row_resource_id);

  void Init(const InitParams& params);

  // Returns the gfx::NativeView associated with this Widget.
  gfx::NativeView GetNativeView() const;

  // Returns the gfx::NativeWindow associated with this Widget. This may return
  // NULL on some platforms if the widget was created with a type other than
  // TYPE_WINDOW.
  gfx::NativeWindow GetNativeWindow() const;

  // Returns the accelerator given a command id. Returns false if there is
  // no accelerator associated with a given id, which is a common condition.
  virtual bool GetAccelerator(int cmd_id, ui::Accelerator* accelerator);

  // Forwarded from the RootView so that the widget can do any cleanup.
  void ViewHierarchyChanged(bool is_add, View* parent, View* child);

  // Performs any necessary cleanup and forwards to RootView.
  void NotifyNativeViewHierarchyChanged(bool attached,
                                        gfx::NativeView native_view);

  // Returns the topmost Widget in a hierarchy. Will return NULL if called
  // before the underlying Native Widget has been initialized.
  Widget* GetTopLevelWidget();
  const Widget* GetTopLevelWidget() const;

  // Gets/Sets the WidgetDelegate.
  WidgetDelegate* widget_delegate() const { return widget_delegate_; }

  // Sets the specified view as the contents of this Widget. There can only
  // be one contents view child of this Widget's RootView. This view is sized to
  // fit the entire size of the RootView. The RootView takes ownership of this
  // View, unless it is set as not being parent-owned.
  void SetContentsView(View* view);
  View* GetContentsView();

  // Returns the bounds of the Widget in screen coordinates.
  gfx::Rect GetWindowScreenBounds() const;

  // Returns the bounds of the Widget's client area in screen coordinates.
  gfx::Rect GetClientAreaScreenBounds() const;

  // Retrieves the restored bounds for the window.
  gfx::Rect GetRestoredBounds() const;

  // Sizes and/or places the widget to the specified bounds, size or position.
  void SetBounds(const gfx::Rect& bounds);
  void SetSize(const gfx::Size& size);

  // Like SetBounds(), but ensures the Widget is fully visible within the bounds
  // of its parent. If the Widget has no parent, it is centered within the
  // bounds of its screen if it is visible, or |other_widget|'s screen if it is
  // not.
  void SetBoundsConstrained(const gfx::Rect& bounds,
                            Widget* other_widget);

  // Places the widget in front of the specified widget in z-order.
  void MoveAboveWidget(Widget* widget);
  void MoveAbove(gfx::NativeView native_view);
  void MoveToTop();

  // Sets a shape on the widget. This takes ownership of shape.
  void SetShape(gfx::NativeRegion shape);

  // Hides the widget then closes it after a return to the message loop.
  virtual void Close();

  // TODO(beng): Move off public API.
  // Closes the widget immediately. Compare to |Close|. This will destroy the
  // window handle associated with this Widget, so should not be called from
  // any code that expects it to be valid beyond this call.
  void CloseNow();

  // Toggles the enable state for the Close button (and the Close menu item in
  // the system menu).
  void EnableClose(bool enable);

  // Shows or hides the widget, without changing activation state.
  virtual void Show();
  void Hide();

  // Like Show(), but does not activate the window.
  void ShowInactive();

  // Activates the widget, assuming it already exists and is visible.
  void Activate();

  // Deactivates the widget, making the next window in the Z order the active
  // window.
  void Deactivate();

  // Returns whether the Widget is the currently active window.
  virtual bool IsActive() const;

  // Prevents the window from being rendered as deactivated the next time it is.
  // This state is reset automatically as soon as the window becomes activated
  // again. There is no ability to control the state through this API as this
  // leads to sync problems.
  void DisableInactiveRendering();

  // Sets the widget to be on top of all other widgets in the windowing system.
  void SetAlwaysOnTop(bool on_top);

  // Maximizes/minimizes/restores the window.
  void Maximize();
  void Minimize();
  void Restore();

  // Whether or not the window is maximized or minimized.
  virtual bool IsMaximized() const;
  bool IsMinimized() const;

  // Accessors for fullscreen state.
  void SetFullscreen(bool fullscreen);
  bool IsFullscreen() const;

  // Sets the opacity of the widget. This may allow widgets behind the widget
  // in the Z-order to become visible, depending on the capabilities of the
  // underlying windowing system. Note that the caller must then schedule a
  // repaint to allow this change to take effect.
  void SetOpacity(unsigned char opacity);

  // Sets whether or not the window should show its frame as a "transient drag
  // frame" - slightly transparent and without the standard window controls.
  void SetUseDragFrame(bool use_drag_frame);

  // Returns the View at the root of the View hierarchy contained by this
  // Widget.
  View* GetRootView();

  // A secondary widget is one that is automatically closed (via Close()) when
  // all non-secondary widgets are closed.
  // Default is true.
  // TODO(beng): This is an ugly API, should be handled implicitly via
  //             transience.
  void set_is_secondary_widget(bool is_secondary_widget) {
    is_secondary_widget_ = is_secondary_widget;
  }
  bool is_secondary_widget() const { return is_secondary_widget_; }

  // Returns whether the Widget is visible to the user.
  virtual bool IsVisible() const;

  // Returns whether the Widget is customized for accessibility.
  bool IsAccessibleWidget() const;

  // Returns the ThemeProvider that provides theme resources for this Widget.
  virtual ThemeProvider* GetThemeProvider() const;

  // Returns the FocusManager for this widget.
  // Note that all widgets in a widget hierarchy share the same focus manager.
  // TODO(beng): remove virtual.
  virtual FocusManager* GetFocusManager();

  // Returns the InputMethod for this widget.
  // Note that all widgets in a widget hierarchy share the same input method.
  InputMethod* GetInputMethod();

  // Starts a drag operation for the specified view. This blocks until the drag
  // operation completes. |view| can be NULL.
  // If the view is non-NULL it can be accessed during the drag by calling
  // dragged_view(). If the view has not been deleted during the drag,
  // OnDragDone() is called on it.
  void RunShellDrag(View* view, const ui::OSExchangeData& data, int operation);

  // Returns the view that requested the current drag operation via
  // RunShellDrag(), or NULL if there is no such view or drag operation.
  View* dragged_view() { return dragged_view_; }

  // Adds the specified |rect| in client area coordinates to the rectangle to be
  // redrawn.
  void SchedulePaintInRect(const gfx::Rect& rect);

  // Sets the currently visible cursor. If |cursor| is NULL, the cursor used
  // before the current is restored.
  void SetCursor(gfx::NativeCursor cursor);

  // Resets the last move flag so that we can go around the optimization
  // that disregards duplicate mouse moves when ending animation requires
  // a new hit-test to do some highlighting as in TabStrip::RemoveTabAnimation
  // to cause the close button to highlight.
  void ResetLastMouseMoveFlag();

  // Sets/Gets a native window property on the underlying native window object.
  // Returns NULL if the property does not exist. Setting the property value to
  // NULL removes the property.
  void SetNativeWindowProperty(const char* name, void* value);
  void* GetNativeWindowProperty(const char* name) const;

  // Tell the window to update its title from the delegate.
  void UpdateWindowTitle();

  // Tell the window to update its icon from the delegate.
  void UpdateWindowIcon();

  // Retrieves the focus traversable for this widget.
  FocusTraversable* GetFocusTraversable();

  // Notifies the view hierarchy contained in this widget that theme resources
  // changed.
  void ThemeChanged();

  // Notifies the view hierarchy contained in this widget that locale resources
  // changed.
  void LocaleChanged();

  void SetFocusTraversableParent(FocusTraversable* parent);
  void SetFocusTraversableParentView(View* parent_view);

  // Clear native focus set to the Widget's NativeWidget.
  void ClearNativeFocus();

  // Updates the frame after an event caused it to be changed.
  virtual void UpdateFrameAfterFrameChange();

  void set_frame_type(FrameType frame_type) { frame_type_ = frame_type; }
  FrameType frame_type() const { return frame_type_; }

  // Creates an appropriate NonClientFrameView for this widget. The
  // WidgetDelegate is given the first opportunity to create one, followed by
  // the NativeWidget implementation. If both return NULL, a default one is
  // created.
  virtual NonClientFrameView* CreateNonClientFrameView();

  // Whether we should be using a native frame.
  bool ShouldUseNativeFrame() const;

  // Forces the frame into the alternate frame type (custom or native) depending
  // on its current state.
  void DebugToggleFrameType();

  // Tell the window that something caused the frame type to change.
  void FrameTypeChanged();

  NonClientView* non_client_view() {
    return const_cast<NonClientView*>(
        const_cast<const Widget*>(this)->non_client_view());
  }
  const NonClientView* non_client_view() const {
    return non_client_view_;
  }

  ClientView* client_view() {
    return const_cast<ClientView*>(
        const_cast<const Widget*>(this)->client_view());
  }
  const ClientView* client_view() const {
    return non_client_view()->client_view();
  }

#if defined(UNIT_TEST)
  static void set_compositor_factory(ui::Compositor*(*factory)()) {
    compositor_factory_ = factory;
  }
#endif
  static ui::Compositor* (*compositor_factory())() {
    return compositor_factory_;
  }

  const ui::Compositor* GetCompositor() const;
  ui::Compositor* GetCompositor();

  // Invokes method of same name on the NativeWidget.
  void MarkLayerDirty();
  void CalculateOffsetToAncestorWithLayer(gfx::Point* offset, View** ancestor);

  // Notifies assistive technology that an accessibility event has
  // occurred on |view|, such as when the view is focused or when its
  // value changes. Pass true for |send_native_event| except for rare
  // cases where the view is a native control that's already sending a
  // native accessibility event and the duplicate event would cause
  // problems.
  void NotifyAccessibilityEvent(
      View* view,
      ui::AccessibilityTypes::Event event_type,
      bool send_native_event);

  const NativeWidget* native_widget() const;
  NativeWidget* native_widget();

  internal::NativeWidgetPrivate* native_widget_private() {
    return native_widget_;
  }
  const internal::NativeWidgetPrivate* native_widget_private() const {
    return native_widget_;
  }

  // Returns the current event being processed. If there are multiple events
  // being processed at the same time (e.g. one event triggers another event),
  // then the most recent event is returned. Returns NULL if no event is being
  // processed.
  const Event* GetCurrentEvent();

  // Invoked when the tooltip text changes for the specified views.
  void TooltipTextChanged(View* view);

  // Returns a View* that any child Widgets backed by NativeWidgetViews
  // are added to.  The default implementation returns the contents view
  // if it exists and the root view otherwise.
  virtual View* GetChildViewParent();

  // Overridden from NativeWidgetDelegate:
  virtual bool IsModal() const OVERRIDE;
  virtual bool IsDialogBox() const OVERRIDE;
  virtual bool CanActivate() const OVERRIDE;
  virtual bool IsInactiveRenderingDisabled() const OVERRIDE;
  virtual void EnableInactiveRendering() OVERRIDE;
  virtual void OnNativeWidgetActivationChanged(bool active) OVERRIDE;
  virtual void OnNativeFocus(gfx::NativeView focused_view) OVERRIDE;
  virtual void OnNativeBlur(gfx::NativeView focused_view) OVERRIDE;
  virtual void OnNativeWidgetCreated() OVERRIDE;
  virtual void OnNativeWidgetDestroying() OVERRIDE;
  virtual void OnNativeWidgetDestroyed() OVERRIDE;
  virtual gfx::Size GetMinimumSize() OVERRIDE;
  virtual void OnNativeWidgetSizeChanged(const gfx::Size& new_size) OVERRIDE;
  virtual void OnNativeWidgetBeginUserBoundsChange() OVERRIDE;
  virtual void OnNativeWidgetEndUserBoundsChange() OVERRIDE;
  virtual bool HasFocusManager() const OVERRIDE;
  virtual bool OnNativeWidgetPaintAccelerated(
      const gfx::Rect& dirty_region) OVERRIDE;
  virtual void OnNativeWidgetPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual int GetNonClientComponent(const gfx::Point& point) OVERRIDE;
  virtual bool OnKeyEvent(const KeyEvent& event) OVERRIDE;
  virtual bool OnMouseEvent(const MouseEvent& event) OVERRIDE;
  virtual void OnMouseCaptureLost() OVERRIDE;
  virtual ui::TouchStatus OnTouchEvent(const TouchEvent& event) OVERRIDE;
  virtual bool ExecuteCommand(int command_id) OVERRIDE;
  virtual Widget* AsWidget() OVERRIDE;
  virtual const Widget* AsWidget() const OVERRIDE;

  // Overridden from FocusTraversable:
  virtual FocusSearch* GetFocusSearch() OVERRIDE;
  virtual FocusTraversable* GetFocusTraversableParent() OVERRIDE;
  virtual View* GetFocusTraversableParentView() OVERRIDE;

 protected:
  // TODO(beng): Remove NativeWidgetGtk's dependence on the mouse state flags.
  friend class NativeWidgetGtk;

  // Creates the RootView to be used within this Widget. Subclasses may override
  // to create custom RootViews that do specialized event processing.
  // TODO(beng): Investigate whether or not this is needed.
  virtual internal::RootView* CreateRootView();

  // Provided to allow the NativeWidget implementations to destroy the RootView
  // _before_ the focus manager/tooltip manager.
  // TODO(beng): remove once we fold those objects onto this one.
  void DestroyRootView();

  // Used for testing.
  void ReplaceFocusManager(FocusManager* focus_manager);

  // TODO(beng): Remove NativeWidgetGtk's dependence on these:
  // TODO(msw): Make this mouse state member private.
  // If true, the mouse is currently down.
  bool is_mouse_button_pressed_;

  // TODO(beng): Remove NativeWidgetGtk's dependence on these:
  // TODO(msw): Make these mouse state members private.
  // The following are used to detect duplicate mouse move events and not
  // deliver them. Displaying a window may result in the system generating
  // duplicate move events even though the mouse hasn't moved.
  bool last_mouse_event_was_move_;
  gfx::Point last_mouse_event_position_;

 private:
  friend class ScopedEvent;

  // Returns whether capture should be released on mouse release.
  virtual bool ShouldReleaseCaptureOnMouseReleased() const;

  // Persists the window's restored position and maximized state using the
  // window delegate.
  void SaveWindowPosition();

  // Sizes and positions the window just after it is created.
  void SetInitialBounds(const gfx::Rect& bounds);

  internal::NativeWidgetPrivate* native_widget_;

  // Non-owned pointer to the Widget's delegate.  May be NULL if no delegate is
  // being used.
  WidgetDelegate* widget_delegate_;

  // The root of the View hierarchy attached to this window.
  // WARNING: see warning in tooltip_manager_ for ordering dependencies with
  // this and tooltip_manager_.
  scoped_ptr<internal::RootView> root_view_;

  // The View that provides the non-client area of the window (title bar,
  // window controls, sizing borders etc). To use an implementation other than
  // the default, this class must be sub-classed and this value set to the
  // desired implementation before calling |InitWindow()|.
  NonClientView* non_client_view_;

  // The focus manager keeping track of focus for this Widget and any of its
  // children.  NULL for non top-level widgets.
  // WARNING: RootView's destructor calls into the FocusManager. As such, this
  // must be destroyed AFTER root_view_. This is enforced in DestroyRootView().
  scoped_ptr<FocusManager> focus_manager_;

  // A theme provider to use when no other theme provider is specified.
  scoped_ptr<DefaultThemeProvider> default_theme_provider_;

  // Valid for the lifetime of RunShellDrag(), indicates the view the drag
  // started from.
  View* dragged_view_;

  // The event stack.
  std::stack<ScopedEvent*> event_stack_;

  // See class documentation for Widget above for a note about ownership.
  InitParams::Ownership ownership_;

  // See set_is_secondary_widget().
  bool is_secondary_widget_;

  // The current frame type in use by this window. Defaults to
  // FRAME_TYPE_DEFAULT.
  FrameType frame_type_;

  // True when the window should be rendered as active, regardless of whether
  // or not it actually is.
  bool disable_inactive_rendering_;

  // Set to true if the widget is in the process of closing.
  bool widget_closed_;

  // The saved maximized state for this window. See note in SetInitialBounds
  // that explains why we save this.
  bool saved_maximized_state_;

  // The smallest size the window can be.
  gfx::Size minimum_size_;

  // Factory used to create Compositors. Settable by tests.
  static ui::Compositor*(*compositor_factory_)();

  DISALLOW_COPY_AND_ASSIGN(Widget);
};

}  // namespace views

#endif // VIEWS_WIDGET_WIDGET_H_
