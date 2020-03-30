from config import *


def get_config_dict_via_hostname(hostname):
    if 'ustgpu2' in hostname:
        config_tag = ustgpu2_tag
    elif 'ustgpu1' in hostname:
        config_tag = ustgpu1_tag
    elif 'gpu24' in hostname:
        config_tag = gpu24_tag
    else:
        config_tag = None
    config_dict = get_config_dict(config_tag, '../..')
    return config_dict
