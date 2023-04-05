# 2-D FenwickTree

class FenwickTree:

    def __init__(self, matrix):
        self.m = len(matrix)
        self.n = len(matrix[0])
        self.ft = [[0 for i in range(self.n + 1)] for i in range(self.m + 1)] # (m+1)*(n+1) matrix full of 0
        for i in range(self.m):
            for j in range(self.n):
                self.update(i+1, j+1, matrix[i][j]) # ft[1,m][1,n]

    def LSB(self, x):
        return x & (-x) # toggling of the last set 1 bit in the binary representation of i
    
    def update(self, x, y, val):
        while x <= self.m:
            y1 = y
            while y1 <= self.n:
                self.ft[x][y1] += val
                y1 += self.LSB(y1)
            x += self.LSB(x)
    
    def summation(self, x, y):
        if x > self.m or y > self.n or x < 1 or y < 1:
            raise IndexError(f"0 < x < {self.m +1}, 0 < y < {self.n + 1}")
        s = 0
        x1 = x
        while x1 > 0:
            y1 = y
            while y1 > 0:
                s += self.ft[x1][y1]
                y1 -= self.LSB(y1)
            x1 -= self.LSB(x1)
        return s

    def Summation(self, x1, y1, x2, y2):
        return (self.summation(x2, y2) - self.summation(x1-1, y2) - self.summation(x2, y1-1) + self.summation(x1-1,x2-1))
    
        
if __name__ == "__main__":
    
    matrix = [[1, 2, 3, 4],
              [5, 3, 8, 1],
              [4, 6, 7, 5]]
    
    f = FenwickTree(matrix)

    print(f.summation(2,3)) # 1+2+3+5+3+8
    print(f.summation(1, 1)) # 1
    print(f.Summation(1,2,2,3)) # 2+3+3+8
