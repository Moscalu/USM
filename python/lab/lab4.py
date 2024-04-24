# Sarcina 1. Crearea unei liste de cumpărături (shopping list)
# a)	Definiți 3 funcții: una pentru a adăuga denumirea unui produs în listă, una pentru a șterge denumirea unui
#       produs din listă și una pentru afișarea tuturor elementelor din lista curentă.
# b)	Creați un meniu din 4 opțiuni:
#       1.	Afișarea listei curente de produse,
#       2.	Adăugarea produsului în listă, (în baza funcției input()),
#       3.	Ștergerea denumirii produsului din listă,
#       4.	Ieșirea din regimul de editare a listei.

myList = ["just", "for", "example"]

def add_product():
    new_product = str(input())
    myList.append(new_product)

def del_product():
    rem_product = str(input())
    myList.remove(rem_product)

def list_product():
    for x in myList:
        print(x)

# Sarcina 2.
# a) Calculează suma tuturor numerelor de la 1 la 100. Creează o variantă a programului folosind bucle FOR,
#    iar alta variantă folosind bucle WHILE. Afișează rezultatul pe ecran într-un format precum:
#    “Suma numerelor de 1 la 100 este…”.
def task_2_a():
    total_sum = 0
    print("The sum between 1 and 100 using for loop:")
    for x in range(1, 101):
        total_sum += x
    print(total_sum)
    total_sum = 0
    y = 1
    print("The sum between 1 and 100 using while loop:")
    while y != 101:
        total_sum += y
        y += 1
    print(total_sum)

# b) Creează un program care determină dacă un număr (introdus de la tastatură) este par sau impar.
#    Se va afișa în terminal un mesaj similar cu: “Numărul introdus X este par”, în cazul în care numărul este par,
#    iar “Numărul nu este par” în caz contrar.
#    NOTĂ: Un număr este par dacă se poate împărți la 2. Exemplu (2, 4, 8, etc.)
def task_2_b():
    while True:
        try:
            print("Please enter an integer number to calculate if it is even or odd.")
            choice = int((input("")))
            if choice % 2 == 0:
                print("Numărul introdus " + str(choice) + " este par")
                return choice
            else:
                print("Numărul nu este par")
                return choice
        except ValueError:
            print("Invalid input!!!")

# c) Creați în mod iterativ două variabile utilizând următoarele tipuri de date: list, tuple, set sau dicționar.
def task_2_c():
    some_list = ["something", 2, "test", 9]
    tuple_res = []
    dict_res = {}
# Enumerate return value of an list with it's index ex: [(0, 4), (1, 2), (2, 6), (3, 9)]
    for index, element in enumerate(some_list):
        tuple_res.append((element, index))
        dict_res[index] = element
    print("Tuple created using for loop: {}".format(tuple_res))
    print("Dictionary created using for loop: {}".format(dict_res))
    print(dict_res[0])

# d) Scrieți un program care sorteză crescător elementele unui tuplu și calculează suma acestora.
def task_2_d():
    some_tuple = (5, 2, 4, 0, 9)
    print("Elementele tuplului la moment sunt: ", some_tuple)
    sorted_tuple = sorted(some_tuple)
    sum_of_tuple_elements = sum(sorted_tuple)
    print("Tuplul sortat: ", sorted_tuple)
    print("Suma elementelor din tuplul sortat: ", sum_of_tuple_elements)

# e) Creați 2 liste și returnați un set care conține elementele comune între cele două liste.
def task_2_e():
    list1 = [1,2,3,4,5]
    list2 = [4,5,6,7,8]
    common_set = set(list1).intersection(set(list2))
    print(common_set)

# Sarcina 3.
# Scrieți 3 exemple de cod, în care să utilizați câte 2 funcții și metode (la discreția voastră) pe care le veți aplica
# asupra elementelor: listelor, mulțimilor, seturi sau asupra dicționarelor.
def task_3_a():
    my_list = [3, 1, 2, 3, 4, 2, 5, 6, 1]
    unique_sorted_list = sorted(set(my_list))
    print("Eliminarea dublicarilor cu set si sortarea cu sorted: ", unique_sorted_list)

def task_3_b():
    set1 = {1, 2, 3, 4, 5}
    set2 = {4, 5, 6, 7, 8}
    intersection_set = set1.intersection(set2)
    difference_set = set1.difference(set2)
    print("Intersectia la set1 si set2 este: ", intersection_set)
    print("Diferenta dintre set1 si set2 este: ", difference_set)

def task_3_c():
    my_list = [3, 1, 2, 3, 4, 2, 5, 6, 1]
    unique_sorted_list = sorted(set(my_list))
    print("Eliminarea dublicarilor cu set si sortarea cu sorted: ", unique_sorted_list)

# Sarcina 4.
# Analizați următoarele coduri Python și apoi explicați ce rezultate vor fi generate în urma interpretării lor.
# a)
# i = sum = 0
# while i <= 4:
#     sum += i
#     i = i+1
# print(sum)
# 0 + 1 + 2 + 3 + 4 = 10
# b)
# for char in 'PYTHON STRING':
#   if char == ' ':
#       break
#   print(char, end='')
#   if char == 'O':
#       continue
#   print('*', end='')
# PYTHON

def get_user_input():
    while True:
        try:
            choice = int(input("Choose an option...[1 - Print List, 2 - Add Item, 3 - Delete Item,"
                               " 4 - Exit]: "))
            if 1 <= choice <= 4:
                return choice
            else:
                print("Insert a number between 1 and 4 please!")
        except ValueError:
            print("Invalid input!!!")

def get_choosed_task():
    while True:
        try:
            choice = int(input("Choose nr of the task...[1 - Task1, 2 - Task2_A, 3 - Task2_B, 4 - Task2_C,"
                               " 5 - Task2_D, 6 - Task2_E, 7 - Task3, 8 - Task4_a, 9 - Task4_b, 0 - Exit]: "))
            if 0 <= choice <= 9:
                return choice
            else:
                print("Insert a number between 1 and 9 please!")
        except ValueError:
            print("Invalid input!!!")

def get_user_input_t3():
    while True:
        try:
            choice = int(input("Choose an option...[1 - Task3_A, 2 - Task3_B, 3 - Task3_C,"
                               " 4 - Exit]: "))
            if 1 <= choice <= 4:
                return choice
            else:
                print("Insert a number between 1 and 4 please!")
        except ValueError:
            print("Invalid input!!!")

def main():
    while True:
        user_choice = get_choosed_task()

        if user_choice == 1:
            while True:
                user_choice = get_user_input()
                if user_choice == 1:
                    list_product()
                elif user_choice == 2:
                    add_product()
                elif user_choice == 3:
                    print("Write down the product you want to delete:")
                    del_product()
                elif user_choice == 4:
                    print("Return to main menu.")
                    break
        elif user_choice == 2:
            task_2_a()
        elif user_choice == 3:
            task_2_b()
        elif user_choice == 4:
            task_2_c()
        elif user_choice == 5:
            task_2_d()
        elif user_choice == 6:
            task_2_e()
        elif user_choice == 7:
            while True:
                user_choice = get_user_input_t3()
                if user_choice == 1:
                    task_3_a()
                elif user_choice == 2:
                    task_3_b()
                elif user_choice == 3:
                    task_3_c()
                elif user_choice == 4:
                    print("Return to main menu.")
                    break
        elif user_choice == 8:
            print("Not done yet.")
        elif user_choice == 9:
            print("Not done yet.")
        elif user_choice == 0:
            print("Goodbye!")
            break


if __name__ == "__main__":
    main()
