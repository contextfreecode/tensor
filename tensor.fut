let scores: [][]f64 = [
  [95, 83, 76],
  [99, 89, 82]
]

let mean_row [n][m] (array: [n][m]f64): [m]f64 =
  let sum = reduce (map2 (+)) (replicate m 0) array
  in map (/ (f64.i64 n)) sum

-- > mean_row scores
