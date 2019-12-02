/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/attribute/edge_attribute_delete.h"

#include <string>

#include "brave/third_party/blink/brave_page_graph/page_graph.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

#include "brave/third_party/blink/brave_page_graph/graph_item/node/node.h"

#include "brave/third_party/blink/brave_page_graph/graph_item/node/actor/node_script.h"

#include "brave/third_party/blink/brave_page_graph/graph_item/node/html/node_html_element.h"

using ::std::string;
using ::std::to_string;

namespace brave_page_graph {

EdgeAttributeDelete::EdgeAttributeDelete(PageGraph* const graph,
    NodeActor* const out_node, NodeHTMLElement* const in_node,
    const string& name, const bool is_style) :
      EdgeAttribute(graph, out_node, in_node, name, is_style) {}

EdgeAttributeDelete::~EdgeAttributeDelete() {}

ItemName EdgeAttributeDelete::GetItemName() const {
  return "delete attribute";
}

bool EdgeAttributeDelete::IsEdgeAttributeDelete() const {
  return true;
}

}  // namespace brave_page_graph
