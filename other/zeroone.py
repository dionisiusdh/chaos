x = "1111111111111111100000111111111111111111n1111111111111000111111100011111111111111n1111111111110111111111111100111111111111n1111111111101111111111111111011111111111n1111111111011111111111111111001111111111n1111111111111111111111111111101111111111n1111111110011111111111111111110111111111n1111111110011111111111111111101111111111n1111111110011111111111111111111111111111n1111111110111111111111111001101111111111n1111111110111111111110011111101111111111n1111111111111111111111111111011111111111n1111111111110111101111111100111111111111n1111111111111111111111111111111111111111n1111111111111111101110111111111111111111n1111111111111001111101111011111111111111n1111111111111111101110111111111111111111n1111111111111111111110111111111111111111n1111111111111111111111111111111111111111n1111111111110100101111110100111111111111n1111111111101111001111011111011111111111n1111111111011111111111111111011111111111n1111111111011111111111111111011111111111n1111111111100001000000000000111111111111n"
y = ""
for i in range(len(x)):
	if (x[i] == "0"):
		y += "1"
	elif (x[i] == "1"):
		y += "0"
	else:
		y += "n"

output = open("zeroone.txt","w")
output.write(y)