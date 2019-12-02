/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_JS_EDGE_JS_CALL_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_JS_EDGE_JS_CALL_H_

#include <string>
#include <vector>
#include <libxml/tree.h>

#include "third_party/blink/renderer/platform/wtf/casting.h"

#include "brave/third_party/blink/brave_page_graph/types.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/js/edge_js.h"

namespace brave_page_graph {

class Node;
class NodeScript;
class NodeJS;
class PageGraph;

class EdgeJSCall final : public EdgeJS {
friend class PageGraph;
 public:
  EdgeJSCall() = delete;
  ~EdgeJSCall() override;

  ItemName GetItemName() const override;
  ItemDesc GetItemDesc() const override;

  void AddGraphMLAttributes(xmlDocPtr doc, xmlNodePtr parent_node)
      const override;

  const std::vector<const std::string>& GetArguments() const;
  std::string GetArgumentsString() const;
  const MethodName& GetMethodName() const override;
  bool IsEdgeJSCall() const override;

 protected:
  EdgeJSCall(PageGraph* const graph, NodeScript* const out_node,
    NodeJS* const in_node, const std::vector<const std::string>& arguments);

 private:
  const std::vector<const std::string> arguments_;
};

}  // namespace brave_page_graph

namespace blink {

template <>
struct DowncastTraits<brave_page_graph::EdgeJSCall> {
  static bool AllowFrom(const brave_page_graph::EdgeJS& edge) {
    return edge.IsEdgeJSCall();
  }
  static bool AllowFrom(const brave_page_graph::Edge& edge) {
    return IsA<brave_page_graph::EdgeJSCall>(
        DynamicTo<brave_page_graph::EdgeJS>(edge));
  }
  static bool AllowFrom(const brave_page_graph::GraphItem& graph_item) {
    return IsA<brave_page_graph::EdgeJSCall>(
        DynamicTo<brave_page_graph::Edge>(graph_item));
  }
};

}  // namespace blink

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_JS_EDGE_JS_CALL_H_
