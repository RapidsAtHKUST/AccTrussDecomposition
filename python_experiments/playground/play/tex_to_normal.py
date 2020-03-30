if __name__ == '__main__':
    with open('tmp.txt') as ifs:
        lines = [
            l.lstrip().replace('\item', '(1)').replace('\\begin{inparaenum}[(1)]', '').
                replace('\end{inparaenum}', '')
            # .replace('$', '')
            for l in ifs.readlines()]
        line = '\n'.join(lines)
        new_line = line.replace('\n', ' ')
        max_space_num = 5
        for i in range(max_space_num):
            new_line = new_line.replace('  ', ' ')
        with open('tmp_out.txt', 'w') as ofs:
            ofs.write(new_line)
