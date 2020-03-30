## Experimental Results

* Export the python module search path `export PYTHONPATH=$(pwd)`, 
supposing the current path as the working directory path
* Run experiments: see [run_experiments](run_experiments), working dir should be the current dir
* Result parsing scripts: see [data_analysis](data_analysis)

## Dataset Directory Tree / Statistics

Dataset | V |  E | d | max-d | DODG-max-d 
--- | --- | --- | --- | --- | --- 
s19-16 | `524,288` | `7,741,115` (TC: `188,045,046`) |
s20-16 | `1,048,575` | `15,700,698` (TC: `423,655,469`) |
s21-16 | `2,097,151` | `31,767,000` (TC: `949,568,516`) |
s22-16 | `4,194,304` | `64,153,931` (TC: `2,111,612,199`) |
s23-16 | `8,388,606` | `129,335,179` (TC: `4,667,881,015`) |
s24-16 | `16,777,216` | `260,379,286` (TC: `10,283,746,484`) |
livejournal (LJ)  |  `4,036,538`  |  `34,681,189`  |  `17.2`  |  `14,815`  | `527` 
orkut (OR)   | `3,072,627`  |  `117,185,083`  |  `76.3`  |  `33,312` | `535` 
web-uk (WU)    | `18,520,343` | `150,568,277` | `16.3` | `169,382` | `943` 
web-eu (WE)   |  `11,264,052` | `191,414,391` | `34.0` | `183,591`  | `9,666` 
webbase (WB)  |  `118,142,143`  |  `525,013,368` |  `8.9`  |  `803,138` |   `1,225` 
web-it  (WI)  |  `41,291,083`  |  `583,044,292`  |  `28.2`  |  `1,243,927` | `3,212` 
twitter  (TW)  |  `41,652,230`  |  `684,500,375` |  `32.9`  |  `1,405,985`  | `3,317` 
friendster (FR)  |  `124,836,180`  |  `1,806,067,135` |  `28.9`  |  `5,214`  | `868`  
rmat_v0.5m_e0.5g |  `500,000` | `499,999,971` | `2000` | `4,936` | `192,655`
rmat_v5m_e0.5g  | `4,999,986` | `500,000,000` | `200` | `769` | `94,431`
rmat_v50m_e0.5g | `49,999,953` | `500,000,000 ` | `20` | `136` | `29,271`
rmat_v1m_e1g    | `1,000,000` | `999,999,986` | `2000` | `5,547` | `304,492` 
rmat_v10m_e1g   | `9,999,998` | `1,000,000,000` | `200` | `806` | `125,362`
rmat_v100m_e1g  | `99,999,795` | `1,000,000,000` | `20` | `141` | `41,197`
rmat_v2m_e2g | `1,999,997` | `1,999,999,989` | `2000` | `6,089` | `458,951`
rmat_v20m_e2g | `19,999,972` | `2,000,000,000` | `200` | `1,391` | `172,735`
rmat_v200m_e2g | `199,999,407` | `2000,000,000` | `20` | `155` | `53,954`

Dataset | DODG-max-d | TC | MC | CoreVal | TrussVal
--- | --- | --- | --- | --- | --- 
livejournal (LJ)  | `527` | `177,820,130` | `327` | `360` | `352`
orkut (OR)   | `535` |  `627,584,181` | `51` | `253` | `78`
web-uk (WU)  | `943` | `2,219,257,972` | `944` | `943` | `944`
web-eu (WE)  | `9,666` | `340,972,167,210` | `9,667` | `9,666` | `9,667` 
webbase (WB)  | `1,225` | `6,931,658,967` | `1,226` | `1,225` | `1,226`
web-it  (WI)  | `3,212` | `24,382,942,061` | `3,210` | `3,209` | `3,210`
twitter  (TW)  | `3,317` | `23,871,588,549` | `364` | `2,059` | `1,517`
friendster (FR) | `868`  | `4,173,724,142` | `129` | `304` | `129`
rmat_v0.5m_e0.5g |  `4,936` | `171,681,167,254` | `373` | `4,228` | `2,138`
rmat_v5m_e0.5g  | `769` | `1,705,342,424` | `30` | `627` | `99`
rmat_v50m_e0.5g | `136` | `6,127,241` | `5` | `84` | `5`
rmat_v1m_e1g   | `5,547` | `305,445,659,482` | `367` | `4,835` | `2,322`
rmat_v10m_e1g  | `806` | `2,288,408,709` | `19` | `679` | `86`
rmat_v100m_e1g  | `141` | `9,394,872` | `5` | `94` | `5`
rmat_v2m_e2g | `6,089` | `495,273,096,725` | `316` | `5,771` | `2,502`
rmat_v20m_e2g  | `1,391` | `3,341,193,251` | `19` | `773` | `78`
rmat_v200m_e2g | `155` | `12,665,950` | `4` | `104` | `5` 

Dataset | 4 | 5 | 6 | 7 | 8 | 9
--- | --- | --- | --- | --- | --- | --- 
LJ  | `5,216,918,441` |  ` 246,378,629,120` | `10,990,740,312,954`
OR   | `3,221,946,137` | ` 15,766,607,860` | `75,249,427,585` | `353,962,921,685` |  ` 1,632,691,821,296` | `7,248,102,160,867`
WU | `107,386,384,124` | `11,575,113,391,749` |
WE  | 
WB | `781,028,274,064` 
WI  | `7,510,704,698,598`
TW  | `3,629,832,195,348` | 
FR | `8,963,503,263` | `21,710,817,218` | ` 59,926,510,355` | 

## Maximum Clique (Lijun's State-of-the-art-seq-method)

* On the TW

```
./MC-BRB MC-BRB /ssd/zlai/yche-datasets/datasets/datasets/webgraph_twitter                                                                   ✔  8875  14:32:58
**** MaxClique (Debug) build at 14:18:13 Jan  2 2020 ***
**** Alg: MC-BRB, Graph: /ssd/zlai/yche-datasets/datasets/datasets/webgraph_twitter ***
**** W/ kernelization, W/ recolor,  ***
        start reading graph
        n = 41,652,230; m = 684,500,375 (undirected)
        *** Finished reading graph
*** Heuristic clique size: 13, time: 10,030,878 (microseconds)
*** Degeneracy clique size: 123, max_core: 2059, Time: 30,275,572 (microseconds)
        Reduced graph size: |V|=789,397, |E|=258,683,010 (undirected)
*** ego_degen clique size: 362, UB: 505, Time: 598,279,580 (microseconds)
        MC-EGO Time: 648,973,891
degree_one_two_three_with_folding finds clique of size: 363                                                                                                                                                        
greedy_extend finds clique of size: 364                                                                                                                                                                            
Number of matrix constructed: 3,038
Average density: 0.8737, min density: 0.7655, average kernel_effect: 0.1682
Number of egos searched: 3,038, branches: 17,132,171
Average ego_density: 0.8737, min ego_density: 0.7655
        Maximum Clique Size: 364, Max Depth: 3, Total Time: 140,204,901,374

```
