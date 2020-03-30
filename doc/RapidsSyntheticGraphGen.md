## Introduction

* We provide graph generators and pre-processors (removing multi-edge and self-loops to get undirected graphs, and converting an edge list binary format into a compressed sparse row (CSR) format). 

* The related projects are as follows

Repo | Description
--- | ---
[RapidsAtHKUST/GTGraphFork.git](https://github.com/RapidsAtHKUST/GTGraphFork.git) | GT Graph Generator (3 types), Random, RMAT, Clique
[RapidsAtHKUST/Graph500KroneckerGraphGenerator.git](https://github.com/RapidsAtHKUST/Graph500KroneckerGraphGenerator.git) | Kronecker Model (RMAT) Graph
[RapidsAtHKUST/KroneckerBinEdgeListToCSR.git](https://github.com/RapidsAtHKUST/KroneckerBinEdgeListToCSR.git) |  Parallel Graph Pre-Processing and Conversion

## Install Our Software

* execute the following python3 script (`install_graph_generators.py`), assuming `cmake-3.12` and `g++` are properly installed
* on your terminal, do as follows, where `/home/yche/yche-bin` should be replaced with your local path to install the software

```zsh
python3 install_graph_generators.py /home/yche/yche-bin
```

* The `install_graph_generators.py` is as follows, which can also be found in [../python_experiments/install_graph_generators.py](../python_experiments/install_graph_generators.py).

```python
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

```

## Installed Software

The installed software is as follows, 
where `configurations` is for the GTgraph config files. 
`GTgraph` comprises three generators, `yche_generator_omp` is another rmat generator, `kron_converter` is to convert the edge list binary file into the Lijun Chang's CSR (compressed sparese row) Format. 

* `tree` results

```
├── configurations
│   ├── random-config
│   ├── random-config-template
│   ├── rmat-config
│   ├── rmat-config-template
│   ├── ssca2-config
│   └── ssca2-config-template
├── GTgraph-random-bin
├── GTgraph-rmat-bin
├── GTgraph-ssca2-bin
├── GTgraph-ssca2-with-locality-bin
├── kron_converter
└── yche_generator_omp
```

## Some Examples To Get a Binary Edge List

### SSCA Generator

* SSCA Generator generates graphs with some cliques, where the total number of edges can be estimated by `clique-size * number-of-vertices / 2`. 
* `GTgraph-ssca2-with-locality-bin` means there is no shuffling to preserve the locality of vertex IDs

* Our sample config file, important factors: `SCALE` (numer-of-vertices: `2^{SCALE}`), `MaxCliqueSize`

```
SCALE 17
# By default, TotVertices = 2^SCALE, MaxCliqueSize = floor (2^(SCALE/3.0)) and MaxWeight = 2^SCALE

# These parameters can also be set separately
MaxCliqueSize 1000

MaxParallelEdges 1

ProbIntercliqueEdges 0.5

ProbUnidirectional 0.2

MinWeight 0

# Other parameters
SORT_EDGELISTS 0

# Sorting alg. to use: 0 for counting sort (works only if TOT_VERTICES is
# less than 2^31 - 1, i.e SCALE <= 31), 1 for heap sort
SORT_TYPE 0

WRITE_TO_FILE 0
```

* Usage (with a config file and an output path)

```zsh
./GTgraph-ssca2-with-locality-bin -c ./configurations/ssca2-config -o /mnt/optane-ssd/yche/datasets/ssca2-config-s17-c1000.bin
```

### RMAT Generator

* Usage (SCALE: 24, degree: 64 (`-e 32`), binary format: `-b`, output path: `-o`)

```zsh
./yche_generator_omp 24 -e 32 -o /mnt/optane-ssd/yche/datasets/s24-32.bin -b 
```

### Convert to CSR Binary Format

```zsh
./kron_converter -f /mnt/optane-ssd/yche/datasets/ssca2-config-s17-c10000.bin -o  /mnt/optane-ssd/yche/datasets/ssca2-config-s17-c10000
```

```zsh
./kron_converter -f /mnt/optane-ssd/yche/datasets/s24-32.bin -o  /mnt/optane-ssd/yche/datasets/s24-32 
```

### CSR Format

* See [Lijun Chang's CSR Format](https://github.com/LijunChang/Cohesive_subgraph_book/tree/master/datasets)
* Check the file [https://github.com/RapidsAtHKUST/KroneckerBinEdgeListToCSR/blob/master/util/graph/graph.cpp](https://github.com/RapidsAtHKUST/KroneckerBinEdgeListToCSR/blob/master/util/graph/graph.cpp) for the detail input/output. 

### Projects Using the CSR Format

* [Lijun's Cohesive Subgraph Tutorial](https://github.com/LijunChang/Cohesive_subgraph_book)
* [Maximum Clique](https://github.com/LijunChang/MC-BRB)
* [pSCAN, sequential graph clustering](https://github.com/LijunChang/pSCAN)
* [ppSCAN, pthread-based parallel graph clustering](https://github.com/RapidsAtHKUST/ppSCAN)
* [accTC, accelerating all-edge triangle counting](https://github.com/RapidsAtHKUST/AccTriCnt)