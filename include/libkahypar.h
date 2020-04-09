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

#ifndef LIBKAHYPAR_H
#define LIBKAHYPAR_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KAHYPAR_API
#  ifdef _WIN32
#     if defined(KAHYPAR_BUILD_SHARED)  /* build dll */
#         define KAHYPAR_API __declspec(dllexport)
#     elif !defined(KAHYPAR_BUILD_STATIC)  /* use dll */
#         define KAHYPAR_API __declspec(dllimport)
#     else  /* static library */
#         define KAHYPAR_API
#     endif
#  else
#     if __GNUC__ >= 4
#         define KAHYPAR_API __attribute__ ((visibility("default")))
#     else
#         define KAHYPAR_API
#     endif
#  endif
#endif

struct kahypar_context_s;
typedef struct kahypar_context_s kahypar_context_t;

typedef unsigned int kahypar_hypernode_id_t;
typedef unsigned int kahypar_hyperedge_id_t;
typedef int kahypar_hypernode_weight_t;
typedef int kahypar_hyperedge_weight_t;
typedef unsigned int kahypar_partition_id_t;

KAHYPAR_API kahypar_context_t* kahypar_context_new();
KAHYPAR_API void kahypar_context_free(kahypar_context_t* kahypar_context);

KAHYPAR_API void kahypar_set_custom_target_block_weights(const kahypar_partition_id_t num_blocks,
                                                         const kahypar_hypernode_weight_t* block_weights,
                                                         kahypar_context_t* kahypar_context);

KAHYPAR_API void kahypar_read_hypergraph_from_file(const char* file_name,
                                                   kahypar_hypernode_id_t* num_vertices,
                                                   kahypar_hyperedge_id_t* num_hyperedges,
                                                   size_t** hyperedge_indices,
                                                   kahypar_hyperedge_id_t** hyperedges,
                                                   kahypar_hyperedge_weight_t** hyperedge_weights,
                                                   kahypar_hypernode_weight_t** vertex_weights);

KAHYPAR_API void kahypar_partition(const kahypar_hypernode_id_t num_vertices,
                                   const kahypar_hyperedge_id_t num_hyperedges,
                                   const double epsilon,
                                   const kahypar_partition_id_t num_blocks,
                                   const kahypar_hypernode_weight_t* vertex_weights,
                                   const kahypar_hyperedge_weight_t* hyperedge_weights,
                                   const size_t* hyperedge_indices,
                                   const kahypar_hyperedge_id_t* hyperedges,
                                   kahypar_hyperedge_weight_t* objective,
                                   kahypar_context_t* kahypar_context,
                                   kahypar_partition_id_t* partition);


KAHYPAR_API void kahypar_improve_partition(const kahypar_hypernode_id_t num_vertices,
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
                                           kahypar_partition_id_t* improved_partition);

KAHYPAR_API void kahypar_set_context_partition_mode(kahypar_context_t* kahypar_context,
						    const char* mode);


KAHYPAR_API void kahypar_set_context_verbose_output(kahypar_context_t* kahypar_context,
						    bool verbose_output);
  

KAHYPAR_API void kahypar_set_context_partition_objective(kahypar_context_t* kahypar_context,
							 const char* s);

KAHYPAR_API void kahypar_set_context_partition_k(kahypar_context_t* kahypar_context,
						 kahypar_partition_id_t k);

KAHYPAR_API void kahypar_set_context_partition_seed(kahypar_context_t* kahypar_context,
						    int seed);

KAHYPAR_API void kahypar_set_context_partition_global_search_iterations(kahypar_context_t* kahypar_context,
									uint32_t global_search_iterations);

KAHYPAR_API void kahypar_set_context_partition_time_limit(kahypar_context_t* kahypar_context,
							  int time_limit);

KAHYPAR_API void kahypar_set_context_partition_max_part_weights(kahypar_context_t* kahypar_context,
								kahypar_hypernode_weight_t* max_part_weights);

KAHYPAR_API void kahypar_set_context_partition_hyperedge_size_threshold(kahypar_context_t* kahypar_context,
									kahypar_hyperedge_id_t hyperedge_size_threshold);

KAHYPAR_API void kahypar_set_context_partition_verbose_output(kahypar_context_t* kahypar_context,
							      bool verbose_output);

KAHYPAR_API void kahypar_set_context_partition_quiet_mode(kahypar_context_t* kahypar_context,
							  bool quiet_mode);

KAHYPAR_API void kahypar_set_context_partition_sp_process_output(kahypar_context_t* kahypar_context,
								 bool sp_process_output);

KAHYPAR_API void kahypar_set_context_partition_use_individual_part_weights(kahypar_context_t* kahypar_context,
									   bool use_individual_part_weights);

KAHYPAR_API void kahypar_set_context_partition_graph_filename(kahypar_context_t* kahypar_context,
							      const char* graph_filename);

