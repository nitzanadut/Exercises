#Recieves a camel-case string and adds spaces
camel_to_spaces = lambda string: ''.join([' ' + c if c.isupper() else c for i, c in enumerate(string)])

print(camel_to_spaces('camelCaseIsAwesome'))
print(camel_to_spaces('biss10IsTheBest'))