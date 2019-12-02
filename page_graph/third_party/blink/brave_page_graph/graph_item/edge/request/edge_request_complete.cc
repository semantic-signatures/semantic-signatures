/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/request/edge_request_complete.h"

#include <string>
#include <libxml/tree.h>

#include "third_party/blink/renderer/platform/loader/fetch/resource.h"

#include "brave/third_party/blink/brave_page_graph/graphml.h"
#include "brave/third_party/blink/brave_page_graph/page_graph.h"
#include "brave/third_party/blink/brave_page_graph/types.h"
#include "brave/third_party/blink/brave_page_graph/utilities/response_metadata.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_resource.h"

namespace brave_page_graph {

EdgeRequestComplete::EdgeRequestComplete(PageGraph* const graph,
    NodeResource* const out_node, Node* const in_node,
    const InspectorId request_id, const blink::ResourceType resource_type,
    const ResponseMetadata& metadata, const std::string& hash)
    : EdgeRequestResponse(graph, out_node, in_node, request_id,
          kRequestStatusComplete, metadata),
      resource_type_(resource_type),
      hash_(hash) {}

EdgeRequestComplete::~EdgeRequestComplete() {}

ItemName EdgeRequestComplete::GetItemName() const {
  return "request complete";
}

ItemDesc EdgeRequestComplete::GetItemDesc() const {
  return EdgeRequestResponse::GetItemDesc()
    + " [" + ResourceTypeToString(resource_type_) + "]";
}

void EdgeRequestComplete::AddGraphMLAttributes(xmlDocPtr doc,
    xmlNodePtr parent_node) const {
  EdgeRequestResponse::AddGraphMLAttributes(doc, parent_node);
  GraphMLAttrDefForType(kGraphMLAttrDefResourceType)
      ->AddValueNode(doc, parent_node, ResourceTypeToString(resource_type_));
  GraphMLAttrDefForType(kGraphMLAttrDefResponseHash)
      ->AddValueNode(doc, parent_node, hash_);
}

bool EdgeRequestComplete::IsEdgeRequestComplete() const {
  return true;
}

}  // namespace brave_page_graph