KAHYPAR_API void kahypar_set_context_partition_fixed_vertex_filename(kahypar_context_t* kahypar_context,
								     const char* fixed_vertex_filename);

KAHYPAR_API void kahypar_set_context_partition_input_partition_filename(kahypar_context_t* kahypar_context,
									const char* input_partition_filename);

KAHYPAR_API void kahypar_set_context_preprocessing_enable_min_hash_sparsifier(kahypar_context_t* kahypar_context,
									      bool enable_min_hash_sparsifier);

KAHYPAR_API void kahypar_set_context_preprocessing_enable_community_detection(kahypar_context_t* kahypar_context,
									      bool enable_community_detection);

KAHYPAR_API void kahypar_set_context_preprocessing_enable_deduplication(kahypar_context_t* kahypar_context,
									bool enable_deduplication);

KAHYPAR_API void kahypar_set_context_preprocessing_min_hash_sparsifier_max_hyperedge_size(kahypar_context_t* kahypar_context,
											  uint32_t max_hyperedge_size);

KAHYPAR_API void kahypar_set_context_preprocessing_min_hash_sparsifier_max_cluster_size(kahypar_context_t* kahypar_context,
											uint32_t max_cluster_size);

KAHYPAR_API void kahypar_set_context_preprocessing_min_hash_sparsifier_min_cluster_size(kahypar_context_t* kahypar_context,
											uint32_t min_cluster_size);

KAHYPAR_API void kahypar_set_context_preprocessing_min_hash_sparsifier_num_hash_functions(kahypar_context_t* kahypar_context,
											  uint32_t num_hash_functions);

KAHYPAR_API void kahypar_set_context_preprocessing_min_hash_sparsifier_combined_num_hash_functions(kahypar_context_t* kahypar_context,
												   uint32_t combined_num_hash_functions);

KAHYPAR_API void kahypar_set_context_preprocessing_min_hash_sparsifier_min_median_he_size(kahypar_context_t* kahypar_context,
											  kahypar_hypernode_id_t min_median_he_size);

KAHYPAR_API void kahypar_set_context_preprocessing_community_detection_enable_in_initial_partitioning(kahypar_context_t* kahypar_context,
												      bool enable_in_initial_partitioning);

KAHYPAR_API void kahypar_set_context_preprocessing_community_detection_reuse_communities(kahypar_context_t* kahypar_context,
											 bool reuse_communities);

KAHYPAR_API void kahypar_set_context_preprocessing_community_detection_edge_weight(kahypar_context_t* kahypar_context,
										   const char* edge_weight);

KAHYPAR_API void kahypar_set_context_preprocessing_community_detection_max_pass_iterations(kahypar_context_t* kahypar_context,
											   uint32_t max_pass_iterations);

KAHYPAR_API void kahypar_set_context_preprocessing_community_detection_min_eps_improvement(kahypar_context_t* kahypar_context,
											   double min_eps_improvement);

KAHYPAR_API void kahypar_set_context_coarsening_algorithm(kahypar_context_t* kahypar_context,
							  const char* ctype);

KAHYPAR_API void kahypar_set_context_coarsening_contraction_limit_multiplier(kahypar_context_t* kahypar_context,
									     kahypar_hypernode_id_t contraction_limit_multiplier);

KAHYPAR_API void kahypar_set_context_coarsening_max_allowed_weight_multiplier(kahypar_context_t* kahypar_context,
									      double max_allowed_weight_multiplier);

KAHYPAR_API void kahypar_set_context_coarsening_RP_rating_function(kahypar_context_t* kahypar_context,
								   const char* rating_score);

KAHYPAR_API void kahypar_set_context_coarsening_RP_community_policy(kahypar_context_t* kahypar_context,
								    bool use_communities);

KAHYPAR_API void kahypar_set_context_coarsening_RP_heavy_node_policy(kahypar_context_t* kahypar_context,
								     const char* penalty);

KAHYPAR_API void kahypar_set_context_coarsening_RP_acceptance_policy(kahypar_context_t* kahypar_context,
								     const char* crit);

KAHYPAR_API void kahypar_set_context_coarsening_RP_fixed_vertex_acceptance_policy(kahypar_context_t* kahypar_context,
										  const char* crit);

KAHYPAR_API void kahypar_set_context_local_search_algorithm(kahypar_context_t* kahypar_context,
							    const char* rtype);

KAHYPAR_API void kahypar_set_context_local_search_iterations_per_level(kahypar_context_t* kahypar_context,
								       int iterations_per_level);

KAHYPAR_API void kahypar_set_context_local_search_fm_max_number_of_fruitless_moves(kahypar_context_t* kahypar_context,
										   uint32_t max_number_of_fruitless_moves);

KAHYPAR_API void kahypar_set_context_local_search_fm_adaptive_stopping_alpha(kahypar_context_t* kahypar_context,
									     double adaptive_stopping_alpha);

KAHYPAR_API void kahypar_set_context_local_search_fm_stopping_rule(kahypar_context_t* kahypar_context,
								   const char* stopfm);

