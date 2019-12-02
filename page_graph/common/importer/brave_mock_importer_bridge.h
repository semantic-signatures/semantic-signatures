/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMMON_IMPORTER_BRAVE_MOCK_IMPORTER_BRIDGE_H_
#define BRAVE_COMMON_IMPORTER_BRAVE_MOCK_IMPORTER_BRIDGE_H_

#include <vector>

#include "brave/common/importer/brave_ledger.h"
#include "brave/common/importer/brave_stats.h"
#include "brave/common/importer/imported_browser_window.h"
#include "chrome/common/importer/mock_importer_bridge.h"
#include "net/cookies/canonical_cookie.h"
#include "testing/gmock/include/gmock/gmock.h"

struct BraveStats;
struct BraveLedger;

class BraveMockImporterBridge : public MockImporterBridge {
 public:
  BraveMockImporterBridge();

  MOCK_METHOD1(SetCookies,
               void(const std::vector<net::CanonicalCookie>&));
  MOCK_METHOD1(UpdateStats,
               void(const BraveStats&));
  MOCK_METHOD1(UpdateLedger,
               void(const BraveLedger&));
  MOCK_METHOD1(UpdateWindows,
               void(const ImportedWindowState&));

 private:
  ~BraveMockImporterBridge() override;
};

#endif  // BRAVE_COMMON_IMPORTER_BRAVE_MOCK_IMPORTER_BRIDGE_H_
