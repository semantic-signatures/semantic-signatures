/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graphml.h"

#include <map>
#include <string>
#include <vector>

#include <libxml/entities.h>
#include <libxml/tree.h>

#include "base/logging.h"

#include "brave/third_party/blink/brave_page_graph/graphml.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

using ::std::endl;
using ::std::map;
using ::std::string;
using ::std::to_string;
using ::std::unique_ptr;
using ::std::vector;

namespace brave_page_graph {

namespace {
  const GraphMLAttr* const attr_name_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "attr name");
  const GraphMLAttr* const attr_value = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "attr value");
  const GraphMLAttr* const before_node_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "before", kGraphMLAttrTypeLong);
  const GraphMLAttr* const block_type_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "block type");
  const GraphMLAttr* const call_args = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "args");
  const GraphMLAttr* const edge_type_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "edge type");
  const GraphMLAttr* const event_listener_id_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "event listener id", kGraphMLAttrTypeLong);
  const GraphMLAttr* const host_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "host");
  const GraphMLAttr* const incognito_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "incognito");
  const GraphMLAttr* const is_deleted_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "is deleted", kGraphMLAttrTypeBoolean);
  const GraphMLAttr* const is_style_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "is style", kGraphMLAttrTypeBoolean);
  const GraphMLAttr* const key_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "key");
  const GraphMLAttr* const method_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "method");
  const GraphMLAttr* const node_id_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "node id", kGraphMLAttrTypeLong);
  const GraphMLAttr* const node_text = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "text");
  const GraphMLAttr* const node_type = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "node type");
  const GraphMLAttr* const page_graph_edge_id_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "id", kGraphMLAttrTypeLong);
  const GraphMLAttr* const page_graph_node_id_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "id", kGraphMLAttrTypeLong);
  const GraphMLAttr* const page_graph_edge_time_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "timestamp", kGraphMLAttrTypeDouble);
  const GraphMLAttr* const page_graph_node_time_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "timestamp", kGraphMLAttrTypeDouble);
  const GraphMLAttr* const parent_node_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "parent", kGraphMLAttrTypeLong);
  const GraphMLAttr* const primary_pattern_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "primary pattern");
  const GraphMLAttr* const request_id_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "request id", kGraphMLAttrTypeLong);
  const GraphMLAttr* const request_type_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "request type");
  const GraphMLAttr* const resource_type_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "resource type");
  const GraphMLAttr* const response_hash_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "response hash");
  const GraphMLAttr* const rule_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "rule");
  const GraphMLAttr* const script_id_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "script id", kGraphMLAttrTypeLong);
  const GraphMLAttr* const script_type = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "script type");
  const GraphMLAttr* const secondary_pattern_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "secondary pattern");
  const GraphMLAttr* const source_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "source");
  const GraphMLAttr* const status_type = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "status");
  const GraphMLAttr* const success_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "is success", kGraphMLAttrTypeBoolean);
  const GraphMLAttr* const tag_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "tag name");
  const GraphMLAttr* const url_attr = new GraphMLAttr(
    kGraphMLAttrForTypeNode, "url");
  const GraphMLAttr* const value_attr = new GraphMLAttr(
    kGraphMLAttrForTypeEdge, "value");

  const vector<const GraphMLAttr* const> _all_graphml_attrs = {
    attr_name_attr, attr_value, before_node_attr, block_type_attr, call_args,
    edge_type_attr, event_listener_id_attr, host_attr, incognito_attr,
    is_deleted_attr, is_style_attr, key_attr, method_attr, node_id_attr,
    node_text, node_type, page_graph_edge_id_attr, page_graph_node_id_attr,
    page_graph_edge_time_attr, page_graph_node_time_attr,
    parent_node_attr, primary_pattern_attr, request_id_attr, request_type_attr,
    resource_type_attr, response_hash_attr, rule_attr, script_id_attr,
    script_type, secondary_pattern_attr, source_attr, status_type, success_attr,
    tag_attr, url_attr, value_attr
  };
}

const vector<const GraphMLAttr* const>& GetGraphMLAttrs() {
  return _all_graphml_attrs;
}

namespace {
  uint32_t graphml_index = 0;
}

GraphMLAttr::GraphMLAttr(const GraphMLAttrForType for_value,
    const string& name) :
      id_(++graphml_index),
      for_(for_value),
      name_(name),
      type_(kGraphMLAttrTypeString) {}

GraphMLAttr::GraphMLAttr(const GraphMLAttrForType for_value, const string& name,
    const GraphMLAttrType type) :
      id_(++graphml_index),
      for_(for_value),
      name_(name),
      type_(type) {}

GraphMLId GraphMLAttr::GetGraphMLId() const {
  return "d" + to_string(id_);
}

void GraphMLAttr::AddDefinitionNode(xmlNodePtr parent_node) const {
  xmlNodePtr new_node = xmlNewChild(parent_node, NULL, BAD_CAST "key", NULL);
  xmlSetProp(new_node, BAD_CAST "id", BAD_CAST GetGraphMLId().c_str());
  xmlSetProp(new_node, BAD_CAST "for",
      BAD_CAST GraphMLForTypeToString(for_).c_str());
  xmlSetProp(new_node, BAD_CAST "attr.name", BAD_CAST name_.c_str());
  xmlSetProp(new_node, BAD_CAST "attr.type",
      BAD_CAST GraphMLAttrTypeToString(type_).c_str());
}

void GraphMLAttr::AddValueNode(xmlDocPtr doc, xmlNodePtr parent_node,
    const char* value) const {
  AddValueNode(doc, parent_node, string(value));
}

