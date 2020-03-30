from data_analysis.util.read_file_utils import *
from config import *


def generate_statistics(platform_tag):
    config_dict = get_config_dict(platform_tag, '../..')
    json_file_dir = '../data-json/' + platform_tag
    md_file_dir = '../data-md/' + platform_tag

    root_dir = config_dict[exp_res_root_mount_path_tag] + os.sep + 'edge-list-to-csr-performance'
    json_file_name = '09_03_edge-list-to-csr-performance.json'
    md_file_name = '09_03_edge-list-to-csr-performance.md'

    def fetch_data_to_json():
        os.system('mkdir -p ' + json_file_dir)

        my_dict = {}
        for data_set in config_dict[data_set_lst_tag]:
            # data_set = data_set + os.sep + rabbit_order_tag

            my_dict[data_set] = {}
            for algorithm in config_dict[to_csr_exec_lst_tag]:
                test_file_path = os.sep.join([root_dir, data_set, normal_no_reorder_tag, algorithm + '.txt'])
                my_dict[data_set][algorithm] = get_edge_lst_to_csr_time_info(test_file_path)

        with open(os.sep.join([json_file_dir, json_file_name]), 'w') as ofs:
            ofs.write(json.dumps(my_dict, indent=4))

    def convert_json_to_md():
        with open(os.sep.join([json_file_dir, json_file_name])) as ifs:
            my_dict = json.load(ifs)
        lines = ['# Edge List to CSR Time', '\n\nUnit: seconds']
        # lines.append('\n\n## varying num of threads')

        for data_set in config_dict[data_set_lst_tag]:
            # data_set = data_set + os.sep + rabbit_order_tag
            lines.extend(['\n\n### ' + data_set + '\n',
                          ' | '.join(['exec-name'] + edge_lst_to_csr_time_tag_lst),
                          ' | '.join(['---' for _ in range(len(edge_lst_to_csr_time_tag_lst) + 1)]), ])
            for exec_name in config_dict[to_csr_exec_lst_tag]:
                lines.append(' | '.join(
                    [exec_name] + list(map(lambda tag: str(my_dict[data_set][exec_name][tag]),
                                           edge_lst_to_csr_time_tag_lst))))

        os.system('mkdir -p ' + md_file_dir)
        with open(os.sep.join([md_file_dir, md_file_name]), 'w') as ofs:
            ofs.write('\n'.join(lines))

    fetch_data_to_json()
    convert_json_to_md()


if __name__ == '__main__':
    generate_statistics(platform_tag=lccpu12_tag)
    generate_statistics(platform_tag=knl_tag)
