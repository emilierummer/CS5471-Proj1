# RBF

This assignment implements a Random Bloom Filter for checking dangerous IP addresses. For the sake of the assignment, IPs starting with 192.168 are considered dangerous.

The RBF may have false positives but will never have false negatives. This means it may mark a safe address as dangerous but it will never mark a dangerous address as safe.

# Questions

a.  List space cost = 13 * 8 * 10,000 = 1,040,000 bits
    RBF space cost (m1) = (-kn) / ln(1 - P^(1/k)) 
                        = (-8 * 10,000) / ln(1 - 0.0001^(1/8)) 
                        = 210,454.0924
                        = 210,455 bits
    Compression factor (c1) = 1,040,000 / 210,455 = 4.94

b.  RBF space cost (m2) = (-8 * 10,000) / ln(1 - 0.001^(1/8)) 
                        = 146,076.9748
                        = 147,077 bits
    Compression factor (c2) = 1,040,000 / 147,077 = 7.12

## Final Values
m1 = 210,455 bits
c1 = 4.94
m2 = 147,077 bits
c2 = 7.12

# Compilation Steps
1. Run `make all`
2. Run `./RBFGen m output.txt`
3. Run `./IPCheck output.txt ip`
