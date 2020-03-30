import json


def load_data_sets(relative_path='local_config'):
    with open('{}/data_sets.json'.format(relative_path)) as ifs:
        return json.load(ifs)
