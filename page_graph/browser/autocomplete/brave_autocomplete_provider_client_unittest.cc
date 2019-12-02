/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/autocomplete/brave_autocomplete_provider_client.h"

#include "base/strings/utf_string_conversions.h"
#include "brave/common/webui_url_constants.h"
#include "chrome/common/webui_url_constants.h"
#include "chrome/test/base/testing_profile.h"
#include "content/public/test/fake_service_worker_context.h"
#include "content/public/test/test_browser_thread_bundle.h"
#include "testing/gtest/include/gtest/gtest.h"

class BraveAutocompleteProviderClientUnitTest : public testing::Test {
 public:
  void SetUp() override {
    profile_ = std::make_unique<TestingProfile>();
    client_ =
        std::make_unique<BraveAutocompleteProviderClient>(profile_.get());
  }

  bool BuiltinExists(const base::string16& builtin) {
    std::vector<base::string16> v = client_->GetBuiltinURLs();
    auto it = std::find(v.begin(), v.end(), builtin);
    return it != v.end();
  }

 protected:
  content::TestBrowserThreadBundle test_browser_thread_bundle_;
  std::unique_ptr<TestingProfile> profile_;
  std::unique_ptr<BraveAutocompleteProviderClient> client_;
};

TEST_F(BraveAutocompleteProviderClientUnitTest,
       SyncURLSuggestedNotSyncInternal) {
  ASSERT_FALSE(BuiltinExists(base::ASCIIToUTF16(chrome::kChromeUISyncInternalsHost)));
  ASSERT_TRUE(BuiltinExists(base::ASCIIToUTF16(kBraveUISyncHost)));
}
