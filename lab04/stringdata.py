import time


def get_data() -> tuple:
    string_data_set = ["."] * (26**5)
    temp_set = [".", ".", ".", ".", "."]
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    index = 0
    for i in range(len(alphabet)):
        temp_set[4] = alphabet[i]
        for j in range(len(alphabet)):
            temp_set[3] = alphabet[j]
            for k in range(len(alphabet)):
                temp_set[2] = alphabet[k]
                for l in range(len(alphabet)):
                    temp_set[1] = alphabet[l]
                    for m in range(len(alphabet)):
                        temp_set[0] = alphabet[m]
                        string_data_set[index] = (temp_set[0] + temp_set[1] + temp_set[2] + temp_set[3] + temp_set[4])
                        index += 1
    string_data_set.sort()
    string_data_tuple = tuple(string_data_set)
    return string_data_tuple


def main():
    string_data = get_data()


if __name__ == '__main__':
    main()
