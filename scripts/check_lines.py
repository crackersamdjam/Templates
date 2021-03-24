# https://github.com/wesley-a-leung/Resources/blob/master/Scripts/CheckLines.py
# Thanks Wesley
import argparse
import sys

parser = argparse.ArgumentParser(
	description="Script to check that \\r\\n is not used, "
				"that \\r is not used, "
				"and that indents use \\t instead of four spaces)"
)
parser.add_argument("filenames", metavar="file", type=str, nargs="+")
filenames = parser.parse_args().filenames

good = 0
bad = 0
for filename in filenames:
	print()
	print(filename + ":")
	with open(filename, "rb") as file:
		ok = True
		for curLine, line in enumerate(file, 1):
			if line.endswith(b"\r\n"):
				print(f"line {curLine} ends in \\r\\n")
				ok = False
			if line.endswith(b"\r"):
				print(f"line {curLine} ends in \\r")
				ok = False
			if line.startswith(b"    "):
				print(f"line {curLine} starts with four spaces")
				ok = False
		if ok:
			print("All lines good")
			good += 1
		else:
			bad += 1

print()
print(len(filenames), "file(s) checked")
print(good, "good")
print(bad, "with errors")
sys.exit(bad != 0)