"""
Some more interesting for loops
"""

if __name__ == "__main__":


    first_list = [1,2,3,4,5]
    second_list = [6,7,8,9,10]
    third_list = [11,12,13,14,15]
    fourth_list = [16,17,18,19,20]
    fifth_list = [21,22,23,24,25]

    my_total_list = [first_list, second_list, third_list, fourth_list, fifth_list]

    for element in my_total_list:
        print(element)

    for row in my_total_list:
        for element_in_row in row:
            print(element_in_row, end=" ")
    print()

    #This was a lot of work to make a list in chunks of 5 up to 25, can we do this better?

    #Enter the list comprehension

    my_first_list_com = [element for element in range(1, 6)]
    print("The value held by my_first_list_com:", my_first_list_com)

    my_list_of_lists_from_comp = [ [element for element in range(i, i+5)] for i in range(1,22,5)]
    print("The comprehension of lists is :", my_list_of_lists_from_comp)

    for row in my_list_of_lists_from_comp:
        for element_in_row in row:
            print(element_in_row, end=" ")
    print()