void GraphMLAttr::AddValueNode(xmlDocPtr doc, xmlNodePtr parent_node,
    const string& value) const {
  LOG_ASSERT(type_ == kGraphMLAttrTypeString);
  xmlChar* encoded_content = xmlEncodeEntitiesReentrant(doc,
      BAD_CAST value.c_str());
  xmlNodePtr new_node = xmlNewTextChild(parent_node, NULL,
      BAD_CAST "data", encoded_content);
  xmlSetProp(new_node, BAD_CAST "key", BAD_CAST GetGraphMLId().c_str());
  xmlFree(encoded_content);
}

void GraphMLAttr::AddValueNode(xmlDocPtr doc, xmlNodePtr parent_node,
    const int value) const {
  LOG_ASSERT(type_ == kGraphMLAttrTypeLong);
  xmlNodePtr new_node = xmlNewTextChild(parent_node, NULL, BAD_CAST "data",
      BAD_CAST to_string(value).c_str());
  xmlSetProp(new_node, BAD_CAST "key", BAD_CAST GetGraphMLId().c_str());
}

void GraphMLAttr::AddValueNode(xmlDocPtr doc, xmlNodePtr parent_node,
    const bool value) const {
  LOG_ASSERT(type_ == kGraphMLAttrTypeBoolean);
  xmlNodePtr new_node = xmlNewTextChild(parent_node, NULL, BAD_CAST "data",
      BAD_CAST to_string(value).c_str());
  xmlSetProp(new_node, BAD_CAST "key", BAD_CAST GetGraphMLId().c_str());
}

void GraphMLAttr::AddValueNode(xmlDocPtr doc, xmlNodePtr parent_node,
    const uint64_t value) const {
  LOG_ASSERT(type_ == kGraphMLAttrTypeLong);
  xmlNodePtr new_node = xmlNewTextChild(parent_node, NULL, BAD_CAST "data",
      BAD_CAST to_string(value).c_str());
  xmlSetProp(new_node, BAD_CAST "key", BAD_CAST GetGraphMLId().c_str());
}

void GraphMLAttr::AddValueNode(xmlDocPtr doc, xmlNodePtr parent_node,
    const double value) const {
  LOG_ASSERT(type_ == kGraphMLAttrTypeDouble);
  xmlNodePtr new_node = xmlNewTextChild(parent_node, NULL, BAD_CAST "data",
      BAD_CAST to_string(value).c_str());
  xmlSetProp(new_node, BAD_CAST "key", BAD_CAST GetGraphMLId().c_str());
}

const GraphMLAttr* GraphMLAttrDefForType(const GraphMLAttrDef type) noexcept {
  switch (type) {
    case kGraphMLAttrDefAttrName:
      return attr_name_attr;
    case kGraphMLAttrDefBeforeNodeId:
      return before_node_attr;
    case kGraphMLAttrDefBlockType:
      return block_type_attr;
    case kGraphMLAttrDefCallArgs:
      return call_args;
    case kGraphMLAttrDefEdgeType:
      return edge_type_attr;
    case kGraphMLAttrDefEventListenerId:
      return event_listener_id_attr;
    case kGraphMLAttrDefHost:
      return host_attr;
    case kGraphMLAttrDefIncognito:
      return incognito_attr;
    case kGraphMLAttrDefIsDeleted:
      return is_deleted_attr;
    case kGraphMLAttrDefIsStyle:
      return is_style_attr;
    case kGraphMLAttrDefKey:
      return key_attr;
    case kGraphMLAttrDefMethodName:
      return method_attr;
    case kGraphMLAttrDefNodeTag:
      return tag_attr;
    case kGraphMLAttrDefNodeId:
      return node_id_attr;
    case kGraphMLAttrDefNodeText:
      return node_text;
    case kGraphMLAttrDefNodeType:
      return node_type;
    case kGraphMLAttrDefPageGraphEdgeId:
      return page_graph_edge_id_attr;
    case kGraphMLAttrDefPageGraphNodeId:
      return page_graph_node_id_attr;
    case kGraphMLAttrDefPageGraphEdgeTimestamp:
      return page_graph_edge_time_attr;
    case kGraphMLAttrDefPageGraphNodeTimestamp:
      return page_graph_node_time_attr;
    case kGraphMLAttrDefParentNodeId:
      return parent_node_attr;
    case kGraphMLAttrDefPrimaryPattern:
      return primary_pattern_attr;
    case kGraphMLAttrDefRequestId:
      return request_id_attr;
    case kGraphMLAttrDefRequestType:
      return request_type_attr;
    case kGraphMLAttrDefResourceType:
      return resource_type_attr;
    case kGraphMLAttrDefResponseHash:
      return response_hash_attr;
    case kGraphMLAttrDefRule:
      return rule_attr;
    case kGraphMLAttrDefScriptId:
      return script_id_attr;
    case kGraphMLAttrDefScriptType:
      return script_type;
    case kGraphMLAttrDefSecondaryPattern:
      return secondary_pattern_attr;
    case kGraphMLAttrDefSource:
      return source_attr;
    case kGraphMLAttrDefStatus:
      return status_type;
    case kGraphMLAttrDefSuccess:
      return success_attr;
    case kGraphMLAttrDefURL:
      return url_attr;
    case kGraphMLAttrDefValue:
      return value_attr;
    case kGraphMLAttrDefUnknown:
      return nullptr;
  }
}

}  // namespace brave_page_graph
