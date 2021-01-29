let a: []f64 = [1, 2, 3]
let scores: [][]f64 = [
  [95, 83, 76],
  [99, 89, 82]
]

let fact (n: i32): i32 = reduce (*) 1 (1...n)

-- > fact 4i32

-- let main (n: i32) = copy a
-- let main (n: i32): i32 = fact n

let sum_across_rows [n][m] (array: [n][m]f64): [m]f64 =
  let sum = reduce (map2 (+)) (replicate m 0) array
  in map (/ (f64.i64 n)) sum

-- > sum_across_rows scores
