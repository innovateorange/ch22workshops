"""
A program to demonstrate the function len()

len(x) works for any "list-like" x. Strings are like-lists of characters. We'll see more on lists next week
"""

if __name__ == "__main__":
    
    user_input = input("Enter some random stuff here: ")

    print("The user entered,", len(user_input), "characters")