
fn bsearch(arr: &[i32], val: i32, low: usize, high: usize) -> usize {
    let mid = (low + high) / 2;
    // if low == high & arr[mid] != val {
    //     return -1;
    // }
    if arr[mid] == val {
        return mid;
    }
    else if arr[mid] > val {
        let high = mid - 1;
        return bsearch(arr, val, low, high);
    }
    else {
        let low = mid + 1;
        return bsearch(arr, val, low, high);
    }
}


fn main() {
    let arr = [3, 4, 56, 65, 76, 87, 98, 564, 767, 8786];
    let val = 87;

    let (low, high) = (0, arr.len() - 1);
    let index = bsearch(&arr, val, low, high);
    println!("{}", index);
}
