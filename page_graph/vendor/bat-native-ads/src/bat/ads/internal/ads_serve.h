/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_ADS_SERVE_H_
#define BAT_ADS_INTERNAL_ADS_SERVE_H_

#include <stdint.h>
#include <string>
#include <map>
#include <memory>

#include "bat/ads/ads_client.h"

#include "bat/ads/internal/ads_impl.h"

namespace ads {

class AdsImpl;
class Bundle;

class AdsServe {
 public:
  AdsServe(
      AdsImpl* ads,
      AdsClient* ads_client,
      Bundle* bundle);

  ~AdsServe();

  void DownloadCatalog();
  uint64_t CatalogLastUpdated() const;
  void UpdateNextCatalogCheck();

  void Reset();

 private:
  std::string url_;
  void BuildUrl();

  uint64_t next_catalog_check_timestamp_in_seconds;

  void OnCatalogDownloaded(
      const std::string& url,
      const int response_status_code,
      const std::string& response,
      const std::map<std::string, std::string>& headers);
  bool ProcessCatalog(const std::string& json);
  void OnCatalogSaved(const Result result);

  uint64_t next_retry_start_timer_in_;
  void RetryDownloadingCatalog();
  uint64_t catalog_last_updated_;

  void ResetCatalog();
  void OnCatalogReset(const Result result);

  AdsImpl* ads_;  // NOT OWNED
  AdsClient* ads_client_;  // NOT OWNED
  Bundle* bundle_;  // NOT OWNED
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_ADS_SERVE_H_
