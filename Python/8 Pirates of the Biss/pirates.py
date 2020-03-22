def dejumble(jumbled_word, words):
    "Recieves a jumbled_word and a list of fixed words. The function returns the dejumbled word"

    words_new = [sorted(word) for word in words]
    return [words[i] for i, word in enumerate(words_new) if word == sorted(jumbled_word)]

print(dejumble('ortsp', ['sport', 'parrot', 'ports', 'matey']))