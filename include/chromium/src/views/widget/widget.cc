// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "views/widget/widget.h"

#include "base/logging.h"
#include "base/message_loop.h"
#include "base/utf_string_conversions.h"
#include "ui/base/l10n/l10n_font_util.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/compositor/compositor.h"
#include "views/focus/view_storage.h"
#include "views/ime/input_method.h"
#include "views/views_delegate.h"
#include "views/widget/default_theme_provider.h"
#include "views/widget/root_view.h"
#include "views/widget/native_widget_private.h"
#include "views/widget/tooltip_manager.h"
#include "views/widget/widget_delegate.h"
#include "views/window/custom_frame_view.h"

namespace views {

namespace {
// Set to true if a pure Views implementation is preferred
bool use_pure_views = false;
}

// This class is used to keep track of the event a Widget is processing, and
// restore any previously active event afterwards.
class ScopedEvent {
 public:
  ScopedEvent(Widget* widget, const Event& event)
      : widget_(widget),
        event_(&event) {
    widget->event_stack_.push(this);
  }

  ~ScopedEvent() {
    if (widget_)
      widget_->event_stack_.pop();
  }

  void reset() {
    widget_ = NULL;
  }

  const Event* event() {
    return event_;
  }

 private:
  Widget* widget_;
  const Event* event_;

  DISALLOW_COPY_AND_ASSIGN(ScopedEvent);
};

// A default implementation of WidgetDelegate, used by Widget when no
// WidgetDelegate is supplied.
class DefaultWidgetDelegate : public WidgetDelegate {
 public:
  explicit DefaultWidgetDelegate(Widget* widget) : widget_(widget) {}
  virtual ~DefaultWidgetDelegate() {}

  // Overridden from WidgetDelegate:
  virtual void DeleteDelegate() OVERRIDE {
    delete this;
  }
  virtual Widget* GetWidget() {
    return widget_;
  }
  virtual const Widget* GetWidget() const {
    return widget_;
  }

 private:
  Widget* widget_;

