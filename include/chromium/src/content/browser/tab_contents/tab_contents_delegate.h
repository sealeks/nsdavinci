// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_TAB_CONTENTS_TAB_CONTENTS_DELEGATE_H_
#define CONTENT_BROWSER_TAB_CONTENTS_TAB_CONTENTS_DELEGATE_H_
#pragma once

#include <set>
#include <string>

#include "base/basictypes.h"
#include "content/browser/tab_contents/navigation_entry.h"
#include "content/common/navigation_types.h"
#include "content/common/page_transition_types.h"
#include "ui/gfx/native_widget_types.h"
#include "webkit/glue/window_open_disposition.h"

namespace content {
class JavaScriptDialogCreator;
}

namespace gfx {
class Point;
class Rect;
class Size;
}

namespace history {
class HistoryAddPageArgs;
}

struct ContextMenuParams;
class GURL;
class HtmlDialogUIDelegate;
struct NativeWebKeyboardEvent;
class Profile;
class RenderViewHost;
class TabContents;

// Objects implement this interface to get notified about changes in the
// TabContents and to provide necessary functionality.
class TabContentsDelegate {
 public:
  TabContentsDelegate();

  // Opens a new URL inside the passed in TabContents (if source is 0 open
  // in the current front-most tab), unless |disposition| indicates the url
  // should be opened in a new tab or window.
  //
  // A NULL source indicates the current tab (callers should probably use
  // OpenURL() for these cases which does it for you).
  virtual void OpenURLFromTab(TabContents* source,
                              const GURL& url,
                              const GURL& referrer,
                              WindowOpenDisposition disposition,
                              PageTransition::Type transition);

  // Called to inform the delegate that the tab content's navigation state
  // changed. The |changed_flags| indicates the parts of the navigation state
  // that have been updated, and is any combination of the
  // |TabContents::InvalidateTypes| bits.
  virtual void NavigationStateChanged(const TabContents* source,
                                      unsigned changed_flags);

  // Returns the set of headers to add to the navigation request. Use
  // net::HttpUtil::AppendHeaderIfMissing to build the set of headers.
  virtual std::string GetNavigationHeaders(const GURL& url);

  // Creates a new tab with the already-created TabContents 'new_contents'.
  // The window for the added contents should be reparented correctly when this
  // method returns.  If |disposition| is NEW_POPUP, |pos| should hold the
  // initial position.
  virtual void AddNewContents(TabContents* source,
                              TabContents* new_contents,
                              WindowOpenDisposition disposition,
                              const gfx::Rect& initial_pos,
                              bool user_gesture,
                              const std::wstring& param=L"");

  // Selects the specified contents, bringing its container to the front.
  virtual void ActivateContents(TabContents* contents);

  // Deactivates the specified contents by deactivating its container and
  // potentialy moving it to the back of the Z order.
  virtual void DeactivateContents(TabContents* contents);

  // Notifies the delegate that this contents is starting or is done loading
  // some resource. The delegate should use this notification to represent
  // loading feedback. See TabContents::is_loading()
  virtual void LoadingStateChanged(TabContents* source);

  // Notifies the delegate that the page has made some progress loading.
  // |progress| is a value between 0.0 (nothing loaded) to 1.0 (page fully
  // loaded).
  // Note that to receive this notification, you must have called
  // SetReportLoadProgressEnabled(true) in the render view.
  virtual void LoadProgressChanged(double progress);

  // Request the delegate to close this tab contents, and do whatever cleanup
  // it needs to do.
  virtual void CloseContents(TabContents* source);

  // Request the delegate to move this tab contents to the specified position
  // in screen coordinates.
  virtual void MoveContents(TabContents* source, const gfx::Rect& pos);

  // Causes the delegate to detach |source| and clean up any internal data
  // pointing to it.  After this call ownership of |source| passes to the
  // caller, and it is safe to call "source->set_delegate(someone_else);".
  virtual void DetachContents(TabContents* source);

  // Called to determine if the TabContents is contained in a popup window
  // or a panel window.
  virtual bool IsPopupOrPanel(const TabContents* source) const;

  // Returns true if constrained windows should be focused. Default is true.
  virtual bool ShouldFocusConstrainedWindow();

  // Invoked prior to the TabContents showing a constrained window.
  virtual void WillShowConstrainedWindow(TabContents* source);

  // Notification that the target URL has changed.
  virtual void UpdateTargetURL(TabContents* source, const GURL& url);

  // Notification that there was a mouse event, along with the absolute
  // coordinates of the mouse pointer and whether it was a normal motion event
  // (otherwise, the pointer left the contents area).
  virtual void ContentsMouseEvent(
      TabContents* source, const gfx::Point& location, bool motion);

  // Request the delegate to change the zoom level of the current tab.
  virtual void ContentsZoomChange(bool zoom_in);

  // Check whether this contents is inside a window dedicated to running a web
  // application.
  virtual bool IsApplication() const;

  // Detach the given tab and convert it to a "webapp" view.  The tab must be
  // a TabContents with a valid WebApp set.
  virtual void ConvertContentsToApplication(TabContents* source);

  // Whether the specified tab can be reloaded.
  // Reloading can be disabled e. g. for the DevTools window.
  virtual bool CanReloadContents(TabContents* source) const;

  // Invoked prior to showing before unload handler confirmation dialog.
  virtual void WillRunBeforeUnloadConfirm();

  // Returns true if javascript dialogs and unload alerts are suppressed.
  // Default is false.
  virtual bool ShouldSuppressDialogs();

