/***************************************************************************
 *  Copyright (C) 2014 Sebastian Schlag <sebastian.schlag@kit.edu>
 **************************************************************************/

#ifndef SRC_PARTITION_METRICS_H_
#define SRC_PARTITION_METRICS_H_
#include <cmath>

#include <algorithm>
#include <vector>

#include "lib/datastructure/Hypergraph.h"
#include "lib/definitions.h"

using datastructure::HyperedgeWeight;
using datastructure::IncidenceIterator;
using datastructure::HypergraphType;
using datastructure::HypernodeWeight;
using defs::PartitionID;

namespace metrics {
static const bool dbg_metrics_hyperedge_cut = false;

inline HyperedgeWeight hyperedgeCut(const HypergraphType& hg) {
  HyperedgeWeight cut = 0;
  forall_hyperedges(he, hg) {
    IncidenceIterator begin, end;
    std::tie(begin, end) = hg.pins(*he);
    if (begin == end) {
      continue;
    }
    ASSERT(begin != end, "Accessing empty hyperedge");

    PartitionID partition = hg.partitionIndex(*begin);
    ++begin;

    for (IncidenceIterator pin_it = begin; pin_it != end; ++pin_it) {
      if (partition != hg.partitionIndex(*pin_it)) {
        DBG(dbg_metrics_hyperedge_cut, "Hyperedge " << *he << " is cut-edge");
        cut += hg.edgeWeight(*he);
        break;
      }
    }
  } endfor
  return cut;
}

template <typename CoarsendToHmetisMapping, typename Partition>
inline HyperedgeWeight hyperedgeCut(const HypergraphType& hg, CoarsendToHmetisMapping&
                                    hg_to_hmetis, Partition& partitioning) {
  HyperedgeWeight cut = 0;
  forall_hyperedges(he, hg) {
    IncidenceIterator begin, end;
    std::tie(begin, end) = hg.pins(*he);
    if (begin == end) {
      continue;
    }
    ASSERT(begin != end, "Accessing empty hyperedge");

    PartitionID partition = partitioning[hg_to_hmetis[*begin]];
    ++begin;

    for (IncidenceIterator pin_it = begin; pin_it != end; ++pin_it) {
      if (partition != partitioning[hg_to_hmetis[*pin_it]]) {
        DBG(dbg_metrics_hyperedge_cut, "Hyperedge " << *he << " is cut-edge");
        cut += hg.edgeWeight(*he);
        break;
      }
    }
  } endfor
  return cut;
}

inline double imbalance(const HypergraphType& hypergraph) {
  typedef typename HypergraphType::HypernodeWeight HypernodeWeight;
  std::vector<HypernodeWeight> partition_sizes { 0, 0 };
  HypernodeWeight total_weight = 0;
  forall_hypernodes(hn, hypergraph) {
    ASSERT(hypergraph.partitionIndex(*hn) < 2 && hypergraph.partitionIndex(*hn) != defs::INVALID_PARTITION
           , "Invalid partition index for hypernode " << *hn << ": " << hypergraph.partitionIndex(*hn));
    partition_sizes[hypergraph.partitionIndex(*hn)] += hypergraph.nodeWeight(*hn);
    total_weight += hypergraph.nodeWeight(*hn);
  } endfor

  HypernodeWeight max_weight = std::max(partition_sizes[0], partition_sizes[1]);
  return 2.0 * max_weight / total_weight - 1.0;
}

inline double avgHyperedgeDegree(const HypergraphType& hypergraph) {
  return static_cast<double>(hypergraph.numPins()) / hypergraph.numEdges();
}

inline double avgHypernodeDegree(const HypergraphType& hypergraph) {
  return static_cast<double>(hypergraph.numPins()) / hypergraph.numNodes();
}

template <class Weights>
inline void partitionWeights(const HypergraphType& hypergraph, Weights& weights) {
  forall_hypernodes(hn, hypergraph) {
    weights[hypergraph.partitionIndex(*hn)] += hypergraph.nodeWeight(*hn);
  } endfor
}
} // namespace metrics

#endif  // SRC_PARTITION_METRICS_H_