  DISALLOW_COPY_AND_ASSIGN(DefaultWidgetDelegate);
};

////////////////////////////////////////////////////////////////////////////////
// Widget, InitParams:

Widget::InitParams::InitParams()
    : type(TYPE_WINDOW),
      delegate(NULL),
      child(false),
      transient(false),
      transparent(false),
      accept_events(true),
      can_activate(true),
      keep_on_top(false),
      ownership(NATIVE_WIDGET_OWNS_WIDGET),
      mirror_origin_in_rtl(false),
      has_dropshadow(false),
      double_buffer(false),
      parent(NULL),
      parent_widget(NULL),
      native_widget(NULL) {
}

Widget::InitParams::InitParams(Type type)
    : type(type),
      delegate(NULL),
      child(type == TYPE_CONTROL),
      transient(type == TYPE_POPUP || type == TYPE_MENU),
      transparent(false),
      accept_events(true),
      can_activate(type != TYPE_POPUP && type != TYPE_MENU),
      keep_on_top(type == TYPE_MENU),
      ownership(NATIVE_WIDGET_OWNS_WIDGET),
      mirror_origin_in_rtl(false),
      has_dropshadow(false),
      double_buffer(false),
      parent(NULL),
      parent_widget(NULL),
      native_widget(NULL) {
}

////////////////////////////////////////////////////////////////////////////////
// Widget, public:

// static
Widget::InitParams Widget::WindowInitParams() {
  return InitParams(InitParams::TYPE_WINDOW);
}

Widget::Widget()
    : is_mouse_button_pressed_(false),
      last_mouse_event_was_move_(false),
      native_widget_(NULL),
      widget_delegate_(NULL),
      non_client_view_(NULL),
      dragged_view_(NULL),
      event_stack_(),
      ownership_(InitParams::NATIVE_WIDGET_OWNS_WIDGET),
      is_secondary_widget_(true),
      frame_type_(FRAME_TYPE_DEFAULT),
      disable_inactive_rendering_(false),
      widget_closed_(false),
      saved_maximized_state_(false),
      minimum_size_(100, 100) {
}

Widget::~Widget() {
  while (!event_stack_.empty()) {
    event_stack_.top()->reset();
    event_stack_.pop();
  }

  DestroyRootView();

  if (ownership_ == InitParams::WIDGET_OWNS_NATIVE_WIDGET)
    delete native_widget_;
}

// static
Widget* Widget::CreateWindow(WidgetDelegate* delegate) {
  return CreateWindowWithParentAndBounds(delegate, NULL, gfx::Rect());
}

// static
Widget* Widget::CreateWindowWithParent(WidgetDelegate* delegate,
                                       gfx::NativeWindow parent) {
  return CreateWindowWithParentAndBounds(delegate, parent, gfx::Rect());
}

// static
Widget* Widget::CreateWindowWithBounds(WidgetDelegate* delegate,
                                       const gfx::Rect& bounds) {
  return CreateWindowWithParentAndBounds(delegate, NULL, bounds);
}

// static
Widget* Widget::CreateWindowWithParentAndBounds(WidgetDelegate* delegate,
                                                gfx::NativeWindow parent,
                                                const gfx::Rect& bounds) {
  Widget* widget = new Widget;
  Widget::InitParams params;
  params.delegate = delegate;
#if defined(OS_WIN)
  params.parent = parent;
#endif
  params.bounds = bounds;
  widget->Init(params);
  return widget;
}

// static
void Widget::SetPureViews(bool pure) {
  use_pure_views = pure;
}

// static
bool Widget::IsPureViews() {
#if defined(TOUCH_UI)
  return true;
#else
  return use_pure_views;
#endif
}

// static
Widget* Widget::GetWidgetForNativeView(gfx::NativeView native_view) {
  internal::NativeWidgetPrivate* native_widget =
      internal::NativeWidgetPrivate::GetNativeWidgetForNativeView(native_view);
  return native_widget ? native_widget->GetWidget() : NULL;
}

// static
Widget* Widget::GetWidgetForNativeWindow(gfx::NativeWindow native_window) {
  internal::NativeWidgetPrivate* native_widget =
      internal::NativeWidgetPrivate::GetNativeWidgetForNativeWindow(
          native_window);
  return native_widget ? native_widget->GetWidget() : NULL;
}

// static
Widget* Widget::GetTopLevelWidgetForNativeView(gfx::NativeView native_view) {
  internal::NativeWidgetPrivate* native_widget =
      internal::NativeWidgetPrivate::GetTopLevelNativeWidget(native_view);
  return native_widget ? native_widget->GetWidget() : NULL;
}


// static
void Widget::GetAllChildWidgets(gfx::NativeView native_view,
                                Widgets* children) {
  internal::NativeWidgetPrivate::GetAllChildWidgets(native_view, children);
}

// static
void Widget::ReparentNativeView(gfx::NativeView native_view,
                                gfx::NativeView new_parent) {
  internal::NativeWidgetPrivate::ReparentNativeView(native_view, new_parent);
}

// static
int Widget::GetLocalizedContentsWidth(int col_resource_id) {
  return ui::GetLocalizedContentsWidthForFont(col_resource_id,
      ResourceBundle::GetSharedInstance().GetFont(ResourceBundle::BaseFont));
}

// static
int Widget::GetLocalizedContentsHeight(int row_resource_id) {
  return ui::GetLocalizedContentsHeightForFont(row_resource_id,
      ResourceBundle::GetSharedInstance().GetFont(ResourceBundle::BaseFont));
}

// static
gfx::Size Widget::GetLocalizedContentsSize(int col_resource_id,
                                           int row_resource_id) {
  return gfx::Size(GetLocalizedContentsWidth(col_resource_id),
                   GetLocalizedContentsHeight(row_resource_id));
}

void Widget::Init(const InitParams& params) {
  widget_delegate_ =
      params.delegate ? params.delegate : new DefaultWidgetDelegate(this);
  ownership_ = params.ownership;
  native_widget_ = params.native_widget ?
      params.native_widget->AsNativeWidgetPrivate() :
      internal::NativeWidgetPrivate::CreateNativeWidget(this);
  GetRootView();
  default_theme_provider_.reset(new DefaultThemeProvider);
  if (params.type == InitParams::TYPE_MENU) {
    is_mouse_button_pressed_ =
        internal::NativeWidgetPrivate::IsMouseButtonDown();
  }
  native_widget_->InitNativeWidget(params);
  if (params.type == InitParams::TYPE_WINDOW) {
    non_client_view_ = new NonClientView;
    non_client_view_->SetFrameView(CreateNonClientFrameView());
    // Create the ClientView, add it to the NonClientView and add the
    // NonClientView to the RootView. This will cause everything to be parented.
    non_client_view_->set_client_view(widget_delegate_->CreateClientView(this));
    SetContentsView(non_client_view_);
    SetInitialBounds(params.bounds);
    UpdateWindowTitle();
  }
}

// Unconverted methods (see header) --------------------------------------------

gfx::NativeView Widget::GetNativeView() const {
   return native_widget_->GetNativeView();
}

gfx::NativeWindow Widget::GetNativeWindow() const {
  return native_widget_->GetNativeWindow();
}

bool Widget::GetAccelerator(int cmd_id, ui::Accelerator* accelerator) {
  return false;
}

void Widget::ViewHierarchyChanged(bool is_add, View* parent, View* child) {
  if (!is_add) {
    if (child == dragged_view_)
      dragged_view_ = NULL;

    FocusManager* focus_manager = GetFocusManager();
    if (focus_manager)
      focus_manager->ViewRemoved(child);
    ViewStorage::GetInstance()->ViewRemoved(child);
    native_widget_->ViewRemoved(child);
  }
}

void Widget::NotifyNativeViewHierarchyChanged(bool attached,
                                              gfx::NativeView native_view) {
  if (!attached) {
    FocusManager* focus_manager = GetFocusManager();
    // We are being removed from a window hierarchy.  Treat this as
    // the root_view_ being removed.
    if (focus_manager)
      focus_manager->ViewRemoved(root_view_.get());
  }
  root_view_->NotifyNativeViewHierarchyChanged(attached, native_view);
}

// Converted methods (see header) ----------------------------------------------

Widget* Widget::GetTopLevelWidget() {
  return const_cast<Widget*>(
      const_cast<const Widget*>(this)->GetTopLevelWidget());
}

const Widget* Widget::GetTopLevelWidget() const {
  return native_widget_->GetTopLevelWidget();
}

void Widget::SetContentsView(View* view) {
  root_view_->SetContentsView(view);
}

View* Widget::GetContentsView() {
  return root_view_->GetContentsView();
}

gfx::Rect Widget::GetWindowScreenBounds() const {
  return native_widget_->GetWindowScreenBounds();
}

gfx::Rect Widget::GetClientAreaScreenBounds() const {
  return native_widget_->GetClientAreaScreenBounds();
}

gfx::Rect Widget::GetRestoredBounds() const {
  return native_widget_->GetRestoredBounds();
}

void Widget::SetBounds(const gfx::Rect& bounds) {
  native_widget_->SetBounds(bounds);
}

void Widget::SetSize(const gfx::Size& size) {
  native_widget_->SetSize(size);
}

void Widget::SetBoundsConstrained(const gfx::Rect& bounds,
                                  Widget* other_widget) {
  native_widget_->SetBoundsConstrained(bounds, other_widget);
}

void Widget::MoveAboveWidget(Widget* widget) {
  native_widget_->MoveAbove(widget->GetNativeView());
}

void Widget::MoveAbove(gfx::NativeView native_view) {
  native_widget_->MoveAbove(native_view);
}

void Widget::MoveToTop() {
  native_widget_->MoveToTop();
}

void Widget::SetShape(gfx::NativeRegion shape) {
  native_widget_->SetShape(shape);
}

void Widget::Close() {
  if (widget_closed_) {
    // It appears we can hit this code path if you close a modal dialog then
    // close the last browser before the destructor is hit, which triggers
    // invoking Close again.
    return;
  }

  bool can_close = true;
  if (non_client_view_)
    can_close = non_client_view_->CanClose();
  if (can_close) {
    SaveWindowPosition();
    native_widget_->Close();
    widget_closed_ = true;
  }
}

void Widget::CloseNow() {
  native_widget_->CloseNow();
}

void Widget::EnableClose(bool enable) {
  if (non_client_view_)
    non_client_view_->EnableClose(enable);
  native_widget_->EnableClose(enable);
}

void Widget::Show() {
  if (non_client_view_) {
    native_widget_->ShowNativeWidget(
        saved_maximized_state_ ? internal::NativeWidgetPrivate::SHOW_MAXIMIZED
                               : internal::NativeWidgetPrivate::SHOW_RESTORED);
    // |saved_maximized_state_| only applies the first time the window is shown.
    // If we don't reset the value the window will be shown maximized every time
    // it is subsequently shown after being hidden.
    saved_maximized_state_ = false;
  } else {
    native_widget_->Show();
  }
}

void Widget::Hide() {
  native_widget_->Hide();
}

void Widget::ShowInactive() {
  native_widget_->ShowNativeWidget(
      internal::NativeWidgetPrivate::SHOW_INACTIVE);
}

void Widget::Activate() {
  native_widget_->Activate();
}

void Widget::Deactivate() {
  native_widget_->Deactivate();
}

bool Widget::IsActive() const {
  return native_widget_->IsActive();
}

void Widget::DisableInactiveRendering() {
  disable_inactive_rendering_ = true;
  if (non_client_view_)
    non_client_view_->DisableInactiveRendering(disable_inactive_rendering_);
}

void Widget::SetAlwaysOnTop(bool on_top) {
  native_widget_->SetAlwaysOnTop(on_top);
}

void Widget::Maximize() {
  native_widget_->Maximize();
}

void Widget::Minimize() {
  native_widget_->Minimize();
}

void Widget::Restore() {
  native_widget_->Restore();
}

bool Widget::IsMaximized() const {
  return native_widget_->IsMaximized();
}

bool Widget::IsMinimized() const {
  return native_widget_->IsMinimized();
}

void Widget::SetFullscreen(bool fullscreen) {
  native_widget_->SetFullscreen(fullscreen);
}

bool Widget::IsFullscreen() const {
  return native_widget_->IsFullscreen();
}

void Widget::SetWindowProperty(const std::wstring& param){
    native_widget_->SetWindowProperty(param);
}

void Widget::SetOpacity(unsigned char opacity) {
  native_widget_->SetOpacity(opacity);
}

void Widget::SetUseDragFrame(bool use_drag_frame) {
  native_widget_->SetUseDragFrame(use_drag_frame);
}

View* Widget::GetRootView() {
  if (!root_view_.get()) {
    // First time the root view is being asked for, create it now.
    root_view_.reset(CreateRootView());
  }
  return root_view_.get();
}

bool Widget::IsVisible() const {
  return native_widget_->IsVisible();
}

bool Widget::IsAccessibleWidget() const {
  return native_widget_->IsAccessibleWidget();
}

ThemeProvider* Widget::GetThemeProvider() const {
  const Widget* root_widget = GetTopLevelWidget();
  if (root_widget && root_widget != this) {
    // Attempt to get the theme provider, and fall back to the default theme
    // provider if not found.
    ThemeProvider* provider = root_widget->GetThemeProvider();
    if (provider)
      return provider;

    provider = root_widget->default_theme_provider_.get();
    if (provider)
      return provider;
  }
  return default_theme_provider_.get();
}

FocusManager* Widget::GetFocusManager() {
  Widget* toplevel_widget = GetTopLevelWidget();
  if (toplevel_widget && toplevel_widget != this)
    return toplevel_widget->focus_manager_.get();

  return focus_manager_.get();
}

InputMethod* Widget::GetInputMethod() {
  Widget* toplevel_widget = GetTopLevelWidget();
  return toplevel_widget ?
      toplevel_widget->native_widget_->GetInputMethodNative() : NULL;
}

void Widget::RunShellDrag(View* view, const ui::OSExchangeData& data,
                          int operation) {
  dragged_view_ = view;
  native_widget_->RunShellDrag(view, data, operation);
  // If the view is removed during the drag operation, dragged_view_ is set to
  // NULL.
  if (view && dragged_view_ == view) {
    dragged_view_ = NULL;
    view->OnDragDone();
  }
}

void Widget::SchedulePaintInRect(const gfx::Rect& rect) {
  native_widget_->SchedulePaintInRect(rect);
}

void Widget::SetCursor(gfx::NativeCursor cursor) {
  native_widget_->SetCursor(cursor);
}

void Widget::ResetLastMouseMoveFlag() {
  last_mouse_event_was_move_ = false;
}

void Widget::SetNativeWindowProperty(const char* name, void* value) {
  native_widget_->SetNativeWindowProperty(name, value);
}

void* Widget::GetNativeWindowProperty(const char* name) const {
  return native_widget_->GetNativeWindowProperty(name);
}

void Widget::UpdateWindowTitle() {
  if (!non_client_view_)
    return;

  // If the non-client view is rendering its own title, it'll need to relayout
  // now.
  non_client_view_->Layout();

  // Update the native frame's text. We do this regardless of whether or not
  // the native frame is being used, since this also updates the taskbar, etc.
  string16 window_title;
  if (native_widget_->IsScreenReaderActive()) {
    window_title = WideToUTF16(widget_delegate_->GetAccessibleWindowTitle());
  } else {
    window_title = WideToUTF16(widget_delegate_->GetWindowTitle());
  }
  base::i18n::AdjustStringForLocaleDirection(&window_title);
  native_widget_->SetWindowTitle(UTF16ToWide(window_title));
}

void Widget::UpdateWindowIcon() {
  if (non_client_view_)
    non_client_view_->UpdateWindowIcon();
  native_widget_->SetWindowIcons(widget_delegate_->GetWindowIcon(),
                                 widget_delegate_->GetWindowAppIcon());
}

FocusTraversable* Widget::GetFocusTraversable() {
  return static_cast<internal::RootView*>(root_view_.get());
}

void Widget::ThemeChanged() {
  root_view_->ThemeChanged();
}

void Widget::LocaleChanged() {
  root_view_->LocaleChanged();
}

void Widget::SetFocusTraversableParent(FocusTraversable* parent) {
  root_view_->SetFocusTraversableParent(parent);
}

void Widget::SetFocusTraversableParentView(View* parent_view) {
  root_view_->SetFocusTraversableParentView(parent_view);
}

void Widget::ClearNativeFocus() {
  native_widget_->ClearNativeFocus();
}

void Widget::UpdateFrameAfterFrameChange() {
  native_widget_->UpdateFrameAfterFrameChange();
}

NonClientFrameView* Widget::CreateNonClientFrameView() {
  NonClientFrameView* frame_view = widget_delegate_->CreateNonClientFrameView();
  if (!frame_view)
    frame_view = native_widget_->CreateNonClientFrameView();
  return frame_view ? frame_view : new CustomFrameView(this);
}

bool Widget::ShouldUseNativeFrame() const {
  if (frame_type_ != FRAME_TYPE_DEFAULT)
    return frame_type_ == FRAME_TYPE_FORCE_NATIVE;
  return native_widget_->ShouldUseNativeFrame();
}

void Widget::DebugToggleFrameType() {
  if (frame_type_ == FRAME_TYPE_DEFAULT) {
    frame_type_ = ShouldUseNativeFrame() ? FRAME_TYPE_FORCE_CUSTOM :
        FRAME_TYPE_FORCE_NATIVE;
  } else {
    frame_type_ = frame_type_ == FRAME_TYPE_FORCE_CUSTOM ?
        FRAME_TYPE_FORCE_NATIVE : FRAME_TYPE_FORCE_CUSTOM;
  }
  FrameTypeChanged();
}

void Widget::FrameTypeChanged() {
  native_widget_->FrameTypeChanged();
}

const ui::Compositor* Widget::GetCompositor() const {
  return native_widget_->GetCompositor();
}

ui::Compositor* Widget::GetCompositor() {
  return native_widget_->GetCompositor();
}

void Widget::MarkLayerDirty() {
  native_widget_->MarkLayerDirty();
}

void Widget::CalculateOffsetToAncestorWithLayer(gfx::Point* offset,
                                                View** ancestor) {
  native_widget_->CalculateOffsetToAncestorWithLayer(offset, ancestor);
}

void Widget::NotifyAccessibilityEvent(
    View* view,
    ui::AccessibilityTypes::Event event_type,
    bool send_native_event) {
  // Send the notification to the delegate.
  if (ViewsDelegate::views_delegate)
    ViewsDelegate::views_delegate->NotifyAccessibilityEvent(view, event_type);

  if (send_native_event)
    native_widget_->SendNativeAccessibilityEvent(view, event_type);
}

const NativeWidget* Widget::native_widget() const {
  return native_widget_;
}

NativeWidget* Widget::native_widget() {
  return native_widget_;
}

const Event* Widget::GetCurrentEvent() {
  return event_stack_.empty() ? NULL : event_stack_.top()->event();
}

void Widget::TooltipTextChanged(View* view) {
  TooltipManager* manager = native_widget_private()->GetTooltipManager();
  if (manager)
    manager->TooltipTextChanged(view);
}

View* Widget::GetChildViewParent() {
  return GetContentsView() ? GetContentsView() : GetRootView();
}

////////////////////////////////////////////////////////////////////////////////
// Widget, NativeWidgetDelegate implementation:

bool Widget::IsModal() const {
  return widget_delegate_->IsModal();
}

bool Widget::IsDialogBox() const {
  return !!widget_delegate_->AsDialogDelegate();
}

bool Widget::CanActivate() const {
  return widget_delegate_->CanActivate();
}

bool Widget::IsInactiveRenderingDisabled() const {
  return disable_inactive_rendering_;
}

void Widget::EnableInactiveRendering() {
  disable_inactive_rendering_ = false;
  if (non_client_view_)
    non_client_view_->DisableInactiveRendering(false);
}

void Widget::OnNativeWidgetActivationChanged(bool active) {
  if (!active)
    SaveWindowPosition();

  // TODO(beng): merge these two.
  widget_delegate_->OnWidgetActivated(active);
  widget_delegate_->OnWindowActivationChanged(active);
}

void Widget::OnNativeFocus(gfx::NativeView focused_view) {
  GetFocusManager()->GetWidgetFocusManager()->OnWidgetFocusEvent(
      focused_view,
      GetNativeView());
}

void Widget::OnNativeBlur(gfx::NativeView focused_view) {
  GetFocusManager()->GetWidgetFocusManager()->OnWidgetFocusEvent(
      GetNativeView(),
      focused_view);
}

void Widget::OnNativeWidgetCreated() {
  if (GetTopLevelWidget() == this) {
    // Only the top level Widget in a native widget hierarchy has a focus
    // manager.
    focus_manager_.reset(new FocusManager(this));
  }

  native_widget_->SetAccessibleRole(
      widget_delegate_->GetAccessibleWindowRole());
  native_widget_->SetAccessibleState(
      widget_delegate_->GetAccessibleWindowState());

  if (widget_delegate_->IsModal())
    native_widget_->BecomeModal();
}

void Widget::OnNativeWidgetDestroying() {
  if (non_client_view_)
    non_client_view_->WindowClosing();
  widget_delegate_->WindowClosing();
}

void Widget::OnNativeWidgetDestroyed() {
  widget_delegate_->DeleteDelegate();
  widget_delegate_ = NULL;
}

gfx::Size Widget::GetMinimumSize() {
  return non_client_view_ ? non_client_view_->GetMinimumSize() : gfx::Size();
}

void Widget::OnNativeWidgetSizeChanged(const gfx::Size& new_size) {
  root_view_->SetSize(new_size);
}

void Widget::OnNativeWidgetBeginUserBoundsChange() {
  widget_delegate_->OnWindowBeginUserBoundsChange();
}

void Widget::OnNativeWidgetEndUserBoundsChange() {
  widget_delegate_->OnWindowEndUserBoundsChange();
}

bool Widget::HasFocusManager() const {
  return !!focus_manager_.get();
}

bool Widget::OnNativeWidgetPaintAccelerated(const gfx::Rect& dirty_region) {
  ui::Compositor* compositor = GetCompositor();
  if (!compositor)
    return false;

  compositor->NotifyStart();
  GetRootView()->PaintToLayer(dirty_region);
  GetRootView()->PaintComposite();
  compositor->NotifyEnd();
  return true;
}

void Widget::OnNativeWidgetPaint(gfx::Canvas* canvas) {
  GetRootView()->Paint(canvas);
}

int Widget::GetNonClientComponent(const gfx::Point& point) {
  return non_client_view_ ? non_client_view_->NonClientHitTest(point) : 0;
}

bool Widget::OnKeyEvent(const KeyEvent& event) {
  ScopedEvent scoped(this, event);
  return static_cast<internal::RootView*>(GetRootView())->OnKeyEvent(event);
}

bool Widget::OnMouseEvent(const MouseEvent& event) {
  ScopedEvent scoped(this, event);
  switch (event.type()) {
    case ui::ET_MOUSE_PRESSED:
      last_mouse_event_was_move_ = false;
      // Make sure we're still visible before we attempt capture as the mouse
      // press processing may have made the window hide (as happens with menus).
      if (GetRootView()->OnMousePressed(event) && IsVisible()) {
        is_mouse_button_pressed_ = true;
        if (!native_widget_->HasMouseCapture())
          native_widget_->SetMouseCapture();
        return true;
      }
      return false;
    case ui::ET_MOUSE_RELEASED:
      last_mouse_event_was_move_ = false;
      is_mouse_button_pressed_ = false;
      // Release capture first, to avoid confusion if OnMouseReleased blocks.
      if (native_widget_->HasMouseCapture() &&
          ShouldReleaseCaptureOnMouseReleased()) {
        native_widget_->ReleaseMouseCapture();
      }
      GetRootView()->OnMouseReleased(event);
      return (event.flags() & ui::EF_IS_NON_CLIENT) ? false : true;
    case ui::ET_MOUSE_MOVED:
    case ui::ET_MOUSE_DRAGGED:
      if (native_widget_->HasMouseCapture() && is_mouse_button_pressed_) {
        last_mouse_event_was_move_ = false;
        GetRootView()->OnMouseDragged(event);
      } else if (!last_mouse_event_was_move_ ||
                 last_mouse_event_position_ != event.location()) {
        last_mouse_event_position_ = event.location();
        last_mouse_event_was_move_ = true;
        GetRootView()->OnMouseMoved(event);
      }
      return false;
    case ui::ET_MOUSE_EXITED:
      last_mouse_event_was_move_ = false;
      GetRootView()->OnMouseExited(event);
      return false;
    case ui::ET_MOUSEWHEEL:
      return GetRootView()->OnMouseWheel(
          reinterpret_cast<const MouseWheelEvent&>(event));
    default:
      return false;
  }
  return true;
}

void Widget::OnMouseCaptureLost() {
  if (is_mouse_button_pressed_)
    GetRootView()->OnMouseCaptureLost();
  is_mouse_button_pressed_ = false;
}

ui::TouchStatus Widget::OnTouchEvent(const TouchEvent& event) {
  ScopedEvent scoped(this, event);
  return static_cast<internal::RootView*>(GetRootView())->OnTouchEvent(event);
}

bool Widget::ExecuteCommand(int command_id) {
  return widget_delegate_->ExecuteWindowsCommand(command_id);
}

Widget* Widget::AsWidget() {
  return this;
}

const Widget* Widget::AsWidget() const {
  return this;
}

////////////////////////////////////////////////////////////////////////////////
// Widget, FocusTraversable implementation:

FocusSearch* Widget::GetFocusSearch() {
  return root_view_->GetFocusSearch();
}

FocusTraversable* Widget::GetFocusTraversableParent() {
  // We are a proxy to the root view, so we should be bypassed when traversing
  // up and as a result this should not be called.
  NOTREACHED();
  return NULL;
}

View* Widget::GetFocusTraversableParentView() {
  // We are a proxy to the root view, so we should be bypassed when traversing
  // up and as a result this should not be called.
  NOTREACHED();
  return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// Widget, protected:

internal::RootView* Widget::CreateRootView() {
  return new internal::RootView(this);
}

void Widget::DestroyRootView() {
  root_view_.reset();

  // Defer focus manager's destruction. This is for the case when the
  // focus manager is referenced by a child NativeWidgetGtk (e.g. TabbedPane in
  // a dialog). When gtk_widget_destroy is called on the parent, the destroy
  // signal reaches parent first and then the child. Thus causing the parent
  // NativeWidgetGtk's dtor executed before the child's. If child's view
  // hierarchy references this focus manager, it crashes. This will defer focus
  // manager's destruction after child NativeWidgetGtk's dtor.
  FocusManager* focus_manager = focus_manager_.release();
  if (focus_manager)
    MessageLoop::current()->DeleteSoon(FROM_HERE, focus_manager);
}

void Widget::ReplaceFocusManager(FocusManager* focus_manager) {
  focus_manager_.reset(focus_manager);
}

////////////////////////////////////////////////////////////////////////////////
// Widget, private:

// static
ui::Compositor*(*Widget::compositor_factory_)() = NULL;

bool Widget::ShouldReleaseCaptureOnMouseReleased() const {
  return true;
}

void Widget::SaveWindowPosition() {
  // The window delegate does the actual saving for us. It seems like (judging
  // by go/crash) that in some circumstances we can end up here after
  // WM_DESTROY, at which point the window delegate is likely gone. So just
  // bail.
  if (!widget_delegate_)
    return;

  bool maximized;
  gfx::Rect bounds;
  native_widget_->GetWindowBoundsAndMaximizedState(&bounds, &maximized);
  widget_delegate_->SaveWindowPlacement(bounds, maximized);
}

void Widget::SetInitialBounds(const gfx::Rect& bounds) {
  if (!non_client_view_)
    return;

  // First we obtain the window's saved show-style and store it. We need to do
  // this here, rather than in Show() because by the time Show() is called,
  // the window's size will have been reset (below) and the saved maximized
  // state will have been lost. Sadly there's no way to tell on Windows when
  // a window is restored from maximized state, so we can't more accurately
  // track maximized state independently of sizing information.
  widget_delegate_->GetSavedMaximizedState(
      &saved_maximized_state_);

  // Restore the window's placement from the controller.
  gfx::Rect saved_bounds = bounds;
  if (widget_delegate_->GetSavedWindowBounds(&saved_bounds)) {
    if (!widget_delegate_->ShouldRestoreWindowSize()) {
      saved_bounds.set_size(non_client_view_->GetPreferredSize());
    } else {
      // Make sure the bounds are at least the minimum size.
      if (saved_bounds.width() < minimum_size_.width()) {
        saved_bounds.SetRect(saved_bounds.x(), saved_bounds.y(),
                             saved_bounds.right() + minimum_size_.width() -
                                 saved_bounds.width(),
                             saved_bounds.bottom());
      }

      if (saved_bounds.height() < minimum_size_.height()) {
        saved_bounds.SetRect(saved_bounds.x(), saved_bounds.y(),
                             saved_bounds.right(),
                             saved_bounds.bottom() + minimum_size_.height() -
                                 saved_bounds.height());
      }
    }

    // Widget's SetBounds method does not further modify the bounds that are
    // passed to it.
    SetBounds(saved_bounds);
  } else {
    if (bounds.IsEmpty()) {
      // No initial bounds supplied, so size the window to its content and
      // center over its parent.
      native_widget_->CenterWindow(non_client_view_->GetPreferredSize());
    } else {
      // Use the supplied initial bounds.
      SetBoundsConstrained(bounds, NULL);
    }
  }
}

namespace internal {

////////////////////////////////////////////////////////////////////////////////
// internal::NativeWidgetPrivate, NativeWidget implementation:

internal::NativeWidgetPrivate* NativeWidgetPrivate::AsNativeWidgetPrivate() {
  return this;
}

}  // namespace internal
}  // namespace views
