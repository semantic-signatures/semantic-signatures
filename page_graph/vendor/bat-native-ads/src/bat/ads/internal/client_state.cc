/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/client_state.h"
#include "bat/ads/internal/json_helper.h"
#include "bat/ads/internal/static_values.h"

namespace ads {

ClientState::ClientState() :
    ads_shown_history({}),
    ad_uuid(""),
    ads_uuid_seen({}),
    available(false),
    last_search_time(0),
    last_shop_time(0),
    last_user_activity(0),
    last_user_idle_stop_time(0),
    locale(kDefaultLanguageCode),
    locales({}),
    last_page_classification(""),
    page_score_history({}),
    creative_set_history({}),
    campaign_history({}),
    score(0.0),
    search_activity(false),
    search_url(""),
    shop_activity(false),
    shop_url("") {}

ClientState::ClientState(const ClientState& state) :
  ads_shown_history(state.ads_shown_history),
  ad_uuid(state.ad_uuid),
  ads_uuid_seen(state.ads_uuid_seen),
  available(state.available),
  last_search_time(state.last_search_time),
  last_shop_time(state.last_shop_time),
  last_user_activity(state.last_user_activity),
  last_user_idle_stop_time(state.last_user_idle_stop_time),
  locale(state.locale),
  locales(state.locales),
  last_page_classification(state.last_page_classification),
  page_score_history(state.page_score_history),
  creative_set_history(state.creative_set_history),
  campaign_history(state.campaign_history),
  score(state.score),
  search_activity(state.search_activity),
  search_url(state.search_url),
  shop_activity(state.shop_activity),
  shop_url(state.shop_url) {}

ClientState::~ClientState() = default;

const std::string ClientState::ToJson() {
  std::string json;
  SaveToJson(*this, &json);
  return json;
}

Result ClientState::FromJson(
    const std::string& json,
    std::string* error_description) {
  rapidjson::Document client;
  client.Parse(json.c_str());

  if (client.HasParseError()) {
    if (error_description) {
      *error_description = helper::JSON::GetLastError(&client);
    }

    return FAILED;
  }

  if (client.HasMember("adsShownHistory")) {
    for (const auto& ad_shown : client["adsShownHistory"].GetArray()) {
      ads_shown_history.push_back(ad_shown.GetUint64());
    }
  }

  if (client.HasMember("adUUID")) {
    ad_uuid = client["adUUID"].GetString();
  }

  if (client.HasMember("adsUUIDSeen")) {
    for (const auto& ad_uuid_seen : client["adsUUIDSeen"].GetObject()) {
      ads_uuid_seen.insert({ad_uuid_seen.name.GetString(),
          ad_uuid_seen.value.GetInt64()});
    }
  }

  if (client.HasMember("available")) {
    available = client["available"].GetBool();
  }

  if (client.HasMember("lastSearchTime")) {
    last_search_time = client["lastSearchTime"].GetUint64();
  }

  if (client.HasMember("lastShopTime")) {
    last_shop_time = client["lastShopTime"].GetUint64();
  }

  if (client.HasMember("lastUserActivity")) {
    last_user_activity = client["lastUserActivity"].GetUint64();
  }

  if (client.HasMember("lastUserIdleStopTime")) {
    last_user_idle_stop_time = client["lastUserIdleStopTime"].GetUint64();
  }

  if (client.HasMember("locale")) {
    locale = client["locale"].GetString();
  }

  if (client.HasMember("locales")) {
    for (const auto& locale : client["locales"].GetArray()) {
      locales.push_back(locale.GetString());
    }
  }

  if (client.HasMember("last_page_classification")) {
    last_page_classification = client["last_page_classification"].GetString();
  }

  if (client.HasMember("pageScoreHistory")) {
    for (const auto& history : client["pageScoreHistory"].GetArray()) {
      std::vector<double> page_scores = {};

      for (const auto& page_score : history.GetArray()) {
        page_scores.push_back(page_score.GetDouble());
      }

      page_score_history.push_back(page_scores);
    }
  }

  if (client.HasMember("creativeSetHistory")) {
    for (const auto& history : client["creativeSetHistory"].GetObject()) {
      std::deque<uint64_t> timestamps_in_seconds = {};
      for (const auto& timestamp_in_seconds : history.value.GetArray()) {
        timestamps_in_seconds.push_back(timestamp_in_seconds.GetUint64());
      }

      std::string creative_set_id = history.name.GetString();
      creative_set_history.insert({creative_set_id, timestamps_in_seconds});
    }
  }

  if (client.HasMember("campaignHistory")) {
    for (const auto& history : client["campaignHistory"].GetObject()) {
      std::deque<uint64_t> timestamps_in_seconds = {};
      for (const auto& timestamp_in_seconds : history.value.GetArray()) {
        timestamps_in_seconds.push_back(timestamp_in_seconds.GetUint64());
      }

      std::string campaign_id = history.name.GetString();
      campaign_history.insert({campaign_id, timestamps_in_seconds});
    }
  }

  if (client.HasMember("score")) {
    score = client["score"].GetDouble();
  }

  if (client.HasMember("searchActivity")) {
    search_activity = client["searchActivity"].GetBool();
  }

  if (client.HasMember("searchUrl")) {
    search_url = client["searchUrl"].GetString();
  }

  if (client.HasMember("shopActivity")) {
    shop_activity = client["shopActivity"].GetBool();
  }

  if (client.HasMember("shopUrl")) {
    shop_url = client["shopUrl"].GetString();
  }

  return SUCCESS;
}

void SaveToJson(JsonWriter* writer, const ClientState& state) {
  writer->StartObject();

  writer->String("adsShownHistory");
  writer->StartArray();
  for (const auto& ad_shown : state.ads_shown_history) {
    writer->Uint64(ad_shown);
  }
  writer->EndArray();

  writer->String("adUUID");
  writer->String(state.ad_uuid.c_str());

  writer->String("adsUUIDSeen");
  writer->StartObject();
  for (const auto& ad_uuid_seen : state.ads_uuid_seen) {
    writer->String(ad_uuid_seen.first.c_str());
    writer->Uint64(ad_uuid_seen.second);
  }
  writer->EndObject();

  writer->String("available");
  writer->Bool(state.available);

  writer->String("lastSearchTime");
  writer->Uint64(state.last_search_time);

  writer->String("lastShopTime");
  writer->Uint64(state.last_shop_time);

  writer->String("lastUserActivity");
  writer->Uint64(state.last_user_activity);

  writer->String("lastUserIdleStopTime");
  writer->Uint64(state.last_user_idle_stop_time);

  writer->String("locale");
  writer->String(state.locale.c_str());

  writer->String("locales");
  writer->StartArray();
  for (const auto& locale : state.locales) {
    writer->String(locale.c_str());
  }
  writer->EndArray();

  writer->String("last_page_classification");
  writer->String(state.last_page_classification.c_str());

  writer->String("pageScoreHistory");
  writer->StartArray();
  for (const auto& page_score : state.page_score_history) {
    writer->StartArray();
    for (const auto& score : page_score) {
      writer->Double(score);
    }
    writer->EndArray();
  }
  writer->EndArray();

  writer->String("creativeSetHistory");
  writer->StartObject();
  for (const auto& creative_set_id : state.creative_set_history) {
    writer->String(creative_set_id.first.c_str());
    writer->StartArray();
    for (const auto& timestamp_in_seconds : creative_set_id.second) {
      writer->Uint64(timestamp_in_seconds);
    }
    writer->EndArray();
  }
  writer->EndObject();

  writer->String("campaignHistory");
  writer->StartObject();
  for (const auto& campaign_id : state.campaign_history) {
    writer->String(campaign_id.first.c_str());
    writer->StartArray();
    for (const auto& timestamp_in_seconds : campaign_id.second) {
      writer->Uint64(timestamp_in_seconds);
    }
    writer->EndArray();
  }
  writer->EndObject();

  writer->String("score");
  writer->Double(state.score);

  writer->String("searchActivity");
  writer->Bool(state.search_activity);

  writer->String("searchUrl");
  writer->String(state.search_url.c_str());

  writer->String("shopActivity");
  writer->Bool(state.shop_activity);

  writer->String("shopUrl");
  writer->String(state.shop_url.c_str());

  writer->EndObject();
}

}  // namespace ads
