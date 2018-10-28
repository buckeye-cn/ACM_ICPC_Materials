import math 

if __name__ == "__main__":
    n = int(input())
    
    dp = math.log(math.log(2) * n, 2)
    ds = n/math.pow(2, dp)
    
    dp = int(dp)
    ds = int(ds)
    if math.pow(2, dp) * ds < n:
        dp += 1
    if math.pow(2, dp) * ds < n:
        ds += 1
    print(dp + ds)