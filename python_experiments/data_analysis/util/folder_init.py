import os


def init_folder_md_json_file(relative_path, hostname, filename):
    md_dir = '{}/data-md/{}'.format(relative_path, hostname)
    json_dir = '{}/data-json/{}'.format(relative_path, hostname)

    os.system('mkdir -p {}'.format(json_dir))
    os.system('mkdir -p {}'.format(md_dir))
    file_path_app = '{}/data-md/{}/{}'.format(relative_path, hostname, filename)
    os.system('rm ' + file_path_app)
    return file_path_app
