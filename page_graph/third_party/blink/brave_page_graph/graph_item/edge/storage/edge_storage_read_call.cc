/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/storage/edge_storage_read_call.h"

#include <string>

#include "brave/third_party/blink/brave_page_graph/page_graph.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

#include "brave/third_party/blink/brave_page_graph/graph_item/node/actor/node_script.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/storage/node_storage.h"

using ::std::string;

namespace brave_page_graph {

EdgeStorageReadCall::EdgeStorageReadCall(PageGraph* const graph,
    NodeScript* const out_node, NodeStorage* const in_node,
    const string& key) :
      EdgeStorage(graph, out_node, in_node, key) {}

EdgeStorageReadCall::~EdgeStorageReadCall() {}

ItemName EdgeStorageReadCall::GetItemName() const {
  return "read storage call";
}

bool EdgeStorageReadCall::IsEdgeStorageReadCall() const {
  return true;
}

}  // namespace brave_page_graph
