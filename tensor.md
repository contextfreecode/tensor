
```futhark
let scores: [][]f64 = [
  [95, 83, 76],
  [99, 89, 82]
]

let mean_col [n][m] (array: [n][m]f64): [n]f64 =
  let sum = map (reduce (+) 0) array
  in map (/ (f64.i64 m)) sum

let mean_row [n][m] (array: [n][m]f64): [m]f64 =
  mean_col (transpose array)
```

```
> mean_col (scores)
```

```
[84.66666666666667f64, 90.0f64]
```


```
> mean_row (scores)
```

```
[97.0f64, 86.0f64, 79.0f64]
```

