input = [4, 1, 15, 12, 0, 9, 9, 5, 5, 8, 7, 3, 14, 5, 12, 3]
prevConfig = []
cycles = 0
inputNotInPC = 0
cyclesList = []

while inputNotInPC < 2:
   if input in prevConfig:
      inputNotInPC += 1
      cyclesList.append(cycles)
      cycles = 0
      prevConfig = []
      continue
   else:
      prevConfig.append(list(input))

   m = max(input)
   mpos = 0

   for i, value in enumerate(input):
      if m == value:
         mpos = i
         break
   input[mpos] = 0
   
   while m > 0:
      mpos += 1
      input[mpos % len(input)] += 1
      m -= 1

   cycles += 1

print(cyclesList[-1])