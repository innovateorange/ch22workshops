"""
A program to demonstrate converting between str's int's and floats

"""

if __name__ == "__main__":
    my_int = 1
    my_str = "hello world!"
    my_float = 3.1415
    #concat_my_str_and_int = my_str + my_int <= this doesn't work!!!

    concat_my_str_and_int = my_str + str(my_int) #use str() to convert my_int to a str

    concat_my_str_and_float = my_str + str(my_float)

    my_new_int = 2
    
    my_new_str = "4304"

    my_new_float = 2.718

    add_new_int_and_new_str = my_new_int + int(my_new_str)

    add_new_float_and_new_str = my_new_float + float(my_new_str)

    print("The value of concat_my_str_and_int is,", concat_my_str_and_int)
    print("The value of concat_my_str_and_float is,", concat_my_str_and_float)
    print("The value of add_new_int_and_new_str is,", add_new_int_and_new_str)
    print("The value of add_new_float_and_new_str is,", add_new_float_and_new_str)