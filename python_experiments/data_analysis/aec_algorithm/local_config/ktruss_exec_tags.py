import json

tri_time_tag = 'Tri time'
shrink_time_tag = 'Shrink Time'
scan_time_tag = 'Scan Time'
proc_time_tag = 'Proc Time'
sync_time_tag = 'Sync Time'
total_time_tag = 'Total computation cost'
t_lst = ['1', '20', '40']
speedup_tag = 'speedup'
hyper_threading_tag = 'hyper-threading-speedup'

kernel_time_tag = 'PKT_CUDA kernel time'
prepare_cpu_time_tag = 'Prepare CPU time'
scan_cpu_time_tag = 'Scan CPU time'
shrink_cpu_time_tag = 'Shrink CPU time'
copy_cpu_time_tag = 'Copy CPU time'
sub_level_process_cpu_time_tag = 'Sub process CPU time'
set_inter_cpu_time_tag = 'Set Intersection time'
update_processed_cpu_time_tag = 'Update processed time'
offload_total_tag = 'Offloading Comp Time'
pkt_total_tag = 'Parallel K-Truss'

gpu_cpu_time_tag_lst = [pkt_total_tag, offload_total_tag, kernel_time_tag,
                        prepare_cpu_time_tag, scan_cpu_time_tag, shrink_cpu_time_tag,
                        copy_cpu_time_tag, sub_level_process_cpu_time_tag,
                        set_inter_cpu_time_tag, update_processed_cpu_time_tag]
gpu_show_time_tag_lst = [prepare_cpu_time_tag, scan_cpu_time_tag, shrink_cpu_time_tag,
                         copy_cpu_time_tag, sub_level_process_cpu_time_tag,
                         offload_total_tag, pkt_total_tag]
gpu_detail_tag_lst = [kernel_time_tag, set_inter_cpu_time_tag, update_processed_cpu_time_tag,
                      sub_level_process_cpu_time_tag]
local_tag_lst = [tri_time_tag, sync_time_tag, shrink_time_tag, scan_time_tag, proc_time_tag]
total_tag_lst = [total_time_tag]
all_tag_lst = local_tag_lst + total_tag_lst

comment_dict = {
    'pkt-inter-legacy': 'PKT-I',
    'pkt-mark-legacy-org': 'PKT-M',
    'pkt-inter-handle-skew': '+GA',
    'pkt-inter-handle-skew-vec': '+GA/Vec',
    'pkt-inter-handle-skew-vec-baselinetc': 'DODG-TC',
    'pkt-no-shrink': '+GA/Vec',
    'pkt-no-tc': '+Shrink',
    'pkt-no-incurr': '+TC',
    'pkt-no-first-last-cut': '+InCurr',
    'pkt-no-bucket': '+FirstLastOpt',
    'pkt-scan-bmp': '+SCAN-BMP',
    'pkt-inter-shrink': '+Bucket'
}


def get_comment(name):
    if name in comment_dict:
        return comment_dict[name]
    else:
        return ''


def get_data_set_names(path):
    with open('{}/datasets_names.json'.format(path)) as ifs:
        data_names = json.load(ifs)
        return data_names
