with open('abstract.txt') as ifs:
    paragraph = ' '.join([l.strip() for l in ifs.readlines()]).replace('$\ge$', '>=').replace('$>$', '>')
    print(paragraph)
    print(len(paragraph.split()))
