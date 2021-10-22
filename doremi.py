import re
import sys

melodies = ["ド", "レ", "ミ", "フ", "ソ", "ラ", "シ"]
numbers = [chr(ord('0') + i) for i in range(10)]

def getPreSymbol(output, symbol) :
    return output[0:len(output)-1] + symbol + output[len(output)-1]

with open(sys.argv[1], "r") as fp:
    str = re.sub("ァ", "", fp.read())
    str = re.sub("\n", "", str)

output = ""
for char in list(str):
    if char in melodies:
        output += "%d" % (melodies.index(char) + 1)
    elif char == '〜':
        output = getPreSymbol(output, "-")
    elif char == '♭':
        output = getPreSymbol(output, "$")
    elif char == '*':
        output = getPreSymbol(output, "*")
    elif char == '/':
        output = getPreSymbol(output, "/")
    elif char == '+':
        output = getPreSymbol(output, "+")
    elif char == ' ':
        output += "0"
    elif char in numbers:
        no = ord(char) - ord('0')
        output = output[0:len(output)-1] + chr(ord(output[len(output)-1]) + 7 * no)
    else:
        output += char
print(output + "!")

"""
a 加速 a
r 原則 r
- - 1伸ばし 〜
- $ フラット ♭
- # シャープ #
- / x0.5　/
- * x1.5 *
- 0 空白 ' '
- [0-9] オクターブをあげる
- [a-z]
- +  /*+//ド
"""

# ファ -> 1 -> #♭