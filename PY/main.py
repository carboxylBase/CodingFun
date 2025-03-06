import sys
# sys.stdin = open('input.txt', 'r')

def solve():
    inputs = list(map(int, sys.stdin.readline().split()))
    # print(inputs)
    idx = 0  

    m = inputs[idx]
    idx += 1
    a = inputs[idx]
    idx += 1
    b = inputs[idx]
    idx += 1
    c = inputs[idx]
    idx += 1

    m1, m2 = m, m
    ans = 0

    if m1 >= a:
        ans += a
        m1 -= a
    else:
        ans += m1
        m1 = 0

    if m2 >= b:
        ans += b
        m2 -= b
    else:
        ans += m2
        m2 = 0

    m1 = m1 + m2
    if m1 >= c:
        ans += c
    else:
        ans += m1

    print(ans)
    return

# 读取测试用例数量
_ = int(sys.stdin.readline())
while _ > 0:
    solve()
    _ -= 1
