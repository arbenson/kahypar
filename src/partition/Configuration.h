/***************************************************************************
 *  Copyright (C) 2014 Sebastian Schlag <sebastian.schlag@kit.edu>
 **************************************************************************/

#ifndef SRC_PARTITION_CONFIGURATION_H_
#define SRC_PARTITION_CONFIGURATION_H_

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

#include "lib/datastructure/Hypergraph.h"

using datastructure::HypergraphType;

namespace partition {
enum class CoarseningScheme { HEAVY_EDGE_FULL, HEAVY_EDGE_HEURISTIC, HYPEREDGE };

struct Configuration {
  typedef typename HypergraphType::HypernodeWeight HypernodeWeight;
  typedef typename HypergraphType::HypernodeID HypernodeID;
  typedef typename HypergraphType::HyperedgeID HyperedgeID;
  typedef typename HypergraphType::PartitionID PartitionID;

  struct CoarseningParameters {
    CoarseningParameters() :
      threshold_node_weight(0),
      minimal_node_count(0),
      hypernode_weight_fraction(0.0),
      scheme(CoarseningScheme::HEAVY_EDGE_FULL) { }

    HypernodeWeight threshold_node_weight;
    HypernodeID minimal_node_count;
    double hypernode_weight_fraction;
    CoarseningScheme scheme;
  };

  struct PartitioningParameters {
    PartitioningParameters() :
      k(2),
      seed(0),
      initial_partitioning_attempts(1),
      global_search_iterations(1),
      epsilon(1.0),
      partition_size_upper_bound(std::numeric_limits<HypernodeWeight>::max()),
      hyperedge_size_threshold(-1),
      verbose_output(false),
      graph_filename(),
      graph_partition_filename(),
      coarse_graph_filename(),
      coarse_graph_partition_filename() { }

    PartitionID k;
    int seed;
    int initial_partitioning_attempts;
    int global_search_iterations;
    double epsilon;
    HypernodeWeight partition_size_upper_bound;
    HyperedgeID hyperedge_size_threshold;
    bool verbose_output;
    std::string graph_filename;
    std::string graph_partition_filename;
    std::string coarse_graph_filename;
    std::string coarse_graph_partition_filename;
  };

  struct TwoWayFMParameters {
    TwoWayFMParameters() :
      max_number_of_fruitless_moves(50),
      num_repetitions(1),
      alpha(4),
      beta(0.0),
      stopping_rule(),
      active(true) { }

    int max_number_of_fruitless_moves;
    int num_repetitions;
    double alpha;
    double beta;
    std::string stopping_rule;
    bool active;
  };

  struct HERFMParameters {
    HERFMParameters() :
      max_number_of_fruitless_moves(10),
      num_repetitions(1),
      stopping_rule(),
      active(false) { }

    int max_number_of_fruitless_moves;
    int num_repetitions;
    std::string stopping_rule;
    bool active;
  };

  PartitioningParameters partitioning;
  CoarseningParameters coarsening;
  TwoWayFMParameters two_way_fm;
  HERFMParameters her_fm;

  Configuration() :
    partitioning(),
    coarsening(),
    two_way_fm(),
    her_fm() { }
};

inline std::string toString(const Configuration& config) {
  std::ostringstream oss;
  oss << std::left;
  oss << "Partitioning Parameters:" << std::endl;
  oss << std::setw(30) << "  Hypergraph: " << config.partitioning.graph_filename << std::endl;
  oss << std::setw(30) << "  Partition File: " << config.partitioning.graph_partition_filename
  << std::endl;
  oss << std::setw(30) << "  Coarsened Hypergraph: " << config.partitioning.coarse_graph_filename
  << std::endl;
  oss << std::setw(30) << "  Coarsened Partition File: "
  << config.partitioning.coarse_graph_partition_filename << std::endl;
  oss << std::setw(30) << "  k: " << config.partitioning.k << std::endl;
  oss << std::setw(30) << "  epsilon: " << config.partitioning.epsilon
  << std::endl;
  oss << std::setw(30) << "  L_max: " << config.partitioning.partition_size_upper_bound
  << std::endl;
  oss << std::setw(30) << "  seed: " << config.partitioning.seed << std::endl;
  oss << std::setw(30) << "  # initial partitionings: "
  << config.partitioning.initial_partitioning_attempts << std::endl;
  oss << std::setw(30) << "  # global search iterations: "
  << config.partitioning.global_search_iterations << std::endl;
  oss << std::setw(30) << "  hyperedge size threshold: " << config.partitioning.hyperedge_size_threshold
  << std::endl;
  oss << "Coarsening Parameters:" << std::endl;
  oss << std::setw(30) << "  scheme: ";
  switch (config.coarsening.scheme) {
    case CoarseningScheme::HEAVY_EDGE_FULL:
      oss << "heavy_full";
      break;
    case CoarseningScheme::HEAVY_EDGE_HEURISTIC:
      oss << "heavy_heuristic";
      break;
    case CoarseningScheme::HYPEREDGE:
      oss << "hyperedge";
      break;
  }
  oss << std::endl;
  oss << std::setw(30) << "  hypernode weight fraction: "
  << config.coarsening.hypernode_weight_fraction << std::endl;
  oss << std::setw(30) << "  max. hypernode weight: " << config.coarsening.threshold_node_weight
  << std::endl;
  oss << std::setw(30) << "  min. # hypernodes: " << config.coarsening.minimal_node_count
  << std::endl;
  if (config.two_way_fm.active) {
    oss << "2-Way-FM Refinement Parameters:" << std::endl;
    oss << std::setw(30) << "  stopping rule: " << config.two_way_fm.stopping_rule << std::endl;
    oss << std::setw(30) << "  max. # repetitions: " << config.two_way_fm.num_repetitions << std::endl;
    oss << std::setw(30) << "  max. # fruitless moves: "
    << config.two_way_fm.max_number_of_fruitless_moves << std::endl;
    oss << std::setw(30) << "  random walk stop alpha: "
    << config.two_way_fm.alpha << std::endl;
    oss << std::setw(30) << "  random walk stop beta : "
    << config.two_way_fm.beta << std::endl;
  }
  if (config.her_fm.active) {
    oss << "HER-FM Refinement Parameters:" << std::endl;
    oss << std::setw(30) << "  stopping rule: " << config.her_fm.stopping_rule << std::endl;
    oss << std::setw(30) << "  max. # repetitions: " << config.her_fm.num_repetitions << std::endl;
    oss << std::setw(30) << "  max. # fruitless moves: "
    << config.her_fm.max_number_of_fruitless_moves << std::endl;
  }
  return oss.str();
}
} // namespace partition

#endif  // SRC_PARTITION_CONFIGURATION_H_
