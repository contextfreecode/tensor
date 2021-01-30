let scores: [][]f64 = [
  [95, 83, 76],
  [99, 89, 82]
]

let mean_col [n][m] (array: [n][m]f64): [n]f64 =
  let sum = map (reduce (+) 0) array
  in map (/ (f64.i64 m)) sum

let mean_row [n][m] (array: [n][m]f64): [m]f64 =
  mean_col (transpose array)

-- > mean_col scores

-- > mean_row scores
