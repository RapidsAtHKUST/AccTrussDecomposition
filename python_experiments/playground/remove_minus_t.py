if __name__ == '__main__':
    with open('change_tex.txt') as ifs:
        lines = ifs.readlines()
        for line in lines:
            if line[0] == '\t':
                print('ok')
            else:
                print('not')
                print(line)
        # print(lines[0][0]+'test')
        new_lines = [l[1:] if l[0] == '\t' else l for l in lines]
        with open('indent_text.txt', 'w') as ofs:
            ofs.writelines(new_lines)
