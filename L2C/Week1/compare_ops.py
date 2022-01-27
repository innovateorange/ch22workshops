"""
This is a python program to demonstrate comparison operators
"""

if __name__ == "__main__":
    print("1 < 2: ", 1 < 2)
    print("2 > 1:", 2 > 1)
    print("1 == 2", 1 == 2)
    print("1 != 2", 1 != 2)

    print("'hello' == 'cat'", "hello"=="cat")
    print("'hello' != 'cat'", "hello" != "cat")
    my_first_float = 1.1432424534873498312094783289710872304710783412319047887012834701325874325
   
    my_second_float = my_first_float + 1*10**(-24)
    my_third_float = my_second_float - 1*10**(-24)

    print("my_first_float == my_third_float", my_first_float == my_third_float)
    print("my_first_float == my_second_float", my_first_float == my_second_float)
    print("the value of my_first_float is:", my_first_float)
    print("the value of my_second_float is:",my_second_float)
