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


def get_user_input():
    while True:
        try:
            choice = int(input("Choose an option...[1 - Print List, 2 - Add Item, 3 - Delete Item,"
                               " 4 - Exit, 5 - Task2_A, 6 - Task2_B, 7 - Task2_C]:"))
            if 1 <= choice <= 7:
                return choice
            else:
                print("Insert a number between 1 and 6 please!")
        except ValueError:
            print("Invalid input!!!")


def main():
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
            print("Goodbye!")
            break
        elif user_choice == 5:
            task_2_a()
        elif user_choice == 6:
            task_2_b()
        elif user_choice == 7:
            task_2_c()


if __name__ == "__main__":
    main()

# Sarcina 2.
# a) Calculează suma tuturor numerelor de la 1 la 100. Creează o variantă a programului folosind bucle FOR,
#    iar alta variantă folosind bucle WHILE. Afișează rezultatul pe ecran într-un format precum:
#    “Suma numerelor de 1 la 100 este…”.
# b) Creează un program care determină dacă un număr (introdus de la tastatură) este par sau impar.
#    Se va afișa în terminal un mesaj similar cu: “Numărul introdus X este par”, în cazul în care numărul este par,
#    iar “Numărul nu este par” în caz contrar.
#    NOTĂ: Un număr este par dacă se poate împărți la 2. Exemplu (2, 4, 8, etc.)
# c) Creați în mod iterativ două variabile utilizând următoarele tipuri de date: list, tuple, set sau dicționar.
# d) Scrieți un program care sorteză crescător elementele unui tuplu și calculează suma acestora.
# f) Creați 2 liste și returnați un set care conține elementele comune între cele două liste.
#
# Sarcina 3.
# Scrieți 3 exemple de cod, în care să utilizați câte 2 funcții și metode (la discreția voastră) pe care le veți aplica
# asupra elementelor: listelor, mulțimilor, seturi sau asupra dicționarelor.
#
# Sarcina 4.
# Analizați următoarele coduri Python și apoi explicați ce rezultate vor fi generate în urma interpretării lor.
# a)
# i = sum = 0
# while i <= 4:
#     sum += i
#     i = i+1
# print(sum)
# b)
# for char in 'PYTHON STRING':
#   if char == ' ':
#       break
#   print(char, end='')
#   if char == 'O':
#       continue
#   print('*', end='')
#
