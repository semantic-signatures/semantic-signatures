# Artifacts for IEEE Security & Privacy (2020) submission #760 Improving Web Content Blocking With Event-Loop-Turn Granularity JavaScript Signatures

This repository includes both the source code of the PageGraph implementation, and the data on which our evaluation (Section IV & V of the paper) was based.

Contents:

## PageGraph Source Code

This can be found under page_graph/. We publish this as a set of patches for Chromium's Blink layout engine and V8 JavaScript engine. The modifications to Blink and V8 are mostly hook points that invoke our custom runtime that maintains the graph representation in memory. This custom runtime is found in third_party/blink/brave_page_graph.

## Graph Representation of Crawled Websites

The graph representation of websites in our crawl of the Alexa top 100K can be found at [this](https://drive.google.com/file/d/1NzXBN5Iv4xfBYkbZJeJ7-ZcKAc6bWAWA/view?usp=sharing) Google Drive link. The graphs are in the GraphML format. Each GraphML file corresponds to one visited website, indicated by the name of the GraphML file.

## All Generated Signatures

[This](https://drive.google.com/file/d/1PELYR9YXLZ2Nd8yWwE3VALqGFmSmKPRt/view?usp=sharing) Google Drive link hosts all of the signatures that were generated by applying our algorithm described in Section III-B of the paper to each individual graph representation of websites. Since the signatures are essentially subgraphs of the original graph representation of websites, they are also in the GraphML format.

## EasyList/EasyPrivacy (EL/EP) Rules

We also include the EL/EP rules that we used to determine ground truth of privacy-harming behaviours. These are found in data/easylist.txt and data/easyprivacy.txt.

## Scripts that Match Signatures of Privacy-Harming Behaviours

We publish the scripts that match signatures of privacy-harming behaviours, as well as the first-party websites where they are found, in a separate JSON file found in data/summary_readable.json. For each script, we also indicate whether they are blocked by an existing EL/EP rule (i.e., data/easylist.txt and data/easyprivacy.txt), and if so, the EL/EP rule that blocked it. Additionally, we also publish all of the scripts referenced in that file as a tarball at [this](https://drive.google.com/file/d/1ej3xtFafDl10LTZSqty98XqTfvPTD_qN/view?usp=sharing) Google Drive link (the correspondence between the script URLs and the file names in the tarball is encoded in a JSON file in data/mappings.json).
