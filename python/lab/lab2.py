# Afișează un mesaj de salutare pe ecran, folosind funcția print() și input(), solicitând utilizatorului numele său.
# Salvează modificările în fișierul din dosarul creat anterior. Interpretază codul și notează rezultatul.
print("Hello World!")
print("Input your name: ")
name = input()
print(name + " how are you?")

# Definiți 4 variabile folosind denumiri corecte pentru ele în Python. Atribuiți fiecăreia dintre ele,
# în ordine: o valoare întreagă numerică, o valoare reală, o valoare text scurtă, o valoare text care ocupă 3-4 linii.

intreg = int(10)  # Note that is not mandatory to specify the type of the data
real = float(5.7)
text = str("bla")
longtext = str('''In programming, data type is an important concept.
Variables can store data of different types, and different types can do different things.
Python has the following data types built-in by default, in these categories:''')
# print(longtext)

print(f"First variable have type of: {type(text)} and second have: {type(longtext)}")  # 5th task

print(len(longtext))  # 6th Pentru una dintre variabilele text definite, afișați lungimea șirului de text.
print(longtext.upper())  # 7th Convertiți textul stocat în una dintre variabilele text în litere majuscule.

# Testing print(longtext.split('-')[1])
substring = longtext[0:14]  # 8th "Tăiați", folosind operatorul [], și apoi afișați un subșir.
print(substring)

# Analizează următoarele coduri Python și apoi explicăți ce rezultate vor fi obținute la interpretarea lor:

txt = "More results from text..."
# It does cut not by index, and beggining is from next value, 5
substr = txt[4:12]
print(substr)
# " results"
print(substr.strip())
# substr = "results"

txt = "More results from text..."
print(txt.split())
# "More" "results" "from" "text..."
print(type(txt.split()))

age = 36
txt = "My name is Mary, and I am {}"
# .format will replace {} with the value of variable age, also it will return a list
print(txt.format(age))


