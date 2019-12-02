/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMMON_IMPORTER_BRAVE_STATS_H_
#define BRAVE_COMMON_IMPORTER_BRAVE_STATS_H_

struct BraveStats {
  int adblock_count;
  int trackingProtection_count;
  int httpsEverywhere_count;

  BraveStats()
    : adblock_count(0),
      trackingProtection_count(0),
      httpsEverywhere_count(0) {}
};

#endif  // BRAVE_COMMON_IMPORTER_BRAVE_STATS_H_
