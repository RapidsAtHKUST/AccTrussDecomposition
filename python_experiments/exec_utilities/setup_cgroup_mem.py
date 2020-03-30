import os

if __name__ == '__main__':
    folder_tag = 'yche-exp'
    user_name = 'yche'
    os.system('cgdelete memory:{}'.format(folder_tag))
    os.system('cgcreate -g memory:{}'.format(folder_tag))
    os.system('chown -R {} /sys/fs/cgroup/memory/{}'.format(user_name, folder_tag))

    size = 61 * 1024 * 1024 * 1024
    os.system('echo {} | tee /sys/fs/cgroup/memory/{}/memory.limit_in_bytes'.format(size, folder_tag))
    # os.system('echo 0 > /sys/fs/cgroup/memory/{}/memory.swappiness'.format(folder_tag))
    swap_file = '/sys/fs/cgroup/memory/{}/memory.swappiness'.format(folder_tag)
    print('swap file: ', swap_file)
    os.system('echo {} | tee {}'.format(0, swap_file))

    # Check our parameters of cgroup
    os.system('cat /sys/fs/cgroup/memory/{}/memory.limit_in_bytes'.format(folder_tag))
    os.system('cat /sys/fs/cgroup/memory/{}/memory.swappiness'.format(folder_tag))
