# bar_lst_lst (select column)
def statistics_select_col(lst_lst):
    assert len(lst_lst) > 0 and len(lst_lst[0]) > 0
    n_cols = len(lst_lst[0])

    def select(i):
        filtered = list(filter(lambda v: v != 0, [lst[i] for lst in lst_lst]))
        max_v, min_v = max(filtered + [-1]), min(filtered + [9999999]),
        if min_v == 9999999:
            min_v = -1
        gap = max_v / min_v

        return 'Max: %.1f\nMin: %.1f\nGap: %.1f' % (
            max_v, min_v, gap) if n_cols > 6 else 'Max: %.1f, Min: %.1f, Gap: %.1f' % (max_v, min_v, gap)

    return [select(i) for i in range(n_cols)]


def autolabel(ax, rects, fontsize=24, roration=60, amp_factor=1.05):
    """
    Attach a text label above each bar displaying its height
    """
    for rect in rects:
        height = rect.get_height()
        if height != 0:
            ax.text(rect.get_x() + rect.get_width() / 2., amp_factor * height,
                    '%.0f' % float(height) if height > 100 else
                    '%.1f' % float(height) if height > 1
                    else '%.2f' % float(height),
                    ha='center', va='bottom', fontsize=fontsize, rotation=roration)
