/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_SYNC_BOOKMARK_ORDER_UTIL_H_
#define BRAVE_COMPONENTS_BRAVE_SYNC_BOOKMARK_ORDER_UTIL_H_

#include <string>
#include <vector>

namespace brave_sync {

  std::vector<int> OrderToIntVect(const std::string& s);
  bool CompareOrder(const std::string& left, const std::string& right);

} // namespace brave_sync

#endif // BRAVE_COMPONENTS_BRAVE_SYNC_BOOKMARK_ORDER_UTIL_H_
