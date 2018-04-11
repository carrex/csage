proc fb(): bool {.exportc.} = 
  for i in 1..100:
    if i %% 15 == 0:
      echo "fizzbuzz"
    elif i %% 5 == 0:
      echo "buzz"
    elif i %% 3 == 0:
      echo "fizz"
    else:
      echo i
