"""
Using a while loop with an and conditional
"""

if __name__ == "__main__":
    i = 0
    while( (input("Enter your name: ")!= "your name") and i < 10):
        print("Nope sorry try again")
        i = i + 1

    print("Done with program")