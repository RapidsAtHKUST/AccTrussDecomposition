import json
import os

local_log_dir = '/home/yche/logs/'

k_truss_exec_path_tag = 'k_truss_exec_path'
graph_stat_exec_tag = 'graph_stat_exec_tag'
karypis_k_truss_exec_path_tag = 'karypis_k_truss_exec_path'
necleus_decomp_exec_path_tag = 'necleus_decomp_exec_path'
exec_path_tag = 'our_exec_path'
exec_path_non_hbw_tag = 'our_exec_non_hbw_path'
data_set_path_tag = 'data_set_path'

lccpu12_tag = 'lccpu12'
knl_tag = 'knl'
gpu23_tag = 'gpu23'
gpu24_tag = 'gpu24'
gpu_other_tag = 'gpu-other'
hnode_79_tag = 'hnode-79'
ustgpu2_tag = 'ustgpu2'
ustgpu1_tag = 'ustgpu1'

thread_num_tag = 'thread_num'
thread_num_lst_tag = 'thread num lst'
data_set_lst_tag = 'data_set_lst'

exp_res_root_path_tag = 'exp_res_root_path'
exp_res_root_mount_path_tag = 'exp_res_root_mount_path'

triangle_exec_lst_tag = 'tri_cnt_exec_lst'
exec_lst_tag = 'exec_lst'
synthetic_exec_lst_tag = 'synthetic_exec_lst'
hash_exec_lst_tag = 'hash_exec_lst'
exec_avx512_lst_tag = 'exec_avx512_lst'
to_csr_exec_lst_tag = 'to_csr_exec_lst'

rabbit_order_tag = 'rabbit_order'
rev_deg_order_tag = 'rev_deg'
normal_no_reorder_tag = 'normal'

ppSCAN_exec_path_tag = 'ppSCAN_exec_path'
ppSCAN_input_to_edge_lst_unidr_exec_tag = 'ppSCAN_input_to_edge_lst_unidr_exec_path'
ppSCAN_input_to_edge_lst_unidr_exec_verification_tag = 'ppSCAN_input_to_edge_lst_unidr_verification_path'
rabbit_order_exec_path_tag = 'rabbit_order_exec_path'
reordering_to_ppscan_input_exec_path_tag = 'reordering_to_ppscan_input_exec_path'
edge_lst_to_csr_exec_path_tag = 'edge_lst_to_csr_exec_path'
han_order_exec_path_tag = 'han_order_exec_path'
weihao_order_exec_path_tag = 'weihao_order_exec_path'


def get_config_dict(env_tag, config_root='.'):
    with open(config_root + os.sep + 'config.json') as ifs:
        my_config_dict = json.load(ifs)[env_tag]
        return my_config_dict
