
def bsearch(arr, val, low, high):
    mid = (low + high) // 2
    if low == high and arr[mid] != val:
        return -1
    if arr[mid] == val:
        return mid
    elif arr[mid] > val:
        high = mid - 1
        return bsearch(arr, val, low, high)
    else:
        low = mid + 1
        return bsearch(arr, val, low, high)


if __name__ == '__main__':
    arr = [3, 5, 6, 75, 643, 654, 656, 7545]
    val = 76
    low, high = 0, len(arr) - 1
    print(bsearch(arr, val, low, high))
