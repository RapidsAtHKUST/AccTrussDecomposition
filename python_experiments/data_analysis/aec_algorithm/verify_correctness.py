from data_analysis.vis.vis_all_edge_res import *

if __name__ == '__main__':
    stat_dict = get_all_edge_cnt_dict()
    for dataset in stat_dict:
        for algorithm, single_stat_dict in stat_dict[dataset]['40'].iteritems():
            if single_stat_dict[is_time_out_tag] is False and single_stat_dict[is_correct_tag] is False:
                if single_stat_dict[output_cores_non_cores_tag] is not None:
                    print(algorithm, dataset, single_stat_dict[all_edge_cnc_comp_tag])
