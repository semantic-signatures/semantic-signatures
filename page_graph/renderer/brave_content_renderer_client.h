/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_RENDERER_BRAVE_CONTENT_RENDERER_CLIENT_H_
#define BRAVE_RENDERER_BRAVE_CONTENT_RENDERER_CLIENT_H_

#include "chrome/renderer/chrome_content_renderer_client.h"

class BraveContentRendererClient : public ChromeContentRendererClient {
 public:
  BraveContentRendererClient();
  ~BraveContentRendererClient() override;
  void SetRuntimeFeaturesDefaultsBeforeBlinkInitialization() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(BraveContentRendererClient);
};

#endif  // BRAVE_RENDERER_BRAVE_CONTENT_RENDERER_CLIENT_H_
