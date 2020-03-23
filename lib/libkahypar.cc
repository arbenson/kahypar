/*******************************************************************************
 * This file is part of KaHyPar.
 *
 * Copyright (C) 2018 Sebastian Schlag <sebastian.schlag@kit.edu>
 *
 * KaHyPar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KaHyPar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KaHyPar.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include "libkahypar.h"

#include "kahypar/io/hypergraph_io.h"
#include "kahypar/macros.h"
#include "kahypar/partition/context.h"
#include "kahypar/partitioner_facade.h"
#include "kahypar/utils/randomize.h"


// PartitioningParameters

kahypar_context_t* kahypar_context_new() {
  return reinterpret_cast<kahypar_context_t*>(new kahypar::Context());
}

void kahypar_set_context_partition_mode(kahypar_context_t* kahypar_context,
					const std::string& mode) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.partition.mode = kahypar::modeFromString(mode);
}

void kahypar_set_context_partition_objective(kahypar_context_t* kahypar_context,
					     kahypar::Objective objective) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.objective = objective;
}

void kahypar_set_context_partition_k(kahypar_context_t* kahypar_context,
				     kahypar::PartitionID k) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.k = k;
  context.partition.rb_lower_k = 0;
  context.partition.rb_lower_k = 0;  
}

void kahypar_set_context_partition_seed(kahypar_context_t* kahypar_context,
					int seed) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.seed = seed;
}

void kahypar_set_context_partition_global_search_iterations(kahypar_context_t* kahypar_context,
							    uint32_t global_search_iterations) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.global_search_iterations = global_search_iterations;
}

void kahypar_set_context_partition_time_limit(kahypar_context_t* kahypar_context,
					      int time_limit) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.time_limit = time_limit;
}

void kahypar_set_context_partition_max_part_weights(kahypar_context_t* kahypar_context,
						    std::vector<kahypar::HypernodeWeight>& max_part_weights) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.max_part_weights = max_part_weights;
}

void kahypar_set_context_partition_hyperedge_size_threshold(kahypar_context_t* kahypar_context,
							    kahypar::HyperedgeID hyperedge_size_threshold) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.partition.hyperedge_size_threshold = hyperedge_size_threshold;  
  if (hyperedge_size_threshold == -1) {
    std::numeric_limits<kahypar::HyperedgeID>::max();
  }
}

void kahypar_set_context_partition_verbose_output(kahypar_context_t* kahypar_context,
						  bool verbose_output) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.verbose_output = verbose_output;
}

void kahypar_set_context_partition_quiet_mode(kahypar_context_t* kahypar_context,
					      bool quiet_mode) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.quiet_mode = quiet_mode;
}

void kahypar_set_context_partition_sp_process_output(kahypar_context_t* kahypar_context,
						     bool sp_process_output) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.sp_process_output = sp_process_output;
}

void kahypar_set_context_partition_use_individual_part_weights(kahypar_context_t* kahypar_context,
							       bool use_individual_part_weights) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.use_individual_part_weights = use_individual_part_weights;
  if (use_individual_part_weights) {
    context.partition.epsilon = 0;
  }
}

void kahypar_set_context_partition_graph_filename(kahypar_context_t* kahypar_context,
						  const std::string& graph_filename) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.graph_filename = graph_filename;

  std::string epsilon_str = std::to_string(context.partition.epsilon);
  epsilon_str.erase(epsilon_str.find_last_not_of('0') + 1, std::string::npos);
  
  context.partition.graph_partition_filename =
    context.partition.graph_filename
    + ".part"
    + std::to_string(context.partition.k)
    + ".epsilon"
    + epsilon_str
    + ".seed"
    + std::to_string(context.partition.seed)
    + ".KaHyPar";
}

void kahypar_set_context_partition_fixed_vertex_filename(kahypar_context_t* kahypar_context,
							 const std::string& fixed_vertex_filename) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.fixed_vertex_filename = fixed_vertex_filename;
}

void kahypar_set_context_partition_input_partition_filename(kahypar_context_t* kahypar_context,
							    const std::string& input_partition_filename) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.partition.input_partition_filename = input_partition_filename;
}

void kahypar_set_context_preprocessing_enable_min_hash_sparsifier(kahypar_context_t* kahypar_context,
								  bool enable_min_hash_sparsifier) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.enable_min_hash_sparsifier = enable_min_hash_sparsifier;
}

void kahypar_set_context_preprocessing_enable_community_detection(kahypar_context_t* kahypar_context,
								  bool enable_community_detection) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.enable_community_detection = enable_community_detection;
}

void kahypar_set_context_preprocessing_enable_deduplication(kahypar_context_t* kahypar_context,
							    bool enable_deduplication) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.enable_deduplication = enable_deduplication;
}

void kahypar_set_context_preprocessing_min_hash_sparsifier_max_hyperedge_size(kahypar_context_t* kahypar_context,
									      uint32_t max_hyperedge_size) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.min_hash_sparsifier.max_hyperedge_size = max_hyperedge_size;
}

void kahypar_set_context_preprocessing_min_hash_sparsifier_max_cluster_size(kahypar_context_t* kahypar_context,
									    uint32_t max_cluster_size) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.min_hash_sparsifier.max_cluster_size = max_cluster_size;
}

void kahypar_set_context_preprocessing_min_hash_sparsifier_min_cluster_size(kahypar_context_t* kahypar_context,
									    uint32_t min_cluster_size) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.min_hash_sparsifier.min_cluster_size = min_cluster_size;
}

void kahypar_set_context_preprocessing_min_hash_sparsifier_num_hash_functions(kahypar_context_t* kahypar_context,
									      uint32_t num_hash_functions) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.min_hash_sparsifier.num_hash_functions = num_hash_functions;
}

void kahypar_set_context_preprocessing_min_hash_sparsifier_combined_num_hash_functions(kahypar_context_t* kahypar_context,
										       uint32_t combined_num_hash_functions) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.min_hash_sparsifier.combined_num_hash_functions = combined_num_hash_functions;
}

void kahypar_set_context_preprocessing_min_hash_sparsifier_min_median_he_size(kahypar_context_t* kahypar_context,
									      kahypar::HypernodeID min_median_he_size) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.min_hash_sparsifier.min_median_he_size = min_median_he_size;
}

void kahypar_set_context_preprocessing_community_detection_enable_in_initial_partitioning(kahypar_context_t* kahypar_context,
											  bool enable_in_initial_partitioning) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.community_detection.enable_in_initial_partitioning = enable_in_initial_partitioning;
}

void kahypar_set_context_preprocessing_community_detection_reuse_communities(kahypar_context_t* kahypar_context,
									     bool reuse_communities) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.community_detection.reuse_communities = reuse_communities;
}

void kahypar_set_context_preprocessing_community_detection_edge_weight(kahypar_context_t* kahypar_context,
								       const std::string& edge_weight) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.community_detection.edge_weight = kahypar::edgeWeightFromString(edge_weight);
}

void kahypar_set_context_preprocessing_community_detection_max_pass_iterations(kahypar_context_t* kahypar_context,
									       uint32_t max_pass_iterations)  {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.community_detection.max_pass_iterations = max_pass_iterations;
}

void kahypar_set_context_preprocessing_community_detection_min_eps_improvement(kahypar_context_t* kahypar_context,
									       long double min_eps_improvement) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);  
  context.preprocessing.community_detection.min_eps_improvement = min_eps_improvement;
}

// Context.CoarseningParameters
void kahypar_set_context_coarsening_algorithm(kahypar_context_t* kahypar_context,
					      const std::string& ctype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.algorithm = kahypar::coarseningAlgorithmFromString(ctype);
}

void kahypar_set_context_coarsening_contraction_limit_multiplier(kahypar_context_t* kahypar_context,
								 kahypar::HypernodeID contraction_limit_multiplier) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.contraction_limit_multiplier = contraction_limit_multiplier;
}

void kahypar_set_context_coarsening_max_allowed_weight_multiplier(kahypar_context_t* kahypar_context,
								  double max_allowed_weight_multiplier) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.max_allowed_weight_multiplier = max_allowed_weight_multiplier;
}

void kahypar_set_context_coarsening_RP_rating_function(kahypar_context_t* kahypar_context,
						       const std::string& rating_score) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.rating.rating_function = kahypar::ratingFunctionFromString(rating_score);
}

void kahypar_set_context_coarsening_RP_community_policy(kahypar_context_t* kahypar_context,
							bool use_communities) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.rating.community_policy =
          (use_communities ? kahypar::CommunityPolicy::use_communities :
           kahypar::CommunityPolicy::ignore_communities);
}

void kahypar_set_context_coarsening_RP_heavy_node_policy(kahypar_context_t* kahypar_context,
							 const std::string& penalty) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.rating.heavy_node_penalty_policy = kahypar::heavyNodePenaltyFromString(penalty);
}

void kahypar_set_context_coarsening_RP_acceptance_policy(kahypar_context_t* kahypar_context,
							 const std::string& crit) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.rating.acceptance_policy = kahypar::acceptanceCriterionFromString(crit);
}

void kahypar_set_context_coarsening_RP_fixed_vertex_acceptance_policy(kahypar_context_t* kahypar_context,
								      const std::string& crit) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.coarsening.rating.fixed_vertex_acceptance_policy = kahypar::fixedVertexAcceptanceCriterionFromString(crit);
}

// Context.LocalSearchParameters
void kahypar_set_context_local_search_algorithm(kahypar_context_t* kahypar_context,
				      const std::string& rtype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.algorithm = kahypar::refinementAlgorithmFromString(rtype);
}

void kahypar_set_context_local_search_iterations_per_level(kahypar_context_t* kahypar_context,
							   int iterations_per_level) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.iterations_per_level = iterations_per_level;
  if (context.local_search.iterations_per_level == -1) {
    context.local_search.iterations_per_level = std::numeric_limits<int>::max();
  }
}

void kahypar_set_context_local_search_fm_max_number_of_fruitless_moves(kahypar_context_t* kahypar_context,
								       uint32_t max_number_of_fruitless_moves) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.fm.max_number_of_fruitless_moves = max_number_of_fruitless_moves;
  if (context.local_search.iterations_per_level == -1) {
    context.local_search.iterations_per_level = std::numeric_limits<int>::max();
  }
}

void kahypar_set_context_local_search_fm_adaptive_stopping_alpha(kahypar_context_t* kahypar_context,
								 double adaptive_stopping_alpha) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.fm.adaptive_stopping_alpha = adaptive_stopping_alpha;
}

void kahypar_set_context_local_search_fm_stopping_rule(kahypar_context_t* kahypar_context,
						       const std::string& stopfm) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.fm.stopping_rule = kahypar::stoppingRuleFromString(stopfm);
}

void kahypar_set_context_local_search_flow_algorithm(kahypar_context_t* kahypar_context,
						     const std::string& ftype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.algorithm = kahypar::flowAlgorithmFromString(ftype);
}

void kahypar_set_context_local_search_flow_network(kahypar_context_t* kahypar_context,
						   const std::string& ftype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.network = kahypar::flowNetworkFromString(ftype);
}

void kahypar_set_context_local_search_flow_alpha(kahypar_context_t* kahypar_context,
						 double alpha) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.alpha = alpha;
}

void kahypar_set_context_local_search_flow_beta(kahypar_context_t* kahypar_context,
						size_t beta) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.beta = beta;
}

void kahypar_set_context_local_search_flow_use_most_balanced_minimum_cut(kahypar_context_t* kahypar_context,
									 bool use_most_balanced_minimum_cut) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.use_most_balanced_minimum_cut = use_most_balanced_minimum_cut;
}

void kahypar_set_context_local_search_flow_use_adaptive_alpha_stopping_rule(kahypar_context_t* kahypar_context,
									    bool use_adaptive_alpha_stopping_rule) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.use_adaptive_alpha_stopping_rule = use_adaptive_alpha_stopping_rule;
}

void kahypar_set_context_local_search_flow_ignore_small_hyperedge_cut(kahypar_context_t* kahypar_context,
								      bool ignore_small_hyperedge_cut) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.ignore_small_hyperedge_cut = ignore_small_hyperedge_cut;
}

void kahypar_set_context_local_search_flow_use_improvement_history(kahypar_context_t* kahypar_context,
								   bool use_improvement_history) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.local_search.flow.use_improvement_history = use_improvement_history;
}


// InitialPartitioningParameters
void kahypar_set_context_initial_partitioning_mode(kahypar_context_t* kahypar_context,
						   const std::string& ip_mode) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.mode = kahypar::modeFromString(ip_mode);
}

void kahypar_set_context_initial_partitioning_algo(kahypar_context_t* kahypar_context,
						   const std::string& ip_algo) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.algo = kahypar::initialPartitioningAlgorithmFromString(ip_algo);
}

void kahypar_set_context_initial_partitioning_nruns(kahypar_context_t* kahypar_context,
						    uint32_t nruns) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.nruns = nruns;
}

void kahypar_set_context_initial_partitioning_verbose_output(kahypar_context_t* kahypar_context,
							     bool verbose_output) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.verbose_output = verbose_output;
}

void kahypar_set_context_initial_partitioning_coarsening_algorithm(kahypar_context_t* kahypar_context,
								   const std::string& ctype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.algorithm = kahypar::coarseningAlgorithmFromString(ctype);
}

void kahypar_set_context_initial_partitioning_coarsening_contraction_limit_multiplier(kahypar_context_t* kahypar_context,
										      kahypar::HypernodeID contraction_limit_multiplier) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.contraction_limit_multiplier = contraction_limit_multiplier;
}

void kahypar_set_context_initial_partitioning_coarsening_max_allowed_weight_multiplier(kahypar_context_t* kahypar_context,
										       double max_allowed_weight_multiplier) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.max_allowed_weight_multiplier = max_allowed_weight_multiplier;
}

void kahypar_set_context_initial_partitioning_coarsening_RP_rating_function(kahypar_context_t* kahypar_context,
									    const std::string& rating_score) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.rating.rating_function = kahypar::ratingFunctionFromString(rating_score);
}

void kahypar_set_context_initial_partitioning_coarsening_RP_community_policy(kahypar_context_t* kahypar_context,
									     bool use_communities) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.rating.community_policy =
          (use_communities ? kahypar::CommunityPolicy::use_communities :
           kahypar::CommunityPolicy::ignore_communities);
}

void kahypar_set_context_initial_partitioning_coarsening_RP_heavy_node_policy(kahypar_context_t* kahypar_context,
									      const std::string& penalty) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.rating.heavy_node_penalty_policy = kahypar::heavyNodePenaltyFromString(penalty);
}

void kahypar_set_context_initial_partitioning_coarsening_RP_acceptance_policy(kahypar_context_t* kahypar_context,
									      const std::string& crit) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.rating.acceptance_policy = kahypar::acceptanceCriterionFromString(crit);
}

void kahypar_set_context_initial_partitioning_coarsening_RP_fixed_vertex_acceptance_policy(kahypar_context_t* kahypar_context,
											   const std::string& crit) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.coarsening.rating.fixed_vertex_acceptance_policy = kahypar::fixedVertexAcceptanceCriterionFromString(crit);
}

void kahypar_set_context_initial_partitioning_local_search_algorithm(kahypar_context_t* kahypar_context,
								     const std::string& rtype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.algorithm = kahypar::refinementAlgorithmFromString(rtype);
}

void kahypar_set_context_initial_partitioning_local_search_iterations_per_level(kahypar_context_t* kahypar_context,
										int iterations_per_level) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.iterations_per_level = iterations_per_level;
  if (context.local_search.iterations_per_level == -1) {
    context.initial_partitioning.local_search.iterations_per_level = std::numeric_limits<int>::max();
  }
}

void kahypar_set_context_initial_partitioning_local_search_fm_max_number_of_fruitless_moves(kahypar_context_t* kahypar_context,
											    uint32_t max_number_of_fruitless_moves) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.fm.max_number_of_fruitless_moves = max_number_of_fruitless_moves;
  if (context.local_search.iterations_per_level == -1) {
    context.initial_partitioning.local_search.iterations_per_level = std::numeric_limits<int>::max();
  }
}

void kahypar_set_context_initial_partitioning_local_search_fm_adaptive_stopping_alpha(kahypar_context_t* kahypar_context,
										      double adaptive_stopping_alpha) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.fm.adaptive_stopping_alpha = adaptive_stopping_alpha;
}

void kahypar_set_context_initial_partitioning_local_search_fm_stopping_rule(kahypar_context_t* kahypar_context,
									    const std::string& stopfm) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.fm.stopping_rule = kahypar::stoppingRuleFromString(stopfm);
}

void kahypar_set_context_initial_partitioning_local_search_flow_algorithm(kahypar_context_t* kahypar_context,
									  const std::string& ftype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.algorithm = kahypar::flowAlgorithmFromString(ftype);
}

void kahypar_set_context_initial_partitioning_local_search_flow_network(kahypar_context_t* kahypar_context,
									const std::string& ftype) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.network = kahypar::flowNetworkFromString(ftype);
}

void kahypar_set_context_initial_partitioning_local_search_flow_alpha(kahypar_context_t* kahypar_context,
								      double alpha) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.alpha = alpha;
}

void kahypar_set_context_initial_partitioning_local_search_flow_beta(kahypar_context_t* kahypar_context,
								     size_t beta) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.beta = beta;
}

void kahypar_set_context_initial_partitioning_local_search_flow_use_most_balanced_minimum_cut(kahypar_context_t* kahypar_context,
											      bool use_most_balanced_minimum_cut) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.use_most_balanced_minimum_cut = use_most_balanced_minimum_cut;
}

void kahypar_set_context_initial_partitioning_local_search_flow_use_adaptive_alpha_stopping_rule(kahypar_context_t* kahypar_context,
												 bool use_adaptive_alpha_stopping_rule) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.use_adaptive_alpha_stopping_rule = use_adaptive_alpha_stopping_rule;
}

void kahypar_set_context_initial_partitioning_local_search_flow_ignore_small_hyperedge_cut(kahypar_context_t* kahypar_context,
											   bool ignore_small_hyperedge_cut) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.ignore_small_hyperedge_cut = ignore_small_hyperedge_cut;
}

void kahypar_set_context_initial_partitioning_local_search_flow_use_improvement_history(kahypar_context_t* kahypar_context,
											bool use_improvement_history) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.initial_partitioning.local_search.flow.use_improvement_history = use_improvement_history;
}


void kahypar_set_custom_target_block_weights(const kahypar_partition_id_t num_blocks,
                                             const kahypar_hypernode_weight_t* block_weights,
                                             kahypar_context_t* kahypar_context) {
  ASSERT(block_weights != nullptr);

  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  context.partition.use_individual_part_weights = true;

  for (kahypar_partition_id_t i = 0; i != num_blocks; ++i) {
    context.partition.max_part_weights.push_back(block_weights[i]);
  }
}

void kahypar_context_free(kahypar_context_t* kahypar_context) {
  if (kahypar_context == nullptr) {
    return;
  }
  delete reinterpret_cast<kahypar::Context*>(kahypar_context);
}


void kahypar_read_hypergraph_from_file(const char* file_name,
                                       kahypar_hypernode_id_t* num_vertices,
                                       kahypar_hyperedge_id_t* num_hyperedges,
                                       size_t** hyperedge_indices,
                                       kahypar_hyperedge_id_t** hyperedges,
                                       kahypar_hyperedge_weight_t** hyperedge_weights,
                                       kahypar_hypernode_weight_t** vertex_weights) {
  std::unique_ptr<size_t[]> indices_ptr(nullptr);
  std::unique_ptr<kahypar_hyperedge_id_t[]> hyperedges_ptr(nullptr);

  std::unique_ptr<kahypar_hyperedge_weight_t[]> hyperedge_weights_ptr(nullptr);
  std::unique_ptr<kahypar_hypernode_weight_t[]> vertex_weights_ptr(nullptr);

  kahypar::io::readHypergraphFile(file_name, *num_vertices, *num_hyperedges,
                                  indices_ptr, hyperedges_ptr, hyperedge_weights_ptr,
                                  vertex_weights_ptr);

  *hyperedge_indices = indices_ptr.release();
  *hyperedges = hyperedges_ptr.release();
  *hyperedge_weights = hyperedge_weights_ptr.release();
  *vertex_weights = vertex_weights_ptr.release();
}


void kahypar_partition(const kahypar_hypernode_id_t num_vertices,
                       const kahypar_hyperedge_id_t num_hyperedges,
                       const double epsilon,
                       const kahypar_partition_id_t num_blocks,
                       const kahypar_hypernode_weight_t* vertex_weights,
                       const kahypar_hyperedge_weight_t* hyperedge_weights,
                       const size_t* hyperedge_indices,
                       const kahypar_hyperedge_id_t* hyperedges,
                       kahypar_hyperedge_weight_t* objective,
                       kahypar_context_t* kahypar_context,
                       kahypar_partition_id_t* partition) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  ASSERT(!context.partition.use_individual_part_weights ||
         !context.partition.max_part_weights.empty());
  ASSERT(partition != nullptr);

  context.partition.k = num_blocks;
  context.partition.epsilon = epsilon;
  context.partition.write_partition_file = false;

  kahypar::Hypergraph hypergraph(num_vertices,
                                 num_hyperedges,
                                 hyperedge_indices,
                                 hyperedges,
                                 context.partition.k,
                                 hyperedge_weights,
                                 vertex_weights);

  if (context.partition.vcycle_refinement_for_input_partition) {
    for (const auto hn : hypergraph.nodes()) {
      hypergraph.setNodePart(hn, partition[hn]);
    }
  }

  kahypar::PartitionerFacade partitioner;
  partitioner.partition(hypergraph, context);

  *objective = kahypar::metrics::correctMetric(hypergraph, context);

  for (const auto hn : hypergraph.nodes()) {
    partition[hn] = hypergraph.partID(hn);
  }

  context.partition.perfect_balance_part_weights.clear();
  context.partition.max_part_weights.clear();
  context.evolutionary.communities.clear();
}


void kahypar_improve_partition(const kahypar_hypernode_id_t num_vertices,
                               const kahypar_hyperedge_id_t num_hyperedges,
                               const double epsilon,
                               const kahypar_partition_id_t num_blocks,
                               const kahypar_hypernode_weight_t* vertex_weights,
                               const kahypar_hyperedge_weight_t* hyperedge_weights,
                               const size_t* hyperedge_indices,
                               const kahypar_hyperedge_id_t* hyperedges,
                               const kahypar_partition_id_t* input_partition,
                               const size_t num_improvement_iterations,
                               kahypar_hyperedge_weight_t* objective,
                               kahypar_context_t* kahypar_context,
                               kahypar_partition_id_t* improved_partition) {
  kahypar::Context& context = *reinterpret_cast<kahypar::Context*>(kahypar_context);
  ALWAYS_ASSERT(context.partition.mode == kahypar::Mode::direct_kway,
                "V-cycle refinement of input partitions is only possible in direct k-way mode");
  ASSERT(*std::max_element(input_partition, input_partition + num_vertices) == num_blocks - 1);
  ASSERT([&]() {
    std::unordered_set<kahypar_partition_id_t> set(input_partition, input_partition + num_vertices);
    LOG << V(set.size());
    for (kahypar_partition_id_t i = 0; i < num_blocks; ++i) {
      if (set.find(i) == set.end()) {
        return false;
      }
    }
    return true;
  } (), "Partition is corrupted.");

  // toggle v-cycle refinement
  context.partition.vcycle_refinement_for_input_partition = true;
  // perform one v-cycle
  context.partition.global_search_iterations = num_improvement_iterations;
  // sparsifier has to be disabled for v-cycle refinement
  context.preprocessing.enable_min_hash_sparsifier = false;

  // use improved_partition as temporary_input_partition
  std::memcpy(improved_partition, input_partition, num_vertices * sizeof(kahypar_partition_id_t));

  kahypar_partition(num_vertices,
                    num_hyperedges,
                    epsilon,
                    num_blocks,
                    vertex_weights,
                    hyperedge_weights,
                    hyperedge_indices,
                    hyperedges,
                    objective,
                    kahypar_context,
                    improved_partition);
}
