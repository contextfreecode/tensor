let scores: [][]f64 = [
  [95, 83, 76],
  [99, 89, 82]
]

let mean_col_generic [n][m] 'a
    (add: a -> a -> a)
    (div: a -> a -> a)
    (conv: i64 -> a)
    (zero: a)
    (array: [n][m]a): [n]a =
  let sum = map (reduce add zero) array
  in map (\x -> div x (conv m)) sum

let mean_col_f64 = mean_col_generic (+) (/) f64.i64 0f64

let mean_col [n][m] (array: [n][m]f64): [n]f64 =
  let sum = map (reduce (+) 0) array
  in map (/ (f64.i64 m)) sum

let mean_row [n][m] (array: [n][m]f64): [m]f64 =
  mean_col (transpose array)

-- > mean_col_f64 scores

-- > mean_col scores

-- > mean_row scores
