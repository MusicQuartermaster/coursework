if __name__ == '__main__':
    with open("ratatouille_script.txt") as original:
        new = open("ratatouille_script_adjusted.txt", 'w')
        nums = open("numbers.txt", 'w')
        for line in original:
            if line[0].isdecimal() and not line[1] == ')':
                nums.write(line)
                continue
            new.write(line)
        original.close()
        new.close()
        nums.close()