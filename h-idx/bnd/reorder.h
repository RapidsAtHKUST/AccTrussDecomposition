#pragma once


template<typename VtxType>
void Preprocess(vector<vector<VtxType> > &left_partition, vector<vector<VtxType>> &right_partition) {
    vector<VtxType> relabel(left_partition.size());

    for (uint32_t i = 0; i < relabel.size(); ++i) {
        relabel[i] = i;
    }
    cout << "Sort based on degree." << endl;
    sort(relabel.begin(), relabel.end(), [&left_partition](const unsigned int left, const unsigned int right) -> bool {
        size_t left_degree = left_partition[left].size();
        size_t right_degree = left_partition[right].size();

        if (left_degree < right_degree) {
            return false;
        } else if (left_degree == right_degree) {
            return left < right;
        } else {
            return true;
        }
    });

    cout << "Relabel vertices." << endl;
    vector<VtxType> newlabel(relabel.size());

    for (uint32_t i = 0; i < newlabel.size(); ++i) {
        newlabel[relabel[i]] = i;
    }

    vector<vector<VtxType>> new_vec(left_partition.size());

    for (uint32_t i = 0; i < left_partition.size(); ++i) {
        uint32_t new_label = newlabel[i];
        new_vec[new_label].swap(left_partition[i]);
    }

    for (uint32_t i = 0; i < right_partition.size(); ++i) {
        for (uint32_t j = 0; j < right_partition[i].size(); ++j) {
            right_partition[i][j] = newlabel[right_partition[i][j]];
        }
    }

#ifdef DEBUG
    for (uint32_t i = 0; i < left_partition.size(); ++i) {
        uint32_t new_label = newlabel[i];
        for (uint32_t j = 0; j < left_partition[i].size(); ++j) {
            if (new_vec[new_label][j] != left_partition[i][j]) {
                cout << "Error" << endl;
                exit(-1);
            }
        }
    }
#endif

    cout << "Reorder vertices." << endl;
    for (auto &row: new_vec) { sort(begin(row), end(row)); }
    for (auto &row: right_partition) { sort(begin(row), end(row)); }

    left_partition.swap(new_vec);
}