KAHYPAR_API void kahypar_set_context_local_search_flow_algorithm(kahypar_context_t* kahypar_context,
								 const char* ftype);

KAHYPAR_API void kahypar_set_context_local_search_flow_network(kahypar_context_t* kahypar_context,
							       const char* ftype);

KAHYPAR_API void kahypar_set_context_local_search_execution_policy(kahypar_context_t* kahypar_context,
								   const char* ftype);

KAHYPAR_API void kahypar_set_context_local_search_flow_alpha(kahypar_context_t* kahypar_context,
							     double alpha);

KAHYPAR_API void kahypar_set_context_local_search_flow_beta(kahypar_context_t* kahypar_context,
							    size_t beta);
  
KAHYPAR_API void kahypar_set_context_local_search_flow_use_most_balanced_minimum_cut(kahypar_context_t* kahypar_context,
										     bool use_most_balanced_minimum_cut);

KAHYPAR_API void kahypar_set_context_local_search_flow_use_adaptive_alpha_stopping_rule(kahypar_context_t* kahypar_context,
											bool use_adaptive_alpha_stopping_rule);

KAHYPAR_API void kahypar_set_context_local_search_flow_ignore_small_hyperedge_cut(kahypar_context_t* kahypar_context,
										  bool ignore_small_hyperedge_cut);

KAHYPAR_API void kahypar_set_context_local_search_flow_use_improvement_history(kahypar_context_t* kahypar_context,
									       bool use_improvement_history);

KAHYPAR_API void kahypar_set_context_initial_partitioning_mode(kahypar_context_t* kahypar_context,
							       const char* ip_mode);

KAHYPAR_API void kahypar_set_context_initial_partitioning_verbose_output(kahypar_context_t* kahypar_context,
									 bool verbose_output);
  
KAHYPAR_API void kahypar_set_context_initial_partitioning_technique(kahypar_context_t* kahypar_context,
								    const char* ip_technique);

KAHYPAR_API void kahypar_set_context_initial_partitioning_algo(kahypar_context_t* kahypar_context,
							       const char* ip_algo);

KAHYPAR_API void kahypar_set_context_initial_partitioning_nruns(kahypar_context_t* kahypar_context,
								uint32_t nruns);

KAHYPAR_API void kahypar_set_context_initial_partitioning_verbose_output(kahypar_context_t* kahypar_context,
									 bool verbose_output);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_algorithm(kahypar_context_t* kahypar_context,
									       const char* ctype);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_contraction_limit_multiplier(kahypar_context_t* kahypar_context,
												  kahypar_hypernode_id_t contraction_limit_multiplier);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_max_allowed_weight_multiplier(kahypar_context_t* kahypar_context,
												   double max_allowed_weight_multiplier);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_RP_rating_function(kahypar_context_t* kahypar_context,
											const char* rating_score);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_RP_community_policy(kahypar_context_t* kahypar_context,
											 bool use_communities);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_RP_heavy_node_policy(kahypar_context_t* kahypar_context,
											  const char* penalty);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_RP_acceptance_policy(kahypar_context_t* kahypar_context,
											  const char* crit);

KAHYPAR_API void kahypar_set_context_initial_partitioning_coarsening_RP_fixed_vertex_acceptance_policy(kahypar_context_t* kahypar_context,
												       const char* crit);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_algorithm(kahypar_context_t* kahypar_context,
										 const char* rtype);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_iterations_per_level(kahypar_context_t* kahypar_context,
											    int iterations_per_level);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_fm_max_number_of_fruitless_moves(kahypar_context_t* kahypar_context,
													uint32_t max_number_of_fruitless_moves);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_fm_adaptive_stopping_alpha(kahypar_context_t* kahypar_context,
												  double adaptive_stopping_alpha);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_fm_stopping_rule(kahypar_context_t* kahypar_context,
											const char* stopfm);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_flow_algorithm(kahypar_context_t* kahypar_context,
										      const char* ftype);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_flow_network(kahypar_context_t* kahypar_context,
										    const char* ftype);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_execution_policy(kahypar_context_t* kahypar_context,
											const char* ftype);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_flow_alpha(kahypar_context_t* kahypar_context,
										  double alpha);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_flow_beta(kahypar_context_t* kahypar_context,
										 size_t beta);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_flow_use_most_balanced_minimum_cut(kahypar_context_t* kahypar_context,
													  bool use_most_balanced_minimum_cut);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_flow_use_adaptive_alpha_stopping_rule(kahypar_context_t* kahypar_context,
													     bool use_adaptive_alpha_stopping_rule);

KAHYPAR_API void kahypar_set_context_initial_partitioning_local_search_flow_ignore_small_hyperedge_cut(kahypar_context_t* kahypar_context,
												       bool ignore_small_hyperedge_cut);
  
#ifdef __cplusplus
}
#endif

#endif    // LIBKAHYPAR_H
