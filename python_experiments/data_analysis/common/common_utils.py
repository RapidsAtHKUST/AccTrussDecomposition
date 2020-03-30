from data_analysis.util.read_file_utils import format_str


def no_body_is_none(lst):
    return len(list(filter(lambda x: x is None, lst))) == 0


def or_for_all_predicates(lst, x):
    val = False
    for functor in lst:
        val |= functor(x)
    return val


def transform(x):
    return format_str(x) if x is not None else '/'
