// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/tab_contents/tab_contents_delegate.h"

#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/memory/singleton.h"
#include "content/browser/javascript_dialogs.h"
#include "content/browser/tab_contents/tab_contents.h"
#include "content/common/url_constants.h"
#include "ui/gfx/rect.h"

TabContentsDelegate::TabContentsDelegate() {
}

void TabContentsDelegate::OpenURLFromTab(TabContents* source,
                                         const GURL& url,
                                         const GURL& referrer,
                                         WindowOpenDisposition disposition,
                                         PageTransition::Type transition) {
}

void TabContentsDelegate::NavigationStateChanged(const TabContents* source,
                                                 unsigned changed_flags) {
}

std::string TabContentsDelegate::GetNavigationHeaders(const GURL& url) {
  return std::string();
}

void TabContentsDelegate::AddNewContents(TabContents* source,
                                         TabContents* new_contents,
                                         WindowOpenDisposition disposition,
                                         const gfx::Rect& initial_pos,
                                         bool user_gesture,
                                         const std::wstring& param) {
}

void TabContentsDelegate::ActivateContents(TabContents* contents) {
}

void TabContentsDelegate::DeactivateContents(TabContents* contents) {
}

void TabContentsDelegate::LoadingStateChanged(TabContents* source) {
}

void TabContentsDelegate::LoadProgressChanged(double progress) {
}

void TabContentsDelegate::CloseContents(TabContents* source) {
}

void TabContentsDelegate::MoveContents(TabContents* source,
                                       const gfx::Rect& pos) {
}

void TabContentsDelegate::DetachContents(TabContents* source) {
}

bool TabContentsDelegate::IsPopupOrPanel(const TabContents* source) const {
  return false;
}

bool TabContentsDelegate::ShouldFocusConstrainedWindow() {
  return true;
}

void TabContentsDelegate::WillShowConstrainedWindow(TabContents* source) {
}

void TabContentsDelegate::UpdateTargetURL(TabContents* source,
                                          const GURL& url) {
}

void TabContentsDelegate::ContentsMouseEvent(
    TabContents* source, const gfx::Point& location, bool motion) {
}

void TabContentsDelegate::ContentsZoomChange(bool zoom_in) { }

bool TabContentsDelegate::IsApplication() const { return false; }

void TabContentsDelegate::ConvertContentsToApplication(TabContents* source) { }

bool TabContentsDelegate::CanReloadContents(TabContents* source) const {
  return true;
}

void TabContentsDelegate::WillRunBeforeUnloadConfirm() {
}

bool TabContentsDelegate::ShouldSuppressDialogs() {
  return false;
}

void TabContentsDelegate::BeforeUnloadFired(TabContents* tab,
                                            bool proceed,
                                            bool* proceed_to_fire_unload) {
  *proceed_to_fire_unload = true;
}

void TabContentsDelegate::SetFocusToLocationBar(bool select_all) {}

bool TabContentsDelegate::ShouldFocusPageAfterCrash() {
  return true;
}

void TabContentsDelegate::RenderWidgetShowing() {}

bool TabContentsDelegate::TakeFocus(bool reverse) {
  return false;
}

void TabContentsDelegate::LostCapture() {
}

void TabContentsDelegate::SetTabContentBlocked(
    TabContents* contents, bool blocked) {
}

void TabContentsDelegate::TabContentsFocused(TabContents* tab_content) {
}

int TabContentsDelegate::GetExtraRenderViewHeight() const {
  return 0;
}

bool TabContentsDelegate::HandleContextMenu(const ContextMenuParams& params) {
  return false;
}

bool TabContentsDelegate::ExecuteContextMenuCommand(int command) {
  return false;
}

void TabContentsDelegate::ShowPageInfo(Profile* profile,
                                       const GURL& url,
                                       const NavigationEntry::SSLStatus& ssl,
                                       bool show_history) {
}

void TabContentsDelegate::ViewSourceForTab(TabContents* source,
                                           const GURL& page_url) {
  // Fall back implementation based entirely on the view-source scheme.
  // It suffers from http://crbug.com/523 and that is why browser overrides
  // it with proper implementation.
  GURL url = GURL(chrome::kViewSourceScheme + std::string(":") +
                      page_url.spec());
  OpenURLFromTab(source,
                 url,
                 GURL(),
                 NEW_FOREGROUND_TAB,
                 PageTransition::LINK);
}

