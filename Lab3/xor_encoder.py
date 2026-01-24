key = 0x5A
s = "The quick red fox jumped over the lazy brown dog"

encoded = "".join(f"\\x{ord(c)^key:02x}" for c in s)
print(encoded)
