/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graph_item/node/filter/node_fingerprinting_filter.h"

#include <string>
#include <libxml/tree.h>

#include "brave/third_party/blink/brave_page_graph/graphml.h"
#include "brave/third_party/blink/brave_page_graph/page_graph.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

#include "brave/third_party/blink/brave_page_graph/graph_item/node/node.h"

#include "brave/third_party/blink/brave_page_graph/graph_item/node/filter/node_fingerprinting_filter.h"

using ::std::to_string;

namespace brave_page_graph {

NodeFingerprintingFilter::NodeFingerprintingFilter(PageGraph* const graph,
    const FingerprintingRule& rule) :
      NodeFilter(graph),
      rule_(rule) {}

NodeFingerprintingFilter::~NodeFingerprintingFilter() {}

ItemName NodeFingerprintingFilter::GetItemName() const {
  return "fingerprinting filter";
}

ItemDesc NodeFingerprintingFilter::GetItemDesc() const {
  return NodeFilter::GetItemDesc() + " [" + rule_.ToString() + "]";
}

void NodeFingerprintingFilter::AddGraphMLAttributes(xmlDocPtr doc,
    xmlNodePtr parent_node) const {
  NodeFilter::AddGraphMLAttributes(doc, parent_node);
  GraphMLAttrDefForType(kGraphMLAttrDefPrimaryPattern)
      ->AddValueNode(doc, parent_node, rule_.primary_pattern);
  GraphMLAttrDefForType(kGraphMLAttrDefSecondaryPattern)
      ->AddValueNode(doc, parent_node, rule_.secondary_pattern);
  GraphMLAttrDefForType(kGraphMLAttrDefSource)
      ->AddValueNode(doc, parent_node, rule_.source);
  GraphMLAttrDefForType(kGraphMLAttrDefIncognito)
      ->AddValueNode(doc, parent_node, rule_.incognito);
}

bool NodeFingerprintingFilter::IsNodeFingerprintingFilter() const {
  return true;
}

}  // namespace brave_page_graph