void TabContentsDelegate::ViewSourceForFrame(TabContents* source,
                                             const GURL& frame_url,
                                             const std::string& content_state) {
  // Same as ViewSourceForTab, but for given subframe.
  GURL url = GURL(chrome::kViewSourceScheme + std::string(":") +
                      frame_url.spec());
  OpenURLFromTab(source,
                 url,
                 GURL(),
                 NEW_FOREGROUND_TAB,
                 PageTransition::LINK);
}

bool TabContentsDelegate::PreHandleKeyboardEvent(
    const NativeWebKeyboardEvent& event,
    bool* is_keyboard_shortcut) {
  return false;
}

void TabContentsDelegate::HandleKeyboardEvent(
    const NativeWebKeyboardEvent& event) {
}

void TabContentsDelegate::HandleMouseUp() {
}

void TabContentsDelegate::HandleMouseActivate() {
}

void TabContentsDelegate::DragEnded() {
}

void TabContentsDelegate::ShowRepostFormWarningDialog(
    TabContents* tab_contents) {
}

bool TabContentsDelegate::OnGoToEntryOffset(int offset) {
  return true;
}

bool TabContentsDelegate::ShouldAddNavigationToHistory(
    const history::HistoryAddPageArgs& add_page_args,
    NavigationType::Type navigation_type) {
  return true;
}

gfx::NativeWindow TabContentsDelegate::GetFrameNativeWindow() {
  return NULL;
}

void TabContentsDelegate::TabContentsCreated(TabContents* new_contents) {
}

void TabContentsDelegate::ContentRestrictionsChanged(TabContents* source) {
}

void TabContentsDelegate::RendererUnresponsive(TabContents* source) {
}

void TabContentsDelegate::RendererResponsive(TabContents* source) {
}

void TabContentsDelegate::WorkerCrashed(TabContents* source) {
}

void TabContentsDelegate::DidNavigateMainFramePostCommit(
    TabContents* tab) {
}

void TabContentsDelegate::DidNavigateToPendingEntry(TabContents* tab) {
}

// A stubbed-out version of JavaScriptDialogCreator that doesn't do anything.
class JavaScriptDialogCreatorStub : public content::JavaScriptDialogCreator {
 public:
  static JavaScriptDialogCreatorStub* GetInstance() {
    return Singleton<JavaScriptDialogCreatorStub>::get();
  }

  virtual void RunJavaScriptDialog(content::JavaScriptDialogDelegate* delegate,
                                   TitleType title_type,
                                   const string16& title,
                                   int dialog_flags,
                                   const string16& message_text,
                                   const string16& default_prompt_text,
                                   IPC::Message* reply_message,
                                   bool* did_suppress_message) OVERRIDE {
    *did_suppress_message = true;
  }

  virtual void RunBeforeUnloadDialog(
      content::JavaScriptDialogDelegate* delegate,
      const string16& message_text,
      IPC::Message* reply_message) OVERRIDE {
    delegate->OnDialogClosed(reply_message, true, string16());
  }

  virtual void ResetJavaScriptState(
      content::JavaScriptDialogDelegate* delegate) OVERRIDE {
  }
 private:
  friend struct DefaultSingletonTraits<JavaScriptDialogCreatorStub>;
};

content::JavaScriptDialogCreator*
TabContentsDelegate::GetJavaScriptDialogCreator() {
  return JavaScriptDialogCreatorStub::GetInstance();
}

TabContentsDelegate::~TabContentsDelegate() {
  while (!attached_contents_.empty()) {
    TabContents* tab_contents = *attached_contents_.begin();
    tab_contents->set_delegate(NULL);
  }
  DCHECK(attached_contents_.empty());
}

void TabContentsDelegate::Attach(TabContents* tab_contents) {
  DCHECK(attached_contents_.find(tab_contents) == attached_contents_.end());
  attached_contents_.insert(tab_contents);
}

void TabContentsDelegate::Detach(TabContents* tab_contents) {
  DCHECK(attached_contents_.find(tab_contents) != attached_contents_.end());
  attached_contents_.erase(tab_contents);
}
