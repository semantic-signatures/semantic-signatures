/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef H_BRAVE_COMPONENTS_BRAVE_SYNC_BRAVE_SYNC_JSLIB_MESSAGES_H
#define H_BRAVE_COMPONENTS_BRAVE_SYNC_BRAVE_SYNC_JSLIB_MESSAGES_H

#include <string>
#include <memory>
#include <vector>

#include <base/time/time.h>

namespace brave_sync {

namespace jslib {

// Simple C++ structures to work with messages from sync lib
// Since it is not possible to use sync lib C++ protobuf generated by reasons:
// 1) Chromium everywhere uses `syntax = "proto2";`, sync-lib - `syntax = "proto3";`
// 2) forcing to use version 3 makes to have a deps "//third_party/protobuf:protobuf_full" :
//    marked `Do not use in Chrome code.` in src/third_party/protobuf/BUILD.gn
// 3) even with a depth of a deps "//third_party/protobuf:protobuf_full" there are questions
//    how to convert json -> protobuf class, not all of fields were converted

class Site {
public:
  Site();
  Site(const Site& site);
  ~Site();
  static std::unique_ptr<Site> Clone(const Site& site);

  std::string location;
  std::string title;
  std::string customTitle;
  base::Time lastAccessedTime;
  base::Time creationTime;
  std::string favicon;
};

class Bookmark {
public:
  Bookmark();
  Bookmark(const Bookmark& bookmark);
  ~Bookmark();
  static std::unique_ptr<Bookmark> Clone(const Bookmark& bookmark);

  Site site;
  bool isFolder;
  std::string parentFolderObjectId; // bytes
  std::string prevObjectId; // bytes
  std::vector<std::string> fields;
  bool hideInToolbar;
  std::string order;
  std::string prevOrder;
  std::string nextOrder;
  std::string parentOrder;
};

class SiteSetting {
public:
  SiteSetting();
  ~SiteSetting();
  static std::unique_ptr<SiteSetting> Clone(const SiteSetting& site_setting);

  std::string hostPattern;
  double zoomLevel;
  bool shieldsUp;
  enum AdControl {
    ADC_INVALID = -1,
    SHOW_BRAVE_ADS = 0,
    BLOCK_ADS = 1,
    ALLOW_ADS_AND_TRACKING = 2,
    ADC_MIN = SHOW_BRAVE_ADS,
    ADC_MAX = ALLOW_ADS_AND_TRACKING,
  };
  enum CookieControl {
    CC_INVALID = -1,
    BLOCK_THIRD_PARTY_COOKIE = 0,
    ALLOW_ALL_COOKIES = 1,
    BLOCK_ALL_COOKIES = 2,
    CC_MIN = BLOCK_THIRD_PARTY_COOKIE,
    CC_MAX = BLOCK_ALL_COOKIES,
  };
  AdControl adControl;
  CookieControl cookieControl;
  bool safeBrowsing;
  bool noScript;
  bool httpsEverywhere;
  bool fingerprintingProtection;
  bool ledgerPayments;
  bool ledgerPaymentsShown;
  std::vector<std::string> fields;
};

class Device {
public:
  Device();
  ~Device();
  static std::unique_ptr<Device> Clone(const Device& device);
  std::string name;
};


class SyncRecord {
public:
  SyncRecord();
  ~SyncRecord();

  static std::unique_ptr<SyncRecord> Clone(const SyncRecord& record);

  enum Action {
    A_INVALID = -1,
    A_CREATE = 0,
    A_UPDATE = 1,
    A_DELETE = 2,
    A_MIN = A_CREATE,
    A_MAX = A_DELETE,
  };

  Action action;
  std::string deviceId; // bytes
  std::string objectId; // bytes

  std::string objectData;

  bool has_bookmark() const;
  bool has_historysite() const;
  bool has_sitesetting() const;
  bool has_device() const;
  const Bookmark& GetBookmark() const;
  const Site& GetHistorySite() const;
  const SiteSetting& GetSiteSetting() const;
  const Device& GetDevice() const;

  void SetBookmark(std::unique_ptr<Bookmark> bookmark);
  void SetHistorySite(std::unique_ptr<Site> history_site);
  void SetSiteSetting(std::unique_ptr<SiteSetting> site_setting);
  void SetDevice(std::unique_ptr<Device> device);

  base::Time syncTimestamp;
private:
  std::unique_ptr<Bookmark> bookmark_;
  std::unique_ptr<Site> history_site_;
  std::unique_ptr<SiteSetting> site_setting_;
  std::unique_ptr<Device> device_;
};

}  // namespace jslib

}  // namespace brave_sync

#endif  // H_BRAVE_COMPONENTS_BRAVE_SYNC_BRAVE_SYNC_JSLIB_MESSAGES_H
