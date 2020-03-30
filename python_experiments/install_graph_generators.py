import os, sys
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger(__name__)


def system_wrapper(cmd):
    logger.info('cmd: {}'.format(cmd))
    os.system(cmd)


def build_cmake_project(workspace_path, git_link, install_path):
    os.chdir(workspace_path)
    system_wrapper('git clone {}'.format(git_link))
    project_name = git_link.split('/')[-1].replace('.git', '')

    build_dir_name = 'build-{}'.format(project_name)
    build_dir_path = '{}/{}'.format(workspace_path, build_dir_name)
    logger.info(project_name)
    logger.info(build_dir_path)

    system_wrapper('rm -rf {}'.format(build_dir_path))
    system_wrapper('mkdir -p {}'.format(build_dir_path))

    os.chdir(build_dir_path)
    system_wrapper('cmake -H{}/{} -B{} -DCMAKE_INSTALL_PREFIX={}'.format(
        workspace_path, project_name, build_dir_path, install_path))
    system_wrapper('make -j')
    system_wrapper('make install')


if __name__ == '__main__':
    workspace_path = os.path.abspath('./workspace')
    system_wrapper('mkdir -p {}'.format(workspace_path))

    install_dir = sys.argv[1] if len(sys.argv) >= 2 else './{}'.format(workspace_path)
    build_cmake_project(workspace_path, 'https://github.com/RapidsAtHKUST/GTGraphFork.git', install_dir)
    build_cmake_project(workspace_path, 'https://github.com/RapidsAtHKUST/KroneckerBinEdgeListToCSR.git', install_dir)
    build_cmake_project(workspace_path, 'https://github.com/RapidsAtHKUST/Graph500KroneckerGraphGenerator.git',
                        install_dir)
