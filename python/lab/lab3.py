# 1b Definiți o listă cu valori în Python. Afișați la ecran prima și cea de-a treia valoare din listă.
# Înlocuiți o valoare din listă cu o alta.

someList = ["apple", "banana", "tomato", "ananas", "mango"]

print(someList[0], someList[2], "\n" + "\n" + "=" * 30 + "\n")

someList[4] = "icecream"
print(someList, "\n" + "\n" + "=" * 30 + "\n")

# 1c Definiți un tuplu cu date în python. Afișați la ecran tipul de date a tuplului (pentru a ne convinge ca așa este),
# iar apoi afișați la ecran prima și ultima valoare a lui.

exampleTuple = ("gradinita", "scoala", "universitate", "lucru")
print(type(exampleTuple))
print(exampleTuple[0], exampleTuple[-1], "\n" + "\n" + "=" * 30 + "\n")

# 1d Definiți o mulțime (set) cu valori în python. Utilizați valori ce se repetă în mulțime.
# Afișați toate elementele mulțimii la ecran.

exampleSet = {"bmw", 5, "audi", "porsche", "audi"}
# Once a set is created, you can't change its items, but you can add new items.
for x in exampleSet:
    print(x)
print("\n" + "=" * 30 + "\n")

# 1e Creați un dicționar în bază de chei textuale și un dicționar în bază de indici numerici.
# Accesați câte un element din fiecare dicționar și afișați-l la ecran.

kubeAccess = {
    "user": "Daniel",
    "group": "root",
    "password": "someInsecurePass"
}

kubeIdentity = {
    "userId": 1079,
    "registerYear": 2019,
    "passExpirationYear": 2025
}

print("Element din kubeAccess:")
print("Utilizator:", kubeAccess["user"])
print("Grup:", kubeAccess["group"])
print("Parola:", kubeAccess["password"])

print("\n" + "=" * 30 + "\n")

print("Element din kubeIdentity:")
print("UserID:", kubeIdentity["userId"])
print("An inregistrare:", kubeIdentity["registerYear"])
print("An expirare parola:", kubeIdentity["passExpirationYear"])

# 1f Transformați un tip de date definit anterior în acest cod, într-un alt tip.
# Explicați și exemplificați pentru ce ar fi necesară această acțiune.

tupleFromList = tuple(someList)
print(tupleFromList)
setFromTuple = set(exampleTuple)
print(setFromTuple)
listFromSet = list(exampleSet)
print(listFromSet)

print("Transformarea tipurilor de date poate fi utilă în diverse situații, cum ar fi gestionarea cerințelor specifice"
      "ale unor funcții sau module, optimizarea performanței sau manipularea datelor în moduri diferite.")

# 2a Creați o listă formată din 3 elemente numerice și o listă formată din trei elemente de tip șir de caractere,
# care să prezinte denumirile a 3 produse. Apoi alcătuiți o informație, utilizând metoda format() și cele 6 valori,
# din cele 2 liste, care să prezinte corect denumirea produsului și prețul acestuia.
# Afișați această informație la ecran.

# Crearea listelor
numericList = [10, 20, 30]
stringList = ["mere", "banane", "ananas"]

# Crearea informației utilizând format()
information = "Produs: {}, Preț: {} MDL"
formattedInfo = information.format(stringList[0], numericList[0])

# Afișarea informației la ecran
print(formattedInfo)

# 2b Solicitați introducerea vârstei (unei valori numerice) de la tastatură, a utilizatorului.
# Transformați-o într-un număr și apoi utilizați această valoare într-un calcul aritmetic.
# Apoi afișați-o la ecran (gen peste 5 ani veți avea X ani), inclusă într-un text. Utilizați operatorul de concatenare,
# dar și operatorii aritmetici.

age_input = input("Introduceți vârsta: ")

age = int(age_input)

future_age = age + 5
print("Peste 5 ani veți avea {} ani.".format(future_age))

# 2c Gândiți-va la o secvență de cod în care să utilizați operatorul ”in” sau ”not in”. Prezentați soluția.

# Verificarea dacă un element se află în listă
check_element = "apple"
if check_element in someList:
    print(f"{check_element} se află în listă.")
else:
    print(f"{check_element} nu se află în listă.")
