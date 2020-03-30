```python
                # generate_md_table_from_lines(hostname.upper() + '-Ratio', lines_ratio)
                # generate_md_table_from_lines(hostname.upper() + '-Speedup', lines_speedup)

                    # t_num = str(max(map(int, filter(lambda e: e != '56' and e != '52', t_lst))))


lines_ratio = [
            ['Dataset'] + [tag.replace('Time', 'Ratio').replace('time', 'Ratio') for tag in tag_lst],
            ['---' for _ in range(len(tag_lst) + 1)]]
        lines_speedup = [
            ['Dataset'] + [tag.replace('Time', 'Speedup').replace('time', 'Speedup') for tag in tag_lst],
            ['---' for _ in range(len(tag_lst) + 1)]]

 lines_ratio.append([data_names[data_set]] + [
                format_str(100 * time / time_lst[-1]) if len(filter(lambda x: x is None, time_lst)) == 0 \
                    else None for time in time_lst])
            lines_speedup.append(
                [data_names[data_set]] + [data_dict[data_set][t_num][speedup_tag][k] for k in tag_lst])
```