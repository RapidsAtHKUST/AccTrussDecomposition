from config import *
import os

if __name__ == '__main__':
    config_dict = get_config_dict(gpu23_tag, '..')
    mount_dir = os.sep.join([config_dict[exp_res_root_mount_path_tag], 'exp-03-11-study-tri-cnt-deg'])
    data_set_lst = config_dict[data_set_lst_tag]
    tri_exec_lst = config_dict[triangle_exec_lst_tag]

    print(mount_dir, data_set_lst, tri_exec_lst)
    # print os.sep.join([mount_dir, ])
    reorder_method_lst = ['gro', 'org', 'deg', 'kcore']
    for data_set in data_set_lst:
        file_dir = os.sep.join([mount_dir, data_set, '40'])
        for exec_name in tri_exec_lst:
            file_path = os.sep.join([file_dir, exec_name + '.txt'])
            print(file_path)

            if os.path.exists(file_path):
                with open(file_path) as ifs:
                    num = 0
                    splitter_line_num = [0]
                    lines = ifs.readlines()
                    for i in range(len(lines)):
                        if 'is_time_out' in lines[i]:
                            splitter_line_num.append(i + 1)
                            num += 1

                    assert len(splitter_line_num) <= 5
                    if len(splitter_line_num) == 5:
                        for i in range(4):
                            ofs_lines = lines[splitter_line_num[i]:splitter_line_num[i + 1]]
                            l_file_dir = os.sep.join(
                                [mount_dir, data_set, reorder_method_lst[i], '40'])
                            os.system('mkdir -p ' + l_file_dir)
                            ofs_path = os.sep.join([l_file_dir, exec_name + '.txt'])
                            with open(ofs_path, 'w') as ofs:
                                ofs.write('\n'.join(ofs_lines))
                    else:
                        print(file_path, 'not full file yet')
            else:
                print(file_path, 'not exist')