  // Tells us that we've finished firing this tab's beforeunload event.
  // The proceed bool tells us whether the user chose to proceed closing the
  // tab. Returns true if the tab can continue on firing it's unload event.
  // If we're closing the entire browser, then we'll want to delay firing
  // unload events until all the beforeunload events have fired.
  virtual void BeforeUnloadFired(TabContents* tab,
                                 bool proceed,
                                 bool* proceed_to_fire_unload);

  // Sets focus to the location bar or some other place that is appropriate.
  // This is called when the tab wants to encourage user input, like for the
  // new tab page.
  virtual void SetFocusToLocationBar(bool select_all);

  // Returns whether the page should be focused when transitioning from crashed
  // to live. Default is true.
  virtual bool ShouldFocusPageAfterCrash();

  // Called when a popup select is about to be displayed. The delegate can use
  // this to disable inactive rendering for the frame in the window the select
  // is opened within if necessary.
  virtual void RenderWidgetShowing();

  // This is called when WebKit tells us that it is done tabbing through
  // controls on the page. Provides a way for TabContentsDelegates to handle
  // this. Returns true if the delegate successfully handled it.
  virtual bool TakeFocus(bool reverse);

  // Invoked when the page loses mouse capture.
  virtual void LostCapture();

  // Changes the blocked state of the tab at |index|. TabContents are
  // considered blocked while displaying a tab modal dialog. During that time
  // renderer host will ignore any UI interaction within TabContent outside of
  // the currently displaying dialog.
  virtual void SetTabContentBlocked(TabContents* contents, bool blocked);

  // Notification that |tab_contents| has gained focus.
  virtual void TabContentsFocused(TabContents* tab_content);

  // Return much extra vertical space should be allotted to the
  // render view widget during various animations (e.g. infobar closing).
  // This is used to make painting look smoother.
  virtual int GetExtraRenderViewHeight() const;

  // Returns true if the context menu operation was handled by the delegate.
  virtual bool HandleContextMenu(const ContextMenuParams& params);

  // Returns true if the context menu command was handled
  virtual bool ExecuteContextMenuCommand(int command);

  // Shows the page info using the specified information.
  // |url| is the url of the page/frame the info applies to, |ssl| is the SSL
  // information for that page/frame.  If |show_history| is true, a section
  // showing how many times that URL has been visited is added to the page info.
  virtual void ShowPageInfo(Profile* profile,
                            const GURL& url,
                            const NavigationEntry::SSLStatus& ssl,
                            bool show_history);

  // Opens source view for given tab contents that is navigated to the given
  // page url.
  virtual void ViewSourceForTab(TabContents* source, const GURL& page_url);

  // Opens source view for the given subframe.
  virtual void ViewSourceForFrame(TabContents* source,
                                  const GURL& url,
                                  const std::string& content_state);

  // Allows delegates to handle keyboard events before sending to the renderer.
  // Returns true if the |event| was handled. Otherwise, if the |event| would be
  // handled in HandleKeyboardEvent() method as a normal keyboard shortcut,
  // |*is_keyboard_shortcut| should be set to true.
  virtual bool PreHandleKeyboardEvent(const NativeWebKeyboardEvent& event,
                                      bool* is_keyboard_shortcut);

  // Allows delegates to handle unhandled keyboard messages coming back from
  // the renderer.
  virtual void HandleKeyboardEvent(const NativeWebKeyboardEvent& event);

  virtual void HandleMouseUp();
  virtual void HandleMouseActivate();

  // Render view drag n drop ended.
  virtual void DragEnded();

  // Shows the repost form confirmation dialog box.
  virtual void ShowRepostFormWarningDialog(TabContents* tab_contents);

  // Allows delegate to override navigation to the history entries.
  // Returns true to allow TabContents to continue with the default processing.
  virtual bool OnGoToEntryOffset(int offset);

  // Returns whether this tab contents should add the specified navigation to
  // history.
  virtual bool ShouldAddNavigationToHistory(
      const history::HistoryAddPageArgs& add_page_args,
      NavigationType::Type navigation_type);

  // Returns the native window framing the view containing the tab contents.
  virtual gfx::NativeWindow GetFrameNativeWindow();

  // Notifies the delegate about the creation of a new TabContents. This
  // typically happens when popups are created.
  virtual void TabContentsCreated(TabContents* new_contents);

  // Notifies the delegate that the content restrictions for this tab has
  // changed.
  virtual void ContentRestrictionsChanged(TabContents* source);

  // Notification that the tab is hung.
  virtual void RendererUnresponsive(TabContents* source);

  // Notification that the tab is no longer hung.
  virtual void RendererResponsive(TabContents* source);

  // Notification that a worker associated with this tab has crashed.
  virtual void WorkerCrashed(TabContents* source);

  // Invoked when a main fram navigation occurs.
  virtual void DidNavigateMainFramePostCommit(TabContents* tab);

  // Invoked when navigating to a pending entry. When invoked the
  // NavigationController has configured its pending entry, but it has not yet
  // been committed.
  virtual void DidNavigateToPendingEntry(TabContents* tab);

  // Returns a pointer to a service to create JavaScript dialogs. The default
  // pointer returned is to a stub service that marks all dialogs as suppressed
  // and displays nothing.
  virtual content::JavaScriptDialogCreator* GetJavaScriptDialogCreator();

 protected:
  virtual ~TabContentsDelegate();

 private:
  friend class TabContents;

  // Called when |this| becomes the TabContentsDelegate for |source|.
  void Attach(TabContents* source);

  // Called when |this| is no longer the TabContentsDelegate for |source|.
  void Detach(TabContents* source);

  // The TabContents that this is currently a delegate for.
  std::set<TabContents*> attached_contents_;
};

#endif  // CONTENT_BROWSER_TAB_CONTENTS_TAB_CONTENTS_DELEGATE_H_
