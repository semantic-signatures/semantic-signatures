/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_rewards/browser/reconcile_info.h"

namespace brave_rewards {

ReconcileInfo::ReconcileInfo()
  : retry_step_(STEP_NO), retry_level_(0) {}

ReconcileInfo::~ReconcileInfo() {}

ReconcileInfo::ReconcileInfo(const ReconcileInfo& info) {
  viewing_id_ = info.viewing_id_;
  amount_ = info.amount_;
  retry_step_ = info.retry_step_;
  retry_level_ = info.retry_level_;
}

}  // namespace brave_rewards
