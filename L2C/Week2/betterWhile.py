"""
This is a program which is designed to emphasize the usage of while loop conditionals
"""

if __name__== "__main__":
    user_name = ""
    while(user_name != "your name"):

        user_name = input("Enter your name: ")
        print("You entered: ", user_name)