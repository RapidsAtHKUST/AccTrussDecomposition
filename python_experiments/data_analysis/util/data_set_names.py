data_set_names = {
    "webgraph_webbase": "WB",
    "webgraph_it": "WI",
    "webgraph_twitter": "TW",
    "snap_friendster": "FR",
    "snap_livejournal": "LJ",
    "snap_orkut": "OR",
    "webgraph_eu": "WE",
    "webgraph_uk": "WU"
}


def get_data_set_name(name):
    if name in data_set_names:
        return data_set_names[name]
    else:
        return name
