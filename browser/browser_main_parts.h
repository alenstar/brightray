// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE-CHROMIUM file.

#ifndef BRIGHTRAY_BROWSER_BROWSER_MAIN_PARTS_H_
#define BRIGHTRAY_BROWSER_BROWSER_MAIN_PARTS_H_

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/browser_main_parts.h"

namespace devtools_http_handler {
class DevToolsHttpHandler;
}

#if defined(TOOLKIT_VIEWS)
namespace brightray {
class ViewsDelegate;
}
#endif

#if defined(USE_AURA) && defined(USE_X11)
namespace wm {
class WMState;
}
#endif

namespace brightray {

class BrowserContext;

class BrowserMainParts : public content::BrowserMainParts {
 public:
  BrowserMainParts();
  ~BrowserMainParts();

  BrowserContext* browser_context() { return browser_context_.get(); }

 protected:
  // content::BrowserMainParts:
  void PreEarlyInitialization() override;
  void ToolkitInitialized() override;
  void PreMainMessageLoopStart() override;
  void PreMainMessageLoopRun() override;
  void PostMainMessageLoopRun() override;
  int PreCreateThreads() override;

  // Subclasses should override this to provide their own BrowserContxt
  // implementation. The caller takes ownership of the returned object.
  virtual BrowserContext* CreateBrowserContext();

 private:
#if defined(OS_MACOSX)
  void IncreaseFileDescriptorLimit();
  void InitializeMainNib();
#endif

  scoped_refptr<BrowserContext> browser_context_;
  scoped_ptr<devtools_http_handler::DevToolsHttpHandler> devtools_http_handler_;

#if defined(TOOLKIT_VIEWS)
  scoped_ptr<ViewsDelegate> views_delegate_;
#endif

#if defined(USE_AURA) && defined(USE_X11)
  scoped_ptr<wm::WMState> wm_state_;
#endif

  DISALLOW_COPY_AND_ASSIGN(BrowserMainParts);
};

}  // namespace brightray

#endif
