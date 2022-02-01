"""
This is a program to demonstrate the list type
"""

if __name__ == "__main__":
    my_first_list = [1,2,3,4,5]

    my_first_string = "hello world"

    print("The length of my list is:", len(my_first_list))
    print("The length of my string is:", len(my_first_string))
    
    print("the first item in my_first_list is:", my_first_list[0])
    print("the first item in my_first_string is:", my_first_string[0])

    my_first_tuple = (1,2,3,4,5)

    print("The length of my tuple is",len(my_first_tuple))

    # I can loop over items in the list

    for item in my_first_list:
        print(item)

    # I can loop over items and their indexes in a list

    for index, item in enumerate(my_first_list):
        print("The item at index",index, "is",item)
    
    # I can change items in a list

    for index, item in enumerate(my_first_list):
        if item > index:
            my_first_list[index] = index
    
    print("the transformed version of my_first_list is:", my_first_list)
